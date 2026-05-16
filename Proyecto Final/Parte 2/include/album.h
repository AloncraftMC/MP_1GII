/**
 * @file album.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase Album.
 */

#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include "artist.h"
#include "date.h"
#include "song.h"

using namespace std;

/**
 * @class Album
 * @brief Representa un álbum musical, con su título, artista, fecha de lanzamiento y canciones.
 */
class Album {

    private:

        string title;           ///< Título del álbum.
        Artist* artist;         ///< Puntero al artista del álbum.
        Date releaseDate;       ///< Fecha de lanzamiento del álbum.
        int num_songs;          ///< Número de canciones en el álbum.
        Song** songs;           ///< Array de punteros a las canciones del álbum.
        
        /**
         * @brief Copia los atributos de otro álbum a este álbum.
         * @param album El álbum del cual se copian los atributos.
         */
        void pasteAttributes(const Album& album);

    public:

        // CONSTRUCTORES Y DESTRUCTOR

        /**
         * @brief Constructor por defecto.
         */
        Album();

        /**
         * @brief Constructor con parámetros.
         * @param title Título del álbum.
         * @param artist Puntero al artista del álbum.
         * @param releaseDate Fecha de lanzamiento del álbum.
         * @param songs Array de punteros a las canciones del álbum.
         * @param num_songs Número de canciones en el álbum.
         */
        Album(string title, Artist* artist, Date releaseDate, Song** songs, int num_songs);

        /**
         * @brief Constructor copia.
         * @param album El álbum a copiar.
         */
        Album(const Album& album) { this->pasteAttributes(album); }

        /**
         * @brief Destructor.
         * @warning Sólo libera la memoria del array de punteros a canciones, no de las canciones ni del artista, ya que el álbum no es el propietario de esos objetos.
         */
        ~Album();

        // GETTERS

        /**
         * @brief Obtiene el título del álbum.
         * @return El título del álbum.
         */
        inline string getTitle() const { return this->title; }

        /**
         * @brief Obtiene el artista del álbum.
         * @return Puntero al artista del álbum.
         */
        inline Artist* getArtist() const { return this->artist; }

        /**
         * @brief Obtiene la fecha de lanzamiento del álbum.
         * @return La fecha de lanzamiento del álbum.
         */
        inline Date getReleaseDate() const { return this->releaseDate; }

        /**
         * @brief Obtiene el número de canciones en el álbum.
         * @return El número de canciones en el álbum.
         */
        inline int getNumSongs() const { return this->num_songs; }

        /**
         * @brief Obtiene una canción del álbum.
         * @param i Índice de la canción a obtener.
         * @return Puntero a la canción solicitada.
         */
        inline Song* getSong(int i) const { return this->songs[i]; }

        // SETTERS

        /**
         * @brief Establece el título del álbum.
         * @param title El nuevo título del álbum.
         */
        inline void setTitle(string title) { this->title = title; }

        /**
         * @brief Establece el artista del álbum.
         * @param artist El nuevo artista del álbum.
         */
        inline void setArtist(Artist* artist) { this->artist = artist; }

        /**
         * @brief Establece la fecha de lanzamiento del álbum.
         * @param releaseDate La nueva fecha de lanzamiento del álbum.
         */
        inline void setReleaseDate(Date releaseDate) { this->releaseDate = releaseDate; }

        /**
         * @brief Establece las canciones del álbum.
         * @param num_songs El número de canciones en el álbum.
         * @param songs El array de punteros a las canciones del álbum.
         */
        void setNewSongs(int num_songs, Song** songs);

        // SOBRECARGAS DE OPERADORES

        /**
         * @brief Sobrecarga del operador de asignación.
         * @param album El álbum a asignar.
         * @return Referencia al álbum asignado.
         */
        Album& operator=(const Album& album);

        /**
         * @brief Sobrecarga del operador de indexación.
         * @param i Índice de la canción a obtener.
         * @return Referencia constante a la canción solicitada.
         */
        inline const Song& operator[](int i) const { return *this->songs[i]; }

        // OTROS MÉTODOS

        /**
         * @brief Añade una canción al álbum.
         * @param song La canción a añadir.
         * @return true si la canción se añadió correctamente, false en caso contrario.
         */
        bool addSong(Song* song);

};

/**
 * @brief Sobrecarga del operador de inserción para imprimir un álbum.
 * @param flujo Flujo de salida.
 * @param album Álbum a imprimir.
 * @return Referencia al flujo de salida.
 */
ostream& operator<<(ostream& flujo, const Album& album);

#endif