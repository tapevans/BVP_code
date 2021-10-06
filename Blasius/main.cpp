#include "Blasius.h"
#include<iostream>
// Main code to solve Blasius problem

int main ()
{
    Blasius test;
    test.initialMesh();

    //Print mesh
    for(int j = 0; j < (test.jPoints); j++)
    {
        //std::cout<<"\n j = "<<j<<"\t x = "<< test.x[j];
    }

    test.initialSolution();
    //Print init solution
    for(int j = 0; j < (test.jPoints); j++)
    {
        for(int n = 0; n < (test.nVariables); n++)
        {
            //std::cout<<"\n j = "<<j<<"\t n = "<<n<<"\t x = "<< test.depM[n][j];
            std::cout<<"\t \t"<< test.depM[n][j];
        }
        cout<<"\n";
    }
    //cout<<test.depM;
    test.residual();
    //Print residual
    cout<<"\n Residual \n";
    for(int j = 0; j < (test.jPoints); j++)
    {
        for(int n = 0; n < (test.nVariables); n++)
        {
            //std::cout<<"\n j = "<<j<<"\t n = "<<n<<"\t x = "<< test.depM[n][j];
            std::cout<<"\t \t"<< test.resM[n][j];
        }
        cout<<"\n";
    }

    return 0;
}