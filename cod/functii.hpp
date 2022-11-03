//
//  functii.hpp
//  tema2
//
//  Created by Simionescu Nicoleta on 30.10.2022.
//

#ifndef functii_hpp
#define functii_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class functie{
public:
    //functiile de calcul:
    double functionToUse(string &functionToBeUsed, vector<double> &v);
    double deJong(vector<double> &v);
    double schwefel(vector<double> &v);
    double rastrigin(vector<double> &v);
    double michalewicz(vector<double> &v);
    virtual void setParameters(double maxim, double minim, int precizie, unsigned int dimensiune)=0;
    virtual void showParameters()=0;
    virtual void setFunctionUsed(string functionToBeCalled)=0;
};
#endif /* functii_hpp */
