
#include <iostream>
#include <cstdio>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <cmath>
#include <fstream>


using namespace std;

gsl_complex funkcja(gsl_complex z){
    gsl_complex z2 = gsl_complex_mul(z,z);
    gsl_complex z3 = gsl_complex_mul(z2,z);
    gsl_complex wynik = gsl_complex_add_real(z3,-1);

    return wynik;
}

gsl_complex pochodna(gsl_complex z){

    gsl_complex z2 =gsl_complex_mul(z,z);
    gsl_complex wynik = gsl_complex_mul_real(z2,3);
    return wynik;
}




bool double_equals(double a, double b, double epsilon = 0.000001)
{
    return std::abs(a - b) < epsilon;
}




int main() {

    ofstream fout;
    fout.open("wynik.txt");
    gsl_complex z0;
    double epsilon = 0.000000001;
    int licznik=0;

    for(double i=-1;i<=1 ;i=i+0.01) {
        if(i == 0)i=i+0.01;
        for(double j=-1;j<=1;j=j+0.01) {
            if(j == 0)j=j+0.01;
            z0 =gsl_complex_rect(i,j);
            gsl_complex z1 = z0;
            while (abs(funkcja(z1).dat[0]) > epsilon && abs(funkcja(z1).dat[1]) > epsilon) {
                z1 = gsl_complex_sub(z0, gsl_complex_div(funkcja(z0), pochodna(z0)));
                z0 = z1;
            }
            if(double_equals(z0.dat[0],1))licznik = 1;
            else if(double_equals(z0.dat[0],-0.5) && z0.dat[1] > 0)licznik = 2;
            else if(double_equals(z0.dat[0],-0.5) && z0.dat[1] < 0)licznik = 3;
            fout << i << "  " << j << "  " << licznik << "\r" << endl;
            licznik =0;
        }
    }
    fout.close();
}







