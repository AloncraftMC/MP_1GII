#include "user.h"

void User::init(){

    this->max_saved_songs = 4;
    this->max_playlists = 4;

    this->num_saved_songs = 0;
    this->num_playlists = 0;

    this->saved_songs = new Song*[this->max_saved_songs];
    this->playlists = new Playlist*[this->max_playlists];

}

void User::pasteAttributes(const User& user){

    this->name = user.name;
    this->email = user.email;
    this->birthdate = user.birthdate;
    this->gender = user.gender;

    this->max_saved_songs = user.max_saved_songs;
    this->max_playlists = user.max_playlists;

    this->num_saved_songs = user.num_saved_songs;
    this->num_playlists = user.num_playlists;

    this->saved_songs = new Song*[user.max_saved_songs];

    for(int i = 0; i < user.num_saved_songs; i++)
        this->saved_songs[i] = user.saved_songs[i];

    this->playlists = new Playlist*[user.max_playlists];

    for(int i = 0; i < user.num_playlists; i++)
        this->playlists[i] = user.playlists[i];

}

User::User(){

    this->name = "New user";
    this->email = "user@example.com";
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

User::~User(){

    delete[] this->saved_songs;
    delete[] this->playlists;

    this->saved_songs = nullptr;
    this->playlists = nullptr;

}

string User::getGender() const {

    switch(gender){
        case FEMALE:    return "Female";
        case MALE:      return "Male";
        case OTHER:     return "Other";
        default:        return "Unknown";
    }

}

User& User::operator=(const User& user){

    if(&user != this){

        delete[] this->saved_songs;
        delete[] this->playlists;
        this->pasteAttributes(user);

    }

    return *this;

}

const Song& User::operator()(int i, int j) const{
    return (*this->playlists[i])[j];
}

bool User::addSong(Song* song_to_add){

    // Ignorar si ya está guardada

    for(int i = 0; i < this->num_saved_songs; i++)
        if(this->saved_songs[i] == song_to_add) return false;
    
    // Doblar si está lleno

    if(this->num_saved_songs == this->max_saved_songs){

        if(this->max_saved_songs < 4)   this->max_saved_songs = 4;
        else                            this->max_saved_songs *= 2;

        Song** aux = new Song*[this->max_saved_songs];

        for(int i = 0; i < this->num_saved_songs; i++)
            aux[i] = this->saved_songs[i];

        delete[] this->saved_songs;
        this->saved_songs = aux;

    }

    // Añadir el nuevo elemento

    this->saved_songs[this->num_saved_songs] = song_to_add;
    this->num_saved_songs++;

    return true;

}

bool User::addPlaylist(Playlist* playlist_to_add){

    // Ignorar si ya está guardada

    for(int i = 0; i < this->num_playlists; i++)
        if(this->playlists[i] == playlist_to_add) return false;
    
    // Doblar si está lleno

    if(this->num_playlists == this->max_playlists){

        if(this->max_playlists < 4)   this->max_playlists = 4;
        else                          this->max_playlists *= 2;

        Playlist** aux = new Playlist*[this->max_playlists];

        for(int i = 0; i < this->num_playlists; i++)
            aux[i] = this->playlists[i];

        delete[] this->playlists;
        this->playlists = aux;

    }

    // Añadir el nuevo elemento

    this->playlists[this->num_playlists] = playlist_to_add;
    this->num_playlists++;

    return true;

}

bool User::deleteSong(Song* song_to_delete){

    // Encontrar la posición

    int pos = -1;

    for(int i = 0; i < this->num_saved_songs && pos == -1; i++)
        if(this->saved_songs[i] == song_to_delete)  pos = i;

    if(pos == -1) return false;

    // Desplazar los elementos de la derecha 1 posición a la izquierda

    for(int i = pos; i < this->num_saved_songs - 1; i++)
        this->saved_songs[i] = this->saved_songs[i + 1];

    // Eliminar el último elemento

    this->saved_songs[this->num_saved_songs - 1] = nullptr;
    this->num_saved_songs--;

    // Reducir si se queda a menos de la mitad del máximo

    if(this->num_saved_songs < this->max_saved_songs / 2){

        if(this->max_saved_songs / 2 < 4)   this->max_saved_songs = 4;
        else                                this->max_saved_songs /= 2;

        Song** aux = new Song*[this->max_saved_songs];

        for(int i = 0; i < this->num_saved_songs; i++)
            aux[i] = this->saved_songs[i];

        delete[] this->saved_songs;
        this->saved_songs = aux;

    }

    return true;

}

bool User::deletePlaylist(Playlist* playlist_to_delete){

    // Encontrar la posición

    int pos = -1;

    for(int i = 0; i < this->num_playlists && pos == -1; i++)
        if(this->playlists[i] == playlist_to_delete)  pos = i;

    if(pos == -1) return false;

    // Desplazar los elementos de la derecha 1 posición a la izquierda

    for(int i = pos; i < this->num_playlists - 1; i++)
        this->playlists[i] = this->playlists[i + 1];

    // Eliminar el último elemento

    this->playlists[this->num_playlists - 1] = nullptr;
    this->num_playlists--;

    // Reducir si se queda a menos de la mitad del máximo

    if(this->num_playlists < this->max_playlists / 2){

        if(this->max_playlists / 2 < 4)   this->max_playlists = 4;
        else                              this->max_playlists /= 2;

        Playlist** aux = new Playlist*[this->max_playlists];

        for(int i = 0; i < this->num_playlists; i++)
            aux[i] = this->playlists[i];

        delete[] this->playlists;
        this->playlists = aux;

    }

    return true;

}

bool User::createPlaylist(Song** songs, int num_songs, string title){

    Playlist* playlist = new Playlist(title, this, Date(), PRIVATE);

    for(int i = 0; i < num_songs; i++)
        playlist->addSong(songs[i], this);

    if(!this->addPlaylist(playlist)){

        delete playlist;
        return false;

    }

    return true;

}