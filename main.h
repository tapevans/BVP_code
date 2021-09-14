
/*
This is the main file which gets the user input, calls the boundary value
solver and then post-processes the solution
*/

// Include files
#include<iostream>
#include "bvpSolver.h"

// Functions

int main();
int userInput(std::string filename);
int getResidual();

// Variables
int nv;                         // Number of solution variables

