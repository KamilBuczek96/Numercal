#include <iostream>
#include <cmath>
#include <fstream>



using namespace std;
const int N=11;
const double start=-5;
const double koniec=5;

const double h=10/(N-1);
const double pi=3.14159265359;

double function1(double x){
    return (1/((x*x)+1));
}

double function2(double x){
    return exp(-(x*x));
}

double xn(int n){
    return -5+h*n;
}

double sinc(int n,double x){


    double p_iloraz_h=pi/h;
    double licznik=0;
    double mianownik=0;
    
    licznik=sin(p_iloraz_h*(x-xn(n)));
    mianownik=p_iloraz_h*(x-xn(n));
    if(mianownik==0)return 1;
    return licznik/mianownik;
}


double f(double x){

    double suma=0;

    for(int i=0;i<N;i++){
        suma=suma+function1(xn(i))*sinc(i,x);
    }
    return suma;
}


int main() {


    ofstream fout;
    fout.open("plik.txt");

    for(int i=start;i<=koniec;i++){
        fout<<i<<"  "<<f(i)<<" "<<function1(i)<<endl;
    }

    fout.close();
    return 0;
}







