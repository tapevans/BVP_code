%% BVP_main
% This function will take inputs for a Boundary Value Problem (BVP) and
% perform a Modified Damping Newton's Algorithm to solve it. 

clear all; clc; close all;
%% Get User Inputs
[MESH, SIM, TOL, BC, FLAG] = get_Input();

%% Perform Initial calculations
[MESH, SIM, TOL, FLAG] = BVP_initialization(MESH, SIM, TOL, FLAG);

%% Solve Directly (for testing purposes)
SV_dir = solveDirectly(MESH, SIM, BC, TOL, FLAG);

%% Solve Problem
SV_0 = SIM.SV_0;
[SV, MESH, SIM] = Modified_Damped_Newtons_Method(SV_0, MESH, SIM, BC, TOL, FLAG);

%% Save Results


%% Plot Solution
BVP_plot(SV, MESH, SIM, SV_dir); %%%%%% These inputs should just point to the file where the results are saved
