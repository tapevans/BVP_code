function BVP_plot(SV, MESH, SIM)
%% Organize Variables 
SV = reshape(SV,SIM.nDepVariables,[]);

%% Plot temperature
figure
hold on
plot(MESH.x_vec,SV(SIM.Nf,:),'LineWidth',2,'DisplayName','f')
plot(MESH.x_vec,SV(SIM.Ng,:),'LineWidth',2,'DisplayName','g')
plot(MESH.x_vec,SV(SIM.NT,:),'LineWidth',2,'DisplayName','T')
lgn = legend;
xlabel('\eta')
ylabel('f,g')
xlim([0,MESH.L])
ylim([0,4.5])
%% Plot iteration results


end