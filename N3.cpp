#include <iostream>
#include <fstream>

using namespace std;

// rozmiar: rozwiazujemy układ (N+1)*(N+1)
const int N=1000;

void thomas_method(double *a, double * b, double *c, double *d, double *x, int const & N){
    double temp=0.0;
    for (int i=1;i<N;++i){
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

    //obliczanie h^2 podstawimy dla wygody pod zmienna o nazwie h
    const double h=0.01*0.01;

    // Ax=f takie rownanie rozwiazujemy
    // a,b,c to diagonale; y to wektor ktory chcemy znalezc, f to wektor wyrazow wolnych
    double a[N+1];
    double b[N+1];
    double c[N+1];
    double f[N+1]={0};
    double y[N+1];

    //stworzenie wektorow u i v
    double u[N+1]={0};
    double v[N+1]={0};

    //stworzenie odpowidnich wektorow a,b,c oraz na podstawie układu rownan z zadania N3
    for(int i=0;i<N+1;++i){
        a[i]=1.0/h;
        b[i]=(-2.0/h)+1;
        c[i]=1.0/h;
    }

    //uzupełniam wektory a,b,c,u,v,f w odpowiednim miejscu
    a[0]=0;
    a[N]=1;
    b[0]=1;
    b[N]=-2;
    c[0]=0;
    c[N]=0;
    u[N]=1;
    v[0]=1;
    f[0]=1;

    //tworzenie wektorow z i q do rozwiazan rownan Az=f oraz Aq=u
    double z[N+1];
    double q[N+1];

    //rozwiazanie rownan Az=f oraz Aq=u
    thomas_method(a,b,c,f,z,N+1);
    thomas_method(a,b,c,u,q,N+1);

    //zmienne do przechowania iloczynu wektorow vtz oraz vtq
    double vtz=0;
    double vtq=0;

    //mnozenia transponowanego v razy t lub z co daje nam dwa skalare
    for(int i=0;i<N+1;++i){
        vtz=vtz+(v[i]*z[i]);
        vtq=vtq+(v[i]*q[i]);
    }

    //operacje na wszyskich liczbach i zapisanie ich do jednej zmiennej dla wygody
    double liczba= vtz/(vtq+1);

    //ostateczne wyliczenie rozwiaza rownania ze wzoru
    for(int i=0;i<N+1;++i) {
        y[i]=z[i]-(liczba*q[i]);
    }
    //otwarcie strumienia
    ofstream fout;
    fout.open(R"(C:\Users\bucka\Desktop\plik.txt)");
    fout.precision(10);

    //zapis wynikow do pliku
    for(int i=0;i<N;++i){
        fout<<i*0.01<<"    "<<y[i]<<"\r"<<std::endl;
    }

    //zamkniecie strumienia
    fout.close();
}



