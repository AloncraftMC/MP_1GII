/**
 * @file Práctica 2 - Ejercicio 1
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

string arrayToString(const int array[], const int TAMANIO){

    string resultado = "{";

    for(int i = 0; i < TAMANIO; i++){

        resultado += to_string(array[i]);

        if(i != TAMANIO - 1) resultado += ", ";

    }
    
    return resultado + "}";

}

void mayorSecuenciaMonotona(const int array[], const int TAMANIO, int resultado[], int& tamanioResultado){

    int aux[TAMANIO];
    int tamanioAux = 1;
 
    aux[0] = array[0];
    tamanioResultado = 1;

    for(int i = 1; i < TAMANIO; i++){

        if(array[i] > array[i - 1]){
            
            aux[tamanioAux] = array[i];
            tamanioAux++;

        }else{

            if(tamanioAux > tamanioResultado){

                for(int j = 0; j < tamanioAux; j++) resultado[j] = aux[j];

                tamanioResultado = tamanioAux;

            }

            aux[0] = array[i];
            tamanioAux = 1;

        }

    }

    if(tamanioAux > tamanioResultado){

        for(int i = 0; i < tamanioAux; i++) resultado[i] = aux[i];

        tamanioResultado = tamanioAux;

    }

}

void diferenciasElementosConsecutivos(const int array[], const int TAMANIO, int resultado[]){

    for(int i = 0; i < TAMANIO - 1; i++){

        resultado[i] = array[i + 1] - array[i];

    }

}

void mezclarOrdenadamente(const int array1[], const int TAMANIO_1, const int array2[], const int TAMANIO_2, int resultado[]){

    int tamanioResultado = TAMANIO_2;

    for(int i = 0; i < tamanioResultado; i++) resultado[i] = array2[i];

    for(int i = 0; i < TAMANIO_1; i++){

        int posicionInsercion = 0;

        while(posicionInsercion < tamanioResultado && resultado[posicionInsercion] < array1[i]) posicionInsercion++;

        for(int j = tamanioResultado; j > posicionInsercion; j--) resultado[j] = resultado[j - 1];

        resultado[posicionInsercion] = array1[i];
        tamanioResultado++;

    }

}

int main(){

    /* 1. Mayor secuencia Monótona */

    const int TAMANIO_1 = 8;
    int array1[TAMANIO_1] = {3, 5, 7, 2, 4, 6, 8, 1};
    
    int resultado1[TAMANIO_1];
    int tamanioResultado1;

    cout << "=== 1. Mayor Secuencia Monótona ===" << endl;
    cout << "Entrada: " << arrayToString(array1, TAMANIO_1) << endl;

    mayorSecuenciaMonotona(array1, TAMANIO_1, resultado1, tamanioResultado1);

    cout << "Salida: " << arrayToString(resultado1, tamanioResultado1) << "\t(tamaño = " << tamanioResultado1 << ")" << endl;
    cout << endl;

    /* 2. Diferencias entre Elementos Consecutivos */

    const int TAMANIO_2 = 5;
    int array2[TAMANIO_2] = {4, 7, 1, 9, 6};

    int tamanioResultado2 = TAMANIO_2 - 1;
    int resultado2[tamanioResultado2];

    cout << "=== 2. Diferencias entre Elementos Consecutivos ===" << endl;
    cout << "Entrada: " << arrayToString(array2, TAMANIO_2) << endl;
    
    diferenciasElementosConsecutivos(array2, TAMANIO_2, resultado2);

    cout << "Salida: " << arrayToString(resultado2, tamanioResultado2) << endl;
    cout << endl;

    /* 3. Mezclar Ordenadamente */

    const int TAMANIO_3 = 4;
    
    int arrayV1[TAMANIO_3] = {1, 3, 5, 8};
    int arrayV2[TAMANIO_3] = {2, 3, 6, 9};
    
    int tamanioResultado3 = 2 * TAMANIO_3;
    int resultado3[tamanioResultado3];
    
    cout << "=== 3. Mezclar Ordenadamente ===" << endl;
    cout << "Entrada: " << endl;
    cout << "v1 = " << arrayToString(arrayV1, TAMANIO_3) << "\tv2 = " << arrayToString(arrayV2, TAMANIO_3) << endl;
    
    mezclarOrdenadamente(arrayV1, TAMANIO_3, arrayV2, TAMANIO_3, resultado3);

    cout << "Salida: " << arrayToString(resultado3, tamanioResultado3) << endl;
    cout << endl;

    return 0;
    
}