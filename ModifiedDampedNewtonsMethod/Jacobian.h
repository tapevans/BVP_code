/*
Jacobian
*/
#ifndef JACOBIAN_H
#define JACOBIAN_H

//#include "BoundaryValueProblem.h"
#include "Residual.h"
#include "Mesh.h"

using namespace std;
#include <vector>

class Jacobian
{
public:
    // Constructor
        Jacobian();
    // Functions
    void calculateJacobian(std::vector<double>, Mesh*, Residual*);
        void calculatePerturbation(std::vector<double> SV);


    // Variables
    std::vector<std::vector<double> > jacM;
    std::vector<std::vector<double> > perV;

    int totSV;

    double absPer; // Absolute pertebation value for the jacobian
    double relPer; // Relative pertebation value for the jacobian
};

#endif //JACOBIAN_H