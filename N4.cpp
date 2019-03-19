#include <iostream>
#include <fstream>

using namespace std;

// rozmiar: rozwiazujemy układ (N+1)*(N+1)
const int N=1000;

int main() {

    //obliczanie h^2 podstawimy dla wygody pod zmienna o nazwie h
    const double h=0.01*0.01;

    double a;
    double b;
    double c;
    double y[N+1];

    a=1.0/h;
    b=(-2.0/h)+1;
    c=1.0/h;


    //wyliczenie jawne pierwszych trzech wyrazów po wczesniejszym ustawieniu ostatniego rownania jako drugie
    y[0]=1;
    y[1]=40000.0/59999.0;
    y[2]=3-4*y[1];


    //ostateczne wyliczenie rozwiaza rownania ze wzoru ktory do obliczenia y wykorzystuje dwa poprzednie y
    for(int i=3;i<N+1;++i) {
        y[i]=(-a*y[i-2]-b*y[i-1])/c;
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



