#include "BoundaryValueProblem.h"
#include <iostream>
// Main code to solve BVP

// Had to type this in the command line to link the two .cpp files
//g++ mainBVP.cpp BoundaryValueProblem.cpp -o BVP

//Used .\BVP.exe to actually run the executable in the terminal window

int main ()
{
    BoundaryValueProblem test;

    //Read input file (may skip this)
    test.readUserInput();

    //Initialize variables from input file
    test.setFlags();
    test.setDependentVariableLimits();
    test.setTolerance();
    test.initialMesh();
    test.initialSolution();

    // Test input from user
    //int value;
    //std::cin >> value;

    //Start algorithm
    /*
        while the mesh is unrefined, the solution is not within 
        tolerance, and the next solution doesn't meet Look Ahead conditions
    */
    

    int countNextSV, countSolution, countMesh;

    test.meshRefined = false;
    test.foundSolution = false;
    test.SVWithinLimits = true;
    test.normIsSmaller = false;
    test.foundNextSV = false;

    countNextSV = 0; //Temporary
    countSolution = 0; //Temporary
    countMesh = 0; //Temporary
    
    int numIterations = 0;
    int numJacobian = 0;

    while (!test.meshRefined)
    {
        // Start Iterations
        
        while (!test.foundSolution)
        {
            numIterations++;
            // Solve for the correction vector
                // Calculate the Jacobian
                if (numIterations == 1)
                {
                    //Call the function that will solve for the Jacobian
                }
                
                if (numJacobian < 20)
                {
                    // Keep the current Jacobian
                }
                else
                {
                    //Call the function that will solve for the Jacobian
                }
                
                // Calculate the residual based on current SV
                    // Call the function that calculates the residual 

                // Calculate the correction vector
                    // Call the function or do that calculation here in this line 

            // Solve for the next SV
                

                while (!test.foundNextSV)
                {
                    // Calculate a temporary next SV  (SV_temp = SV_current - lambda * currentCorrectionVector)
                        std::vector<double> tempSV;
                        //tempSV = test.currentSV - test.lambda * test.currentCorrectionVector;

                    // Check if lambda meets tolerance
                        // Are all the state variables within their defined limits?
                            test.checkStateVariableLimits();
                        // Does lambda meet the Look Ahead criteria
                            test.checkLookAhead();
                            
                            
                            


                    
                    if (countNextSV < 2)
                    {
                        countNextSV++;
                    }
                    else
                    {
                        test.foundNextSV = true;
                    }
                }
            test.checkSolutionTolerance();
            test.foundNextSV = false;
            countNextSV = 0;
            if (countSolution < 2)
            {
                countSolution++;
            }
            else
            {
                test.foundSolution = true;
            }
        }
        test.checkMeshTolerance();
        test.foundSolution = false;
        countSolution = 0;
        if (countMesh < 2)
        {
            countMesh++;
        }
        else
        {
            test.meshRefined = true;
        }
    }
    

    return 0;
}