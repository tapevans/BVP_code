
#include "Residual.h"
#include <iostream>

Residual::Residual()
{
    Nf = 0;
    Ng = 1; 
    NT = 2;
    nVariables = 3;
}

//void BVP_Residual::calculateResidual(std::vector<std::vector<double> > SV, int jPoints, std::vector<double> x)
MatrixXd Residual::calculateResidual(MatrixXd SV, Mesh* ptrMesh)
{
    //std::cout<<"\t\t\tCalculating residual inside class residual\n";

    // Reshape the incoming vector
    SV.resize(nVariables, ptrMesh->jPoints);
    
    //Create Residual matrix
    MatrixXd res;
    res.resize(nVariables, ptrMesh->jPoints);

    // Plate surface boundary
    res(Nf,0) = SV(Nf,0) - BC(Nf,0); 
    res(Ng,0) = SV(Ng,0) - BC(Ng,0); 
    res(NT,0) = SV(NT,0) - BC(NT,0); 

    // Interior 
    // x_vector is not defined in this class. How can it call reference to the mesh class??*****
    for(int j = 1; j < (ptrMesh->jPoints-1); j++)
    {
        res(Nf,j) = (SV(Nf,j) - SV(Nf,j-1))/ (ptrMesh->x(j) - ptrMesh->x(j-1)) - SV(Ng,j);
        res(Ng,j) = SV(Nf,j) * (SV(Ng,j) - SV(Ng,j-1)) /  (ptrMesh->x(j) - ptrMesh->x(j-1)) 
                    + 2 * (SV(Ng,j - 1) - 2 * SV(Ng,j)  + SV(Ng,j + 1)) / ((ptrMesh->x(j) - ptrMesh->x(j-1))* (ptrMesh->x(j) - ptrMesh->x(j-1)));
        res(NT,j) = Pr * SV(Nf,j) * (SV(NT,j+1) - SV(NT,j))/ (ptrMesh->x(j) - ptrMesh->x(j-1))
                    + 2 * (SV(NT,j - 1) - 2 * SV(NT,j)  + SV(NT,j + 1)) / ((ptrMesh->x(j) - ptrMesh->x(j-1))* (ptrMesh->x(j) - ptrMesh->x(j-1)));
    }

    // Outer free flow boundary
    res(Nf,ptrMesh->jPoints-1) = (SV(Nf,ptrMesh->jPoints-1) - SV(Nf,ptrMesh->jPoints-2))/ (ptrMesh->x(ptrMesh->jPoints-1) - ptrMesh->x(ptrMesh->jPoints-2)) 
                         - SV(Ng,ptrMesh->jPoints-1);
    res(Ng,ptrMesh->jPoints-1) =  SV(Ng,ptrMesh->jPoints-1) - BC(Ng,1);
    res(NT,ptrMesh->jPoints-1) =  SV(NT,ptrMesh->jPoints-1) - BC(NT,1);

    // Reshape the residual function to a vector form
    res.resize(nVariables*(ptrMesh->jPoints),1);
    return res;
}

/*
std::vector<double> Residual::matrix2Vector(std::vector<std::vector<double> > mat , int jPoints)
{
    std::vector<double> vec;
    vec.resize(jPoints*nVariables, 0.0);
    for(int j = 0; j<jPoints; j++)
    {
        for(int n = 0; n<nVariables; n++)
        {
            vec(j*nVariables +n) = mat(n,j);
        }
    }
    return vec;
}

std::vector<std::vector<double> > Residual::vector2Matrix(std::vector<double> vec, int jPoints)
{
    std::vector<std::vector<double> > mat;
    mat.resize(nVariables, std::vector<double>(jPoints, 0.0));
    int j,n;
    for(int k = 0; k < nVariables*jPoints; k++)
    {
        j = (k - k%nVariables)/nVariables;
        n = k%nVariables;
        mat(n,j) = vec(k);
    }
    return mat;
}
*/
