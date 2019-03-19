#include <iostream>
#include <cmath>

using namespace std;
const int N=3;


double * Relaxation(double matrix[][N], const double vector_b[N], double *start_vector,double gamma){
    //utworzenie wektora początkowego
    double temp[N];
    //zmienna okreslajaca do jakiej dokladnosci prowadzic obliczenia
    double epsilon=0.0000000001;
    // roznica=epsilon+1 zeby mozna było wystartować pętle
    double roznica=epsilon+1;
    //liczba iteracji do uzyskania wynikow
    int liczba_iteracji=0;


    while(roznica>epsilon){
        ++liczba_iteracji;
        //wyliczenia kolejnych iteracji
        temp[0]=start_vector[0]+gamma*(vector_b[0]-(matrix[0][0]*start_vector[0]+matrix[0][1]*start_vector[1]));
        temp[1]=start_vector[1]+gamma*(vector_b[1]-(matrix[1][0]*start_vector[0]+matrix[1][1]*start_vector[1]+matrix[1][2]*start_vector[2]));
        temp[2]=start_vector[2]+gamma*(vector_b[2]-(matrix[2][1]*start_vector[1]+matrix[2][2]*start_vector[2]));

        //okreslenie roznicy pomiedzy najnowsza a starszą iteracją
        roznica=abs(start_vector[0]-temp[0]);
        for(int i=0;i<N;++i){start_vector[i]=temp[i];}
    }
    printf("Liczba iteracji metoda relaksacyjna : %d \n",liczba_iteracji);
    printf("Wyliczony wektor to: %.10f, %.10f, %.10f \n",temp[0],temp[1],temp[2]);
}

double * Jacobiego(double matrix[][N], const double vector_b[N], double *start_vector){
    //utworzenie wektora początkowego
    double temp[N];
    //zmienna okreslajaca do jakiej dokladnosci prowadzic obliczenia
    double epsilon=0.0000000001;
    // roznica=epsilon+1 zeby mozna było wystartować pętle
    double roznica=epsilon+1;
    //liczba iteracji do uzyskania wynikow
    int liczba_iteracji=0;


    while(roznica>epsilon){
        ++liczba_iteracji;
        //wyliczenia kolejnych iteracji
        temp[0]=(vector_b[0]+start_vector[1])/matrix[0][0];
        temp[1]=(vector_b[1]+start_vector[0]+start_vector[2])/matrix[1][1];
        temp[2]=(vector_b[2]+start_vector[1])/matrix[2][2];
        //okreslenie roznicy pomiedzy najnowsza a starszą iteracją
        roznica=abs(temp[0]-start_vector[0]);
        for(int i=0;i<N;++i){start_vector[i]=temp[i];}
    }
    printf("Liczba iteracji metoda Jacobiego: %d \n",liczba_iteracji);
    printf("Wyliczony wektor to: %.10f, %.10f, %.10f \n",temp[0],temp[1],temp[2]);
}

double * GS(double matrix[][N], const double vector_b[N], double *start_vector){
    //utworzenie wektora początkowego {0,0,0}
    double temp[N];
    //zmienna okreslajaca do jakiej dokladnosci prowadzic obliczenia
    double epsilon=0.0000000001;
    // roznica=epsilon+1 zeby mozna było wystartować pętle
    double roznica=epsilon+1;
    //liczba iteracji do uzyskania wynikow
    int liczba_iteracji=0;


    while(roznica>epsilon){
        ++liczba_iteracji;
        //wyliczenia kolejnych iteracji
        temp[0]=(vector_b[0]+start_vector[1])/matrix[0][0];
        temp[1]=(vector_b[1]+temp[0]+start_vector[2])/matrix[1][1];
        temp[2]=(vector_b[2]+temp[1])/matrix[2][2];
        //okreslenie roznicy pomiedzy najnowsza a starszą iteracją
        roznica=abs(temp[0]-start_vector[0]);
        //skopiowanie najnowszej ieracji do tablicy temp
        for(int i=0;i<N;++i){start_vector[i]=temp[i];}
    }
    printf("Liczba iteracji metoda GS : %d \n",liczba_iteracji);
    printf("Wyliczony wektor to: %.10f, %.10f, %.10f \n",temp[0],temp[1],temp[2]);
}

double * SOV(double matrix[][N], const double vector_b[N], double *start_vector,double w){
    //utworzenie wektora początkowego {0,0,0}
    double temp[N]={start_vector[0],start_vector[1],start_vector[2]};

    //zmienna okreslajaca do jakiej dokladnosci prowadzic obliczenia
    double epsilon=0.0000000001;
    // roznica=epsilon+1 zeby mozna było wystartować pętle
    double roznica=epsilon+1;
    //liczba iteracji do uzyskania wynikow
    int liczba_iteracji=0;

    while(roznica>epsilon){
        ++liczba_iteracji;

        temp[0]=(1-w)*start_vector[0]+(w/matrix[0][0])*(vector_b[0]-(matrix[0][1]*start_vector[1]+matrix[0][2]*start_vector[2]));
        temp[1]=(1-w)*start_vector[1]+(w/matrix[1][1])*(vector_b[1]-matrix[1][0]*temp[0]-matrix[1][2]*start_vector[2]);
        temp[2]=(1-w)*start_vector[2]+(w/matrix[2][2])*(vector_b[2]-(matrix[2][0]*temp[0]+matrix[2][1]*temp[1]));

        //okreslenie roznicy pomiedzy najnowsza a starszą iteracją
        roznica=abs(temp[0]-start_vector[0]);
        for(int i=0;i<N;++i){start_vector[i]=temp[i];}
    }
    printf("Liczba iteracji metoda SOV : %d \n",liczba_iteracji);
    printf("Wyliczony wektor to: %.10f, %.10f, %.10f \n",temp[0],temp[1],temp[2]);
}




int main() {

    double macierz[N][N]={{4,-1,0},
                          {-1,4,-1},
                          {0,-1,4}};

    double wektor[N]={2,6,2};
    double start1[N]={0};
    double start2[N]={0};
    double start3[N]={0};
    double start4[N]={0};

    Relaxation(macierz,wektor,start1,0.252);
   Jacobiego(macierz,wektor,start2);
    GS(macierz,wektor,start3);
   SOV(macierz,wektor,start4,1.04);


}



