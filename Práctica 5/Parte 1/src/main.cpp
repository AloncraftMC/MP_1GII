#include <iostream>
#include "TablaHash.h"

using namespace std;

void menu() {

    cout << "\n===== TABLA HASH =====\n";
    cout << "1. Insertar elemento\n";
    cout << "2. Buscar elemento\n";
    cout << "3. Eliminar elemento\n";
    cout << "4. Mostrar tabla\n";
    cout << "0. Salir\n";
    cout << "Selecciona una opción: ";

}

int main(){

    int capacidad;
    cout << "Introduce el tamaño de la tabla: ";
    cin >> capacidad;

    TablaHash ht(capacidad);

    int opcion;
    int valor;

    do{

        menu();
        cin >> opcion;

        switch(opcion){

        case 1:

            cout << "Introduce el valor a insertar: ";
            cin >> valor;
            ht.insertar(valor);
            cout << "Elemento insertado.\n";
            break;

        case 2:

            cout << "Introduce el valor a buscar: ";
            cin >> valor;

            if(ht.buscar(valor))
                cout << "Elemento encontrado.\n";
            else
                cout << "Elemento NO encontrado\n";
            break;

        case 3:

            cout << "Introduce el valor a eliminar: ";
            cin >> valor;

            if(ht.eliminar(valor))
                cout << "Elemento eliminado.\n";
            else
                cout << "Elemento no existe.\n";
            break;

        case 4:

            cout << "\nContenido de la tabla:\n";
            ht.mostrar();
            break;

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opción inválida.\n";

        }

    }while(opcion != 0);

    return 0;

}