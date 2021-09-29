%% Jacobian 
% This function will be used to return the Jacobian of any system
% Inputs
%   -
% Outputs
%   -

function Jac = Jacobian(SV, MESH, SIM, BC, TOL)
% Calculate residual without perturbation
F_init = BVP_residual(SV, MESH, SIM, BC, TOL);
Jac    = zeros(MESH.N_SV, MESH.N_SV);
% Perturbate each SV and calculate its dF/dSV = ( F(SV+p) - F(SV) ) / p
% where p is the perturbation of one of the variables
% and F(SV) = F_init

for i = 1:MESH.N_SV %%%%%Change this to N_SV later
    p    = zeros(MESH.N_CV,1);
    p(i) = TOL.r * SV(i) + TOL.a ;
    SV_p = SV + p;
    F_j  = BVP_residual(SV_p, MESH, SIM, BC, TOL);
    
    Jac(:,i) = ( F_j - F_init ) / p(i);
end

end