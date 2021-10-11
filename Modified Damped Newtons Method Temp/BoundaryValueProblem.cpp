
#include "BoundaryValueProblem.h"
#include <iostream>
using namespace std;


void BoundaryValueProblem::readUserInput()
{
    std::cout<<"Reading user input \n";
}

void BoundaryValueProblem::initialSolution()
{
    std::cout<<"Setting the initial solution\n";
}

void BoundaryValueProblem::setFlags()   // PLACEHOLDER
{
    std::cout<<"Setting Algorithm Flags\n";
}

void BoundaryValueProblem::setDependentVariableLimits() // PLACEHOLDER
{
    std::cout<<"Setting Limits on dependent variables\n";
}

void BoundaryValueProblem::setTolerance() // PLACEHOLDER
{
    std::cout<<"Setting Tolerances\n";
}

void BoundaryValueProblem::performNewtonInteration()
{
    std::cout<<"Performing Modified Damped Newtons Method to find the solution\n";
    while (!foundSolution)
    {
        foundNextSV = false;
        lambda = 1.0; 
        calcCorrectionVector();
        calcNextSV();
        checkSolutionTolerance(); //This will determine if another MDNM needs to be performed
    }    
}

void BoundaryValueProblem::calcCorrectionVector()
{
    std::cout<<"Calculating correction vector\n";
    // Calculate Jacobian
    MyJacobian.calculateJacobian();
    
    // Calculate Residual
    MyRes.calculateResidual();
    
    // Calculate inverse of the Jacobian **********

    // Solve for correction vector
    currentCorrectionVector = (MyJacobian.jacM)^(-1) * MyRes.resV; //****** Figure out how to multiply a matrix by a vector
}

void BoundaryValueProblem::calcNextSV()
{
    std::cout<<"Calculating the next solution vector\n";
    
    // while a nextSV has not been found
    while (!foundNextSV)
    {
        // Calculate a temporary SV
        std::vector<double> tempSV;
        tempSV = currentSV - lambda * currentCorrectionVector;

        // Check if this SV is within the limits
        checkSVLimits(tempSV);

        // Check if the damping is satisfied
        checkLookAhead(tempSV);

        // Determine if the solution should be kept or if a new Jacobian should be calculated
        // If keeping the solution, set tempSV to nextSV
        if (normIsSmaller && SVWithinLimits)
        {
            foundNextSV = true;
            nextSV = tempSV;
            // Set the next correction vector from what was calculated inside check Look Ahead so maybe just do this there
        }
        else
        {
            lambda = lambda * 0.5;
        }
    }
}

void BoundaryValueProblem::checkSVLimits(std::vector<double> tempSV)
{
    std::cout<<"Checking if all state variables are within the defined limits\n";
    SVWithinLimits = true; // This function needs to be built
}

void BoundaryValueProblem::checkLookAhead(std::vector<double> tempSV)
{
    std::cout<<"Checking if the new state vector meets look ahead tolerance\n";


}
void BoundaryValueProblem::checkSolutionTolerance()
{
    std::cout<<"Checking if the latest solution is within tolerance\n";
    // norm(next(or current) correction vector) < max of (  Abs_tol or Rel_tol*SV_next (or cuurent?)  )
    if (SVWithinLimits)
    {
        foundSolution = true;
    }
}

void BoundaryValueProblem::saveResults()
{
    std::cout<<"Saving the results to a file\n";
}

 /*
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
                            //test.checkStateVariableLimits();
                        // Does lambda meet the Look Ahead criteria
                            //test.checkLookAhead();
                            
                            
                            


                    
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
    */