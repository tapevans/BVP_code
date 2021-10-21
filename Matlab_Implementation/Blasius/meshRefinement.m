%% meshRefinement
% This function will be used to return the Jacobian of any system
% Inputs
%   -
% Outputs
%   -

% Mesh refinement needs to resolve
% 1) Gradients
% 2) Curvature
function [MESH, SV_new, SIM, TOL, FLAG, mesh_is_refined] = meshRefinement(MESH, SV_old, SIM, TOL, FLAG)
% %% Reshape SV
% 
% %% Check Refinement Conditions
% for i = 1:SIM.nDepVariables
%     gradientBound = TOL.delta*(max(SV_old) - min(SV_old));
%     %         curvatureBound =
%     for j = 1:MESH.jPoints-1
%         %             SV(i,j) - SV(i,j+1) %This is how I would envision it with
%         %             more dependent variables
%         needsRefining(j) = (abs(SV_old(j) - SV_old(j+1)) > gradientBound);
%         %%%Also need to check the curvature requirement but I'm not doing that at the moment
%     end
% end
% 
% %% Place new jPoints
% % If the jth element in needRefining is 1, then a new node needs to be
% % placed between x(j) and x(j+1)
% count = 0;
% sumRef = sum(needsRefining);
% x_new = zeros(MESH.jPoints+sumRef,1);
% SV_new = zeros(MESH.jPoints+sumRef,1);
% 
% x_new(1) = MESH.x_vec(1);
% for j = 2:MESH.jPoints -1
%    if needsRefining(j-1) == 1
%       x_new(j+count) = ( MESH.x_vec(j-1) + MESH.x_vec(j) ) * 0.5;
%       x_new(j+1+count) = MESH.x_vec(j);%%%%Does this work?
%       
%       SV_new(j+count) = ( SV_old(j-1) + SV_old(j) ) * 0.5;
%       SV_new(j+1+count) = SV_old(j);%%%%Does this work?
%       
%       count = count + 1;
%    else
%        x_new(j+count) = MESH.x_vec(j);
%        
%        SV_new(j+count) = SV_old(j);
%    end
% end
% x_new(MESH.jPoints+count) = MESH.x_vec(MESH.jPoints);
% SV_new(MESH.jPoints+count) = SV_old(MESH.jPoints);
% 
% MESH.x_vec = x_new;
% 
% if sumRef == 0
%     mesh_is_refined = true;
% else
%     mesh_is_refined = false;
% end

end