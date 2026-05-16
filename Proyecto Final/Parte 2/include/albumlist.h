/**
 * @file albumlist.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase AlbumList.
 */

#ifndef ALBUMLIST_H
#define ALBUMLIST_H

#include <iostream>
#include "album.h"

using namespace std;

/**
 * @brief Capacidad máxima de la lista de álbumes.
 */
const int MAX_ALBUMS = 1000;

class SongList;
class ArtistList;

/**
 * @class AlbumList
 * @brief Representa una lista dinámica de álbumes.
 */
class AlbumList{

    private:

        int current_size;           ///< Número actual de álbumes en la lista.
        Album* list[MAX_ALBUMS];    ///< Array de álbumes.

    public:

        // CONSTRUCTOR Y DESTRUCTOR

        /**
         * @brief Constructor con parámetros.
         * @param file_path Ruta del archivo .txt con los datos de los álbumes.
         * @param artistList Referencia a la lista de artistas para asociar los artistas a los álbumes.
         * @param songList Referencia a la lista de canciones para asociar las canciones a los álbumes.
         */
        AlbumList(string file_path, ArtistList& artistList, SongList& songList);

        /**
         * @brief Destructor.
         */
        ~AlbumList();

        // GETTERS

        /**
         * @brief Obtiene el número actual de álbumes en la lista.
         * @return Número de álbumes en la lista.
         */
        inline int getCurrentSize() const { return this->current_size; }

        /**
         * @brief Obtiene un álbum por su posición en la lista.
         * @param id Índice del álbum a obtener.
         * @return Puntero al álbum solicitado o nullptr si no se encuentra.
         */
        inline Album* getAlbumById(int id) const { return this->list[id]; }

        // OTROS MÉTODOS

        /**
         * @brief Guarda la lista de álbumes en un archivo .txt.
         * @param file_path Ruta del archivo .txt donde se guardarán los datos de los álbumes.
         * @return true si la operación fue exitosa, false en caso contrario.
         */
        bool dump(string file_path);

        /**
         * @brief Imprime la información de un álbum dado su título.
         * @param title El título del álbum a imprimir.
         */
        void printAlbum(string title) const;

};

#endif