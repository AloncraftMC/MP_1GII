/**
 * @file user.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase User.
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include "date.h"
#include "playlist.h"
#include "song.h"

using namespace std;

/**
 * @brief Enum para representar el género de un usuario.
 */
enum Gender {FEMALE, MALE, OTHER};

class Playlist;

/**
 * @brief Representa a un usuario.
 */
class User {

    private:

        string name;                     ///< Nombre y apellidos
        string email;                    ///< Correo electrónico
        Date birthdate;                  ///< Fecha de nacimiento
        Gender gender;                   ///< Género

        int max_saved_songs;             ///< Tamaño del vector `saved_songs`
        int max_playlists;               ///< Tamaño del vector `wishlist`

        int num_saved_songs;             ///< Número actual de canciones en `saved_songs`
        int num_playlists;               ///< Número actual de listas de reproducción en `playlists`

        Song** saved_songs;              ///< Array de punteros a las canciones guardadas por el usuario
        Playlist** playlists;            ///< Array de punteros a las playlists del usuario

        /**
         * @brief Inicializa los valores necesarios invocado por los constructores.
         */
        void init();

        /**
         * @brief Pega los valores de otro objeto al implícito asumiendo que es vacío.
         * @param user El objeto User del cual se pegarán los valores.
         */
        void pasteAttributes(const User& user);

    public:

        // CONSTRUCTORES Y DESTRUCTOR

        /**
         * @brief Constructor por defecto.
         */
        User();

        /**
         * @brief Constructor con parámetros.
         * @param name Nombre y apellidos del usuario.
         * @param email Correo electrónico del usuario.
         * @param birthdate Fecha de nacimiento del usuario.
         * @param gender Género del usuario.
         */
        User(string name, string email, Date birthdate, Gender gender);

        /**
         * @brief Constructor de copia.
         * @param user El objeto User del cual se copiarán los valores.
         */
        User(const User& user) { this->pasteAttributes(user); }

        /**
         * @brief Destructor.
         * @warning Sólo libera la memoria de los arrays de punteros a canciones y playlists, no de las canciones ni playlists en sí, ya que el usuario no es el propietario de esos objetos.
         */
        ~User();

        // GETTERS

        /**
         * @brief Obtiene el nombre del usuario.
         * @return El nombre del usuario.
         */
        inline string getName() const { return this->name; }

        /**
         * @brief Obtiene el correo electrónico del usuario.
         * @return El correo electrónico del usuario.
         */
        inline string getEmail() const { return this->email; }

        /**
         * @brief Obtiene la fecha de nacimiento del usuario.
         * @return La fecha de nacimiento del usuario.
         */
        inline Date getBirthdate() const { return this->birthdate; }

        /**
         * @brief Obtiene el género del usuario como string.
         * @return El género del usuario como string.
         */
        string getGender() const;
               
        /**
         * @brief Obtiene el número de canciones guardadas por el usuario.
         * @return El número de canciones guardadas por el usuario.
         */
        inline int getNumSavedSongs() const { return this->num_saved_songs; }

        /**
         * @brief Obtiene el número de playlists creadas por el usuario.
         * @return El número de playlists creadas por el usuario.
         */
        inline int getNumPlaylists() const { return this->num_playlists; }

        // SETTERS

        /**
         * @brief Establece el nombre del usuario.
         * @param name El nombre del usuario.
         */
        inline void setName(string name) { this->name = name; }

        /**
         * @brief Establece el correo electrónico del usuario.
         * @param email El correo electrónico del usuario.
         */
        inline void setEmail(string email) { this->email = email; }

        /**
         * @brief Establece la fecha de nacimiento del usuario.
         * @param birthdate La fecha de nacimiento del usuario.
         */
        inline void setBirthdate(Date birthdate) { this->birthdate = birthdate; }

        /**
         * @brief Establece el género del usuario.
         * @param gender El género del usuario.
         */
        inline void setGender(Gender gender) { this->gender = gender; }

        // SOBRECARGAS DE OPERADORES

        /**
         * @brief Sobrecarga del operador de asignación.
         * @param user El objeto User que se asignará al implícito.
         * @return Una referencia al objeto User resultante de la asignación.
         */
        User& operator=(const User& user);

        /**
         * @brief Sobrecarga del operador de indexación `[]` para acceder a las canciones guardadas por el usuario.
         * @param i El índice de la canción a acceder.
         * @return Una referencia a la canción en la posición dada del array `saved_songs`.
         */
        inline Song& operator[](int i) const { return *this->saved_songs[i]; }

        /**
         * @brief Sobrecarga del operador de indexación `()` para acceder a las playlists creadas por el usuario.
         * @param i El índice de la playlist a acceder.
         * @return Una referencia a la playlist en la posición dada del array `playlists`.
         */
        inline Playlist& operator()(int i) const { return *this->playlists[i]; }

        /**
         * @brief Sobrecarga del operador de indexación `()` para acceder a las canciones de una playlist específica.
         * @param i El índice de la playlist a la que pertenece la canción.
         * @param j El índice de la canción dentro de la playlist.
         * @return Una referencia a la canción en la posición dada dentro de la playlist dada.
         */
        const Song& operator()(int i, int j) const;

        // OTROS MÉTODOS

        /**
         * @brief Añade una canción a las canciones guardadas por el usuario si no está ya guardada.
         * @param song_to_add Puntero a la canción que se añadirá.
         * @return true si la canción se añadió exitosamente, false en caso contrario.
         */
        bool addSong(Song* song_to_add);

        /**
         * @brief Añade una playlist a las playlists creadas por el usuario si no está ya agregada.
         * @param playlist_to_add Puntero a la playlist que se añadirá.
         * @return true si la playlist se añadió exitosamente, false si no se pudo agregar.
         */
        bool addPlaylist(Playlist* playlist_to_add);

        /**
         * @brief Elimina una canción de las canciones guardadas por el usuario si está guardada.
         * @param song_to_delete Puntero a la canción que se eliminará.
         * @return true si la canción se eliminó exitosamente, false en caso contrario.
         */
        bool deleteSong(Song* song_to_delete);

        /**
         * @brief Elimina una playlist de las playlists creadas por el usuario si está creada.
         * @param playlist_to_delete Puntero a la playlist que se eliminará.
         * @return true si la playlist se eliminó exitosamente, false si no se pudo eliminar.
         */
        bool deletePlaylist(Playlist* playlist_to_delete);

        /**
         * @brief Crea una nueva playlist privada con las canciones dadas y la agrega a las playlists creadas por el usuario.
         * @param songs Array de punteros a las canciones que se agregarán a la nueva playlist.
         * @param num_songs El número de canciones en el array `songs`.
         * @param title El título de la nueva playlist.
         * @return true si la playlist se creó y agregó exitosamente, false si no se pudo crear o agregar la playlist.
         */
        bool createPlaylist(Song** songs, int num_songs, string title);
        
};

/**
 * @brief Sobrecarga del operador de inserción.
 * @param flujo Flujo de salida.
 * @param user Usuario a imprimir.
 * @return Referencia al flujo de salida.
 */
inline ostream& operator<<(ostream& flujo, const User& user){

    return flujo << user.getName() << " ("
                 << user.getEmail() << ") " << endl
                 << user.getBirthdate() << " | "
                 << user.getGender() << endl
                 << user.getNumSavedSongs() << " saved songs | "
                 << user.getNumPlaylists() << " created playlists" << endl;

}

#endif