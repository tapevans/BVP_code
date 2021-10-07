/*
BVP_Residual
*/

using namespace std;
#include <vector>

class BVP_Residual
{
    public:
    // Functions
        void calculateResidual();

    // Variables
        std::vector<std::vector<double> > resV;
        int nVariables;



};