#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <iostream>
#include <fstream>

class GameOfLife {

public:

    /**
     * @brief Constructor de la clase GameOfLife.
     * @param rows Número de filas de la matriz.
     * @param cols Número de columnas de la matriz.
     */
    GameOfLife(int rows, int cols);

    /**
     * @brief Destructor de la clase GameOfLife. Debe invocar a la función de liberación.
     */
    ~GameOfLife();

    /**
     * @brief Inicializa el tablero con valores aleatorios.
     * // Initialize a random number generator
     * #include <random.h>
     * random_device rd;
     * mt19937 gen(rd());
     * uniform_int_distribution<> distrib(min, max);
     * 
     * // Generate random number in the range [min, max]
     * int randomValue = distrib(gen);
     */
    void initializeRandom();

    /**
     * @brief Inicializa el tablero con valores aleatorios.
     * @param numAliveCells Número máximo de celdas vivas a establecer.
     */
    void initializeRandom(int numAliveCells);

    /**
     * @brief Calcula la siguiente generación del tablero.
     * ES NECESARIO USAR UN TABLERO INTERMEDIO CON MEMORIA DINÁMICA
     */
    void nextGeneration();

    /**
     * @brief Imprime el estado actual del tablero en la consola.
     */
    void printBoard() const;

    /**
     * @brief Guarda el estado actual del tablero en un archivo.
     * @param filename Nombre del archivo.
     */
    void saveToFile(const std::string& filename) const;

private:

    int rows, cols;
    bool** board; ///< Matriz dinámica (vector de punteros).

    /**
     * @brief Asigna memoria para el tablero. Utilizar el esquema siguiente
     * en el que board es un vector de punteros a bool
     * board -> P -> B B B B
     *          P -> B B B B
     *          P -> B B B B
     *          P -> B B B B
     *          P -> B B B B
     */
    void allocateBoard();   ///< Asigna memoria para el tablero.

    /**
     * @brief Libera la memoria asignada para el tablero.
     */
    void deallocateBoard(); ///< Libera la memoria asignada.

    /**
     * @brief Cuenta la cantidad de vecinos vivos de una celda específica.
     * @param row Fila de la celda.
     * @param col Columna de la celda.
     * @return Número de vecinos vivos.
     */
    int countNeighbors(int row, int col) const;

};

#endif