#include <iostream>
#include <cstdlib>
#include "Barquitos.h"

using namespace std;

int main(int argc, char* argv[]){

    if(argc != 3){
        cout << "Uso: " << argv[0] << " <filas> <columnas> " << endl;
        return 1;
    }

    int filas = atoi(argv[1]);
    int columnas = atoi(argv[2]);

    Barquitos juego(filas, columnas);

    cout << "=== TABLERO INICIAL ===" << endl;
    juego.mostrar();

    cout << "\n=== COLOCACION DE BARCOS ===" << endl;

    // Barco base
    cout << "Barco 1 (B2, tam 3, H): "
         << juego.colocarBarco('B', 2, 3, 'H') << endl;

    // SOLAPAMIENTO
    cout << "Barco 2 (B3, tam 2, H) [SOLAPA]: "
         << juego.colocarBarco('B', 3, 2, 'H') << endl;

    // ROCE (adyacente)
    cout << "Barco 3 (A2, tam 2, H) [ROZA]: "
         << juego.colocarBarco('A', 2, 2, 'H') << endl;

    // válido
    cout << "Barco 4 (E5, tam 2, V): "
         << juego.colocarBarco('E', 5, 2, 'V') << endl;

    cout << "\n=== TABLERO ===" << endl;
    juego.mostrar();

    cout << "\n=== DISPAROS ===" << endl;

    cout << "Disparo A1 (agua): "
         << juego.disparar('A', 1) << endl;

    cout << "Disparo B2 (tocado): "
         << juego.disparar('B', 2) << endl;
        
    cout << "Disparo B3 (tocado): "
         << juego.disparar('B', 3) << endl;

    cout << "Disparo B4 (hundido): "
         << juego.disparar('B', 4) << endl;

    cout << "\n=== TABLERO FINAL ===" << endl;
    juego.mostrar();

    return 0;

}