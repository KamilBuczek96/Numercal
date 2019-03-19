#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

using namespace std;
const int N=3;


void Metoda_iteracyjna_QR(double Matrix[][N],int LP,double * wynik) {
    gsl_vector *Vector = gsl_vector_alloc(N);
    gsl_matrix *A = gsl_matrix_alloc(N, N);
    gsl_matrix *Q = gsl_matrix_alloc(N, N);
    gsl_matrix *R = gsl_matrix_alloc(N, N);

    //Kopiowanie tablicy do nowej
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            gsl_matrix_set(A, i, j, Matrix[i][j]);
        }
    }

    //Znajdowanie wartsci własnych
    for(int i=0;i<LP;++i) {
        gsl_linalg_QR_decomp(A, Vector);
        gsl_linalg_QR_unpack(A, Vector, Q, R);
        gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1.0,R,Q,0.0,A);
    }

    //Zapisywanie diagonali do wektora wynikowego
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(i==j){
                wynik[i]=gsl_matrix_get(A,i,j);
            }
        }
    }

    gsl_vector_free(Vector);
    gsl_matrix_free(A);
    gsl_matrix_free(Q);
    gsl_matrix_free(R);

}

void Metoda_Power(double Matrix[][N],int LP,double * wynik,double * x0){
    gsl_matrix *A = gsl_matrix_alloc(N, N);
    gsl_vector *xn = gsl_vector_alloc(N);
    gsl_vector *xn1 = gsl_vector_alloc(N);
    gsl_vector *u =gsl_vector_alloc(N);
    gsl_matrix *lampdautu = gsl_matrix_alloc(N,N);
    double skalar;

    //Kopiowanie tablicy do nowej
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            gsl_matrix_set(A, i, j, Matrix[i][j]);
        }
        gsl_vector_set(xn,i,x0[i]);
    }

    for(int k=0;k<N;++k) {
        //xn+1 =A*xn
        for (int i = 0; i < LP; ++i) {
            gsl_blas_dgemv(CblasNoTrans, 1.0, A, xn, 0.0, xn1);
            if (LP - 1 != i)gsl_vector_memcpy(xn, xn1);
        }

        //wyliczenie wartosci własnej
        double lampda = gsl_blas_dnrm2(xn1) / gsl_blas_dnrm2(xn);
        wynik[k] = lampda;

        //wyznaczanie wektora własnego u
        for (int i = 0; i < N; ++i) {
            gsl_vector_set(u, i, (gsl_vector_get(xn1, i) / gsl_blas_dnrm2(xn1)));
        }

        //Tworzenie macierz lampda*ut*u oraz A=A-lampda*ut*u
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                gsl_matrix_set(lampdautu, i, j, (gsl_vector_get(u, i) * gsl_matrix_get(A, k, j)));
            }
        }
        skalar = (1 / gsl_vector_get(u, k));
        gsl_matrix_scale(lampdautu, skalar);
        gsl_matrix_sub(A, lampdautu);

    }
    gsl_vector_free(u);
    gsl_vector_free(xn1);
    gsl_vector_free(xn);
    gsl_matrix_free(A);
    gsl_matrix_free(lampdautu);

}

void Metoda_Rayleigha(double Matrix[][N],int LP,double * wynik,double * x0){
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

    for(int k=0;k<N;++k) {
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
        wynik[k]=reileight;

        //wyznaczanie wektora własnego u
        for (int i = 0; i < N; ++i) {
            gsl_vector_set(u, i, (gsl_vector_get(xn1, i) / gsl_blas_dnrm2(xn1)));
        }

        //Tworzenie macierz lampda*ut*u oraz A=A-lampda*ut*u
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                gsl_matrix_set(lampdautu, i, j,(gsl_vector_get(u, i)*gsl_matrix_get(A,k,j)));
            }
        }
        skalar=(1/gsl_vector_get(u,k));
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
}

int main() {

    double Matrix[N][N]={{1,2,3},{2,4,5},{3,5,-1}};
    double wynik_pm[N];
    double wynik_r[N];
    double wynik_qr[N];
    double x0[N]={1,0,0};
    Metoda_Power(Matrix,40,wynik_pm,x0);
    Metoda_Rayleigha(Matrix,40,wynik_r,x0);
    Metoda_iteracyjna_QR(Matrix,20,wynik_qr);

    printf("\nWartosci własne macierzy ( Metoda QR ) to: %.8f, %.8f, oraz %.8f  \n",wynik_qr[0],wynik_qr[1],wynik_qr[2]);
    printf("Wartosci własne macierzy ( Power Method ) to: %.8f, %.8f oraz %.8f \n",wynik_pm[0],wynik_pm[1],wynik_pm[2]);
    printf("Wartosci własne macierzy ( Metoda Rayleigha ) to %.8f, %.8f oraz %.8f: \n",wynik_r[0],wynik_r[1],wynik_r[2]);
    return 0;
}




