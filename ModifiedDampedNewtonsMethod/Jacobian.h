/*
Jacobian Class:
This is a class that contains all variables and functions needed to calculate the Jacobian
*/
#ifndef JACOBIAN_H
#define JACOBIAN_H

#include "Residual.h" 
#include "Mesh.h" 

#include <iostream>
#include <fstream>
#include <Eigen/Eigen>

class Jacobian
{
public:
    // Constructor
        Jacobian();                                         // Sets default parameters when an instance of class Jacobian is created
    
    // Functions
        void calculateJacobian(MatrixXd, Mesh*, Residual*); // Parent function that calls all necessary functions to calculate the Jacobian
            void calculatePerturbation(MatrixXd, int);      // Function that determines that perturbed value for each SV

    // Variables
        MatrixXd jac;                                       // Jacobian matrix
        MatrixXd per;                                       // Perturbation values vector
        MatrixXd tempSV;                                    // Temporary Solution Vector

        double absPer;                                      // Absolute pertubation value for the jacobian
        double relPer;                                      // Relative pertubation value for the jacobian

        int jacobianCounter; // Keeps track of how many Newton iterations the Jacobian has been used for
};

#endif //JACOBIAN_H