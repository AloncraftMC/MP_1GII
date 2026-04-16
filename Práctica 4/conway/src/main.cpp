#include <iostream>
#include <unistd.h> // Para usleep
#include "conway.h"


int main() {
    // Configuración inicial
    const int FILAS = 30;
    const int COLUMNAS = 60;
    const int GENERACIONES = 200;
    const int VELOCIDAD = 100000; // Microsegundos (0.1 segundos)

    // 1. Instanciación del objeto
    GameOfLife juego(FILAS, COLUMNAS);

    // 2. Inicialización (usando el método con parámetro de celdas vivas)
    // Esto permite que el tablero no esté ni vacío ni colapsado
    juego.initializeRandom(600); 

    // 3. Bucle de animación
    for (int i = 0; i < GENERACIONES; ++i) {
        // Secuencia ANSI para mover el cursor al inicio (0,0) 
        // Es más eficiente que system("clear")
        std::cout << "\033[H"; 

        std::cout << "--- Juego de la Vida ---" << std::endl;
        std::cout << "Generación: " << i << std::endl;

        // 4. Dibujar el estado actual
        juego.printBoard();

        // 5. Calcular siguiente estado
        juego.nextGeneration();

        // Pausa para que el ojo humano lo perciba
        usleep(VELOCIDAD);
    }

    // Opcional: Guardar el estado final
    juego.saveToFile("estado_final.txt");
    std::cout << "\nSimulación finalizada. Estado guardado en 'estado_final.txt'" << std::endl;

    return 0;
}