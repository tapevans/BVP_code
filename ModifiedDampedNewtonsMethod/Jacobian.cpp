
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
    
    // Initialize Jacobian to a size nVar*jPoints
    //jac.resize(ptrRes->totSV,ptrRes->totSV);

    // Calculate the unperturbed residual (This has already been accomplished)
    // residualInitial = ptrRes->calculateResidual(SV, ptrMesh);

    // Calculate perturbation value of each SV
    calculatePerturbation(SV, ptrRes);
    
    // Iterate through all states to calculate the jacobian
    
    //std::cout << "Initial Res:\n" << residualInitial << std::endl;
    for (int i = 0; i < (ptrRes->totSV); i++)
    {
        tempSV     = ptrRes->currentRes;
        tempSV(i) += per(i);
        ptrRes->tempRes = ptrRes->calculateResidual(tempSV, ptrMesh);
        //std::cout << "tempRes is :\n" << ptrRes->tempRes << std::endl;
        jac.col(i) = ((ptrRes->tempRes) - (ptrRes->currentRes))/per(i);
    }
    //std::cout << "Jacobian is:\n" << jac << std::endl;
}


void Jacobian::calculatePerturbation(MatrixXd SV, Residual* ptrRes)
{
    //std::cout<<"\nCalculating pertubations\n";
    
    // Reshape SV to be a column vector
    SV.resize((ptrRes->totSV) , 1);
    

    // Initialize the size of the pertubation value vector
    //per.resize(ptrRes->totSV , 1);

    // Loop through each variable and calculate the perturbation value
    per = relPer*SV;
    for (int i = 0; i < ptrRes->totSV; i++)
    {
        per(i) += absPer; ////--------See if Eigen has a function to add a scalar to all elements of a matrix
    }
}
