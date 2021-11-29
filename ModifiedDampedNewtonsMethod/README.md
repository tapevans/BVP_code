# Boundary Value Solver Code (Package?)
A boundary value solver using Modified Damped Newton's Method for stiff numerical problems

## Descriptions of Source Files
- `mainBVP.cpp` 
    - controls the flow of the algorithm
- `Mesh.cpp` 
    - Defines the class Mesh
    - contains all the variables and functions needed for meshing operations
- `Residual.cpp` 
    - Defines the class Residual
    - contains the user defined residual function. This code currently solves the Blasius problem but for any new problem, this file must be modified.
- `Jacobian.cpp` 
    - Defines the class Jacobian
    - contains all the variables and functions needed for calculating the jacobian
- `BoundaryValueProblem.cpp`
    - Defines the class BoundaryValueProblem
    - Implements the Modified Damped Newton's Method to solve a boundary value problem

## Needed Libraries
- Eigen
    - To run this solver, the library Eigen must be installed and its path included in the compiler. 
    - [Download Eigen Here](http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)

## Current Projects
- Update Jacobian calcuation to take advantage of banded structure
- Implement mesh refinement
- Implement an input file
- Implement Cantera connection
- Implement trust region checking

## Future Development
- Update Jacobian to handle multi-zone banded structure
- Example Problems