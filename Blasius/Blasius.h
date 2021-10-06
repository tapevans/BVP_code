/*
Blasius class
*/

using namespace std;
#include<vector>

class Blasius
{
    // Constructor
    

public:
    // Functions
    void residual();                        // Residual function
    void initialMesh();                     // Initial mesh
    void initialSolution();                 // Initial guess
    std::vector<double> matrix2Vector(std::vector<std::vector<double>>);
    std::vector<std::vector<double>> vector2Matrix(std::vector<double>);
    

    // Variables

public:
    int nVariables;                                 // Number of dependent variables
    std::vector<double> f, g, T;            // Vectors for dependent variable f, g and T
    std::vector<std::vector<double>> depM;
    std::vector<std::vector<double>> resM;
    std::vector<double> depV;
    std::vector<double> resV;


    // Mesh
    std::vector<double> x;                  // Vector of mesh coordinates
    std::vector<double> dx;                 // Vector for delta(x)
    int jPoints;                           // Number of grid points

    // Properties
    double Pr;                              // Prandtl number

    // Offsets for dependent variables
    int Nf = 0;
    int Ng = 1; 
    int NT = 2;





};