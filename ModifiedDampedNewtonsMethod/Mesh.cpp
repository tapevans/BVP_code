
#include "Mesh.h"

Mesh::Mesh()
{
    // Set default mesh refinement coefficients
    delta = 0.2;
    gamma = 0.5;
}

void Mesh::initializeMesh()
{
    // Define node location (Outer nodes are located at the boundary)
    for(int j = 0; j< jPoints; j++)
    {
        x(j) =  j * L/(jPoints-1);
    }

    // Define + and - interface location
    calculateSurfaceLocation();
}

void Mesh::calculateSurfaceLocation()
{
    for(int j = 0; j< jPoints+1; j++)
    {
        if (j == 0)
        {
            xNegative(j) =  x(j);
        }
        else if(j == jPoints)
        {
            xPositive(j-1) = x(j-1);
        }
        else
        {
            xNegative(j)   =  (x(j) + x(j-1))*0.5;
            xPositive(j-1) =  (x(j) + x(j-1))*0.5;
        }       
    }
}

void Mesh::refineMesh(MatrixXd* SV){}