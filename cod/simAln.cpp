//
//  simAln.cpp
//  tema2
//
//  Created by Simionescu Nicoleta on 30.10.2022.
//

#include "simAln.hpp"
#include "functii.hpp"
#define ITERATII 1000

simAln::simAln(){
    minim=-500;
    maxim=500;
    precizie=5;
}
simAln::~simAln(){
    
}
void simAln::setParameters(double maxim, double minim, int precizie, unsigned int dimensiune){
    this->maxim=maxim;
    this->minim=minim;
    this->precizie=precizie;
    this->dimensiune=dimensiune;
    lungime=ceil(log((maxim-minim)*pow(10, precizie)))/log(2); //calcul lungime in functie de date
}
void simAln::showParameters(){
    printf("\nlungimea e: %d, precizia e: %d", lungime, precizie);
}
void simAln::setFunctionUsed(string functionToBeCalled){
    bool dateOk=false;
    if(functionToBeCalled=="deJong" ||
       functionToBeCalled=="schwefel" ||
       functionToBeCalled=="rastrigin" ||
       functionToBeCalled=="michalewicz"){
        dateOk=true;
        functionUsed=functionToBeCalled;
    }
    if(!dateOk){
        printf("\nBREAK!Functia introdusa nu este una din functiile disponibile.");
        exit(2);
    }
}

double simAln::candidat(vector<bool> &candidat, int begin, int end){
    double rezultat=0;
    while(begin<end){
        rezultat*=2;
        rezultat+=candidat[begin++];
    }
    rezultat/=(pow(2,lungime)-1);
    return rezultat*(maxim-minim)+minim;
}
vector<double> simAln::transform(vector<bool> &bitToBeTransformed){
    //printf("\nsunt in transform");
    vector<double> rezultat;
    //parcurgem vectorul cu toate elementele si
    //pentru fiecare candidat cu lungimea 'lungime' ii calculam valoare din
    //numar in baza 2
    //in numar zecimal
    //printf("\nValorile candidatiilor: \n");
    for(int i=0; i<dimensiune; i++){
        /*
        int iBit=i*lungime;
        int nBit=iBit+lungime;
        unsigned long bit=0;
        for(int j=iBit; j<nBit; j++){
            bit *= 2;
            bit += bitToBeTransformed[j];
        }
        double x=bit/(pow(2, lungime)-1);
        x=x*(maxim-minim) + minim;
        //printf("lungime: %d, x: %f, bit: %lu\n", lungime, x, bit);
         
        */
        double x=candidat(bitToBeTransformed, i*lungime, i*lungime+lungime);
        //cout<<x<<", ";
         
        rezultat.push_back(x);
    }
    //printf("\n");
    return rezultat;
}

void simAln::calculate(){
    start=clock();
    printf("Starting Simulated Annealing for dimension: %d and precision: %d", dimensiune, precizie);
    for(int i=0; i<30; i++){
        simulatedAnnealing();
        printf("\nAm terminat iteratia: %d pentru dimensiunea: %d", i, dimensiune);
    }
    //-------------------------------
    stop=clock();
    printf("\nMinimul pe functie este: %.10f\nMaximul pe functie este: %.10f", minimClasa, maxiClasa);
    cout<<functionUsed<<" a finalizatat SA ";
    printf("in secundele: %f", (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC)));
}

//functie:
void simAln::simulatedAnnealing(){
    clock_t start1, stop1;
    start1=clock();
    vector<bool> bits;
    srand((unsigned int)clock());
    for(int i=0;i<dimensiune*lungime; i++){
        bits.push_back(rand()%2);
    }
    vector<double> elementeTotale=transform(bits);
    //double min=deJong(elementeTotale);
    double min= functionToUse(functionUsed, elementeTotale);
    //double min =michalewicz(elementeTotale);
    double temperatura=100;
    do{
        for(int i=0; i<ITERATII; i++){
            int random= rand() % (dimensiune*lungime);
            bits[random]=!bits[random];
            //-----------------------------
            elementeTotale=transform(bits);
            double val=functionToUse(functionUsed, elementeTotale);
            if(val<min){
                min=val;
            }
            else if(((double)(rand() % 10000000) / (double)10000000 < exp(-1 * abs(val - min) / temperatura))){
                min=val;
            }
            else{
                bits[random]=!bits[random];
            }
        }
        temperatura*=0.8765432101;
    }while(temperatura>0.00000001);
    if(minimClasa>min){
        minimClasa=min;
    }
    if(maxiClasa<min){
        maxiClasa=min;
    }
    printf("\nMinimul global este: %.10f", min);
    stop1=clock();
    printf("\nTura a costat: %f secunde.",(double)((double)(stop1 - start1) / (double)CLOCKS_PER_SEC));
}
