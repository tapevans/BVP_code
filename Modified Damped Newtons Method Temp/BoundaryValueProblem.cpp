
#include "BoundaryValueProblem.h"
#include <iostream>



void BoundaryValueProblem::readUserInput()
{
    std::cout<<"Reading user input \n";
}

void BoundaryValueProblem::initialMesh()
{
    std::cout<<"Initiating mesh\n";
}

void BoundaryValueProblem::initialSolution()
{
    std::cout<<"Setting the initial solution\n";
}

void BoundaryValueProblem::setFlags()
{
    std::cout<<"Setting Algorithm Flags\n";
}

void BoundaryValueProblem::setDependentVariableLimits()
{
    std::cout<<"Setting Limits on dependent variables\n";
}

void BoundaryValueProblem::setTolerance()
{
    std::cout<<"Setting Tolerances\n";
}

void BoundaryValueProblem::residual()
{
    std::cout<<"Calculating the residual vector\n";
}

void BoundaryValueProblem::checkLookAhead()
{
    std::cout<<"Checking if the new state vector meets look ahead tolerance\n";
}
void BoundaryValueProblem::checkSolutionTolerance()
{
    std::cout<<"Checking if the latest solution is within tolerance\n";
}
void BoundaryValueProblem::checkMeshTolerance()
{
    std::cout<<"Checking if the mesh meets tolerance\n";
}
void BoundaryValueProblem::performNewtonInteration()
{
    std::cout<<"Performing one iteration of MDNM\n";
}
void BoundaryValueProblem::performMeshRefinement()
{
    std::cout<<"Performing mesh refinement\n";
    
}
