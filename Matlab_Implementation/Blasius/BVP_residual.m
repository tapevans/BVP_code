%% BVP_residual
% This function will be used to calculate the residual of the system at its current state

% Inputs
%   -
% Outputs
%   -

function Res = BVP_residual(SV, MESH, SIM, BC, TOL)
% Blasius Residual function

%% Initialize Variables
SV = reshape(SV,SIM.nDepVariables,[]);
Res = zeros(SIM.nDepVariables, MESH.jPoints); 
% Pr = SIM.Pr;

%% Calculate the residual
% Plate surface
j = 1;
Res(SIM.Nf, j) = SV(SIM.Nf, j) - BC(SIM.Nf, SIM.Nplate);
Res(SIM.Ng, j) = SV(SIM.Ng, j) - BC(SIM.Ng, SIM.Nplate);
% Res(SIM.NT, j) = SV(SIM.NT, j) - BC(SIM.NT, SIM.Nplate);

% Internal Control Volumes
for j = 2:MESH.jPoints-1
    Res(SIM.Nf, j) =                  ( SV(SIM.Nf , j) - SV(SIM.Nf , j-1) ) / ( MESH.x_vec(j) - MESH.x_vec(j-1) )...
                     - SV(SIM.Ng , j);
    Res(SIM.Ng, j) = SV(SIM.Nf , j) * ( SV(SIM.Ng , j) - SV(SIM.Ng , j-1) ) / ( MESH.x_vec(j) - MESH.x_vec(j-1) )...
                    + 2 * ( SV(SIM.Ng , j+1) - 2 * SV(SIM.Ng , j) + SV(SIM.Ng , j-1) ) / ( (MESH.x_vec(j+1) - MESH.x_vec(j)) * (MESH.x_vec(j) - MESH.x_vec(j-1)) );
%     Res(SIM.NT, j) = Pr * SV(SIM.Nf , j) * ( SV(SIM.NT , j+1) - SV(SIM.Ng , j) ) / ( MESH.x_vec(j) - MESH.x_vec(j-1) )...
%                     + 2 * ( SV(SIM.NT , j+1) - 2 * SV(SIM.NT , j) + SV(SIM.NT , j-1) ) / ( (MESH.x_vec(j+1) - MESH.x_vec(j)) * (MESH.x_vec(j) - MESH.x_vec(j-1)) );
end

% Freestream boundary
j = MESH.jPoints;
Res(SIM.Nf, j) = ( SV(SIM.Nf , j) - SV(SIM.Nf , j-1) )/( MESH.x_vec(j) - MESH.x_vec(j-1) )...
                     - SV(SIM.Ng , j);
Res(SIM.Ng, j) = SV(SIM.Ng, j) - BC(SIM.Ng, SIM.Nfreestream);
% Res(SIM.NT, j) = SV(SIM.NT, j) - BC(SIM.NT, SIM.Nfreestream);

%% Reshape the residual matrix to a vector
Res = reshape(Res,[],1);


end