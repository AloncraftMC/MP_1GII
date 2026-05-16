/**
 * @file playlist.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase Playlist.
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include "date.h"
#include "song.h"
#include "user.h"

using namespace std;

/**
 * @brief Enum para la privacidad de las playlists.
 */
enum PlaylistPrivacy {PUBLIC, PRIVATE};

class User;

/**
 * @class Playlist
 * @brief Representa una lista de reproducción creada por un usuario, con un título, una fecha de creación, una lista de canciones y una configuración de privacidad.
 */
class Playlist {

    private:

        string title;                   ///< Título de la playlist
        User* creator;                  ///< Puntero al usuario creador de la playlist
        Date creationDate;              ///< Fecha de creación de la playlist
        int max_songs;                  ///< Tamaño del array `songs`
        int num_songs;                  ///< Número de canciones en la playlist
        Song** songs;                   ///< Array de punteros a canciones en la playlist
        PlaylistPrivacy privacy;        ///< Configuración de privacidad de la playlist

        /**
         * @brief Inicializa la lista de canciones vacía y los contadores relacionados.
         */
        void init();

        /**
         * @brief Copia los atributos de otra playlist a esta, asumiendo que esta está vacía.
         * @param playlist La playlist de la que se copiarán los atributos.
         * @warning Este método no libera la memoria del array `songs`, por lo que debe ser llamado solo en constructores o después de liberar la memoria del array.
         */
        void pasteAttributes(const Playlist& playlist);

    public:

        // CONSTRUCTORES Y DESTRUCTOR

        /**
         * @brief Constructor por defecto.
         */
        Playlist();

        /**
         * @brief Constructor con parámetros.
         * @param title Título de la playlist.
         * @param creator Puntero al usuario creador de la playlist.
         * @param creationDate Fecha de creación de la playlist.
         * @param privacy Configuración de privacidad de la playlist.
         */
        Playlist(string title, User* creator, Date creationDate, PlaylistPrivacy privacy);

        /**
         * @brief Constructor copia.
         * @param playlist La playlist a copiar.
         */
        Playlist(const Playlist& playlist) { this->pasteAttributes(playlist); }

        /**
         * @brief Destructor.
         * @warning Sólo libera la memoria del array de punteros a canciones, no de las canciones ni del creador, ya que la playlist no es el propietario de esos objetos.
         */
        ~Playlist();

        // GETTERS

        /**
         * @brief Obtiene el título de la playlist.
         * @return El título de la playlist.
         */
        inline string getTitle() const { return this->title; }

        /**
         * @brief Obtiene el creador de la playlist.
         * @return Una referencia constante al usuario creador de la playlist.
         */
        inline const User& getCreator() const { return *this->creator; }

        /**
         * @brief Obtiene la fecha de creación de la playlist.
         * @return La fecha de creación de la playlist.
         */
        inline Date getCreationDate() const { return this->creationDate; }

        /**
         * @brief Obtiene el número máximo de canciones en la playlist.
         * @return El número máximo de canciones en la playlist.
         */
        inline int getMaxSongs() const { return this->max_songs; }

        /**
         * @brief Obtiene el número de canciones en la playlist.
         * @return El número de canciones en la playlist.
         */
        inline int getNumSongs() const { return this->num_songs; }

        /**
         * @brief Obtiene la configuración de privacidad de la playlist.
         * @return La configuración de privacidad de la playlist.
         */
        inline PlaylistPrivacy getPrivacy() const { return this->privacy; }

        // SETTERS

        /**
         * @brief Establece el título de la playlist.
         * @param title El nuevo título de la playlist.
         */
        inline void setTitle(string title) { this->title = title; }

        /**
         * @brief Establece la fecha de creación de la playlist.
         * @param creationDate La nueva fecha de creación de la playlist.
         */
        inline void setCreationDate(Date creationDate) { this->creationDate = creationDate; }

        /**
         * @brief Establece la configuración de privacidad de la playlist.
         * @param privacy La nueva configuración de privacidad de la playlist.
         */
        inline void setPrivacy(PlaylistPrivacy privacy) { this->privacy = privacy; }

        // OTROS MÉTODOS

        /**
         * @brief Añade una canción a la playlist si el usuario que la añade es el creador de la playlist.
         * @param song La canción a añadir.
         * @param whoAddsIt El usuario que intenta añadir la canción.
         * @return true si la canción fue añadida exitosamente, false en caso contrario.
         */
        bool addSong(Song* song, User* whoAddsIt);

        /**
         * @brief Elimina una canción de la playlist si el usuario que la elimina es el creador de la playlist.
         * @param song La canción a eliminar.
         * @param whoRemovesIt El usuario que intenta eliminar la canción.
         * @return true si la canción fue eliminada exitosamente, false en caso contrario.
         */
        bool deleteSong(Song* song, User* whoRemovesIt);

        // SOBRECARGAS DE OPERADORES

        /**
         * @brief Sobrecarga del operador de asignación.
         * @param playlist La playlist a asignar a esta.
         * @return Una referencia a esta playlist después de la asignación.
         */
        Playlist& operator=(const Playlist& playlist);

        /**
         * @brief Sobrecarga del operador de igualdad.
         * @param playlist La playlist a comparar con esta.
         * @return true si las playlists son iguales (título y creador), false en caso contrario.
         */
        inline bool operator==(const Playlist& playlist) { return this->title == playlist.title && this->creator == playlist.creator; }
        
        /**
         * @brief Sobrecarga del operador de desigualdad.
         * @param playlist La playlist a comparar con esta.
         * @return true si las playlists son diferentes, false en caso contrario.
         */
        inline bool operator!=(const Playlist& playlist) { return !(*this == playlist); }

        /**
         * @brief Sobrecarga del operador de indexación para acceder a las canciones de la playlist.
         * @param i El índice de la canción a acceder.
         * @return Una referencia constante a la canción en la posición i de la playlist.
         */
        inline const Song& operator[](int i) const { return *this->songs[i]; }

};

/**
 * @brief Sobrecarga del operador de inserción para imprimir una playlist.
 * @param flujo Flujo de salida.
 * @param playlist Playlist a imprimir.
 * @return Referencia al flujo de salida.
 */
ostream& operator<<(ostream& flujo, const Playlist& playlist);

#endif