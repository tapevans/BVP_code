#include "BoundaryValueProblem.h"
#include "Jacobian.h"
#include "Residual.h"
#include "Mesh.h"
#include <iostream>
// Main code to solve BVP

// Had to type this in the command line to link the two .cpp files
//g++ mainBVP.cpp BoundaryValueProblem.cpp Mesh.cpp Residual.cpp Jacobian.cpp -o BVP

//Used .\BVP.exe to actually run the executable in the terminal window



int main ()
{
    BoundaryValueProblem BVPsolver;
    BoundaryValueProblem *ptrBVP;
    ptrBVP = &BVPsolver;

    Mesh myMesh;
    Mesh *ptrMesh; // Pointer to a class
    ptrMesh = &myMesh; // Sets the address of the class I created to the pointer

    Jacobian myJacobian;
    Jacobian *ptrJac;
    ptrJac = &myJacobian;

    Residual myRes;
    Residual *ptrRes;
    ptrRes = &myRes;
    
    // Defining user inputs here (Eventually this should be a function that reads a text file)
        // Mesh
        myMesh.L = 6;
        myMesh.jPoints = 10;
        myMesh.meshIsRefined = true; //setting to TRUE will skip mesh refinement
        // Residual
        myRes.nVariables = 3;
        // Boundary Conditions
        myRes.BC.resize(myRes.nVariables, std::vector<double>(2, 0.0));
        myRes.BC[myRes.Nf][0] = 0.0;  myRes.BC[myRes.Nf][1] = 10000000.0;
        myRes.BC[myRes.Ng][0] = 0.0;  myRes.BC[myRes.Ng][1] = 1.0;
        myRes.BC[myRes.NT][0] = 0.0;  myRes.BC[myRes.NT][1] = 1.0;
        // Initial Conditions
        myRes.IC.resize(myRes.nVariables, std::vector<double>(2, 0.0));
        myRes.IC[myRes.Nf][0] = 0.0;  myRes.IC[myRes.Nf][1] = 5.0;
        myRes.IC[myRes.Ng][0] = 0.0;  myRes.IC[myRes.Ng][1] = 1.0;
        myRes.IC[myRes.NT][0] = 0.0;  myRes.IC[myRes.NT][1] = 1.0;
        // Tolerance
        BVPsolver.absTol = 1e-6;
        BVPsolver.relTol = 1e-3;
    
    // Initialization
    myMesh.initializeMesh();
    BVPsolver.initialSolution(ptrMesh, ptrRes);

    //Print mesh
    for(int j = 0; j < (myMesh.jPoints); j++)
    {
        std::cout<<"\n j = "<<j+1<<"\t x = "<< myMesh.x[j];
    }
    std::cout << "\n";


    std::cout << "\n This size of the solution matrix is " << BVPsolver.currentSVM.size() << " rows and " << BVPsolver.currentSVM[0].size() << " columns\n";
    std::cout << "\nThe initial solution vector is: \n";
    //****** Make this a function in BVP class
    for (int i = 0; i < myRes.nVariables; i++) 
    {
        for(int j = 0; j < (myMesh.jPoints); j++)
        {
            std::cout << BVPsolver.currentSVM[i][j] << "\t";
            //std::cout<<"\n j = "<<j<<"\t x = "<< myMesh.x[j];
        }
        std::cout << "\n";
    }
    
    std::cout << "\nThe absolute tolerance is : " << BVPsolver.absTol ;
    std::cout << "\nThe relative tolerance is : " << BVPsolver.relTol ;

    std::cout << "\nThe absolute tolerance is : " << BVPsolver.absTol << std::scientific;
    std::cout << "\nThe relative tolerance is : " << BVPsolver.relTol << std::scientific;



    // Perform Modified Damped Newton's Method
    BVPsolver.foundSolution = false;
    
    BVPsolver.performNewtonIteration(ptrMesh, ptrRes, ptrJac);
    std::cout << "\nThe first calculated residual is: \n";
    //****** Make this a function in BVP class
    for (int i = 0; i < myRes.nVariables; i++) 
    {
        for(int j = 0; j < (myMesh.jPoints); j++)
        {
            std::cout << myRes.resM[i][j] << "\t";
            //std::cout<<"\n j = "<<j<<"\t x = "<< myMesh.x[j];
        }
        std::cout << "\n";
    }

    /*
    // Perform mesh refinement
    while (!myMesh.meshIsRefined)
    {
        myMesh.refineMesh();
        BVPsolver.performNewtonIteration();
    }

    // Save results
    BVPsolver.saveResults();  
    */

    return 0;
}

/* Wait until there is an input file to read for these functions
//Read input file (may skip this)
BVPsolver.readUserInput();

//Initialize variables from input file
BVPsolver.setFlags();
BVPsolver.setDependentVariableLimits();
BVPsolver.setTolerance();
BVPsolver.initialMesh();
BVPsolver.initialSolution();
*/



/*
//Print mesh
for(int j = 0; j < (myMesh.jPoints); j++)
{
std::cout<<"\n j = "<<j<<"\t x = "<< myMesh.x[j];
}
*/



    // BVPsolver input from user
    //int value;
    //std::cin >> value;