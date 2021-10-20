/*
Residual
*/
#ifndef RESIDUAL_H
#define RESIDUAL_H

//#include "BoundaryValueProblem.h"
//#include "Jacobian.h"
#include "Mesh.h"

using namespace std;


class Residual
{
    public:
    // Constructor
        Residual();
    // Functions
        //void initializeParameters();
        MatrixXd calculateResidual(MatrixXd , Mesh*); // Residual Function
        //std::vector<double> matrix2Vector(std::vector<std::vector<double> >, int ); // Convert a matrix into a vector
        //std::vector<std::vector<double> > vector2Matrix(std::vector<double>, int ); // Convert a vector into a matrix

    // Variables
        int Nf, Ng, NT; // Dependent variables' offset
        int nVariables; // Number of dependent variables
        //int jPoints; // Number of mesh points, defined from main*****

        Matrix<double, Dynamic, 2> BC; // This is more like the limits
        Matrix<double, Dynamic, 2> IC; // This is the initial boundary conditions

        // Residual Vectors 
        MatrixXd res;

        // Properties
        double Pr; //Prandtl number //Don't know if this should remain here***** 



};

#endif //RESIDUAL_H