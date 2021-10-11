#include "BoundaryValueProblem.h"
#include <iostream>
// Main code to solve BVP

// Had to type this in the command line to link the two .cpp files
//g++ mainBVP.cpp BoundaryValueProblem.cpp -o BVP

//Used .\BVP.exe to actually run the executable in the terminal window



int main ()
{
    BoundaryValueProblem test;

    // Defining user inputs here (Eventually this should be a function that reads a text file)
    test.MyMesh.L = 10;
    test.MyMesh.jPoints = 10;
    test.MyMesh.meshIsRefined = true; //setting to TRUE will skip mesh refinement
    test.MyRes.nVariables = 3;
        // Need initial values



    
    // Initialization
    test.MyMesh.initializeMesh();
    test.initialSolution();

    // Perform Modified Damped Newton's Method
    test.foundSolution = false;
    test.performNewtonIteration();

    // Perform mesh refinement
    while (!test.MyMesh.meshIsRefined)
    {
        test.MyMesh.refineMesh();
        test.performNewtonIteration();
    }

    // Save results
    test.saveResults();  

    return 0;
}

/* Wait until there is an input file to read for these functions
//Read input file (may skip this)
test.readUserInput();

//Initialize variables from input file
test.setFlags();
test.setDependentVariableLimits();
test.setTolerance();
test.initialMesh();
test.initialSolution();
*/



/*
//Print mesh
for(int j = 0; j < (test.MyMesh.jPoints); j++)
{
std::cout<<"\n j = "<<j<<"\t x = "<< test.MyMesh.x[j];
}
*/



    // Test input from user
    //int value;
    //std::cin >> value;