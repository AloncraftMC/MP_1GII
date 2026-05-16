/**
 * @file artistlist.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase ArtistList.
 */

#ifndef ARTISTLIST_H
#define ARTISTLIST_H

#include <iostream>
#include "artist.h"

using namespace std;

/**
 * @brief Capacidad máxima de la lista de artistas.
 */
const int MAX_ARTISTS = 1000;

/**
 * @class ArtistList
 * @brief Representa una lista dinámica de artistas.
 */
class ArtistList{

    private:

        int current_size;               ///< Número actual de artistas en la lista.
        Artist* list[MAX_ARTISTS];      ///< Array de artistas.

    public:

        // CONSTRUCTOR Y DESTRUCTOR

        /**
         * @brief Constructor con parámetros.
         * @param file_path Ruta del archivo .txt con los datos de los artistas.
         */
        ArtistList(string file_path);

        /**
         * @brief Destructor.
         */
        ~ArtistList();

        // GETTERS

        /**
         * @brief Obtiene el número actual de artistas en la lista.
         * @return Número de artistas en la lista.
         */
        inline int getCurrentSize() const { return this->current_size; }
        
        /**
         * @brief Obtiene un artista por su posición en la lista.
         * @param id Índice del artista a obtener.
         * @return Puntero al artista solicitado o nullptr si no se encuentra.
         */
        inline Artist* getArtistById(int i) const { return this->list[i]; }

};

#endif