%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% GENERATE FAULT 4 DATA TO DATASET1 (CHANGE ALTITUDE MANEUVER) %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% INTERACTING WITH SIMULINK MODEL FROM A MATLAB SCRIPT
% https://www.youtube.com/watch?v=sF_sjFqNFUk
% FAULT 4: Fixed Valve Position
% PARAMETER AFFECTED: cylinder A position

clear
clc
close all

frequency = 10; % Herts
simulation_time = 100; % Seconds
datapoints = simulation_time * frequency;

writefile = true;
file_name = 'F16_DS3_fault4_fixedposition.csv';
file_name_simulink_model = 'F16_DS3_ALTITUDE_SIMULINK.slx';

flights = 500; % qty of flights to generate data

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DEFAULT VALUES - FAULT 4 - VALVE POSITION %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
choices_amplitude = [10:90];
choices_start = [0:50];
choices_period = [5:90];

fault_time = 0.1; %seconds

for i=1:flights
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% Generating Random Values %%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    % random amplitude =>  +- [5, 55]
    reference = [1 1];
    choose = randi([1 2],1,1);
    amplitude = choices_amplitude(randi([1 length(choices_amplitude)],1,1)) * reference(choose);
    
    % random time_start =>  [20, 80]
    time_start = choices_start(randi([1 length(choices_start)],1,1));
    
    % random period maneuver [5:90]
    time_end = choices_period(randi([1 length(choices_period)],1,1));
    
    %%%%%%%%%%%%%%%%%%
    %% Setup Values %%
    %%%%%%%%%%%%%%%%%%

    % ALTITUDE MANUEVER
    input.altitude.amplitude = amplitude;
    input.altitude.timestart = time_start;
    input.altitude.timeend = time_end;
    
    % FAULT BETA
    input.beta.amplitude = 0;
    input.beta.time = 0;
    
    % FAULT BP
    input.bp.amplitude = 0;
    input.bp.time = 0;
    
    % FAULT C LEAK
    input.c_leak.amplitude = 0;
    input.c_leak.time = 0;
    
    % FAULT VALVE POSITION
    input.valve.fault = 0; %valve position
    input.valve.amplitude = 1; %1 - fault activate
    input.valve.time = fault_time;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% run the simulink model using the 'sim' command %%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sim(file_name_simulink_model);
    
    % extract the data generated by the simulink model
    output_arr = ans.simout_arr;
    
    %%%%%%%%%%%%%%%%%%
    %% save in file %%
    %%%%%%%%%%%%%%%%%%
    if (writefile)
        writematrix(output_arr(1:datapoints,:), file_name, 'WriteMode', 'append');
    end
end


