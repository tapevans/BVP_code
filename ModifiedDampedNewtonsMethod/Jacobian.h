/*
Jacobian
*/
#ifndef JACOBIAN_H
#define JACOBIAN_H

//#include "BoundaryValueProblem.h"
#include "Residual.h"
#include "Mesh.h"

class Jacobian
{
public:
    // Constructor
        Jacobian();
    // Functions
    void calculateJacobian(MatrixXd, Mesh*, Residual*);
        void calculatePerturbation(MatrixXd);


    // Variables
    MatrixXd jac; //Jacobian Matrix
    MatrixXd per; //Perturbation vector

    int totSV;

    double absPer; // Absolute pertebation value for the jacobian
    double relPer; // Relative pertebation value for the jacobian
};

#endif //JACOBIAN_H