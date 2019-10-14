#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
const int N=101;
const double h=10.0/(N-1);
const double c=3;


void SOR(double **matrix,const double * vector_b, double *start_vector,double w,int N){

    double tem1 = 23
    double temp[N];
    double epsilon=0.0000000001;
    double roznica=epsilon+1;
    int liczba_iteracji=0;
    double suma1=0;
    double suma2=0;

    while(roznica>epsilon){
        ++liczba_iteracji;

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(j<i && matrix[i][j]!=0)suma1=suma1+matrix[i][j]*temp[j];
                if(j>i&& matrix[i][j]!=0)suma2=suma2+matrix[i][j]*start_vector[j];
            }
            temp[i]=(1-w)*start_vector[i]+(w/matrix[i][i])*(vector_b[i]-suma1-suma2);
            suma1=0;
            suma2=0;
        }

        roznica=fabs(start_vector[0]-temp[0]);
        for(int i=0;i<N;++i){start_vector[i]=temp[i];}
    }
    printf("Liczba iteracji metoda SOR : %d \n",liczba_iteracji);
}

int main() {

    //Tworzenie wektora u N^2
    double u[N*N]={0};

    int licznik=0;

    for(int n=0;n<N;++n){
        for(int m=0;m<N;++m){
            if(n == 0 || n == (N-1) || m == (N-1)){u[n*N+m] = 0;}
            else if(m == 0) u[n*N+m] = 1-fabs(h*n-5)/5;
            else if((((h*n-3)*(h*n-3))+((h*m-7)*(h*m-7))) < 0.2) u[n*N+m] = 1;
            else if((((h*n-8)*(h*n-8))+((h*m-7)*(h*m-7))) < 0.2) u[n*N+m] = 2;
            else{
                u[n*N+m]=c;
                licznik++;
            }
        }
    }

    //Tworzenie macierzy A oraz wektora wyrazów wolnych b z wektora u N^2

    double ** A = new double *[licznik];
    for (int i = 0; i < licznik; ++i)
        A[i] = new double [licznik]{0};

    double b[licznik]={0};

    int e=0;
    int f=0;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(u[i*N+j] == c){
                A[e][f+e]=1;
                if(u[(i*N+j)-1]==c){A[e][f+e-1]=(-1.0/4);}
                if(u[(i*N+j)+1]==c){A[e][f+e+1]=(-1.0/4);}
                if(u[(i*N+j)+N]==c){A[e][f+e+(N-2)]=(-1.0/4);}
                if(u[(i*N+j)-N]==c){A[e][f+e-(N-2)]=(-1.0/4);}
                e++;
            }
            else if(u[i*N+j] == 1 || u[i*N+j] == 2 ){
                b[e]=b[e]+u[i*N+j];
            }
            else{
                b[e]=b[e]+u[i*N+j]/4;
            }
        }
    }

    //użycie metody SOR

    double start4[licznik]={0};
    SOR(A,b,start4,1.89,licznik);
    delete [] A;


    //zapis wyników do pliku N^2

    ofstream fout;
    fout.open(R"(C:\Users\bucka\Desktop\plik.txt)");
    fout.precision(10);

    int lp=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(u[i*N+j]== c)u[i*N+j]=start4[lp++];
            fout<<i<<"    "<<j<<"    "<<u[i*N+j]<<"\r"<<std::endl;
        }
    }
    fout.close();
}


