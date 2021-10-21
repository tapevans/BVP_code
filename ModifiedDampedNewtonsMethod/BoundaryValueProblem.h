/*
Boundary Value Problem Class
This class will be used to solve boundary value problems using the Modified Damped Newton's Method (MDNM)
*/


#ifndef BVP_H
#define BVP_H

#include "Mesh.h"
#include "Residual.h"
#include "Jacobian.h"


class BoundaryValueProblem
{
public:
    // Constructor
        BoundaryValueProblem();                                                     // Defines default values for tolerance and logic when an instance of class BoundaryValueProblem is created

    // Functions
        void readUserInput();                                                       // (Placeholder) Reads the users input from a text file 
        void initialSolution(Mesh*, Residual*);                                     // Using the initial guess values found in the residual class, this function defines the SV at each mesh location using linear distribution scheme
            void setFlags();                                                        // (Placeholder) for future
            void setDependentVariableLimits();                                      // (Placeholder) for future
            void setTolerance();                                                    // (Placeholder) for future
        void performNewtonIteration(Mesh*, Residual*, Jacobian*);                   // Function that performs the MDNM algorithm. Calls other functions when needed
            void calcCorrectionVector(Mesh*, Residual*, Jacobian*);                 // Calculates the correction vector using the currentSV
            void calcNextSV(Mesh*, Residual*, Jacobian*);                           // Calculates what the next SV is from the correction vector
                void checkSVTrustRegion(MatrixXd tempSV);                           // Function that determines if all dependednt variables of the calculated SV are within the trust region
                void checkLookAhead(MatrixXd tempSV, Mesh*, Residual*, Jacobian*);  // Function that determines if the next correction vector produced from the next SV is leading the algorithm in the proper direction
            void checkSolutionTolerance();                                          // After calcNextSV accepts the new SV, this function determines if the solution is within the overall tolerance for the problem
        void saveResults();                                                         // (Placeholder) Function that saves all the desired results into a file (.txt/.csv?)
        // Error handling function????

        // -------- Might move these functions to a new class (helper class) -------- //
        void printInt(int theIntValue); 
        void printDouble(double theIntValue);
        void printMatrix(MatrixXd theMatrix);
    
    // Variables
        bool foundSolution;                                                         // Logic variable used to stop/repeat the MDNM
        bool SVWithinTrustRegion;                                                   // Logic variable used to accept or deny the tempSV
        bool normIsSmaller;                                                         // Logic variable used to accept or deny the tempSV
        bool foundNextSV;                                                           // Logic variable set to TRUE when calcNextSV accepts 

        MatrixXd currentSV;                                                         // Current solution vector
        MatrixXd tempSV;                                                            // Temporary solution vector 
        MatrixXd nextSV;                                                            // Next solution vector (The accepted tempSV from calcNextSV)
        MatrixXd currentCorrectionVector;                                           // Current correction vector
        MatrixXd nextCorrectionVector;                                              // Next correction vector

        double lambda;                                                              // Damping factor
        double absTol;                                                              // Absolute tolerance for the solution
        double relTol;                                                              // Relative tolerance for the solution
        double currentNorm, tempNorm, nextNorm;                                     // Current, temporary, and next norm of the correction vector
};

#endif