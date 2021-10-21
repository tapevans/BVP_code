#include "Mesh.h"
#include "Residual.h"
#include "BoundaryValueProblem.h"
#include "Jacobian.h"

#include <iostream>
#include <Eigen/Eigen>

// How I added the toolsFolder to my working folder (THIS MAY NOT HAVE WORKED)
    // Ctrl+Shift+P and clicked on C/C++: Edit Configurations (JSON)
    // In the JSON file, I added the full path under the section "includePath": (
    // I followed the syntax found in https://code.visualstudio.com/docs/cpp/customize-default-settings-cpp

// Had to type this in the command line to link the .cpp files
//g++ mainBVP.cpp BoundaryValueProblem.cpp Mesh.cpp Residual.cpp Jacobian.cpp -o BVP

//g++ -I F:/TylerFiles/GitHubRepos/BVP_code/ModifiedDampedNewtonsMethod/toolsFolder/eigen3_3_9 mainBVP.cpp Mesh.cpp -o BVP
//g++ -I F:/TylerFiles/GitHubRepos/BVP_code/ModifiedDampedNewtonsMethod/toolsFolder/eigen3_3_9 mainBVP.cpp Mesh.cpp Residual.cpp -o BVP
//g++ -I F:/TylerFiles/GitHubRepos/BVP_code/ModifiedDampedNewtonsMethod/toolsFolder/eigen3_3_9 mainBVP.cpp Mesh.cpp Residual.cpp BoundaryValueProblem.cpp  -o BVP
//g++ -I F:/TylerFiles/GitHubRepos/BVP_code/ModifiedDampedNewtonsMethod/toolsFolder/eigen3_3_9 mainBVP.cpp BoundaryValueProblem.cpp Mesh.cpp Residual.cpp Jacobian.cpp -o BVP

//Used .\BVP.exe to actually run the executable in the terminal window


// Main code to solve BVP
int main ()
{   
    // Create an instance of each of the needed classes: Mesh, Residual, BoundaryValueProblem, Jacobian
    Mesh myMesh;
    Mesh *ptrMesh; // Pointer of type Mesh class
    ptrMesh = &myMesh; // Sets the address of the class I created to the pointer

    Residual myRes;
    Residual *ptrRes;
    ptrRes = &myRes;

    BoundaryValueProblem BVPsolver;
    BoundaryValueProblem *ptrBVP;
    ptrBVP = &BVPsolver;

    Jacobian myJacobian;
    Jacobian *ptrJac;
    ptrJac = &myJacobian;
    
    // Defining user inputs here (Eventually this should be a function that reads a text file)
        // Mesh
        myMesh.L = 6;
        myMesh.jPoints = 10;
        myMesh.meshIsRefined = true; //setting to TRUE will skip mesh refinement
        // Residual
        myRes.nVariables = 3;
        // Boundary Conditions
        myRes.BC.resize(myRes.nVariables, 2);
        myRes.BC(myRes.Nf,0) = 0.0;  myRes.BC(myRes.Nf,1) = 10000000.0; // Find a better way to initialize a BC that doesn't exist (maybe something with cmath.h? nan)
        myRes.BC(myRes.Ng,0) = 0.0;  myRes.BC(myRes.Ng,1) = 1.0;
        myRes.BC(myRes.NT,0) = 0.0;  myRes.BC(myRes.NT,1) = 1.0;
        // Initial Conditions (Initial Guess, Algorithm Seeding)
        myRes.IC.resize(myRes.nVariables, 2);
        myRes.IC(myRes.Nf,0) = 0.0;  myRes.IC(myRes.Nf,1) = 5.0;
        myRes.IC(myRes.Ng,0) = 0.0;  myRes.IC(myRes.Ng,1) = 1.0;
        myRes.IC(myRes.NT,0) = 0.0;  myRes.IC(myRes.NT,1) = 1.0;
        // Tolerance
        BVPsolver.absTol = 1e-6;
        BVPsolver.relTol = 1e-3;
    
    // Initialization
    myMesh.initializeMesh();
    BVPsolver.initialSolution(ptrMesh, ptrRes);
    
    // Perform Modified Damped Newton's Method
    BVPsolver.foundSolution = false;
    
    BVPsolver.performNewtonIteration(ptrMesh, ptrRes, ptrJac);
    double temp;
    std::cin >> temp;
    
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

// ------------Old Debugging/Print Statements-------------- //

/* 
//Print mesh
    for(int j = 0; j < (myMesh.jPoints); j++)
    {
        std::cout<<"\n j = "<<j+1<<"\t x = "<< myMesh.x(j);
    }
    std::cout << "\n";
 */



/*
//Print mesh
for(int j = 0; j < (myMesh.jPoints); j++)
{
std::cout<<"\n j = "<<j<<"\t x = "<< myMesh.x(j);
}
*/



    // BVPsolver input from user
    //int value;
    //std::cin >> value;



/*
    std::cout << "\nThe first calculated residual is: \n";
    for (int i = 0; i < myRes.nVariables; i++) 
    {
        for(int j = 0; j < (myMesh.jPoints); j++)
        {
            std::cout << myRes.res(i,j) << "\t";
            //std::cout<<"\n j = "<<j<<"\t x = "<< myMesh.x(j);
        }
        std::cout << "\n";
    }
    */


/* MatrixXd m(4,1);
    m << 1,2,3,4;
    MatrixXd something(4,1);
    something << 3.0, 7.0, 10.0, 9.0;
    std::cout  << m << std::endl<< std::endl;
    MatrixXd temp;
    for (int i = 0; i < 4; i++)
    {
        temp = m;
        temp(i) += something(i);
        std::cout  << temp - m << std::endl<< std::endl;
    } */


    /*
    //Print BC and IC
    std::cout << "BC:" << std::endl;
    std::cout << myRes.BC << std::endl;

    std::cout << "IC:" << std::endl;
    std::cout << myRes.IC << std::endl;
    */


   /*
    //Test Resize
    MatrixXd test;
    std::cout << "test uninitialized is:" << std::endl;
    std::cout << test << std::endl;
    //MatrixXd test(3,8);
    //MatrixXd test = MatrixXd::Zero(3,8);
    //test = MatrixXd::Zero(3,8);
    test.resize(3,8);
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 3; i++)
        {
        
        //std::cout << "i is :" << i << std::endl;
        //std::cout << "j is :" << j << std::endl;
        //std::cout << "i*8 + j is :" << i*8 + j << std::endl;
        test(i,j) = i + j*3 + 1;
        }
    }
    std::cout << "test is:" << std::endl;
    std::cout << test << std::endl;
    std::cout << "Now reshaping test" << std::endl;
    test.resize(2,12);
    std::cout << test << std::endl;
    std::cout << "Reshaping test again" << std::endl;
    test.resize(4,6);
    std::cout << test << std::endl;
    std::cout << "Reshaping test again into vector" << std::endl;
    test.resize(24,1);
    std::cout << test << std::endl;
    */


       /*
    std::cout << "\n This size of the solution matrix is " << BVPsolver.currentSV.rows() << " rows and " << BVPsolver.currentSV.cols() << " columns\n";
    std::cout << "\nThe initial solution vector is: \n" << BVPsolver.currentSV << std::endl;     
    //****** Make this a function in BVP class
    for (int i = 0; i < myRes.nVariables; i++) 
    {
        for(int j = 0; j < (myMesh.jPoints); j++)
        {
            std::cout << BVPsolver.currentSV(i,j) << "\t";
            //std::cout<<"\n j = "<<j<<"\t x = "<< myMesh.x(j);
        }
        std::cout << "\n";
    }
    
    std::cout << "\nThe absolute tolerance is : " << BVPsolver.absTol ;
    std::cout << "\nThe relative tolerance is : " << BVPsolver.relTol ;

    std::cout << "\nThe absolute tolerance is : " << BVPsolver.absTol << std::scientific;
    std::cout << "\nThe relative tolerance is : " << BVPsolver.relTol << std::scientific;
    */