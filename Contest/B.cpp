#include<iostream>
using namespace std;

void piramides() {

    // Leer el número de cartas disponibles
    long long n ;
    cin >> n;
    long long cnt = 0;

    // Mientras haya más de 2 cartas disponibles
    while(n > 2){
        // (C) : Número de cartas necesarias para aumentar la altura de la pirámide en 1
        // (act) : Número total de cartas utilizadas hasta ahora
        long long C = 5 ;
        long long act = 2 ;

        // Mientras haya suficientes cartas para aumentar la altura de la pirámide
        while(n >= C + act){
            // Aumentar la altura de la pirámide
            act = C + act ;
            // Incrementar C en 3 (2 cartas para la base y 1 carta para el piso de arriba)
            C += 3;
        }

        // Restar las cartas utilizadas del total de cartas disponibles
        n -= act ;
        // Incrementar el contador de pirámides
        cnt ++;
    }

    // Si al final quedan 2 o más cartas, se puede construir una pirámide de altura 1
    if(n >= 2) cnt ++ ;

    // Imprimir el número total de pirámides que se pudieron construir
    cout << cnt << endl ;
   
}

int main(){    
    int casos;
    cin >> casos;
    for (int C = 1; C <= casos; C++){
        piramides();
    }

    return 0;
}