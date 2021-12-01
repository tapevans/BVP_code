#include "Mesh.h"
#include "Residual.h"
#include "Jacobian.h"
#include "BoundaryValueProblem.h"

#include <iostream>
#include <fstream>
#include <Eigen/Eigen>

std::string componentName(int ind);
void writeSolution(int nPoints, int nVars, RowVectorXd grid, MatrixXd currentSV);
void initializeMatrixSize(Mesh*, Residual*, Jacobian*, BoundaryValueProblem*);                     // Sets the size of all matrix used throughout the solver

// ******************************************************************************************** //

// Main code to solve BVP
int main ()
{   
    // Create debug file
    ofstream debugFilestream;
    debugFilestream.open("debugLog.txt", ios::out | ios::trunc);
    debugFilestream << "Hello World\n";
    debugFilestream.close();

    // Create an instance of each of the needed classes: Mesh, Residual, BoundaryValueProblem, Jacobian
    Mesh myMesh;
    Mesh *ptrMesh; // Pointer of type Mesh class
    ptrMesh = &myMesh; // Sets the address of the class created to the pointer

    Residual myRes;
    Residual *ptrRes;
    ptrRes = &myRes;

    Jacobian myJacobian;
    Jacobian *ptrJac;
    ptrJac = &myJacobian;

    BoundaryValueProblem BVPsolver;
    BoundaryValueProblem *ptrBVP;
    ptrBVP = &BVPsolver;
    
    // Defining user inputs here (Eventually this should be a function that reads a text file)
        // Mesh
        myMesh.L = 6;
        myMesh.jPoints = 10;
        myMesh.meshIsRefined = false; //setting to TRUE will skip mesh refinement

        // Residual
        myRes.nVariables = 3;

        // After jPoints and nVariables are defined, all matrices can be initialized to a know size
        initializeMatrixSize(ptrMesh , ptrRes , ptrJac, ptrBVP);

        // Boundary Conditions
        myRes.BC(myRes.Nf,0) = 0.0;  myRes.BC(myRes.Nf,1) = 10000000.0; // Find a better way to initialize a BC that doesn't exist (maybe something with cmath.h? nan)
        myRes.BC(myRes.Ng,0) = 0.0;  myRes.BC(myRes.Ng,1) = 1.0;
        myRes.BC(myRes.NT,0) = 0.0;  myRes.BC(myRes.NT,1) = 1.0;

        // Initial Conditions (Initial Guess, Algorithm Seeding)
        myRes.IC(myRes.Nf,0) = 0.0;  myRes.IC(myRes.Nf,1) = 5.0;
        myRes.IC(myRes.Ng,0) = 0.0;  myRes.IC(myRes.Ng,1) = 1.0;
        myRes.IC(myRes.NT,0) = 0.0;  myRes.IC(myRes.NT,1) = 1.0;

        // Tolerance
        BVPsolver.absTol = 1e-6;
        BVPsolver.relTol = 1e-3;
        
        // Properties
        myRes.Pr = 0.71;
    
    // Initialization
    myMesh.initializeMesh();
    BVPsolver.initialSolution(ptrMesh, ptrRes);

                // Print the mesh and initial solution to the debug file
                debugFilestream.open("debugLog.txt", ios::out | ios::app); 
                debugFilestream << "The initial mesh is:\n";
                debugFilestream << myMesh.x << "\n";
                debugFilestream << "The negative interface locations are:\n";
                debugFilestream << myMesh.xNegative << "\n";
                debugFilestream << "The positive interface locations are:\n";
                debugFilestream << myMesh.xPositive << "\n";
                debugFilestream << "The seeding values (IC) for the algorithm are:\n";
                MatrixXd tempMat;
                tempMat = BVPsolver.currentSV;
                tempMat.resize(myRes.nVariables,myMesh.jPoints);
                debugFilestream << tempMat << "\n";
                debugFilestream.close();

    
    // Run Solver Algorithm
    while (!myMesh.meshIsRefined)
    {
        cout << "In the while loop" << endl;

        // Perform an iteration of Modified Damped Newton's Method
        BVPsolver.foundSolution = false;
        BVPsolver.performNewtonIteration(ptrMesh, ptrRes, ptrJac);

        // Perform mesh refinement
        MatrixXd* solutionPointer = &(BVPsolver.currentSV);
        myMesh.meshIsRefined = true; // While loop runs when this is false. true ends the loop
        //myMesh.refineMesh(solutionPointer);
    }

    // Save results ( Write solution to bvpSolution.csv file )
    writeSolution(myMesh.jPoints, myRes.nVariables, myMesh.x, BVPsolver.currentSV);

    return 0;
}

// ******************************************************************************************** //

void initializeMatrixSize(Mesh* ptrMesh, Residual* ptrRes, Jacobian* ptrJac, BoundaryValueProblem* ptrBVP){
    int totSV = (*ptrMesh).jPoints * (*ptrRes).nVariables;
    // Mesh Matricies
    ptrMesh->x.resize(1, ptrMesh->jPoints);                      
    ptrMesh->xNegative.resize(1, ptrMesh->jPoints);              
    ptrMesh->xPositive.resize(1, ptrMesh->jPoints);              

    // Residual Matricies
    ptrRes->BC.resize(ptrRes->nVariables, 2);                  
    ptrRes->IC.resize(ptrRes->nVariables, 2);                  
    ptrRes->currentRes.resize(totSV,1);
    ptrRes->tempRes.resize(totSV,1);            
    
    // Jacobian Matricies
    ptrJac->jac.resize(totSV , totSV);                
    ptrJac->per.resize(totSV,1);                 
    ptrJac->tempSV.resize(totSV,1);

    // BVP Matricies 
    ptrBVP->currentSV.resize(totSV,1);                   
    ptrBVP->tempSV.resize(totSV,1);                      
    ptrBVP->nextSV.resize(totSV,1);                      
    ptrBVP->currentCorrectionVector.resize(totSV,1);     
    ptrBVP->nextCorrectionVector.resize(totSV,1);        
}


//************ Functions to write to CSV ************// Maybe move to its own header file.... future

std::string componentName(int ind) 
    {
        if(ind == 0)
        {
            return "nf";
        }
        else if (ind == 1)
        {
            return "ng";
        } else if(ind == 2)
        {
            return "nT";
        }
    }

void writeSolution(int nPoints, int nVars, RowVectorXd grid, MatrixXd currentSV) 
    {
        std::string filename;
        filename = "bvpSolution.csv";
        std::ofstream f(filename);    
        currentSV.resize(nVars,nPoints); 
        f << "x" << ",";
        for (int n = 0; n < nVars; n++)
        {   
            f << componentName(n);
            f << ", ";
        }
        f << std::endl;
        for (int j = 0; j < nPoints; j++)
        {
            f << grid(j) <<",";
            for (int n = 0; n < nVars; n++)
            {
                f << currentSV(n,j);
                if (n != nVars - 1) {
                    f << ", ";
                }
            }
            f << std::endl;
        }
    }