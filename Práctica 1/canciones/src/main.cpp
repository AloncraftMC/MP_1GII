/*
 * Programa principal para gestionar canciones.
 *
 * 1. Pedir al usuario cuántas canciones va a ingresar.
 * 2. Crear un array de objetos Cancion .
 * 3. Leer los datos del número de canciones indicadas desde la entrada estándar (getline) y almacenarlas en el array.
 * 4. Pedir al usuario un año para filtrar las canciones.
 * 5. Llamar a la función filtrarCancionesPorAnio para obtener las canciones de ese año.
 * 7. Mostrar en pantalla las canciones filtradas recorriendo el array resultado.
 */

#include "cancion.h"
#include <iostream>

using namespace std;

int main() {
    
    const int MIN_CANCIONES = 1;
    const int MAX_CANCIONES = 100;
    
    int numCanciones;

    do{

        cout << "¿Cuántas canciones vas a ingresar? ";
        cin >> numCanciones;

        if(numCanciones < MIN_CANCIONES || numCanciones > MAX_CANCIONES) cout << "\aError: El número de canciones debe ser un valor entre " << MIN_CANCIONES << " y " << MAX_CANCIONES << endl;
        
    }while(numCanciones < MIN_CANCIONES || numCanciones > MAX_CANCIONES);

    Cancion canciones[numCanciones];

    cout << "\nFORMATO: <Título>,<Artista>,<Duración>,<Género>,<Año>" << endl;
    cout << "Ejemplo: Bohemian Rhapsody,Queen,5.55,Rock,1975\n" << endl;

    string linea;
    cin.ignore();
    
    for(int i = 0; i < numCanciones; i++){

        cout << "> Canción " << i+1 << ": ";
        getline(cin, linea);
        canciones[i] = Cancion(linea);
        
    }

    int anio;

    do{

        cout << "\n¿Por qué año quieres filtrar las canciones? ";
        cin >> anio;
        
    }while(anio < 0);

    Cancion filtradas[numCanciones];
    int numFiltradas;

    filtrarCancionesPorAnio(canciones, numCanciones, anio, filtradas, numFiltradas);

    cout << "\n[ Canciones filtradas por año " << anio << " ] (" << numFiltradas << " resultados):\n" << endl;

    for(int i = 0; i < numFiltradas; i++){

        cout << "=== Canción " << i+1 << " ===\n" << filtradas[i].toString() << endl;

    }

}