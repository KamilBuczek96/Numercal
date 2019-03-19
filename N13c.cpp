#include <iostream>
#include <cmath>
#include <fstream>
#include <gsl/gsl_spline.h>


using namespace std;
const int N=11;
const double start=-5;
const double koniec=5;


double function1(double x){
    return (1/((x*x)+1));
}

double function2(double x){
    return exp(-(x*x));
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

    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_cspline, N);
    gsl_spline_init (spline, tab_x, tab_y, N);

    ofstream fout;
    fout.open("plik.txt");


    for(int i=start;i<=koniec;i++){
        fout<<i<<"  "<<gsl_spline_eval(spline,i,acc)<<" "<<function1(i)<<endl;
    }


    fout.close();

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);

    return 0;
}







