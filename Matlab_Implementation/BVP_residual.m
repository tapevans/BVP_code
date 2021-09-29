%% BVP_residual
% This function will be used to calculate the residual of the system at its current state

% Inputs
%   -
% Outputs
%   -

function Res = BVP_residual(SV, MESH, SIM, BC, TOL)
% Simple Example, Heat Equation

%%%%% Reshape SV once there are more SV
%% Initialize Variables
Res = zeros(MESH.N_CV, 1); %%%%% This might change once there are more SV
k = SIM.k;
q_gen = SIM.q_gen;

%% Calculate the residual

%Left (x=0) Control Volume (BC: Constant Temp)
Res(1, 1) = BC.T_0 - SV(1, 1);

% Internal Control Volumes
for i = 2:MESH.N_CV-1
    Res(i, 1) = ( ( -k * ( SV(i+1) - SV(i)   ) / ( MESH.x_vec(i+1) - MESH.x_vec(i)   ) )...
                 -( -k * ( SV(i)   - SV(i-1) ) / ( MESH.x_vec(i)   - MESH.x_vec(i-1) ) ) )...
                *( -1 / ( MESH.x_vec_p(i)   - MESH.x_vec_m(i) ) )...
               + q_gen;    
end

% Right (x=L) Control Volume (BC: Constant Temp)
Res(MESH.N_CV, 1) = BC.T_L - SV(MESH.N_CV, 1);

end