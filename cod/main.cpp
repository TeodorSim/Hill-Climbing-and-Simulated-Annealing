//
//  main.cpp
//  tema1
//
//  Created by Simionescu Nicoleta on 29.10.2022.
//

#include <iostream>
#include "colectie.hpp"
#include "functii.hpp"
#include "simAln.hpp"
#include <string>
#define PI 3.14159265
//#include "colectie.cpp"
using namespace std;

int main() {
    srand((unsigned int)clock());
    
    /* alegerea functiei folosite */
    string usingF="deJong";
    //string usingF="schwefel";
    //string usingF="rastrigin";
    //string usingF="michalewicz";
    
    /* alegerea metodei in HCL: HCL-First/HCL-Best/HCL-Worst*/
    string method="best improvment";
    //string method="first improvment";
    //string method="worst improvment";
    
    bool SA=false;//if true, SA will be used. Otherwise, HCL will be used;
    //To change
    //SA=!SA;
    unsigned int dimensiune=30;
    //setParameters(maxim, minim, precizie, dimensiune);
    if(SA){
        simAln b;
        b.setFunctionUsed(usingF);
        if(usingF=="deJong")
            b.setParameters(5.12, -5.12, 5, dimensiune);
        else if(usingF=="schwefel")
            b.setParameters(500, -500, 5, dimensiune);
        else if(usingF=="rastrigin")
            b.setParameters(5.12, -5.12, 5, dimensiune);
        else if(usingF=="michalewicz")
            b.setParameters(PI, 0, 5, dimensiune);
        //b.showParameters();
        b.calculate();
    }
    else{
        colectie a;
        a.setFunctionUsed(usingF);
        a.setMethodUsed(method);
        if(usingF=="deJong")
            a.setParameters(5.12, -5.12, 5, dimensiune);
        else if(usingF=="schwefel")
            a.setParameters(500, -500, 5, dimensiune);
        else if(usingF=="rastrigin")
            a.setParameters(5.12, -5.12, 5, dimensiune);
        else if(usingF=="michalewicz")
            a.setParameters(PI, 0, 5, dimensiune);
        //a.showParameters();
        a.calculate();
    }
    cout<<"\n";
    cout<<usingF<<" este functia folosita pentru minim.";
    
    
    return 0;
}
