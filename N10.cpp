#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

double wielomian_charakterystyczny(double lampda){
    return -(lampda*lampda*lampda)+12*(lampda*lampda)-46*lampda+56;
}

double pochodna_wielomianu(double lampda){
    return -3*(lampda*lampda)+24*lampda-46;
}


double metoda_bisekcj(double start,double koniec,double epsilon){
    double punkt;
    int liczba_iteracji=0;

        if (wielomian_charakterystyczny(start) * wielomian_charakterystyczny(koniec) < 0) {
            liczba_iteracji++;
            punkt = (start + koniec) / 2;
            if(wielomian_charakterystyczny(start)*wielomian_charakterystyczny(punkt) < 0)koniec = punkt;
            else if(wielomian_charakterystyczny(punkt)*wielomian_charakterystyczny(koniec) < 0)start = punkt;

            while(abs(wielomian_charakterystyczny(punkt)) > epsilon){
                liczba_iteracji++;
                punkt = (start+koniec)/2;
                if(wielomian_charakterystyczny(start)*wielomian_charakterystyczny(punkt) < 0)koniec = punkt;
                else if(wielomian_charakterystyczny(punkt)*wielomian_charakterystyczny(koniec) < 0)start = punkt;
            }
            printf("Iteracje: %d    ",liczba_iteracji);
            return punkt;

        }
        else printf("Nie można znaleźć rozwiązania dla tych przedzialow\n");
        return 0;


}

double metoda_siecznych(double start,double koniec,double epsilon){
    double punkt;
    int liczba_iteracji=0;

    if (wielomian_charakterystyczny(start) != wielomian_charakterystyczny(koniec)) {
        liczba_iteracji++;
        punkt = (wielomian_charakterystyczny(start)*koniec-wielomian_charakterystyczny(koniec)*start)/(wielomian_charakterystyczny(start)-wielomian_charakterystyczny(koniec));
        start = koniec;
        koniec = punkt;

        while(abs(wielomian_charakterystyczny(punkt)) > epsilon){
            liczba_iteracji++;
            punkt = (wielomian_charakterystyczny(start)*koniec-wielomian_charakterystyczny(koniec)*start)/(wielomian_charakterystyczny(start)-wielomian_charakterystyczny(koniec));
            start = koniec;
            koniec = punkt;
        }
        printf("Iteracje: %d    ",liczba_iteracji);
        return punkt;

    }
    else printf("Nie można znaleźć rozwiązania dla tych przedzialow\n");
    return 0;


}


double metoda_newtona(double x0,double epsilon){

    int liczba_iteracji=0;
    double x1 = x0;

        while(abs(wielomian_charakterystyczny(x1))> epsilon){
            liczba_iteracji++;
            x1 = x0 - (wielomian_charakterystyczny(x0))/(pochodna_wielomianu(x0));
            x0 = x1;
        }
        printf("Iteracje: %d    ",liczba_iteracji);
        return x1;


}

int main() {

    printf("Miejsce zerowe (metoda bisekcji) dla przedziału <1,3> wynosi: %.8f \n" ,metoda_bisekcj(1,3,0.000000001));
    printf("Miejsce zerowe (metoda bisekcji) dla przedziału <3,4.8> wynosi: %.8f \n" ,metoda_bisekcj(3,4.8,0.000000001));
    printf("Miejsce zerowe (metoda bisekcji) dla przedziału <5,6> wynosi: %.8f \n\n" ,metoda_bisekcj(5,6,0.000000001));

    printf("Miejsce zerowe (metoda siecznych) dla przedziału <1,3> wynosi: %.8f \n" ,metoda_siecznych(1,3,0.000000001));
    printf("Miejsce zerowe (metoda siecznych) dla przedziału <3,4.8> wynosi: %.8f \n" ,metoda_siecznych(3,4.8,0.000000001));
    printf("Miejsce zerowe (metoda siecznych) dla przedziału <5,6> wynosi: %.8f \n\n" ,metoda_siecznych(5,6,0.000000001));

    printf("Miejsce zerowe (metoda Newtona) dla punktu x0 = 1 wynosi: %.8f \n" ,metoda_newtona(1,0.000000001));
    printf("Miejsce zerowe (metoda Newtona) dla punktu x0 = 3.4 wynosi: %.8f \n" ,metoda_newtona(3.4,0.000000001));
    printf("Miejsce zerowe (metoda Newtona) dla punktu x0 = 5 wynosi: %.8f \n" ,metoda_newtona(5,0.000000001));
}







