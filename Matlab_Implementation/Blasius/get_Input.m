%% get_Input
% This is a file that contains the users input

function [MESH, SIM, TOL, BC, FLAG] = get_Input()
%% Domain Parameters
MESH.jPoints = 20; % Number of control volumes
MESH.L       = 6; % Length of domain in x-dir %%%% For the blasius, the algorithm will solve if the length is 7 or less
%% Dependent Offsets
SIM.Nf = 1;
SIM.Ng = 2;
% SIM.NT = 3;
% SIM.nDepVariables = 3;
SIM.nDepVariables = 2;

SIM.Nplate = 1;
SIM.Nfreestream = 2;
nBoundaries = 2;
%% BC
BC = zeros(SIM.nDepVariables , nBoundaries);
BC(SIM.Nf,SIM.Nplate) = 0;
BC(SIM.Ng,SIM.Nplate) = 0;
% BC(SIM.NT,SIM.Nplate) = 0;
BC(SIM.Nf,SIM.Nfreestream) = NaN;
BC(SIM.Ng,SIM.Nfreestream) = 1;
% BC(SIM.NT,SIM.Nfreestream) = 1;

%% Properties
% SIM.k = 20;
% SIM.q_gen = 100000;
% SIM.q_gen = 0;
% SIM.Pr = 0.71;

%% Tolerance Parameters
TOL.A = 1e-6; % Absolute tolerance for MDNM
TOL.R = 1e-3; % Relative tolerance for MDNM
TOL.a = 1e-6; % Absolute tolerance for pertebation
TOL.r = 1e-3; % Relative tolerance for pertebation
TOL.delta = 0.2; 
TOL.gamma = 0.5; %%%%Not implemented yet

%% Residual Function Name
SIM.Res_name = 'BVP_residual'; % File name associated with the residual function %%%%%%Not really used in Matlab so maybe won't be needed

%% Initial Guess
f_guess = linspace(0,5,MESH.jPoints);
g_guess = linspace(0,1,MESH.jPoints);
% T_guess = linspace(0,1,MESH.jPoints);
% SIM.SV_0 = [f_guess;g_guess;T_guess];
SIM.SV_0 = [f_guess;g_guess];
SIM.SV_0 = reshape(SIM.SV_0,[],1);


%% Limits on Variables


%% Save Results File Location


%% Flags
FLAG.Do_Mesh_Refinement = 0; % 1 if the algorithm should perform mesh refinement

end