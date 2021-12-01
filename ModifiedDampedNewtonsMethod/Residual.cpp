
#include "Residual.h"
#include <iostream>

Residual::Residual()
{
    // Define index reference to be used in residual calulation function 
    Nf = 0;
    Ng = 1; 
    NT = 2;
    nVariables = 3;
}

MatrixXd Residual::calculateResidual(MatrixXd SV, MatrixXd* ptrMeshX, int* ptrjPoints)
{
    // Reshape the incoming vector
    SV.resize(nVariables, *ptrjPoints);
    
    // Reshape the residual matrix
    tempRes.resize(nVariables, *ptrjPoints);

    // Calculate the residual at the plate surface boundary ("plate" is specific to the Blasius)
    tempRes(Nf,0) = SV(Nf,0) - BC(Nf,0); 
    tempRes(Ng,0) = SV(Ng,0) - BC(Ng,0); 
    tempRes(NT,0) = SV(NT,0) - BC(NT,0); 

    // Calculate the residual for interior mesh points
    for(int j = 1; j < (*ptrjPoints-1); j++)
    {
        tempRes(Nf,j) = (SV(Nf,j) - SV(Nf,j-1))/ ((*ptrMeshX)(j) - (*ptrMeshX)(j-1)) - SV(Ng,j);
        tempRes(Ng,j) = SV(Nf,j) * (SV(Ng,j) - SV(Ng,j-1)) /  ((*ptrMeshX)(j) - (*ptrMeshX)(j-1)) 
                    + 2 * (SV(Ng,j - 1) - 2 * SV(Ng,j)  + SV(Ng,j + 1)) / (((*ptrMeshX)(j) - (*ptrMeshX)(j-1))* ((*ptrMeshX)(j) - (*ptrMeshX)(j-1)));
        tempRes(NT,j) = Pr * SV(Nf,j) * (SV(NT,j+1) - SV(NT,j))/ ((*ptrMeshX)(j) - (*ptrMeshX)(j-1))
                    + 2 * (SV(NT,j - 1) - 2 * SV(NT,j)  + SV(NT,j + 1)) / (((*ptrMeshX)(j) - (*ptrMeshX)(j-1))* ((*ptrMeshX)(j) - (*ptrMeshX)(j-1)));
    }

    // Calculate the residual at the outer free flow boundary
    tempRes(Nf,*ptrjPoints-1) = (SV(Nf,*ptrjPoints-1) - SV(Nf,*ptrjPoints-2))/ ((*ptrMeshX)(*ptrjPoints-1) - (*ptrMeshX)(*ptrjPoints-2)) 
                         - SV(Ng,*ptrjPoints-1);
    tempRes(Ng,*ptrjPoints-1) =  SV(Ng,*ptrjPoints-1) - BC(Ng,1);
    tempRes(NT,*ptrjPoints-1) =  SV(NT,*ptrjPoints-1) - BC(NT,1);

    // Reshape the residual function to a vector form
    tempRes.resize(nVariables*(*ptrjPoints),1); // Not using the variable called totSV. Might be good not to use that so it's one less thing to change when refining the mesh
    SV.resize(nVariables*(*ptrjPoints),1); // Not using the variable called totSV. Might be good not to use that so it's one less thing to change when refining the mesh
    return tempRes;
}