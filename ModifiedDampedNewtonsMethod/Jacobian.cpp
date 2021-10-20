
#include "Jacobian.h"
#include <iostream>

Jacobian::Jacobian()
{
    absPer = 1e-6;
    relPer = 1e-3;
}


void Jacobian::calculateJacobian(MatrixXd SV, Mesh* ptrMesh, Residual* ptrRes)
{
    std::cout<<"Calculating the Jacobian\n";
    
    // Initialize Jacobian to a size nVar*jPoints
    totSV = (ptrMesh->jPoints) * (ptrRes->nVariables);

    // Calculate the unperturbed residual
        MatrixXd residualInitial;
        residualInitial = ptrRes->calculateResidual(SV, ptrMesh);

    // Calculate perturbation value of each SV
        calculatePerturbation(SV);

    // Iterate through all states to calculate the jacobian
    MatrixXd tempSV;
    MatrixXd tempRes;
    jac.resize(totSV,totSV);
    //std::cout << "Initial Res:\n" << residualInitial << std::endl;
    for (int i = 0; i < totSV; i++)
    {
        tempSV = residualInitial;
        tempSV(i) += per(i);

        tempRes = ptrRes->calculateResidual(tempSV, ptrMesh);
        //std::cout << "tempRes is :\n" << tempRes << std::endl;
        jac.col(i) = (tempRes - residualInitial)/per(i);
    }
    //std::cout << "Jacobian is:\n" << jac << std::endl;
}


void Jacobian::calculatePerturbation(MatrixXd SV)
{
    //std::cout<<"Calculating pertubations\n";
    // Loop through each variable and calculate the perturbed value
    // Resize SV
    SV.resize(totSV , 1);

    per.resize(totSV , 1);
    per = relPer*SV;
    for (int i = 0; i < totSV; i++)
    {
        per(i) += absPer;
    }
}
