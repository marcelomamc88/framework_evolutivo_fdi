%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% GENERATE FAULT 4 DATA TO DATASET2 (CHANGE ANGLE AND TORQUE ON THE SURFACE MANEUVER) %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
file_name = 'F16_DS2_fault4_fixedposition.csv';

flights = 150; % qty of flights to generate data

m = [-1, 1];
choices_refangle_basevalue = [-5:.1:5]/10.0;  
choices_refangle_amplitude = [.01:.04:.5];
choices_ts_basevalue = [5:.1:10];   
choices_ts_amplitude = [1:.1:5];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DEFAULT VALUES - NO FAULT %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fault_time = 0; %seconds

for i=1:flights
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% Generating Random Values %%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    % random RefAngle - Base Value => [-.5, .5]      
    refangle_basevalue = choices_refangle_basevalue(randi([1 length(choices_refangle_basevalue)],1,1));

    % random RefAngle - Amplitude => +-[.01, .5]    
    refangle_amplitude = choices_refangle_amplitude(randi([1 length(choices_refangle_amplitude)],1,1))  * m(randi([1 2],1,1));

    % random Torque on the Surface - Base Value => [5,10]    
    torque_basevalue = choices_ts_basevalue(randi([1 length(choices_ts_basevalue)],1,1));

    % random Torque on the Surface - Amplitude => +-[1,5]
    torque_amplitude = choices_ts_amplitude(randi([1 length(choices_ts_amplitude)],1,1)) * m(randi([1 2],1,1));

    % Time Start Maneuver => [5,50]
    timestart_maneuver = randi([5 50],1,1);

    % Time End Maneuver => start + [10,50]
    timeend_maneuver = timestart_maneuver + randi([10 50],1,1);
    
    %%%%%%%%%%%%%%%%%%
    %% Setup Values %%
    %%%%%%%%%%%%%%%%%%

    % SURFACE ANGLE MANUEVER
    input.refangle.basevalue = refangle_basevalue;
    input.refangle.amplitude = refangle_amplitude;
    input.refangle.timestart = timestart_maneuver;
    input.refangle.timeend  = timeend_maneuver;

    % TORQUE ON THE SURFACE MANEUVER
    input.torque.basevalue = torque_basevalue;
    input.torque.amplitude = torque_amplitude;    
    input.torque.timestart = timestart_maneuver;
    input.torque.timeend  = timeend_maneuver;
    
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
    sim('F16_DS2_W_TS_SIMULINK.slx');
    
    % extract the data generated by the simulink model
    output_arr = ans.simout_arr;
    
    %%%%%%%%%%%%%%%%%%
    %% save in file %%
    %%%%%%%%%%%%%%%%%%
    if (writefile)
        writematrix(output_arr(1:datapoints,:), file_name, 'WriteMode', 'append');
    end
end


