function BVP_plot(SV, MESH, SIM, SV_dir)
%% Organize Variables %%%%%maybe this is done in the save function

%% Plot temperature
figure
hold on
plot(MESH.x_vec,SV,'LineWidth',2)
% plot(MESH.x_vec,SV_dir,'o','LineWidth',2)

xlabel('Domain')
ylabel('Temperature (K)')

%% Plot iteration results


end