#ifndef BARQUITOS_H
#define BARQUITOS_H

using namespace std;

class Barquitos{

    private:

        enum Casilla{
            AGUA = 9,
            AGUA_DISPARADA = -9
        };
        
        int filas;
        int columnas;
        int** tablero;

    public:

        Barquitos(int filas, int columnas);
        ~Barquitos();

        bool colocarBarco(char fila, int columna, int tamanio, char direccion) const;
        string disparar(char fila, int columna) const;
        void mostrar() const;

};

#endif