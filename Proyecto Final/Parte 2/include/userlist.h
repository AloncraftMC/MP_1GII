/**
 * @file userlist.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase UserList.
 */

#ifndef USERLIST_H
#define USERLIST_H

#include <iostream>
#include "user.h"
#include "playlist.h"

using namespace std;

/**
 * @brief Capacidad máxima de la lista de usuarios.
 */
const int MAX_USERS = 1000;

/**
 * @brief Capacidad máxima de la lista de playlists.
 */
const int MAX_PLAYLISTS = 2000;

/**
 * @brief Representa una lista de usuarios.
 */
class UserList{

    private:

        int current_size;                       ///< Número actual de usuarios en la lista.
        User* list[MAX_USERS];                  ///< Array de punteros a los usuarios registrados en Spotifry.

        int number_of_playlists;                ///< Número total de playlists creadas por los usuarios.
        Playlist* playlists[MAX_PLAYLISTS];     ///< Array de punteros a las playlists creadas por los usuarios.

    public:

        // CONSTRUCTOR Y DESTRUCTOR

        /**
         * @brief Constructor con parámetros.
         * @param users_file_path Ruta del archivo .txt con los datos de los usuarios.
         * @param spotifry_db_file_path Ruta del archivo .txt con los datos de las canciones y playlists de los usuarios.
         */
        UserList(string users_file_path, string spotifry_db_file_path);

        /**
         * @brief Destructor.
         */
        ~UserList();

        // GETTERS

        /**
        * @brief Obtiene un puntero al usuario con el email dado.
        * @param email El email del usuario a buscar.
        * @return Un puntero al usuario con el email dado, o nullptr si no se encuentra ningún usuario con ese email.
        */
        User* getUserByEmail(string email);

        /**
         * @brief Obtiene el número actual de usuarios en la lista.
         * @return El número actual de usuarios en la lista.
         */
        inline int getCurrentSize() { return this->current_size; }

        /**
         * @brief Obtiene el número total de playlists creadas por los usuarios.
         * @return El número total de playlists creadas por los usuarios.
         */
        inline int getNumberOfPlaylists() { return this->number_of_playlists; }

        // OTROS MÉTODOS

        /**
         * @brief Añade un usuario a la lista de usuarios si no se ha alcanzado el límite máximo de usuarios.
         * @param user_to_add Un puntero al usuario que se desea añadir.
         * @return true si el usuario se añadió exitosamente, false en caso contrario.
         */
        bool addUser(User* user_to_add);

        /**
         * @brief Añade una playlist a la lista de playlists si no se ha alcanzado el límite máximo de playlists.
         * @param playlist_to_add Un puntero a la playlist que se desea añadir.
         * @return true si la playlist se añadió exitosamente, false en caso contrario.
         */
        bool addPlaylist(Playlist* playlist_to_add);

};

#endif