
#include "Residual.h"
#include <iostream>

Residual::Residual()
{
    // Define pointers used in residual calulation function 
    Nf = 0;
    Ng = 1; 
    NT = 2;
    nVariables = 3;
}

MatrixXd Residual::calculateResidual(MatrixXd SV, Mesh* ptrMesh)
{
    // Reshape the incoming vector (Resize is used for dynamic matricies ... I think)
    SV.resize(nVariables, ptrMesh->jPoints);
    
    // Initialize the size of the residual matrix (move this out of the calculation function and into an initialization function or a function that is called by mesh refinement)
    MatrixXd res; ////---------------- Everytime this algorithm runs, will it create a new residual vector or will it replace the memory location of the first one?
    res.resize(nVariables, ptrMesh->jPoints);

    // Calculate the residual at the plate surface boundary ("plate" is specific to the Blasius)
    res(Nf,0) = SV(Nf,0) - BC(Nf,0); 
    res(Ng,0) = SV(Ng,0) - BC(Ng,0); 
    res(NT,0) = SV(NT,0) - BC(NT,0); 

    // Calculate the residual for interior mesh points
    for(int j = 1; j < (ptrMesh->jPoints-1); j++)
    {
        res(Nf,j) = (SV(Nf,j) - SV(Nf,j-1))/ (ptrMesh->x(j) - ptrMesh->x(j-1)) - SV(Ng,j);
        res(Ng,j) = SV(Nf,j) * (SV(Ng,j) - SV(Ng,j-1)) /  (ptrMesh->x(j) - ptrMesh->x(j-1)) 
                    + 2 * (SV(Ng,j - 1) - 2 * SV(Ng,j)  + SV(Ng,j + 1)) / ((ptrMesh->x(j) - ptrMesh->x(j-1))* (ptrMesh->x(j) - ptrMesh->x(j-1)));
        res(NT,j) = Pr * SV(Nf,j) * (SV(NT,j+1) - SV(NT,j))/ (ptrMesh->x(j) - ptrMesh->x(j-1))
                    + 2 * (SV(NT,j - 1) - 2 * SV(NT,j)  + SV(NT,j + 1)) / ((ptrMesh->x(j) - ptrMesh->x(j-1))* (ptrMesh->x(j) - ptrMesh->x(j-1)));
    }

    // Calculate the residual at the outer free flow boundary
    res(Nf,ptrMesh->jPoints-1) = (SV(Nf,ptrMesh->jPoints-1) - SV(Nf,ptrMesh->jPoints-2))/ (ptrMesh->x(ptrMesh->jPoints-1) - ptrMesh->x(ptrMesh->jPoints-2)) 
                         - SV(Ng,ptrMesh->jPoints-1);
    res(Ng,ptrMesh->jPoints-1) =  SV(Ng,ptrMesh->jPoints-1) - BC(Ng,1);
    res(NT,ptrMesh->jPoints-1) =  SV(NT,ptrMesh->jPoints-1) - BC(NT,1);

    // Reshape the residual function to a vector form
    res.resize(nVariables*(ptrMesh->jPoints),1);
    return res;
}
