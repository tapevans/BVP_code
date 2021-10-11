
#include "Blasius.h"
#include<iostream>

void Blasius::initialMesh()
{
    jPoints = 10;
    double L = 10;
    x.resize(jPoints, 0.0);
    dx.resize(jPoints-1, 0.0);

    for(int j = 0; j< jPoints; j++)
    {
        x[j] =  j * L/jPoints;
    }
    for(int j = 0; j< (jPoints-1); j++)
    {
        dx[j] =  x[j + 1] - x[j];
    }
}

void Blasius::initialSolution()
{
    nVariables = 3;
    depM.resize(nVariables, std::vector<double>(jPoints, 0.0));

    for(int j = 0; j< jPoints; j++)
    {
        depM[Nf][j] =  j * (5 - 0)/(x[jPoints-1] - x[0]);
        depM[Ng][j] =  j * (1 - 0)/(x[jPoints-1] - x[0]);
        depM[NT][j] =  j * (1 - 0)/(x[jPoints-1] - x[0]);
    }
}

void Blasius::residual()
{
    resM.resize(nVariables, std::vector<double>(jPoints, 0.0));
    depM.resize(nVariables, std::vector<double>(jPoints, 0.0));

    // Reshape the residual vector to the matrix Res
    //depM = vector2Matrix(depV);

    // Plate surface boundary
    resM[Nf][0] = depM[Nf][0] - 0.0;
    resM[Ng][0] = depM[Ng][0] - 0.0;
    resM[NT][0] = depM[NT][0] - 0.0;

    // Interior 
    for(int j = 1; j< (jPoints-1); j++)
    {
        resM[Nf][j] = (depM[Nf][j] - depM[Nf][j-1])/ (x[j] - x[j-1]) - depM[Ng][j];
        resM[Ng][j] = depM[Nf][j] * (depM[Ng][j] - depM[Ng][j-1]) /  (x[j] - x[j-1]) 
                    + 2 * (depM[Ng][j - 1] - 2 * depM[Ng][j]  + depM[Ng][j + 1]) / ((x[j] - x[j-1])* (x[j] - x[j-1]));
        resM[NT][j] = Pr * depM[Nf][j] * (depM[NT][j+1] - depM[NT][j])/ (x[j] - x[j-1])
                    + 2 * (depM[NT][j - 1] - 2 * depM[NT][j]  + depM[NT][j + 1]) / ((x[j] - x[j-1])* (x[j] - x[j-1]));
    }

    // Outer free flow boundary
    resM[Nf][jPoints-1] = (depM[Nf][jPoints-1] - depM[Nf][jPoints-2])/ (x[jPoints-1] - x[jPoints-2]) 
                         - depM[Ng][jPoints-1];
    resM[Ng][jPoints-1] = depM[Ng][jPoints-1] - 1.0;
    resM[NT][jPoints-1] = depM[NT][jPoints-1] - 1.0;

    // Reshape the residual function to a vector form
    resV = matrix2Vector(resM);
}

std::vector<double> Blasius::matrix2Vector(std::vector<std::vector<double>> mat)
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

std::vector<std::vector<double>> Blasius::vector2Matrix(std::vector<double> vec)
{
    std::vector<std::vector<double>> mat;
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