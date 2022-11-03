//
//  simAln.hpp
//  tema2
//
//  Created by Simionescu Nicoleta on 30.10.2022.
//

#ifndef simAln_hpp
#define simAln_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "functii.hpp"
using namespace std;
class simAln: public functie{
    double minim, maxim;//margini
    int precizie; //precizie
    unsigned int dimensiune; //dimensiune
    int lungime; //lungime candidat
    string functionUsed;//functie gen deJong, etc..
    clock_t start, stop;//calcularea timpilor
    double minimClasa=10000, maxiClasa=-10000;
public:
    //constructor-destructor-setter-getter
    simAln();
    ~simAln();
    void setParameters(double maxim, double minim, int precizie, unsigned int dimensiune);
    void showParameters();
    void setFunctionUsed(string functionToBeCalled);
    
    //atac:
    double candidat(vector<bool> &candidat, int begin, int end);
    vector<double> transform(vector<bool> &bitToBeTransformed);
    void calculate();
    
    //functie:
    void simulatedAnnealing();
    
};
#endif /* simAln_hpp */
