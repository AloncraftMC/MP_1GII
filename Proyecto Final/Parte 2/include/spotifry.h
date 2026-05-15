#ifndef SPOTIFRY_H
#define SPOTIFRY_H

#include <iostream>
#include "albumlist.h"
#include "artistlist.h"
#include "songlist.h"
#include "user.h"
#include "userlist.h"

using namespace std;

class Spotifry{

    private:
    
        ArtistList artists;
        AlbumList albums;
        SongList songs;
        UserList users;

    public:

        Spotifry(string albums_file_path, string songs_file_path, string users_file_path, string spotifry_db_file_path);

        inline SongList&  getSongList()  { return this->songs; }
        inline AlbumList& getAlbumList() { return this->albums; }
        
        bool createPlaylist(string user_email, string playlist_title, int num_songs, string* song_names);
        
        string leerArchivo(const string& nombre);
        string reemplazar(string html, const string& tag, const string& valor);

        string leerTemplateHtml(string string);

        int    numPlaylists(string userEmail);
        int    numSongs(string userEmail);
        string artistaTop(string userEmail);
        string generarPlaylists(string userEmail);
        string generarCanciones(string userEmail);


};

#endif