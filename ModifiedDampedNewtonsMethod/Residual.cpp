
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

void Residual::totalSVCalc(Mesh* ptrMesh){
    totSV = (ptrMesh->jPoints) * (nVariables);
}


MatrixXd Residual::calculateResidual(MatrixXd SV, Mesh* ptrMesh)
{
    // Reshape the incoming vector (Resize is used for dynamic matricies ... I think)
    //std::cout<<"\n This is the SV before calcRes resize:\n" << SV << std::endl;
    SV.resize(nVariables, ptrMesh->jPoints);
    
    // Reshape the residual matrix
    tempRes.resize(nVariables, ptrMesh->jPoints);

    // Calculate the residual at the plate surface boundary ("plate" is specific to the Blasius)
    tempRes(Nf,0) = SV(Nf,0) - BC(Nf,0); 
    tempRes(Ng,0) = SV(Ng,0) - BC(Ng,0); 
    tempRes(NT,0) = SV(NT,0) - BC(NT,0); 

    // Calculate the residual for interior mesh points
    for(int j = 1; j < (ptrMesh->jPoints-1); j++)
    {
        tempRes(Nf,j) = (SV(Nf,j) - SV(Nf,j-1))/ (ptrMesh->x(j) - ptrMesh->x(j-1)) - SV(Ng,j);
        tempRes(Ng,j) = SV(Nf,j) * (SV(Ng,j) - SV(Ng,j-1)) /  (ptrMesh->x(j) - ptrMesh->x(j-1)) 
                    + 2 * (SV(Ng,j - 1) - 2 * SV(Ng,j)  + SV(Ng,j + 1)) / ((ptrMesh->x(j) - ptrMesh->x(j-1))* (ptrMesh->x(j) - ptrMesh->x(j-1)));
        tempRes(NT,j) = Pr * SV(Nf,j) * (SV(NT,j+1) - SV(NT,j))/ (ptrMesh->x(j) - ptrMesh->x(j-1))
                    + 2 * (SV(NT,j - 1) - 2 * SV(NT,j)  + SV(NT,j + 1)) / ((ptrMesh->x(j) - ptrMesh->x(j-1))* (ptrMesh->x(j) - ptrMesh->x(j-1)));
    }

    // Calculate the residual at the outer free flow boundary
    tempRes(Nf,ptrMesh->jPoints-1) = (SV(Nf,ptrMesh->jPoints-1) - SV(Nf,ptrMesh->jPoints-2))/ (ptrMesh->x(ptrMesh->jPoints-1) - ptrMesh->x(ptrMesh->jPoints-2)) 
                         - SV(Ng,ptrMesh->jPoints-1);
    tempRes(Ng,ptrMesh->jPoints-1) =  SV(Ng,ptrMesh->jPoints-1) - BC(Ng,1);
    tempRes(NT,ptrMesh->jPoints-1) =  SV(NT,ptrMesh->jPoints-1) - BC(NT,1);

    // Reshape the residual function to a vector form
    tempRes.resize(nVariables*(ptrMesh->jPoints),1);
    SV.resize(nVariables*(ptrMesh->jPoints),1);
    return tempRes;
}
