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
Res = zeros(MESH.nSV, 1); %%%%% This might change once there are more SV
k = SIM.k;
q_gen = SIM.q_gen;

%% Calculate the residual

%Left (x=0) Control Volume (BC: Constant Temp)
Res(1, 1) = BC.T_0 - SV(1, 1);

% Internal Control Volumes
for j = 2:MESH.jPoints-1
    Res(j, 1) = ( ( -k * ( SV(j+1) - SV(j)   ) / ( MESH.x_vec(j+1) - MESH.x_vec(j)   ) )...
                 -( -k * ( SV(j)   - SV(j-1) ) / ( MESH.x_vec(j)   - MESH.x_vec(j-1) ) ) )...
                *( -1 / ( MESH.x_vec_p(j)   - MESH.x_vec_m(j) ) )...
               + q_gen;    
end

% Right (x=L) Control Volume (BC: Constant Temp)
Res(MESH.jPoints, 1) = BC.T_L - SV(MESH.jPoints, 1);

end