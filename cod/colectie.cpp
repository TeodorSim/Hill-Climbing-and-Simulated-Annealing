//
//  colectie.cpp
//  tema1
//
//  Created by Simionescu Nicoleta on 29.10.2022.
//

#include "colectie.hpp"
#include "functii.hpp"
#define PI 3.14159265358979323846
#define M 10
#define ITERATII 1000
colectie::colectie(){
    minim=-500;
    maxim=500;
    precizie=5;
}
colectie::~colectie(){
    
}
void colectie::setParameters(double maxim, double minim, int precizie, unsigned int dimensiune){
    this->maxim=maxim;
    this->minim=minim;
    this->precizie=precizie;
    this->dimensiune=dimensiune;
    lungime=ceil(log((maxim-minim)*pow(10, precizie)))/log(2); //calcul lungime in functie de date
}
void colectie::showParameters(){
    printf("\nlungimea e: %d, precizia e: %d\n", lungime, precizie);
    cout<<"Functia e: "<<functionUsed<<'\n';
}
void colectie::setMethodUsed(string evaluation){
    this->evaluation=evaluation;
}
void colectie::setFunctionUsed(string functionToBeCalled){
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

//atac:
//transform == decode
double colectie::candidat(vector<bool> candidat, int begin, int end){
    double rezultat=0;
    while(begin<end){
        rezultat*=2;
        rezultat+=candidat[begin++];
    }
    rezultat/=(pow(2,lungime)-1);
    return rezultat*(maxim-minim)+minim;
}
vector<double> colectie::transform(vector<bool> &bitToBeTransformed){
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

double colectie::hillClimbingBest(vector<bool> &bit){
    vector<double> elementeTotale=transform(bit);
    double minMare=functionToUse(functionUsed, elementeTotale);
    int k=0;
    bool local=false;
    do{
        bool schimbat=false;
        local=false;
        for(int i=0; i<dimensiune*lungime; i++){
            bit[i]=!bit[i];
            
            elementeTotale=transform(bit);
            double valActual=functionToUse(functionUsed, elementeTotale);
            if(valActual<minMare){
                minMare=valActual;
                schimbat=true;
                k=i;
            }
            bit[i]=!bit[i];
        }
        if(!schimbat){
            local=true;
        }
        else{
            bit[k]=!bit[k];
        }
    }while(!local);
    return minMare;
}
double colectie::hillClimbingFirst(vector<bool> &bit){
    //printf("\nSunt in parcurgere_first");
    vector<double> elementeTotale=transform(bit);
    //api pentru apelarea functiei cerute, gen deJong/etc..
    double minMare=functionToUse(functionUsed, elementeTotale);
    bool local=false;
    do{
        local=false;
        double initial=minMare;
        for(int i=0; i<dimensiune*lungime; i++){
            bit[i]=!bit[i];
            
            elementeTotale=transform(bit);
            //api pentru apelarea functiei cerute, gen deJong/etc..
            double valActual=functionToUse(functionUsed, elementeTotale);
            if(valActual<minMare){
                minMare= valActual;
                //bit[i]=!bit[i];
                //break;
                continue;
            }
            //bit[i]=!bit[i];
        }
        if(minMare==initial){
            local=true;
        }
    }while(!local);
    return minMare;
}
double colectie::hillClimbingWorst(vector<bool> &bit){
    vector<double> elementeTotale=transform(bit);
    double minMare=functionToUse(functionUsed, elementeTotale);
    double minPenultim=INT_MIN;
    int k=0;
    bool local=false;
    do{
        bool schimbat=false;
        local=false;
        for(int i=0; i<dimensiune*lungime; i++){
            bit[i]=!bit[i];
            
            elementeTotale=transform(bit);
            double valActual=functionToUse(functionUsed, elementeTotale);
            if(valActual>minPenultim && minPenultim<minMare){
                minPenultim=valActual;
                schimbat=true;
                k=i;
                //break;
                //continue;
            }
            bit[i]=!bit[i];
        }
        if(!schimbat){
            local=true;
        }
        else{
            bit[k]=!bit[k];
        }
    }while(!local);
    return minPenultim;
}

void colectie::calculate(){
    start=clock();
    
    //-------------------------------
    /*
    string evaluation="best improvment";
    //string evaluation="first improvment";
    //string evaluation="worst improvment";
     */
    if("best improvment"==evaluation){
        int iteratie=1;
        if(dimensiune>5)    iteratie=15;
        printf("\nDimensiune==%d && Metoda de gasire==best improvment", dimensiune);
        for(int i=0; i<30/iteratie; i++){
            parcurgere_best(start);
            printf("\nAm terminat iteratia: %d pentru dimensiunea: %d", i, dimensiune);
        }
    }
    else if("first improvment"==evaluation){
        printf("\nDimensiune==%d && Metoda de gasire==first improvment", dimensiune);
        for(int i=0; i<30; i++){
            parcurgere_first(start);
            printf("\nAm terminat iteratia: %d pentru dimensiunea: %d", i, dimensiune);
        }
    }
    else if("worst improvment"==evaluation){
        printf("\nDimensiune==%d && Metoda de gasire==worst improvment", dimensiune);
        for(int i=0; i<30; i++){
            parcurgere_worst(start);
            printf("\nAm terminat iteratia: %d pentru dimensiunea: %d", i, dimensiune);
        }
    }
    
    //-------------------------------
    stop=clock();
    printf("\nMinimul pe functie este: %.10f\nMaximul pe functie este: %.10f\n", minimClasa, maxiClasa);
    cout<<functionUsed<<" a finalizatat HC"<<evaluation;
    printf("in secundele: %f", (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC)));
}

//iterate:
void colectie::parcurgere_best(clock_t start){
    //printf("\nsunt in parcurgere_best");
    clock_t start1, stop1;
    start1=clock(); // timpul in iteratia asta
    srand((unsigned int)(start1));
    int Lungime= lungime*dimensiune;
    double minimTotal = ITERATII;
    int xIteratie=0;
    vector<bool> bit;
    vector<double> bitsMin;
    //temperatura maxim 10
    int iteratie=1;
    if(dimensiune>5)
        iteratie=1;
    for(int t=0; t<ITERATII/iteratie; t++){
        bit.clear();
        for(int i=0;i<Lungime; i++){
            bit.push_back(rand()%2);
        }
        double valoareActuala = hillClimbingBest(bit);
        if(valoareActuala<minimTotal){
            minimTotal=valoareActuala;
            xIteratie=t;
            bitsMin=transform(bit);
        }
    }
    printf("\n---------\n");
    printf("\nMinimul global este: %f gasit pozitia: %d cu numarul de iteratii: %d.", minimTotal, xIteratie, ITERATII);
    if(minimTotal<minimClasa)
        minimClasa=minimTotal;
    if(minimTotal>maxiClasa)
        maxiClasa=minimTotal;
    stop1=clock();
    printf("\nPentru dimensiunea %d cu HCB executarea a durat: ", dimensiune);
    cout<<(double)((double)(stop1-start1)/(double)(CLOCKS_PER_SEC))<<" seconds.";
    
}
void colectie::parcurgere_first(clock_t start){
    clock_t start1, stop1;
    start1=clock();
    srand((unsigned int)start1);
    int Lungime=lungime*dimensiune;
    double min= ITERATII;
    int kMin=0;
    vector<bool> bits;
    vector<double> bitsMin;
    for(int i=0; i<ITERATII; i++){
        bits.clear();
        for(int j=0; j< Lungime; j++){
            bits.push_back(rand()%2);
        }
        double ax=hillClimbingFirst(bits);
        if(ax<min){
            min=ax;
            kMin=i;
            bitsMin=transform(bits);
        }
    }
    printf("\n---------\n");
    printf("\nMinimul global este: %f gasit pozitia: %d.\n", min, kMin);
    if(minimClasa>min)
        minimClasa=min;
    if(min>maxiClasa)
        maxiClasa=min;
    stop1=clock();
    printf("Parcurgerea a durat: %f secunde.", (double)((double)(stop1 - start1) / (double)CLOCKS_PER_SEC));
}
void colectie::parcurgere_worst(clock_t start){
    //printf("\nsunt in parcurgere_best");
    clock_t start1, stop1;
    start1=clock(); // timpul in iteratia asta
    srand((unsigned int)(start1));
    int Lungime= lungime*dimensiune;
    double minimTotal = ITERATII;
    int xIteratie=0;
    vector<bool> bit;
    vector<double> bitsMin;
    //temperatura maxim 10
    for(int t=0; t<ITERATII; t++){
        bit.clear();
        for(int i=0;i<Lungime; i++){
            bit.push_back(rand()%2);
        }
        double valoareActuala = hillClimbingWorst(bit);
        if(valoareActuala<minimTotal){
            minimTotal=valoareActuala;
            xIteratie=t;
            bitsMin=transform(bit);
        }
    }
    printf("\n---------\n");
    printf("\nMinimul global este: %f gasit pozitia: %d.\n", minimTotal, xIteratie);
    if(minimClasa>minimTotal)
        minimClasa=minimTotal;
    if(minimTotal>maxiClasa)
        maxiClasa=minimTotal;
    stop1=clock();
    printf("Parcurgerea a durat: %f secunde.", (double)((double)(stop1 - start1) / (double)CLOCKS_PER_SEC));
}
