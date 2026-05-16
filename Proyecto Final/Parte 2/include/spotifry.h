/**
 * @file spotifry.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase Spotifry.
 */

#ifndef SPOTIFRY_H
#define SPOTIFRY_H

#include <iostream>
#include "albumlist.h"
#include "artistlist.h"
#include "songlist.h"
#include "user.h"
#include "userlist.h"

using namespace std;

/**
 * @class Spotifry
 * @brief Representa la aplicación principal de gestión de música, que contiene listas de artistas, álbumes, canciones y usuarios.
 */
class Spotifry{

    private:
    
        ArtistList artists;     ///< Lista de artistas.
        AlbumList albums;       ///< Lista de álbumes.
        SongList songs;         ///< Lista de canciones.
        UserList users;         ///< Lista de usuarios.

    public:

        // CONSTRUCTOR
    
        /**
         * @brief Constructor con parámetros.
         * @param albums_file_path Ruta del archivo .txt con los datos de los álbumes.
         * @param songs_file_path Ruta del archivo .txt con los datos de las canciones.
         * @param users_file_path Ruta del archivo .txt con los datos de los usuarios.
         * @param spotifry_db_file_path Ruta del archivo .txt con los datos de las canciones y playlists de los usuarios.
         */
        Spotifry(string albums_file_path, string songs_file_path, string users_file_path, string spotifry_db_file_path);

        // GETTERS

        /**
         * @brief Obtiene la lista de canciones.
         * @return Referencia a la lista de canciones.
         */
        inline SongList& getSongList() { return this->songs; }

        /**
         * @brief Obtiene la lista de artistas.
         * @return Referencia a la lista de artistas.
         */
        inline AlbumList& getAlbumList() { return this->albums; }

        /**
         * @brief Obtiene la lista de usuarios.
         * @return Referencia a la lista de usuarios.
         */
        inline UserList& getUserList() { return this->users; }

        // OTROS MÉTODOS

        /**
         * @brief Crea una nueva playlist para un usuario dado su email, el título de la playlist y los nombres de las canciones a incluir en la playlist.
         * @param user_email El email del usuario para el cual se creará la playlist.
         * @param playlist_title El título de la nueva playlist.
         * @param num_songs El número de canciones a incluir en la playlist.
         * @param song_names Un array de strings con los nombres de las canciones a incluir en la playlist.
         * @return true si la playlist se creó correctamente, false en caso contrario.
         */
        bool createPlaylist(string user_email, string playlist_title, int num_songs, string* song_names);
        
        /**
         * @brief Lee el contenido de un archivo.
         * @param nombre Ruta del archivo a leer.
         * @return Contenido del archivo.
         */
        string leerArchivo(const string& nombre);

        /**
         * @brief Reemplaza una etiqueta en un string HTML por un valor dado.
         * @param html El string HTML donde se realizará el reemplazo.
         * @param tag La etiqueta a reemplazar (formato "{{TAG}}").
         * @param valor El valor que reemplazará a la etiqueta en el string HTML.
         * @return El string HTML resultante después de realizar el reemplazo.
         */
        string reemplazar(string html, const string& tag, const string& valor);

        /**
         * @brief Lee una plantilla HTML desde un archivo y devuelve su contenido como un string.
         * @param string Ruta del archivo de la plantilla HTML a leer.
         * @return Contenido de la plantilla HTML como un string.
         */
        string leerTemplateHtml(string string);

        /**
         * @brief Genera un string HTML con la información de un álbum dado su título.
         * @param albumTitle El título del álbum para el cual se generará el HTML.
         * @return Un string HTML con la información del álbum, o un mensaje de error si el álbum no se encuentra.
         */
        int numPlaylists(string userEmail);

        /**
         * @brief Obtiene el número de canciones guardadas por un usuario dado su email.
         * @param userEmail El email del usuario para el cual se obtendrá el número de canciones guardadas.
         * @return El número de canciones guardadas por el usuario, o -1 si el usuario no se encuentra.
         */
        int numSongs(string userEmail);

        /**
         * @brief Obtiene un ejemplo de el artista más escuchado por un usuario dado su email.
         * @param userEmail El email del usuario para el cual se obtendrá el artista más escuchado.
         * @return Coldplay
         */
        string artistaTop(string userEmail);
        
        /**
         * @brief Genera un string HTML con la información de las playlists de un usuario dado su email.
         * @param userEmail El email del usuario para el cual se generará el HTML de las playlists.
         * @return Un string HTML con la información de las playlists del usuario, o una cadena vacía si el usuario no se encuentra o no tiene playlists.
         */
        string generarPlaylists(string userEmail);

        /**
         * @brief Genera un string HTML con la información de las canciones guardadas de un usuario dado su email.
         * @param userEmail El email del usuario para el cual se generará el HTML de las canciones guardadas.
         * @return Un string HTML con la información de las canciones guardadas del usuario, o una cadena vacía si el usuario no se encuentra o no tiene canciones guardadas.
         */
        string generarCanciones(string userEmail);

};

#endif