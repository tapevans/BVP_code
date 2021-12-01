
#include "BoundaryValueProblem.h"
#include <iostream>


BoundaryValueProblem::BoundaryValueProblem()
{
    // Default values for tolerance
    absTol = 1e-6;
    relTol = 1e-3;
    
    // Set default values for logic variables
    foundSolution  = true;
    SVWithinTrustRegion = true;
    normIsSmaller  = true;
    foundNextSV    = true;
}

void BoundaryValueProblem::readUserInput()   // PLACEHOLDER
{
    std::cout<<"Reading user input \n";
}

void BoundaryValueProblem::initialSolution(Mesh* ptrMesh, Residual* ptrRes)
{
    std::cout<<"Setting the initial solution\n";

    // Reshape SV
    currentSV.resize((ptrRes->nVariables), (ptrMesh->jPoints));

    // Set the value of all dependent variables linearly from the given seed values
    for (int i = 0; i < (ptrRes->nVariables); i++)
    {
        for(int j = 0; j < (ptrMesh->jPoints); j++)
        {
            currentSV(i,j) = ( (ptrRes->IC(i,1) - ptrRes->IC(i,0))/(ptrMesh->x(ptrMesh->jPoints-1) - ptrMesh->x(0)) ) 
                                * ptrMesh->x(j) + ptrRes->IC(i,0); // Slope eqn for a line
        }
    }
    int totSV = (*ptrMesh).jPoints * (*ptrRes).nVariables;
    currentSV.resize(totSV, 1);
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
    numIterations = 0;
    // Start the algorithm
    while (!foundSolution)
    {
        numIterations++;
        foundNextSV = false;
        lambda = 1.0; 
        calcCorrectionVector(ptrMesh, ptrRes, ptrJac);
        calcNextSV(ptrMesh, ptrRes, ptrJac);
        checkSolutionTolerance(ptrJac); //This will determine if another MDNM needs to be performed 
        
    }    
}

void BoundaryValueProblem::calcCorrectionVector(Mesh* ptrMesh, Residual* ptrRes, Jacobian* ptrJac)
{ 
    int *ptrjPoints    = &((*ptrMesh).jPoints);
    MatrixXd *ptrMeshX = &((*ptrMesh).x);
    // Calculate Residual
    ptrRes->currentRes = (ptrRes->calculateResidual(currentSV, ptrMeshX, ptrjPoints));
    
    // Calculate Jacobian
    if (numIterations == 1)
    {
        ptrJac->calculateJacobian(currentSV, ptrMesh, ptrRes); 
    }
    
    if (ptrJac->jacobianCounter < 20)
    {
        //keep old Jacobian
    }
    else
    {
        ptrJac->calculateJacobian(currentSV, ptrMesh, ptrRes); 
    }
    
    

    // Solve for correction vector ---  CV = inv(Jac(SV))*(-Res(SV))  ---
    currentCorrectionVector = (ptrJac->jac.inverse()) * (-1 * (ptrRes->currentRes)); 
        //std::cout << "Calculation of the correction vector is: \n" << currentCorrectionVector << std::endl;
    
    // Calculate the norm of the correction vector (This is used later)
    currentNorm = currentCorrectionVector.norm();

                ofstream debugFilestream;
                debugFilestream.open("debugLog.txt", ios::out | ios::app); 
                debugFilestream << "numIterations = " << numIterations << "\n";
                debugFilestream << "jacobianCounter = " << ptrJac->jacobianCounter << "\n";
                debugFilestream << "Residual is :\n";
                debugFilestream << ptrRes->currentRes << "\n";
                debugFilestream << "Jacobian is :\n";
                debugFilestream << ptrJac->jac << "\n";
                debugFilestream << "Correction Vector is :\n";
                debugFilestream << currentCorrectionVector << "\n";
                debugFilestream.close();
}

void BoundaryValueProblem::calcNextSV(Mesh* ptrMesh, Residual* ptrRes, Jacobian* ptrJac)
{
    //std::cout<<"\nCalculating the next solution vector\n";
    
    // while a nextSV has not been accepted
    while (!foundNextSV)
    {
        // Calculate a temporary SV
        //std::cout << "Inside calcNextSV. currentSV is:" << currentSV << std::endl;
        tempSV = currentSV + lambda * currentCorrectionVector;

        //std::cout << "Inside calcNextSV. tempSV is:" << tempSV << std::endl;
        // Check if this SV is within the trust region
        checkSVTrustRegion(tempSV); //// --------- This currently does nothing

        // Check if the damping is satisfied (----- Is this the right way of saying this?)
        checkLookAhead(tempSV, ptrMesh, ptrRes, ptrJac);

        // Determine if the temp solution vector is accepted (---------or if a new Jacobian should be calculated or a time step should be taken ----- not implemented yet)
        if (normIsSmaller && SVWithinTrustRegion) // <-- requirement for the tempSV to be accepted
        {
            foundNextSV = true; // Stops the while loop in this function
            nextSV = tempSV;
            nextNorm = tempNorm; 
            ////--------- Set the next correction vector from what was calculated inside check Look Ahead so maybe just do this there?
        }
        else
        {
            lambda = lambda * 0.5;
            if (lambda < 1e-10)
            {
                ptrJac->calculateJacobian(currentSV, ptrMesh, ptrRes);
                lambda = 0.5;
            }
            
        }
        std::cout<< "lambda is: " << lambda << std::endl;
    }
}

void BoundaryValueProblem::checkSVTrustRegion(MatrixXd tempSV) ////-------------- This function needs to be built
{
    SVWithinTrustRegion = true; 
}

void BoundaryValueProblem::checkLookAhead(MatrixXd tempSV, Mesh* ptrMesh, Residual* ptrRes, Jacobian* ptrJac)
{
    std::cout<<"\t\tChecking if the new state vector meets look ahead tolerance\n";
    int *ptrjPoints    = &((*ptrMesh).jPoints);
    MatrixXd *ptrMeshX = &((*ptrMesh).x);

    // Calculate the next correction vector from the next SV
    ptrRes->tempRes = (ptrRes->calculateResidual(tempSV, ptrMeshX, ptrjPoints));
    nextCorrectionVector = (ptrJac->jac.inverse()) * (-1*ptrRes->tempRes);
    
    //Calculate the norm of the current and next correction vectors
    tempNorm = nextCorrectionVector.norm();
    
    std::cout << "The norm of the current correction vector is: " << currentNorm << std::endl;
    std::cout << "The norm of the next correction vector is: "    << tempNorm    << std::endl;

    if (tempNorm < currentNorm)
    {
        normIsSmaller = true;
        
    }
    else
    {
        normIsSmaller = false;
    }
}

void BoundaryValueProblem::checkSolutionTolerance(Jacobian* ptrJac)
{
    std::cout<<"\tChecking if the latest solution is within tolerance\n";
    ////-------- norm(next(or current) correction vector) < max of (  Abs_tol or Rel_tol*SV_next (or curent?)  )
    double maxTol;
    maxTol = std::max(absTol,relTol*nextSV.norm());

    if (nextNorm < maxTol)
    {
        foundSolution = true;
        currentSV = nextSV;
        std::cout << "\nSolution was found!" << std::endl;
                ofstream debugFilestream;
                debugFilestream.open("debugLog.txt", ios::out | ios::app); 
                debugFilestream << "The solution is :\n";
                MatrixXd tempVar;
                tempVar = currentSV;
                tempVar.resize(3,10);
                debugFilestream << tempVar << "\n";
                debugFilestream.close();
    }
    else
    {
        ptrJac->jacobianCounter++;
        currentSV = nextSV;
    }
    
}

void BoundaryValueProblem::saveResults()   // PLACEHOLDER
{
    std::cout<<"Saving the results to a file\n";
}

