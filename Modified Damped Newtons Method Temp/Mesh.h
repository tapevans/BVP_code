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


    // Variables
        std::vector<double> x;
        std::vector<double> xMinus;
        std::vector<double> xPositive;
        
        int jPoints;
        double L;

        bool meshIsRefined = true; // Change this later when mesh refinement function is implemented
};