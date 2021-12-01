/*
Residual
This is a class that contains all variables and functions needed to calculate the residual
*/

#ifndef RESIDUAL_H
#define RESIDUAL_H

#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

class Residual
{
public:
    // Constructor
        Residual();                                     // Defines the pointers and number of dependent variables in the system when an instance of class Residual is created

    // Functions
        MatrixXd calculateResidual(MatrixXd SV, MatrixXd* ptrMeshX, int* ptrjPoints);   // Residual Function

    // Variables
        int Nf, Ng, NT;                                 // Dependent variables' pointers
        int nVariables;                                 // Number of dependent variables

        Matrix<double, Dynamic, 2> BC;                  // Boundary conditions for each dependent variable
        Matrix<double, Dynamic, 2> IC;                  // Initial guess/seeding for the algorithm
        MatrixXd currentRes, tempRes;                   // Residual vectors

        // Properties
        double Pr; //Prandtl number //Don't know if this should remain here***** 
};

#endif //RESIDUAL_H