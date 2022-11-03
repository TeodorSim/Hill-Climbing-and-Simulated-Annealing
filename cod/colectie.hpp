//
//  colectie.hpp
//  tema1
//
//  Created by Simionescu Nicoleta on 29.10.2022.
//

#ifndef colectie_hpp
#define colectie_hpp

#include <stdio.h>
#include <iostream>

#include <vector>
#include <random>
#include <string>
 
#include "functii.hpp"
using namespace std;
class colectie: public functie{
    double minim, maxim;//margini
    int precizie; //precizie
    unsigned int dimensiune; //dimensiune
    int lungime; //lungime candidat
    string evaluation;//metoda folosita: HCL-First/HCL-Best/HCL-Worst
    string functionUsed;//functie gen deJong, etc..
    clock_t start, stop;//calcularea timpilor
    double minimClasa=10000, maxiClasa=-10000; //minim/maxim global
public:
    //constructor-destructor-setter-getter
    colectie();
    ~colectie();
    
    void setParameters(double maxim, double minim, int precizie, unsigned int dimensiune);
    void showParameters();
    void setFunctionUsed(string functionToBeCalled);
    void setMethodUsed(string evaluation);
    
    //atac:
    double candidat(vector<bool> candidat, int begin, int end);
    vector<double> transform(vector<bool> &bitToBeTransformed);
    double hillClimbingBest(vector<bool> &bit);
    double hillClimbingFirst(vector<bool> &bit);
    double hillClimbingWorst(vector<bool> &bit);
    void calculate();
    
    //iterate:
    //parcurgere_best == iteratedHillClimbingBest
    void parcurgere_best(clock_t start);
    void parcurgere_first(clock_t start);
    void parcurgere_worst(clock_t start);
    
    //vector<double> operator=(vec);
};
#endif /* colectie_hpp */
