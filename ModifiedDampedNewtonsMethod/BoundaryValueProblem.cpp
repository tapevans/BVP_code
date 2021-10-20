
#include "BoundaryValueProblem.h"
#include <iostream>
using namespace std;

BoundaryValueProblem::BoundaryValueProblem()
{
    absTol = 1e-6;
    relTol = 1e-3;
    
    foundSolution= true;
    SVWithinLimits= true;
    normIsSmaller= true;
    foundNextSV= true;
}

void BoundaryValueProblem::readUserInput()
{
    std::cout<<"Reading user input \n";
}

void BoundaryValueProblem::initialSolution(Mesh* ptrMesh, Residual* ptrRes)
{
    std::cout<<"Setting the initial solution\n";

    currentSV.resize((ptrRes->nVariables), (ptrMesh->jPoints));

    for (int i = 0; i < (ptrRes->nVariables); i++)
    {
        for(int j = 0; j< (ptrMesh->jPoints); j++)
        {
            currentSV(i,j) = ( (ptrRes->IC(i,1) - ptrRes->IC(i,0))/(ptrMesh->x(ptrMesh->jPoints-1) - ptrMesh->x(0)) ) 
                                * ptrMesh->x(j) + ptrRes->IC(i,0); // Slope eqn for a line
        }
    }
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

void BoundaryValueProblem::performNewtonIteration(Mesh* ptrMesh, Residual* ptrRes, Jacobian* ptrJac)
{
    std::cout<<"\nPerforming Modified Damped Newtons Method to find the solution\n";
    while (!foundSolution)
    {
        foundNextSV = false;
        lambda = 1.0; 
        calcCorrectionVector(ptrMesh, ptrRes, ptrJac);
        calcNextSV();
        checkSolutionTolerance(); //This will determine if another MDNM needs to be performed
    }    
}


void BoundaryValueProblem::calcCorrectionVector(Mesh* ptrMesh, Residual* ptrRes, Jacobian* ptrJac)
{

    //std::cout<<"\tCalculating correction vector\n";
 
    // Calculate Residual
    MatrixXd residual;
    residual = (ptrRes->calculateResidual(currentSV, ptrMesh));
 
    // Calculate Jacobian
    ptrJac->calculateJacobian(currentSV, ptrMesh, ptrRes);
    
    // Solve for correction vector
    currentCorrectionVector = (ptrJac->jac.inverse()) * residual; 
    std::cout << "Calculation of the correction vector is: \n" << currentCorrectionVector << std::endl;
}

void BoundaryValueProblem::calcNextSV()
{
    
    std::cout<<"\nCalculating the next solution vector\n";
    /*
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
    */
}


void BoundaryValueProblem::checkSVLimits(MatrixXd tempSV)
{
    std::cout<<"\t\tChecking if all state variables are within the defined limits\n";
    SVWithinLimits = true; // This function needs to be built
}

void BoundaryValueProblem::checkLookAhead(MatrixXd tempSV)
{
    std::cout<<"\t\tChecking if the new state vector meets look ahead tolerance\n";


}

void BoundaryValueProblem::checkSolutionTolerance()
{
    std::cout<<"\tChecking if the latest solution is within tolerance\n";
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

