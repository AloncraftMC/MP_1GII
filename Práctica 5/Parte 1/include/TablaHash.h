#ifndef TABLA_HASH_H
#define TABLA_HASH_H

struct Nodo{
    int dato;
    Nodo* siguiente;
};

class TablaHash{

    private:

        Nodo** tabla;   // array de listas (punteros a Nodo)
        int capacidad;
        int hash(int clave);

    public:

        TablaHash(int capacidad);
        ~TablaHash();
        
        void insertar(int clave);
        bool buscar(int clave);
        bool eliminar(int clave);
        void mostrar();

};

#endif