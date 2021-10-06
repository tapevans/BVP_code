/*
Jacobian
*/

using namespace std;
#include <vector>
//#ifndef "BVP_Residual.h"
//#define "BVP_Residual.h"
//#endif


class Jacobian
{
// Functions
void calculatePerturbation();
void residual();
void calculateJacobian();


// Variables
std::vector<std::vector<double> > jacM;
std::vector<std::vector<double> > resV;
std::vector<std::vector<double> > resPerV;

};