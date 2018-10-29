#include <iostream>
#include <fstream>

using namespace std;
const int N=1000;
const double h=1.0/N;
void thomas_method(double *a, double * b, double *c, double *d, double *x, int N){
    double temp=0.0;
    for (int i=1;i<N;i++){
        temp=a[i]/b[i-1];
        a[i]=0.0;
        b[i]=b[i]-temp*c[i-1];
        d[i]=d[i]-temp*d[i-1];
    }
    x[N-1]=d[N-1]/b[N-1];

    for(int i =N-2;i>=0;i--){
        x[i]=(d[i]-c[i]*x[i+1])/b[i];
    }
}

int main() {

    double a[N];
    double b[N];
    double c[N];
    double f[N];
    double y[N];

    for(int i=0;i<N;i++){
        a[i]=1/(h*h);
        b[i]=-(2/(h*h));
        c[i]=a[i];
        f[i]=0;
    }
    b[0]=b[N-1]=f[N-1]=1;
    c[0]=a[N-1]=0;

    thomas_method(a,b,c,f,y,N);
    ofstream fout;
    fout.open(R"(C:\Users\bucka\Desktop\plik.txt)");
    fout.precision(10);

    //zapis wynikow do pliku
    for(int i=0;i<N;++i){
        fout<<i*h<<" "<<y[i]<<"\r"<<std::endl;
    }

    //zamkniecie strumienia
    fout.close();
}



