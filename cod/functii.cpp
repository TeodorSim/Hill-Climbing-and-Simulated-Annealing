//
//  functii.cpp
//  tema2
//
//  Created by Simionescu Nicoleta on 30.10.2022.
//

#include "functii.hpp"
#define PI 3.14159265358979323846
#define M 10
double functie::functionToUse(string &functionUsed, vector<double> &v){
    if(functionUsed=="deJong"){
        return deJong(v);
    }
    else if(functionUsed=="schwefel"){
        return schwefel(v);
    }
    else if(functionUsed=="rastrigin"){
        return rastrigin(v);
    }
    else if(functionUsed=="michalewicz")
        return michalewicz(v);
    printf("\n eroare in functionToUse.");
    exit(3);
}
double functie::deJong(vector<double> &v){
    double sum = 0;
    for(auto i:v)
        sum+=i*i;
    return sum;
}
double functie::schwefel(vector<double> &v){
    double result = 0;
        for (double d : v) {
            result += (-1 * d * sin(sqrt(abs(d))));
        }
        return result;
}
double functie::rastrigin(vector<double> &v){
    double result = 10 * v.size();
        for (double d : v) {
            result += ((d * d) - (10 * cos(2 * PI * d)));
        }
        return result;
}
double functie::michalewicz(vector<double> &v){
    double result = 0;
    for (int i = 1; i <= v.size(); ++i) {
        result += (sin(v[i - 1]) * pow(sin((i *v[i - 1] * v[i - 1]) / PI), M * 2));
    }
    result *= -1;
    return result;
}
