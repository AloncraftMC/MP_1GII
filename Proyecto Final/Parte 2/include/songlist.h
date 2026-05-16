/**
 * @file songlist.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase SongList.
 */

#ifndef SONGLIST_H
#define SONGLIST_H

#include <iostream>
#include "albumlist.h"
#include "song.h"

using namespace std;

/**
 * @brief Capacidad máxima de cada bloque de canciones.
 */
const int BLOCK_MAX_SIZE = 10;

/**
 * @struct Block
 * @brief Estructura que representa un bloque de canciones en la lista de canciones.
 */
struct Block{

    Song* list[BLOCK_MAX_SIZE];     ///< Array de punteros a canciones en el bloque.
    int current_size;               ///< Número actual de canciones en el bloque.
    Block* next;                    ///< Puntero al siguiente bloque de canciones.

};

class AlbumList;

/**
 * @class SongList
 * @brief Representa una lista dinámica de canciones utilizando bloques.
 */
class SongList{

    private:

        Block* firstBlock;      ///< Puntero al primer bloque de canciones en la lista.
        Block* lastBlock;       ///< Puntero al último bloque de canciones en la lista.

    public:

        // CONSTRUCTOR Y DESTRUCTOR

        /**
         * @brief Constructor con parámetros.
         * @param file_path Ruta del archivo .txt con los datos de las canciones.
         * @param albumList Referencia a la lista de álbumes para asociar las canciones a los álbumes.
         */
        SongList(string file_path, AlbumList& albumList);

        /**
         * @brief Destructor.
         */
        ~SongList();

        // OTROS MÉTODOS

        /**
         * @brief Añade una nueva canción a la lista.
         * @param title El título de la canción.
         * @param genre El género de la canción.
         * @param duration La duración de la canción en segundos.
         * @param albumList Referencia a la lista de álbumes para asociar la canción al álbum correspondiente.
         * @param album El título del álbum al que pertenece la canción.
         * @return true si la canción se añadió correctamente, false en caso contrario.
         */
        bool addSong(string title, Genre genre, int duration, AlbumList &albumList, string album);

        /**
         * @brief Busca canciones en la lista que coincidan con los criterios de búsqueda.
         * @param searchTerm El término subcadena de búsqueda para el título de la canción.
         * @param genre El género de la canción a buscar (puede ser UNKNOWN para ignorar este filtro).
         * @param durationMin La duración mínima de la canción en segundos (puede ser -1 para ignorar este filtro).
         * @param durationMax La duración máxima de la canción en segundos (puede ser -1 para ignorar este filtro).
         * @param results Array de punteros a canciones donde se almacenarán los resultados encontrados.
         * @param maxResults El tamaño máximo del array de resultados.
         * @param numResults Variable donde se almacenará el número de resultados encontrados.
         * @return true si se encontraron canciones que coincidan con los criterios, false en caso contrario.
         */
        bool findSong(string searchTerm, Genre genre, int durationMin, int durationMax, Song** results, int maxResults, int& numResults);

};

#endif