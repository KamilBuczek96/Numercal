#include <iostream>
#include <cmath>

using namespace std;
const int N=3;

double * Macierz_razy_wektor(double matrix[][N], const double *wektor){
    auto wektor_wynikowy= new double[N];

    wektor_wynikowy[0]=matrix[0][0]*wektor[0]+matrix[0][1]*wektor[1];
    wektor_wynikowy[1]=matrix[1][0]*wektor[0]+matrix[1][1]*wektor[1]+matrix[1][2]*wektor[2];
    wektor_wynikowy[2]=matrix[2][1]*wektor[1]+matrix[2][2]*wektor[2];

    return wektor_wynikowy;
}

double * Gradienty_Sprzezone(double matrix[][N], const double vector_b[N], double *x1,double epsilon){
    //wektor r-połowa na rk a połowa na rk+1 i to samo dla p
    double r[N+N];
    double p[N+N];
    auto  x_wynik=new double[N];
    // wektory o rozmiarach N na skalary alfa i b
    double alfa;
    double beta;
    //Ax1 mnożenie macierz razy wektor
    auto Ax1=Macierz_razy_wektor(matrix,x1);

    for(int i=0;i<N;i++){p[i]=r[i]=vector_b[i]-Ax1[i];}


    double norma=sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
    // cout<<"Norma przed: "<<norma<<endl;
    while(norma>epsilon){
        //obliczenie Apk
        auto Apk=Macierz_razy_wektor(matrix,p);
        //alfa_k
        alfa=(r[0]*r[0]+r[1]*r[1]+r[2]*r[2])/(p[0]*Apk[0]+p[1]*Apk[1]+p[2]*Apk[2]);
        //r_k+1
        for(int i=0;i<N;i++){r[N+i]=r[i]-alfa*Apk[i];}
        //for(int i=0;i<N;i++){cout<<"r+1: "<<r[N+1]<<endl;}
        //usuniecie Apk z pamieci
        delete [] Apk;
        //beta_k
        beta=(r[N+0]*r[N+0]+r[N+1]*r[N+1]+r[N+2]*r[N+2])/(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
        //p_k+1
        for(int i=0;i<N;i++){p[N+i]=r[N+i]+beta*p[i];}
        //x_k+1
        for(int i=0;i<N;i++){x_wynik[i]=x1[i]+alfa*p[i];}

        //zamiany w p i r oraz x
        for(int i=0;i<N;i++){
            r[i]=r[i+N];
            p[i]=p[i+N];
            x1[i]=x_wynik[i];
        }


        //update normy
        norma=sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
        //cout<<"Po r+1: "<<norma<<endl;
    }

    //usuniecie dynamicznie alokowanej pamieci
    delete [] Ax1;
    return x_wynik;
}




int main() {

    double macierz[N][N]={{4,-1,0},
                          {-1,4,-1},
                          {0,-1,4}};

    double wektor[N]={2,6,2};
    double x1[N]={0};

    auto wynik=Gradienty_Sprzezone(macierz,wektor,x1,0.5);

    for(int i=0;i<N;i++){cout<<wynik[i]<<endl;}

    delete [] wynik;

    //auto wynik=Macierz_razy_wektor(macierz,wektor);
    //for(int i=0;i<N;i++){cout<<wynik[i]<<endl;}


}


