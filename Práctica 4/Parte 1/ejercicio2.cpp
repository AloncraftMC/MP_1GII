#include <iostream>

using namespace std;

int *nuevoVector(int* vector, int tamanio){

    // Primero calculo el tamaño del nuevo vector

    int nuevoTamanio = 0;

    for(int i = 0; i < tamanio; i++) nuevoTamanio += vector[i];

    // Ahora reservo la memoria

    int *nuevoVector = new int[nuevoTamanio];
    int *aux = nuevoVector; // Uso un puntero auxiliar para ir guardando los valores

    for(int i = 0; i < tamanio; i++){

        for(int j = 0; j < vector[i]; j++){

            *aux = vector[i];
            aux++;

        }

    }

    // Devuelvo el puntero a la primera posición del nuevo vector

    return nuevoVector;

}

int main(){

    // Declaro el vector

    int tamanio = 3;
    int *vector = new int[tamanio];
    
    vector[0] = 1;
    vector[1] = 3;
    vector[2] = 2;

    // Calculo el tamaño del nuevo vector

    int nuevoTamanio = 0;
    for(int i = 0; i < tamanio; i++) nuevoTamanio += vector[i];

    int *nuevo = nuevoVector(vector, tamanio);

    cout << "Entrada 1:\t";
    for(int i = 0; i < tamanio; i++) cout << vector[i] << " ";
    cout << endl;

    cout << "Salida 1:\t";
    for(int i = 0; i < nuevoTamanio; i++) cout << nuevo[i] << " ";
    cout << endl;

    // Libero la memoria

    delete[] nuevo;
    delete[] vector;

    // Segundo ejemplo

    cout << endl;
    tamanio = 4;
    vector = new int[tamanio];

    vector[0] = 0;
    vector[1] = 1;
    vector[2] = 4;
    vector[3] = 2;

    // Calculo el tamaño del nuevo vector

    nuevoTamanio = 0;
    for(int i = 0; i < tamanio; i++) nuevoTamanio += vector[i];

    nuevo = nuevoVector(vector, tamanio);

    cout << "Entrada 2:\t";
    for(int i = 0; i < tamanio; i++) cout << vector[i] << " ";
    cout << endl;

    cout << "Salida 2:\t";
    for(int i = 0; i < nuevoTamanio; i++) cout << nuevo[i] << " ";
    cout << endl;

    // Libero la memoria

    delete[] nuevo;
    delete[] vector;

    nuevo = nullptr;
    vector = nullptr;

    return 0;

}