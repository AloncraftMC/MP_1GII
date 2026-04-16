/**
 * @file Práctica 3 - Ejercicio 2.3
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

const int MAX_SIZE = 5;

void mostrarArray(const int array[], const int tamanio){

    for(int i = 0; i < tamanio; i++){

        cout << array[i];
        if(i < tamanio - 1) cout << ", ";

    }

    cout << endl;

}

void mostrarMatriz(const int matriz[][MAX_SIZE], const int filas, const int columnas){

    for(int i = 0; i < filas; i++){

        for(int j = 0; j < columnas; j++){

            cout << matriz[i][j];
            if(j < columnas - 1) cout << " ";
            
        }

        cout << endl;

    }

    cout << endl;

}

void invertirLista(int *lista, int tam){

    for(int i = 0; i < tam / 2; i++){

        int aux = *(lista + i);
        *(lista + i) = *(lista + tam - i - 1);
        *(lista + tam - i - 1) = aux;
        
    }

}

void invertirMatriz(int values[][MAX_SIZE], int maxfila, int maxcol){

    for(int i = 0; i < maxfila; i++) invertirLista(*(values + i), maxcol);

}

int main(){

    int lista[MAX_SIZE];
    int matriz[MAX_SIZE][MAX_SIZE];
    
    srand(time(0));

    for(int i = 0; i < MAX_SIZE; i++){

        lista[i] = rand() % 10;

        for(int j = 0; j < MAX_SIZE; j++){

            matriz[i][j] = rand() % 10;

        }

    }

    cout << "lista antes:\t";
    mostrarArray(lista, MAX_SIZE);

    invertirLista(lista, MAX_SIZE);

    cout << "lista después:\t";
    mostrarArray(lista, MAX_SIZE);
    cout << endl;

    cout << "matriz antes:" << endl;
    mostrarMatriz(matriz, MAX_SIZE, MAX_SIZE);

    invertirMatriz(matriz, MAX_SIZE, MAX_SIZE);

    cout << "matriz después:" << endl;
    mostrarMatriz(matriz, MAX_SIZE, MAX_SIZE);

    return 0;

}