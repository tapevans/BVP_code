
#include "Jacobian.h"
#include <iostream>

Jacobian::Jacobian()
{
    absPer = 1e-6;
    relPer = 1e-3;
}


void Jacobian::calculateJacobian(std::vector<double> SV, Mesh* ptrMesh, Residual* ptrRes)
{
    std::cout<<"Calculating the Jacobian\n";
    
    // Initialize Jacobian to a size nVar*jPoints
    totSV = (ptrMesh->jPoints) * (ptrRes->nVariables);

    // Calculate the unperturbed residual
        std::vector<double> residualInitial;
        residualInitial = ptrRes->calculateResidual(SV, ptrMesh);

    // Calculate perturbation value of each SV
        calculatePerturbation(SV);

    // Iterate through all states to calculate the jacobian
     


}

void Jacobian::calculatePerturbation(std::vector<double> SV)
{
    std::cout<<"Calculating pertubations\n";
    // Loop through each variable and calculate the perturbed value
    perV.resize(totSV, 0.0);
    for (int i = 0; i < totSV; i++)
    {
        perV[i] = relPer * SV[i] + absPer;
    }
    
}
