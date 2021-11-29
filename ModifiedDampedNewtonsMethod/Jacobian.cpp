
#include "Jacobian.h"
#include <iostream>

Jacobian::Jacobian()
{   
    // Set default pertubation coefficients
    absPer = 1e-6;
    relPer = 1e-3;

    // Initialize the counter
    jacobianCounter = 0;
}

void Jacobian::calculateJacobian(MatrixXd SV, Mesh* ptrMesh, Residual* ptrRes)
{
    std::cout<<"Calculating the Jacobian\n";
    
    jacobianCounter = 0;

    // Calculate perturbation value of each SV
    calculatePerturbation(SV, ptrRes);
                ofstream debugFilestream;
                debugFilestream.open("debugLog.txt", ios::out | ios::app); 
                debugFilestream << "Perturbation Vector = \n" << per << "\n";
                debugFilestream.close();

    // Iterate through all states to calculate the jacobian
    for (int i = 0; i < (ptrRes->totSV); i++)
    {
        tempSV     = SV;
        tempSV(i) += per(i);
        ptrRes->tempRes = ptrRes->calculateResidual(tempSV, ptrMesh);
        jac.col(i) = ((ptrRes->tempRes) - (ptrRes->currentRes))/per(i);

        debugFilestream.open("debugLog.txt", ios::out | ios::app); 
        debugFilestream << "ith colm = " << i+1 << "\n";
        //debugFilestream << "currentRes = \n" << tempSV << "\n";
        debugFilestream << "tempSV(i) = \n" << tempSV << "\n";
        debugFilestream << "Res(SV_i) = \n" << ptrRes->tempRes << "\n";
        debugFilestream << "Jac(:,i) = \n" << jac.col(i) << "\n";
        debugFilestream.close();
    }
}

void Jacobian::calculatePerturbation(MatrixXd SV, Residual* ptrRes)
{
    // Reshape SV to be a column vector
    SV.resize((ptrRes->totSV) , 1);
    
    // Loop through each variable and calculate the perturbation value
    per = relPer*SV;
    for (int i = 0; i < ptrRes->totSV; i++)
    {
        per(i) += absPer; ////--------See if Eigen has a function to add a scalar to all elements of a matrix
    }
}
