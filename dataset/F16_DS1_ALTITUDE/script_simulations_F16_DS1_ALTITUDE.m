% INTERACT SIMULINK MODEL FROM A MATLAB SCRIPT
%https://www.youtube.com/watch?v=sF_sjFqNFUk

clear
clc
close all

%% DEFAULT VALUES - NO FAULT

% ALTITUDE MANUEVER
input.altitude.amplitude = 0;
input.altitude.timestart = 0;
input.altitude.timeend = 0;

% FAULT BETA
input.beta.amplitude = 0;
input.beta.time = 0;

% FAULT BP
input.bp.amplitude = 0;
input.bp.time = 20;

% FAULT C LEAK
input.c_leak.amplitude = 0;
input.c_leak.time = 0;

% FAULT VALVE POSITION
input.valve.fault = 0;
input.valve.amplitude = 0;
input.valve.time = 0;

sim('F16_DS1_ALTITUDE_SIMULINK.slx')