#include <iostream>
#include <Eigen/Eigen>
// Main code to test the Eigen library

//-I C:\Users\tyevans.ADIT\Desktop\toolsFolder\eigen3_3_9
    // This is the location where I extracted the Eigen library
    // I downloaded this library from: http://eigen.tuxfamily.org/index.php?title=Main_Page#Download

//g++ -o target_name file_name: Compiles and links file_name and generates executable target file with target_name

// Had to type this in the command line to link the two .cpp files
//g++ -I C:\Users\tyevans.ADIT\Desktop\toolsFolder\eigen3_3_9 main.cpp -o TestEigen

//Used .\TestEigen.exe to actually run the executable in the terminal window

using namespace std;
using namespace Eigen;

int main ()
{
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << "\nm is :" << std::endl;
    std::cout << m << std::endl;

    VectorXd v(2);
    v(0) = 1.5;
    v(1) = 3;

    std::cout << "\nv is :" << std::endl;
    std::cout << v << std::endl;

    cout << "\nm * v =" << endl << m * v << endl; // The answer I get from Matlab is [1.5 ; 8.25]

    //std::cout << "\nNow I am going to reshape m to a 1x4 :" << m.resize(1,4) <<  std::endl;

    std::cout << "\nTrying to access only a column or only a row\n";
    std::cout << "\n The first  column of m is :\n" << m.block(0,0,2,1) << std::endl;
    std::cout << "\n The second column of m is :\n" << m.block(0,1,2,1) << std::endl;
    std::cout << "\n The first  row    of m is :\n" << m.block(0,0,1,2) << std::endl;
    std::cout << "\n The second row    of m is :\n" << m.block(1,0,1,2) << std::endl;

    std::cout << "\nTrying to access only a column or only a row using a different method\n";
    std::cout << "\n The first  column of m is :\n" << m.col(0) << std::endl;
    std::cout << "\n The second column of m is :\n" << m.col(1) << std::endl;
    std::cout << "\n The first  row    of m is :\n" << m.row(0) << std::endl;
    std::cout << "\n The second row    of m is :\n" << m.row(1) << std::endl;

    std::cout << "\nTrying to add row vectors\n";
    std::cout << "\n The first  row plus the second row of m is :\n" << m.row(0)+m.row(1) << std::endl;

    // Want to figure out how to pull out or push in an entire column or vector https://eigen.tuxfamily.org/dox/group__TutorialBlockOperations.html 
    // Want to check the operation of adding and subtracting
    // There is a reshape function but I need to figure out which types of matrix it works for https://eigen.tuxfamily.org/dox/group__TutorialReshape.html (Might not be in the version I am using)


    return 0;
}

