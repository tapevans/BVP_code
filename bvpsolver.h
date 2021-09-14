
/*
This is the class for BVP solver.
*/

// Include files


class bvpGrid;            // Friend class

// Class bvpSolver
class bvpSolver
{
public:

    // Constructor and destructor functions
    bvpSolver(int);
    virtual ~bvpSolver();

    //private:

    // All functions must go here
    int solve();


    // All member variables must be listed here
    int m_nv;


};
