/*
Mesh class
*/

using namespace std;
#include <vector>

class Mesh
{
    public:
    // Functions
        void initializeMesh();
        void refineMesh();
        void calculateSurfaceLocation();
        void checkFirstOrderTol(); // This names should be changed to better represent the check
        void checkSecondOrderTol(); // This names should be changed to better represent the check


    // Variables
        std::vector<double> x;
        std::vector<double> xMinus;
        std::vector<double> xPositive;
        
        int jPoints;
        double L;

        bool meshIsRefined;
};