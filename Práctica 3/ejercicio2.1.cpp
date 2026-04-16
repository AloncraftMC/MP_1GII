/**
 * @file Práctica 3 - Ejercicio 2.1
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

void mostrarArray(const int array[], const int tamanio){

    for(int i = 0; i < tamanio; i++){

        cout << array[i];
        if(i < tamanio - 1) cout << ", ";

    }

    cout << endl;

}

int main(){

    const int max_size = 20;
    int lista[max_size] = {7, 6, 0, 5, 1, 5, 9};
    int utiles = 7;

    cout << "lista antes:\t";
    mostrarArray(lista, utiles);

    for(int i = 0; i < utiles / 2; i++){

        int aux = *(lista + i);
        *(lista + i) = *(lista + utiles - i - 1);
        *(lista + utiles - i - 1) = aux;
        
    }

    cout << "lista después:\t";
    mostrarArray(lista, utiles);

    return 0;

}