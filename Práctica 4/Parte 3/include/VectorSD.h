#ifndef VECTOR_SD_H
#define VECTOR_SD_H

#include <iostream>

class VectorSD{

private:

    /**
     * @brief Puntero para la reserva de memoria dinámica.
     */
    double *info;

    /**
     * @brief Número de componentes actualmente usadas.
     */
    int util;

    /**
     * @brief Capacidad total de memoria reservada actualmente.
     */
    int reservado;

public:

    /**
     * @brief Constructor de la clase `VectorSD`.
     * @param n Número de posiciones de memoria dinámica.
     */
    VectorSD(int n);

    /**
     * @brief Destructor de la clase `VectorSD`.
     */
    ~VectorSD();

    /**
     * @brief Añade un elemento al final del vector.
     * @param miInfo Elemento a añadir.
     */
    void aniadir(double miInfo);

    /**
     * @brief Devuelve un puntero a un objeto de tipo `VectorSD` que es una copia exacta del actual.
     */
    VectorSD *copiar() const;

    /**
     * @brief Muestra el vector.
     */
    void mostrar() const;

};

#endif