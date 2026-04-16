#include <iostream>
#include "TablaHash.h"

using namespace std;

inline int TablaHash::hash(int clave){ return clave % this->capacidad; }

TablaHash::TablaHash(int capacidad){

    this->capacidad = capacidad;
    this->tabla = new Nodo*[this->capacidad];
    
    for(int i = 0; i < this->capacidad; i++)    // Al principio, la lista no tiene nodos (nullptr)
        this->tabla[i] = nullptr;

}

TablaHash::~TablaHash(){

    for(int i = 0; i < capacidad; i++){ // Recorro la lista de punteros a nodos

        Nodo* nodo = this->tabla[i];

        while(nodo != nullptr){ // Elimino la lista actual desde la raíz hasta la punta (nullptr)

            Nodo* aux = nodo;
            nodo = nodo->siguiente;
            delete aux;

        }

    }

    delete[] tabla; // Elimino la lista

}

void TablaHash::insertar(int clave){

    int indice = this->hash(clave);

    Nodo* nuevo = new Nodo;
    nuevo->dato = clave;

    // Hago que el nuevo nodo sea el primero de la fila

    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;

}

bool TablaHash::buscar(int clave){

    int indice = this->hash(clave);
    bool res = false;

    Nodo* nodo = tabla[indice]; 

    // Recorro la lista donde debería estar el elemento desde la raíz hasta la punta (nullptr)

    while(nodo != nullptr && !res){
        
        if(nodo->dato == clave) res = true;
        nodo = nodo->siguiente;

    }

    return res;

}

bool TablaHash::eliminar(int clave){

    int indice = this->hash(clave);

    Nodo* nodo = tabla[indice];
    Nodo* anterior = nullptr;

    // Recorro la lista donde debería estar el elemento desde la raíz hasta la punta (nullptr)

    while(nodo != nullptr){

        if(nodo->dato == clave){

            if(anterior == nullptr)
                tabla[indice] = nodo->siguiente;    // Si es el primero de la fila
            else
                anterior->siguiente = nodo->siguiente;  // Si no es el primero

            delete nodo;
            nodo = nullptr;
            return true;

        }

        anterior = nodo;
        nodo = nodo->siguiente;

    }

    return false;

}

void TablaHash::mostrar(){

    for(int i = 0; i < this->capacidad; i++){   // Recorro la lista de punteros a nodos

        cout << i << ": ";

        Nodo* nodo = this->tabla[i];

        while(nodo != nullptr){ // Muestro la lista actual desde la raíz hasta la punta (nullptr)

            cout << nodo->dato << " -> ";
            nodo = nodo->siguiente;

        }

        cout << "NULL" << endl;

    }

}