
/*
This is the class for BVP solver.
*/

// Include files


// Class bvpGrid
class bvpGrid
{
public:

    // Constructor and destructor functions
	bvpGrid();
	virtual ~bvpGrid();

    //private:

    // All functions must go here
    int setupGrid();
    int refineGrid();

    // All member variables must be listed here
    int m_points;                       // Number of grid points


};
