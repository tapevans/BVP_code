
/*
This is the main file which gets the user input, calls the boundary value
solver and then post-processes the solution
*/

// Include the header file
#include "templateMain.h"

// Functions

/* The main function to solve the boundary value problem */
int main()
{
    // Read the user input from .dat file
    userInput("input.dat");

    // Create the BVP class instance
    bvpSolver BVP_instance(nv);

    // Solve the boundary value problem
    BVP_instance.solve();
    /* Note here the BVP solver must have access to the getResidual() function defined here.
       It also should have access to the Mesh class and be able to refine the grid */

    // Post-processing

    return 0;
}

int userInput()
{
    /* This function should read all the input parameters such as number of variables,
    inlet and outlet boundary conditions, species mechanism if present,
    geometry of the domain etc. */
    return 0;
}

int getResidual()
{
    /* This function solves the actual governing equations for the problem at hand */
}
