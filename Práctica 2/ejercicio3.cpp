/**
 * @file Práctica 2 - Ejercicio 3
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

const int MAX_COLS = 10;

int numeroColumnasUnicas(const int matriz[][MAX_COLS], const int filas, const int columnas){

    int resultado = columnas;

    for(int j = 1; j < columnas; j++){

        bool repetida = false;

        for(int k = 0; k < j && !repetida; k++){

            bool misma = true;

            for(int i = 0; i < filas && misma; i++){

                if(matriz[i][j] != matriz[i][k]) misma = false;

            }

            if(misma) repetida = true;

        }

        if(repetida) resultado--;

    }

    return resultado;
    
}

void minimoMaximo(const int matriz[][MAX_COLS], const int filas, const int columnas, int &minimo, int minimoPos[2], int &maximo, int maximoPos[2]){

    maximo = minimo = matriz[0][0];

    for(int i = 0; i < filas; i++){

        for(int j = 0; j < columnas; j++){

            if(matriz[i][j] < minimo){
                
                minimo = matriz[i][j];
                minimoPos[0] = i + 1;
                minimoPos[1] = j + 1;

            }

            if(matriz[i][j] > maximo){

                maximo = matriz[i][j];
                maximoPos[0] = i + 1;
                maximoPos[1] = j + 1;

            }

        }

    }

}

void rotar90Matriz(const int matriz[][MAX_COLS], const int filas, const int columnas, int matrizRotada[][MAX_COLS]){

    for(int i = 0; i < filas; i++){

        for(int j = 0; j < columnas; j++){

            matrizRotada[j][filas - i - 1] = matriz[i][j];

        }

    }

}

int main(){

    /* 1. Número de Columnas Únicas */

    int matriz1[][MAX_COLS] = {
        {3, 1, 0, 1, 3, -4, 1},
        {4, 5, 10, 5, 4, 4, 5},
        {5, 7, -1, 7, 5, 3, 7},
        {7, 8, 9, 8, 7, 3, 8}
    };
    
    int filas1 = 4, columnas1 = 7;

    cout << "=== 1. Número de Columnas Únicas ===" << endl;
    cout << "Entrada:" << endl;

    for(int i = 0; i < filas1; i++){

        for(int j = 0; j < columnas1; j++){

            cout << matriz1[i][j];

            if(j != columnas1 - 1) cout << "\t";

        }

        cout << endl;

    }

    cout << "Número de columnas únicas: " << numeroColumnasUnicas(matriz1, filas1, columnas1) << endl;
    cout << endl;

    /* 2. Mínimo y Máximo */

    int matriz2[][MAX_COLS] = {
        {3, -2, 7, 1},
        {5, 0, 7, 4},
        {-1, 6, 2, 9}
    };
    
    int filas2 = 3, columnas2 = 4;
    int minimo, maximo;
    int minimoPos[2], maximoPos[2];

    cout << "=== 2. Mínimo y Máximo ===" << endl;
    cout << "Entrada:" << endl;

    for(int i = 0; i < filas2; i++){

        for(int j = 0; j < columnas2; j++){

            cout << matriz2[i][j];

            if(j != columnas2 - 1) cout << "\t";

        }

        cout << endl;

    }

    minimoMaximo(matriz2, filas2, columnas2, minimo, minimoPos, maximo, maximoPos);

    cout << "Mínimo: " << minimo << " (" << minimoPos[0] << ", " << minimoPos[1] << ")" << endl;
    cout << "Máximo: " << maximo << " (" << maximoPos[0] << ", " << maximoPos[1] << ")" << endl;
    cout << endl;

    /* 3. Rotación de 90 grados */

    int matriz3[][MAX_COLS] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    int filas3 = 2, columnas3 = 3;

    int matrizRotada[MAX_COLS][MAX_COLS];

    cout << "=== 3. Rotación de 90 grados ===" << endl;
    cout << "Entrada:" << endl;

    for(int i = 0; i < filas3; i++){

        for(int j = 0; j < columnas3; j++){

            cout << matriz3[i][j];

            if(j != columnas3 - 1) cout << "\t";

        }

        cout << endl;

    }

    rotar90Matriz(matriz3, filas3, columnas3, matrizRotada);

    cout << "Salida:" << endl;

    for(int i = 0; i < columnas3; i++){

        for(int j = 0; j < filas3; j++){

            cout << matrizRotada[i][j];

            if(j != filas3 - 1) cout << "\t";

        }

        cout << endl;

    }

    return 0;

}