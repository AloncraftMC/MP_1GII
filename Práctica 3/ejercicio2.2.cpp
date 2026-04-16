/**
 * @file Práctica 3 - Ejercicio 2.2
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

const int *posicionMaximo(const int vector[], const int tamanio){

    const int *p_maximo = vector;

    for(int i = 0; i < tamanio; i++){

        if(vector[i] > *p_maximo) p_maximo = &vector[i];

    }

    return p_maximo;

}

void calcularPosicionMaximo(const int vector[], const int tamanio, const int *&p_maximo){

    p_maximo = vector;

    for(int i = 0; i < tamanio; i++){

        if(vector[i] > *p_maximo) p_maximo = &vector[i];

    }

}

int main(){

    int vector[100];
    int usados;

    srand(time(0));
    usados = 100;

    for(int i = 0; i < usados; i++){
        
        vector[i] = rand() % 1000;
        cout << vector[i];

        if(i < usados - 1) cout << ", ";
        
    }
    
    cout << endl;

    const int *p_maximo;

    calcularPosicionMaximo(vector, usados, p_maximo);
    cout << "Máximo (todo):\t" << *p_maximo << endl;

    int primeraMitad[50];
    int segundaMitad[50];
    
    usados = 50;

    for(int i = 0; i < usados; i++){

        primeraMitad[i] = vector[i];
        segundaMitad[i] = vector[i + usados];

    }

    cout << "Máximo (1ª mitad):\t" << *posicionMaximo(primeraMitad, usados) << endl;
    cout << "Máximo (2ª mitad):\t" << *posicionMaximo(segundaMitad, usados) << endl;
        
    return 0;

}