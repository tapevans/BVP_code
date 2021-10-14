
#include "Residual.h"
#include <iostream>

Residual::Residual()
{
    Nf = 0;
    Ng = 1; 
    NT = 2;
    nVariables = 3;
}

//void BVP_Residual::calculateResidual(std::vector<std::vector<double> > depM, int jPoints, std::vector<double> x)
std::vector<double> Residual::calculateResidual(std::vector<double> depV, Mesh* ptrMesh)
{
    std::cout<<"\t\t\tCalculating residual inside class residual\n";

    // Reshape the incoming vector
    //***********depV -> depM

    resM.resize(nVariables, std::vector<double>(ptrMesh->jPoints, 0.0));

    // Plate surface boundary
    resM[Nf][0] = depM[Nf][0] - BC[Nf][0]; 
    resM[Ng][0] = depM[Ng][0] - BC[Ng][0]; 
    resM[NT][0] = depM[NT][0] - BC[NT][0]; 

    // Interior 
    // x_vector is not defined in this class. How can it call reference to the mesh class??*****
    for(int j = 1; j < (ptrMesh->jPoints-1); j++)
    {
        resM[Nf][j] = (depM[Nf][j] - depM[Nf][j-1])/ (ptrMesh->x[j] - ptrMesh->x[j-1]) - depM[Ng][j];
        resM[Ng][j] = depM[Nf][j] * (depM[Ng][j] - depM[Ng][j-1]) /  (ptrMesh->x[j] - ptrMesh->x[j-1]) 
                    + 2 * (depM[Ng][j - 1] - 2 * depM[Ng][j]  + depM[Ng][j + 1]) / ((ptrMesh->x[j] - ptrMesh->x[j-1])* (ptrMesh->x[j] - ptrMesh->x[j-1]));
        resM[NT][j] = Pr * depM[Nf][j] * (depM[NT][j+1] - depM[NT][j])/ (ptrMesh->x[j] - ptrMesh->x[j-1])
                    + 2 * (depM[NT][j - 1] - 2 * depM[NT][j]  + depM[NT][j + 1]) / ((ptrMesh->x[j] - ptrMesh->x[j-1])* (ptrMesh->x[j] - ptrMesh->x[j-1]));
    }

    // Outer free flow boundary
    resM[Nf][ptrMesh->jPoints-1] = (depM[Nf][ptrMesh->jPoints-1] - depM[Nf][ptrMesh->jPoints-2])/ (ptrMesh->x[ptrMesh->jPoints-1] - ptrMesh->x[ptrMesh->jPoints-2]) 
                         - depM[Ng][ptrMesh->jPoints-1];
    resM[Ng][ptrMesh->jPoints-1] =  depM[Ng][ptrMesh->jPoints-1] - BC[Ng][1];
    resM[NT][ptrMesh->jPoints-1] =  depM[NT][ptrMesh->jPoints-1] - BC[NT][1];

    // Reshape the residual function to a vector form
    resV = matrix2Vector(resM, ptrMesh->jPoints);
    return resV;
}

std::vector<double> Residual::matrix2Vector(std::vector<std::vector<double> > mat , int jPoints)
{
    std::vector<double> vec;
    vec.resize(jPoints*nVariables, 0.0);
    for(int j = 0; j<jPoints; j++)
    {
        for(int n = 0; n<nVariables; n++)
        {
            vec[j*nVariables +n] = mat[n][j];
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
        mat[n][j] = vec[k];
    }
    return mat;
}

