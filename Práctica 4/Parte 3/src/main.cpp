#include <iostream>
#include "VectorSD.h"

using namespace std;

int main(){

    // 1. Inicialización: Capacidad inicial de 2 elementos
    VectorSD miVector(2);

    // 2. Añadir elementos: El tercer elemento fuerza redimensión
    cout << "Añadiendo elementos al vector original..." << endl;
    miVector.aniadir(1.17);
    miVector.aniadir(3.40);
    miVector.aniadir(0.56);

    // 3. Copiar: El método devuelve un PUNTERO a un nuevo objeto
    cout << "Creando copia exacta en memoria dinámica..." << endl;
    VectorSD* punteroCopia = miVector.copiar();

    // 4. Mostrar resultados del vector original
    cout << "\n--- Vector Original ---" << endl;
    miVector.mostrar();

    // 5. Mostrar resultados de la copia a través del puntero
    cout << "\n--- Vector Copia (vía puntero) ---" << endl;
    punteroCopia->mostrar();

    // 6. Liberación de memoria dinámica
    // `miVector` se libera automáticamente (stack), se produce una invocación implícita al destructor.
    // `punteroCopia` requiere liberación manual con delete (heap), hay que hacer una liberación explícita.
    delete punteroCopia;

    cout << "\nMemoria de la copia liberada correctamente." << endl;

    return 0;

}