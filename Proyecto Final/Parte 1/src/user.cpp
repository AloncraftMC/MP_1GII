#include "user.h"

void User::init(){

    this->max_saved_songs = 4;
    this->max_playlists = 4;

    this->num_saved_songs = 0;
    this->num_playlists = 0;

    this->saved_songs = new Song*[this->max_saved_songs];
    this->playlists = new Playlist*[this->max_playlists];

}

User::User(){

    this->name = "Nuevo usuario";
    this->email = "usuario@ejemplo.com";
    this->birthdate = Date();
    this->gender = OTHER;
    this->init();

}

User::User(string name, string email, Date birthdate, Gender gender){

    this->name = name;
    this->email = email;
    this->birthdate = birthdate;
    this->gender = gender;
    this->init();

}

bool User::addSong(Song* song_to_add){

    

}

bool User::addPlaylist(Playlist* playlist_to_add){



}

bool User::deleteSong(Song* song_to_delete){



}

bool User::deletePlaylist(Playlist* playlist_to_delete){



}

bool User::createPlaylist(Song** songs, int num_songs, string title){



}