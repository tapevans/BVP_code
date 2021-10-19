/*
Residual
*/
#ifndef RESIDUAL_H
#define RESIDUAL_H

//#include "BoundaryValueProblem.h"
//#include "Jacobian.h"
#include "Mesh.h"

using namespace std;
#include <vector>

class Residual
{
    public:
    // Constructor
        Residual();
    // Functions
        //void initializeParameters();
        std::vector<double> calculateResidual(std::vector<double> , Mesh*); // Residual Function
        std::vector<double> matrix2Vector(std::vector<std::vector<double> >, int ); // Convert a matrix into a vector
        std::vector<std::vector<double> > vector2Matrix(std::vector<double>, int ); // Convert a vector into a matrix

    // Variables
        int Nf, Ng, NT; // Dependent variables' offset
        int nVariables; // Number of dependent variables
        //int jPoints; // Number of mesh points, defined from main*****

        std::vector<std::vector<double> > BC;
        std::vector<std::vector<double> > IC;

        // Residual Vectors //Should I keep these?
        std::vector<double> resV;
        std::vector<std::vector<double> > resM;

        // Properties
        double Pr; //Prandtl number //Don't know if this should remain here***** 



};

#endif //RESIDUAL_H