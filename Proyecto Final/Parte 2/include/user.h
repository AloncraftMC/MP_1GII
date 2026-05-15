#ifndef USER_H
#define USER_H

#include <iostream>
#include "date.h"
#include "playlist.h"
#include "song.h"

using namespace std;

enum Gender {FEMALE, MALE, OTHER};

class Playlist;

class User {

    private:

        string name;                                // Nombre y apellidos
        string email;                               // Correo electrónico
        Date birthdate;                             // Fecha de nacimiento
        Gender gender;                              // Género

        int max_saved_songs;                        // Tamaño del vector "saved_songs"
        int max_playlists;                          // Tamaño del vector "wishlist"

        int num_saved_songs;                        // Número actual de canciones en "saved_songs"
        int num_playlists;                          // Número actual de listas de reproducción en "playlists"

        Song** saved_songs;                         // La lista de canciones guardadas
        Playlist** playlists;                       // La lista de playlists del usuario

        void init();                                // Inicializa los valores necesarios invocado por los constructores
        void pasteAttributes(const User& user);     // Pega los valores de otro objeto al implícito asumiendo que es vacío

    public:

        User();
        User(string name, string email, Date birthdate, Gender gender);
        User(const User& user) { this->pasteAttributes(user); }
        ~User();

        inline string getName() const               { return this->name; }
        inline string getEmail() const              { return this->email; }
        inline Date   getBirthdate() const          { return this->birthdate; }
               string getGender() const;
        inline int    getNumSavedSongs() const      { return this->num_saved_songs; }
        inline int    getNumPlaylists() const       { return this->num_playlists; }

        inline void setName(string name)            { this->name = name; }
        inline void setEmail(string email)          { this->email = email; }
        inline void setBirthdate(Date birthdate)    { this->birthdate = birthdate; }
        inline void setGender(Gender gender)        { this->gender = gender; }

                     User&     operator= (const User& user);
        inline       Song&     operator[](int i)        const { return *this->saved_songs[i]; }
        inline       Playlist& operator()(int i)        const { return *this->playlists[i]; }
               const Song&     operator()(int i, int j) const;

        bool addSong(Song* song_to_add);
        bool addPlaylist(Playlist* playlist_to_add);
        bool deleteSong(Song* song_to_delete);
        bool deletePlaylist(Playlist* playlist_to_delete);
        bool createPlaylist(Song** songs, int num_songs, string title);
        
};

inline ostream& operator<<(ostream& flujo, const User& user){

    return flujo << user.getName() << " ("
                 << user.getEmail() << ") " << endl
                 << user.getBirthdate() << " | "
                 << user.getGender() << endl
                 << user.getNumSavedSongs() << " saved songs | "
                 << user.getNumPlaylists() << " created playlists" << endl;

}

#endif