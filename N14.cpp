#include <iostream>
#include <cmath>
#include <cstdio>


using namespace std;

const double pi = 3.14159265359;

double f(double x){

    return exp(cos(x)*cos(x));

}


double metoda_trapezow(double start, double end, int N){
    double h , s1 , s2, I;
    double suma = 0;
    double xn;
    int licznik= 0;

    for(int i=0;i<N;i++){
        if(i == 0){
            h = end - start;
            s1 = f(start) + f(end);
            s2 = 0;
            I = 0.5*h*(s1 + 2*s2) ;
        }
        else{
            h = h/2;
            xn = start + h;
            licznik++;

            while(xn < end){
                suma = suma + f(xn);
                licznik++;
                xn = start + (2*licznik + 1)*h;
            }
            s2 = s2 + suma;
            I = 0.5*h*(s1 + 2*s2);
        }
    }
    return I;

}



double metoda_simpsona(double start, double end, int N){
    double h , s1 , s2, s3,  I;
    double suma = 0;
    double xn;
    int licznik= 0;

    for(int i=0;i<N;i++){
        if(i == 0){
            h = (end - start)/2;
            s1 = f(start) + f(end);
            s2 = f(start + h);
            s3 = 0;
            I = (1/3.0)*h*(s1 + 4*s2 + 2*s3) ;
        }
        else{
            h = h/2;
            xn = start + h;
            licznik++;
            s3= s3 + s2;

            while(xn < end){
                suma = suma + f(xn);
                licznik++;
                xn = start + (2*licznik + 1)*h;
            }
            s2 = suma;
            I = (1/3.0)*h*(s1 + 4*s2 + 2*s3) ;
        }
    }
    return I;

}

int main() {


    printf("Całka metoda trapezow wynosi: %.6f \n",metoda_trapezow(0,pi,25));
    printf("Całka metoda simpsona wynosi: %.6f\n",metoda_simpsona(0,pi,27));

    return 0;
}







