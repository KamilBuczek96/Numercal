#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <cmath>

using namespace std;
const int N=100;
const double L=10;
const double h=(2*L)/(N-1);
const double cosinus=cos(h)*cos(h);

void pokaz_macierz(gsl_matrix *A) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << gsl_matrix_get(A, i, j);
        }
        cout << endl;
    }
    cout << endl;
}

void pokaz_wektor(gsl_vector *v){
    for(int i=0;i<N;i++){cout<<" "<<gsl_vector_get(v,i)*(1/gsl_vector_get(v,0));}
    cout<<endl;
}

double delta(int n,int m){
    if(n==m)return 1;
    else return 0;
}


void Metoda_Rayleigha(double Matrix[][N],int LP,double * wynik,double * x0, double WW[][N],int liczba_szukanych){
    gsl_matrix *A = gsl_matrix_alloc(N, N);
    gsl_vector *xn = gsl_vector_alloc(N);
    gsl_vector *xn1 = gsl_vector_alloc(N);
    gsl_vector *tempxn = gsl_vector_alloc(N);
    gsl_vector *tempxn1 = gsl_vector_alloc(N);

    gsl_vector *u =gsl_vector_alloc(N);
    gsl_matrix *lampdautu = gsl_matrix_alloc(N,N);
    double skalar;

    double reileight=0;
    double reileight_m=0;
    double reileight_l=0;



    //Kopiowanie tablicy do nowej
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            gsl_matrix_set(A, i, j, Matrix[i][j]);
        }
        gsl_vector_set(xn,i,x0[i]);
    }

    //Tworzenie macierzy odwrotnej
    int s;
    gsl_permutation *p=gsl_permutation_alloc(N);
    gsl_matrix *Aodwr=gsl_matrix_alloc(N,N);
    gsl_matrix_memcpy(Aodwr,A);

    gsl_linalg_LU_decomp(Aodwr,p,&s);
    gsl_linalg_LU_invert(Aodwr,p,A);

    //Wyszukiwanie wartosci

    for(int k=0;k<liczba_szukanych;++k) {
        for (int i = 0; i < LP; ++i) {
            reileight_l = 0;
            reileight_m = 0;

            //Wyliczanie tak jak w Power_Method xn+1=A*xn
            gsl_blas_dgemv(CblasNoTrans, 1.0, A, xn, 0.0, xn1);

            //Użycie Rayleigh Quotient-czy coś takiego
            gsl_vector_memcpy(tempxn, xn);
            gsl_vector_mul(tempxn, tempxn);
            gsl_vector_memcpy(tempxn1, xn1);
            gsl_vector_mul(tempxn1, xn);
            for (int i = 0; i < N; ++i) {
                reileight_l = reileight_l + gsl_vector_get(tempxn1, i);
                reileight_m = reileight_m + gsl_vector_get(tempxn, i);
            }
            reileight = reileight_l / reileight_m;

            //To samo co w Power_Method
            if (LP - 1 != i)gsl_vector_memcpy(xn, xn1);
        }
        wynik[k]=1/reileight;

        //wyznaczanie wektora własnego u
        for (int i = 0; i < N; ++i) {
            gsl_vector_set(u, i, (gsl_vector_get(xn1, i) / gsl_blas_dnrm2(xn1)));
        }
        //pokaz_wektor(u);
        for(int i=0;i<N;i++){
            WW[k][i]=gsl_vector_get(u,i)*(1/gsl_vector_get(u,0));
        }

        //Tworzenie macierz lampda*ut*u oraz A=A-lampda*ut*u
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                gsl_matrix_set(lampdautu, i, j,(gsl_vector_get(u, i)*gsl_vector_get(u,j)));
            }
        }
        skalar=reileight;
        gsl_matrix_scale(lampdautu,skalar);
        gsl_matrix_sub(A,lampdautu);

    }

    gsl_vector_free(u);
    gsl_vector_free(xn1);
    gsl_vector_free(xn);
    gsl_vector_free(tempxn);
    gsl_vector_free(tempxn1);
    gsl_matrix_free(A);
    gsl_matrix_free(lampdautu);
    gsl_matrix_free(Aodwr);
    gsl_permutation_free(p);
}

int main() {

    double Matrix[N][N]={0};
    double wynik_r[N]; //wektor na wartosci własne
    double x0[N]={1,0,0}; //wektor startowy
    double WW[N][N]={0}; //macierz wektorów wlasnych

    double xn[N]={0};
    for(int i=0;i<N;i++){xn[i]=-L+i*h;}

   // cout<<endl<<" N: "<<N<<endl;
    //cout<<" L: "<<L<<endl;
   // cout<<" h: "<<h<<endl;
    //cout<<" cosh^2: "<<cosinus<<endl;


    //cout<<endl<<" Wektor xn: ";
    //for(int i=0;i<N;i++){cout<<" "<<xn[i];}
    //cout<<endl<<endl;

    //cout<<"Wektory własne: "<<endl<<endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Matrix[i][j]=(-delta(i-1,j)/float(h*h))+((2/float(h*h))+4-(6/(cosinus*xn[i])))*delta(i,j)-(delta(i+1,j)/float(h*h));
            //cout << "    " << Matrix[i][j];
        }
      //  cout << endl;
    }
   // cout << endl;

    Metoda_Rayleigha(Matrix,23,wynik_r,x0,WW,4);
    printf("\nWartosci własne macierzy ( Metoda Rayleigha ) to %.8f, %.8f, %8f oraz %.8f: \n",wynik_r[0],wynik_r[1],wynik_r[2],wynik_r[3]);


   // cout<<"Wektory własne: "<<endl<<endl;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N; j++) {
            //cout << "    " << WW[i][j];
        }
       // cout << endl;
    }
    //cout << endl;


    return 0;
}







