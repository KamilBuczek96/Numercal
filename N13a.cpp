#include <iostream>
#include <cmath>
#include <fstream>


using namespace std;
const int N=21;
const double start=-5;
const double koniec=5;


double function1(double x){
    return (1/((x*x)+1));
}

double function2(double x){
    return exp(-(x*x));
}


double l(int number,double * tab_x, double x){
    double iloczyn=1;

    for(int j=0;j<N;j++){
        if(number!=j){
            iloczyn=iloczyn*((x-tab_x[j])/(tab_x[number]-tab_x[j]));
        }
    }

    return iloczyn;
}

double lagrange_interpolation(double x, double * tab_x ,double * tab_y){
    double suma=0;

    for(int i=0;i<N;i++){
        suma=suma+(l(i,tab_x,x)*tab_y[i]);
    }

    return suma;
}


int main() {

    double dlugosc=fabs(start)+fabs(koniec);
    double przedzial=dlugosc/(N-1);

    //tablice na argumenty i wartosci
    double tab_x[N];
    double tab_y[N];


    for(int i=0;i<N;i++){
        if(i==0)tab_x[i]=start;
        else if(i==N-1)tab_x[i]=koniec;
        else tab_x[i]=start+i*przedzial;
        tab_y[i]=function1(tab_x[i]);

    }

    double max_error=0;
    double error=0;


    ofstream fout;
    fout.open("plik.txt");


    for(int i=-10;i<=10;i++){

        fout<<i<<"  "<<lagrange_interpolation(i,tab_x,tab_y)<<" "<<function1(i)<<endl;
        if(i>=start && i<koniec){
            error=fabs(function1(i)-lagrange_interpolation(i,tab_x,tab_y));
            if( max_error<error)max_error=error;
        }

    }

    printf("Maksymalny blad przyblizenia na przedziale to: %f \n",max_error);

    fout.close();



    return 0;
}







 
