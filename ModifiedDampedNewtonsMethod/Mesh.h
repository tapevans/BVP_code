/*
Mesh class
*/

#ifndef MESH_H
#define MESH_H

//#include "BoundaryValueProblem.h"
//#include "Jacobian.h"
//#include "Residual.h"

using namespace std;
#include <vector>
#include <Eigen/Eigen>
using namespace Eigen;

class Mesh
{
    public:
    // Constructor
        Mesh();
    // Functions
        void initializeMesh();
        void calculateSurfaceLocation();
        void refineMesh();
        void checkFirstOrderTol(); // This names should be changed to better represent the check
        void checkSecondOrderTol(); // This names should be changed to better represent the check


    // Variables
        RowVectorXd x;
        RowVectorXd xMinus;
        RowVectorXd xPositive;
        
        int jPoints;

        double L;
        double delta;  // Mesh refinement parameter: first order 
        double gamma;  // Mesh refinement parameter: second order 

        bool meshIsRefined;
};

#endif //MESH_H