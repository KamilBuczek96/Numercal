#include <iostream>
#include <fstream>

using namespace std;
const int N=1000;

double odwzorowanie(double k,double x){
        return k*x*(1-x);
}

int main() {

    ofstream fout;
    fout.open("plik.txt");

    double x0=0.1;
    double k;
    double xn;

    /*
    k=0.01;
    xn=odwzorowanie(k,x0);
    while(k<1) {
        fout << k << "  " << xn << endl;
        xn = odwzorowanie(k, xn);
        if(k>0.7) k = k+0.00001;
        else k = k + 0.001;
   }
    */

    /*
    k = 1;
    xn=odwzorowanie(k,x0);
    while(k<3) {
        fout << k << "  " << xn << endl;
        xn = odwzorowanie(k, xn);
        if(k>0.7) k = k+0.00001;
        else k = k + 0.001;
    }
    */

    /*
    k = 3;
    xn=odwzorowanie(k,x0);
    while(k<4) {
        fout << k << "  " << xn << endl;
        xn = odwzorowanie(k, xn);
        if(k>0.7) k = k+0.00001;
        else k = k + 0.001;
    }
    */
    k=0.7;
    int licznik=0;
    xn=odwzorowanie(k,x0);
    while(licznik<N) {
        fout << licznik << "  " << xn << endl;
        xn = odwzorowanie(k, xn);
        licznik++;
    }

    fout.close();
    return 0;
}

