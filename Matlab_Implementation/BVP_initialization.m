%% BVP_initialization
% This function will be used to calculate initial properties from the user input

% Inputs
%   -
% Outputs
%   -

function [MESH, SIM, TOL, FLAG] = BVP_initialization(MESH, SIM, TOL, FLAG) %%%% These inputs should just be a pointer?
% Calculate initial discretization
dx = MESH.L/(MESH.jPoints-1);
MESH.x_vec   = 0 : dx : MESH.L; 
MESH.x_vec_m = [0, (MESH.x_vec(2:end) - dx/2)]; %%%%%%%%%%%Fix p and m 
MESH.x_vec_p = [(MESH.x_vec(1:end-1) + dx/2), MESH.L];

% Calculate the number of state variables there are
MESH.nSV = MESH.jPoints * SIM.nDepVariables; 


end