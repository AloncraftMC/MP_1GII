/**
 * @file artist.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase Artist.
 */

#ifndef ARTIST_H
#define ARTIST_H

#include <iostream>

using namespace std;

/**
 * @class Artist
 * @brief Representa un artista con su nombre.
 */
class Artist {

    private:

        string name;    ///< Nombre del artista.

    public:

        // CONSTRUCTORES

        /**
         * @brief Constructor por defecto.
         */
        Artist() { this->name = "New artist"; }

        /**
         * @brief Constructor con parámetros.
         * @param name Nombre del artista.
         */
        Artist(string name) { this->name = name; }

        // GETTERS

        /**
         * @brief Obtiene el nombre del artista.
         * @return Nombre del artista.
         */
        inline string getName() const { return this->name; }

        // SETTERS

        /**
         * @brief Establece el nombre del artista.
         * @param name Nuevo nombre del artista.
         */
        inline void setName(string name) { this->name = name; }

};

/**
 * @brief Sobrecarga del operador de inserción para imprimir un artista.
 * @param flujo Flujo de salida.
 * @param artist Artista a imprimir.
 * @return Referencia al flujo de salida.
 */
inline ostream& operator<<(ostream& flujo, const Artist& artist) { return flujo << artist.getName(); }

#endif