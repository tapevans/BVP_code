/*
Mesh class
This is a class that contains all variables and functions needed to calculate the mesh and perform mesh refinement
*/

#ifndef MESH_H
#define MESH_H

#include <iostream>
#include "toolsFolder\\eigen-3.4.0\\Eigen\\Eigen"

using namespace std;
using namespace Eigen;

class Mesh
{
public:
    // Constructor
        Mesh();                             // Sets default parameters when an instance of class Mesh is created
    
    // Functions
        void initializeMesh();              // Using user inputs, this function initailizes/calculates the mesh vectors used in later calculations
        void calculateSurfaceLocation();    // Function that calculates the location of the interface bewteen mesh points
        void refineMesh();                  // Function that performs/calls all mesh refinement tasks
        void checkFirstOrderTol();          // This names should be changed to better represent the check
        void checkSecondOrderTol();         // This names should be changed to better represent the check


    // Variables
        RowVectorXd x;                      // Vector containing the locations of each mesh point
        RowVectorXd xNegative;              // Vector containing the loction of negative interface between mesh points
        RowVectorXd xPositive;              // Vector containing the loction of positive interface between mesh points
        
        int jPoints;                        // Number of mesh points

        double L;                           // Length of the 1D domain
        double delta;                       // Mesh refinement parameter: first order 
        double gamma;                       // Mesh refinement parameter: second order 

        bool meshIsRefined;                 // Logic variable used to determine if mesh refinement should continue
};

#endif //MESH_H