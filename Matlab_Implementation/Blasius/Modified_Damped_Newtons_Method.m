%% Modified Damped Newtons Method 
% This function will be used to perform the Modified Damped Newtons Method

% Inputs
%   - SV_0: vector, Initial solution vector guess
%   - MESH: struct, Contains mesh properties
% Outputs
%   - SV:   vector, Final solution vector
%   - MESH: struct, Contains mesh properties
%   - SIM:  struct, Contains solution process properties

% Procedure %%%%%%Fix this
% - Find new SV^(n+1)
%   - Look ahead to accept or deny SV^(n+1)
% - Check if Delta SV meets tolerance
% - Check if mesh needs to be refined
        
function [SV, MESH, SIM] = Modified_Damped_Newtons_Method(SV_0, MESH, SIM, BC, TOL, FLAG)
%% Initialize Algorithm
found_soln = false;
mesh_is_refined = false;
num_Jacobian = 0;
SV_current = SV_0;
num_iterations = 0;
needNewJacobian = false;

while ~mesh_is_refined
    %% Start Iterations
    while ~found_soln
        num_iterations = num_iterations + 1;
        %% Solve for the correction vector
        % deltaSV^m = J(SV^m)^-1 F(SV^m)
        
        % Calculate the Jacobian
        
        if num_iterations == 1
            % Calculate Jacobian
            Jac = Jacobian(SV_current, MESH, SIM, BC, TOL);
%             plot_SV = reshape(SV_current,2,[]);
%             figure(1)
%             hold on
%             plot(plot_SV(1,:),MESH.x_vec);
%             
%             figure(2)
%             hold on
%             plot(plot_SV(2,:),MESH.x_vec);
        end
        
        if ( num_Jacobian < 20 )
            % Keep current Jacobian
        else
            % Calculate a new Jacobian
            Jac = Jacobian(SV_current, MESH, SIM, BC, TOL);
            num_Jacobian = 0;
        end
        % Calculate F(SV) <-- F() = Res()
        F_current = BVP_residual(SV_current, MESH, SIM, BC, TOL);
        
        % Calculate correction vector
%         del_SV_current = Jac\(F_current);
        del_SV_current = Jac\(-F_current);
        
        
        %% Solve for the next iteration
        % SV^m+1 = SV^m - lambda^m * deltaSV^m
        
        lambda = 1; %%%%maybe user can add restriction to this in input file
        SV_next = 0;
        del_SV_next = 0;
        found_SV_next = false;
        while ~found_SV_next
            %% Calculate SV^m+1
%             SV_temp = SV_current - lambda * del_SV_current;
            SV_temp = SV_current + lambda * del_SV_current;
            
            %% Check if lambda meets tol
            %%%%%%%%%%%% 1) Not checking if in soln space right now
            
            %  2) Check Look ahead criteria
            %  - Calculate deltaSV^m+1
            F_temp = BVP_residual(SV_temp, MESH, SIM, BC, TOL);
%             del_SV_temp = Jac\(F_temp);
            del_SV_temp = Jac\(-F_temp);
            
            norm_is_smaller = ( norm(del_SV_temp) < norm(del_SV_current) );
            if norm_is_smaller
                % SV^m = SV^m+1
                SV_next = SV_temp;
                del_SV_next = del_SV_temp;
                found_SV_next = true;
            else
                % Try halving lambda
                lambda = lambda * 0.5;
                if lambda < 1e-10
                    Jac = Jacobian(SV_current, MESH, SIM, BC, TOL);
                    lambda = 1/2;
                end
            end
        end
        found_SV_next = false;
%         %% Testing plotting
%         plot_SV = reshape(SV_next,2,[]);
%         figure(1)
%         hold on
%         plot(plot_SV(1,:),MESH.x_vec);
% 
%         figure(2)
%         hold on
%         plot(plot_SV(2,:),MESH.x_vec);
        
        %% Check if the new SV meets the iteration tolerances
        within_tol = ( norm(del_SV_next) < max( TOL.A, TOL.R*norm(SV_next) ) );
        
        if within_tol
            % Solution is found
            found_soln = true;
            SV = SV_next;
        else
            % Start another iteration with the new SV
            SV_current = SV_next;
            num_Jacobian = num_Jacobian + 1;
        end
    end
%% Check if the mesh is refined
if FLAG.Do_Mesh_Refinement
    % check the mesh
    [MESH, SV, SIM, TOL, FLAG,mesh_is_refined] = meshRefinement(MESH, SV, SIM, TOL, FLAG);
else
    mesh_is_refined = true;
end
    
end
end