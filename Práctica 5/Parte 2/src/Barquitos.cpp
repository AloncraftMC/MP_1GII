#include <iostream>
#include "Barquitos.h"

using namespace std;

Barquitos::Barquitos(int filas, int columnas){

    this->filas = filas;
    this->columnas = columnas;
    this->tablero = new int*[filas];

    for(int i = 0; i < filas; i++){

        this->tablero[i] = new int[columnas];

        for(int j = 0; j < columnas; j++)
            this->tablero[i][j] = this->AGUA;

    }

}

Barquitos::~Barquitos(){

    for(int i = 0; i < filas; i++){

        delete[] this->tablero[i];
        this->tablero[i] = nullptr;

    }

    delete[] this->tablero;
    this->tablero = nullptr;

}

bool Barquitos::colocarBarco(char fila, int columna, int tamanio, char direccion) const{

    int filaNum = fila - 'A';
    columna--;

    if(filaNum < 0 || filaNum >= this->filas || columna < 0 || columna >= this->columnas)
        return false;

    if(direccion == 'H'){
        
        // Compruebo que el barquito cabe horizontalmente en el tablero

        if(columna + tamanio > this->columnas) return false;

        // Compruebo que el barquito quiere colocarse en el agua

        for(int i = 0; i < tamanio; i++){

            int casilla = this->tablero[filaNum][columna + i];
            
            if(casilla != this->AGUA && casilla != this->AGUA_DISPARADA)
                return false;

        }

        // Compruebo que las casillas adyacentes también son agua

        for(int i = filaNum - 1; i <= filaNum + 1; i++)

            for(int j = columna - 1; j <= columna + tamanio; j++)

                if(i >= 0 && i < this->filas && j >= 0 && j < this->columnas)

                    if(this->tablero[i][j] != this->AGUA && this->tablero[i][j] != this->AGUA_DISPARADA)
                        return false;

        // Coloco el barquito si se puede

        for(int i = 0; i < tamanio; i++)
            this->tablero[filaNum][columna + i] = tamanio;

    }else if(direccion == 'V'){
        
        // Compruebo que el barquito cabe verticalmente en el tablero

        if(filaNum + tamanio > this->filas) return false;

        // Compruebo que el barquito quiere colocarse en el agua

        for(int i = 0; i < tamanio; i++){

            int casilla = this->tablero[filaNum + i][columna];
            
            if(casilla != this->AGUA && casilla != this->AGUA_DISPARADA)
                return false;

        }

        // Compruebo que las casillas adyacentes también son agua

        for(int i = filaNum - 1; i <= filaNum + tamanio; i++)

            for(int j = columna - 1; j <= columna + 1; j++)

                if(i >= 0 && i < this->filas && j >= 0 && j < this->columnas)

                    if(this->tablero[i][j] != this->AGUA && this->tablero[i][j] != this->AGUA_DISPARADA)
                        return false;

        // Coloco el barquito si se puede

        for(int i = 0; i < tamanio; i++)
            this->tablero[filaNum + i][columna] = tamanio;

    }else{

        return false;

    }

    return true;
    
}

string Barquitos::disparar(char fila, int columna) const{

    int filaNum = fila - 'A';
    columna--;

    if(filaNum < 0 || filaNum >= this->filas || columna < 0 || columna >= this->columnas)
        return "Posición inválida";

    int& casilla = this->tablero[filaNum][columna];

    if(casilla < 0) return "Ya disparado";

    if(casilla == this->AGUA){

        casilla = this->AGUA_DISPARADA;
        return "Agua";

    }
    
    int tamanio = casilla;
    casilla = -casilla;

    // Detecto la orientación del barco
    
    bool horizontal = false, vertical = false;

    if((columna > 0 && abs(this->tablero[filaNum][columna - 1]) == tamanio) ||
    (columna < columnas - 1 && abs(this->tablero[filaNum][columna + 1]) == tamanio))
        horizontal = true;

    if((filaNum > 0 && abs(this->tablero[filaNum - 1][columna]) == tamanio) ||
    (filaNum < filas - 1 && abs(this->tablero[filaNum + 1][columna]) == tamanio))
        vertical = true;

    // Barco unario

    if(!horizontal && !vertical)
        return "Hundido";

    // Recorro el barco

    bool intacto = false;

    if(horizontal){

        int j = columna;

        // Voy hacia la izquierda: desde la casilla hasta el inicio del barco

        while(j > 0 && abs(this->tablero[filaNum][j - 1]) == tamanio)
            j--;

        // Recorro el barco en orden para comprobar si hay partes intactas

        for(int k = j; k < columnas && abs(this->tablero[filaNum][k]) == tamanio; k++){
            if(this->tablero[filaNum][k] == tamanio)
                return "Tocado";
        }

    }else if(vertical){

        int i = filaNum;

        // Voy hacia arriba: desde la casilla hasta el inicio del barco

        while(i > 0 && abs(this->tablero[i - 1][columna]) == tamanio)
            i--;

        // Recorro el barco en orden para comprobar si hay partes intactas

        for(int k = i; k < filas && abs(this->tablero[k][columna]) == tamanio; k++){
            if(this->tablero[k][columna] == tamanio)
                return "Tocado";
        }

    }

    // Si no hay partes intactas es que lo he hundido

    return "Hundido";

}

void Barquitos::mostrar() const{

    cout << "\t";

    for(int i = 0; i < this->columnas; i++)
        cout << i + 1 << "\t";

    cout << endl;

    for(int i = 0; i < this->filas; i++){

        cout << char('A' + i) << "\t";

        for(int j = 0; j < this->columnas; j++){

            switch(this->tablero[i][j]){

                case this->AGUA:
                    cout << "▢";
                break;

                case this->AGUA_DISPARADA:
                    cout << "⊡";
                break;
                
                default:
                    cout << ((this->tablero[i][j] > 0) ? "⛞" : "⛝");

            }

            cout << "\t";

        }

        cout << endl;

    }

}