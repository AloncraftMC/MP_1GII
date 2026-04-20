#include "conway.h"
#include <random>

using namespace std;

GameOfLife::GameOfLife(int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    allocateBoard();
}

GameOfLife::~GameOfLife(){
    deallocateBoard();
}

void GameOfLife::initializeRandom(){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    for(int i = 0; i < rows; i++){

        for(int j = 0; j < cols; j++){

            board[i][j] = distrib(gen);

        }

    }

}

void GameOfLife::initializeRandom(int numAliveCells){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    int usadas = 0;

    for(int i = 0; i < rows; i++){

        for(int j = 0; j < cols; j++){

            if(usadas < numAliveCells){

                board[i][j] = distrib(gen);
                usadas++;

            }

        }

    }

}

void GameOfLife::nextGeneration(){

    // Reservo memoria para un tablero intermedio (adicional)

    bool** aux = new bool*[rows];
    for(int i = 0; i < rows; i++)   aux[i] = new bool[cols];

    // Calculo la siguiente generación recorriendo todo el tablero

    for(int i = 0; i < rows; i++){

        for(int j = 0; j < cols; j++){

            int vecinasVivas = countNeighbors(i, j);

            // Aplico las reglas del juegún según vivas o muertas

            if(board[i][j]){

                aux[i][j] = (vecinasVivas == 2 || vecinasVivas == 3);
            
            }else{

                aux[i][j] = (vecinasVivas == 3);

            }

        }

    }

    // Copio al tablero

    for(int i = 0; i < rows; i++)   delete[] this->board[i];
    
    delete[] this->board;
    this->board = aux;

    /* Menos eficiente:

    for(int i = 0; i < rows; i++){
        
        for(int j = 0; j < cols; j++){

            board[i][j] = aux[i][j];
            
        }

    }

    */

    // Libero la memoria

    for(int i = 0; i < rows; i++)   delete[] aux[i];
    delete[] aux;

}

void GameOfLife::printBoard() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Usamos caracteres ASCII para que se vea mejor en terminal
            std::cout << (board[i][j] ? "█" : " "); 
        }
        std::cout << "\n";
    }
}

void GameOfLife::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << board[i][j];
        }
        file << "\n";
    }
    file.close();
}

void GameOfLife::allocateBoard(){

    board = new bool*[rows];    // board es un puntero a un array de punteros a arrays de booleanos

    for(int i = 0; i < rows; i++) board[i] = new bool[cols];    // Inicializo todos los punteros a arrays de booleanos

}

void GameOfLife::deallocateBoard(){

    for(int i = 0; i < rows; i++) delete[] board[i];

    delete[] board;

    board = nullptr;

}

int GameOfLife::countNeighbors(int row, int col) const{

    int resultado = 0;

    // Recorro las células adyacentes

    for(int i = -1; i <= 1; i++){

        for(int j = -1; j <= 1; j++){

            if( !(i == 0 && j == 0)                // no contar la misma celda
                && row + i >= 0 && row + i < rows  // asegurar fila váida (dentro del tablero)
                && col + j >= 0 && col + j < cols  // asegurar columna válida (dentro del tablero)
                && board[row + i][col + j] )       // Condición principal: la célula vecina está viva
                resultado++;

        }

    }
    
    return resultado;

}