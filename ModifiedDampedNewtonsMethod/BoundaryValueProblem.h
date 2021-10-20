/*
Boundary Value Problem Class
This class will be used to solve boundary value problems using the Modified Damped Newton's Method
*/


#ifndef BVP_H
#define BVP_H

#include "Mesh.h"
#include "Residual.h"
#include "Jacobian.h"

//using namespace std;


class BoundaryValueProblem
{
public:
    // Constructor
    BoundaryValueProblem();
    // Functions
    void readUserInput();  // Reads the users input from a text file
    void initialSolution(Mesh*, Residual*);
    void setFlags(); //Placeholder for future
    void setDependentVariableLimits(); //Placeholder for future
    void setTolerance(); //Placeholder for future
    void performNewtonIteration(Mesh*, Residual*, Jacobian*);
        void calcCorrectionVector(Mesh*, Residual*, Jacobian*);
        void calcNextSV(Mesh*, Residual*, Jacobian*);
            void checkSVLimits(MatrixXd tempSV);
            void checkLookAhead(MatrixXd tempSV, Mesh*, Residual*, Jacobian*);
        void checkSolutionTolerance();
    void saveResults();
    // Error handling function????
    void printInt(int theIntValue);
    void printDouble(double theIntValue);
    void printVector(std::vector<double> theVector);
    void printMatrix(std::vector<std::vector<double> > theMatrix);
    


// Variables
    bool foundSolution;
    bool SVWithinLimits;
    bool normIsSmaller;
    bool foundNextSV;

    MatrixXd currentSV;
    MatrixXd nextSV;
    MatrixXd currentCorrectionVector;
    MatrixXd nextCorrectionVector;

    //MatrixXd currentSVM;

    double lambda; // Damping factor
    double absTol; // Absolute tolerance for the solution
    double relTol; // Relative tolerance for the solution
    double currentNorm, nextNorm; //Current and next norm of the correction vector


};

#endif