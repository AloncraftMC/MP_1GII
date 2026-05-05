#include "playlist.h"

void Playlist::init(){

    this->max_songs = 0;
    this->num_songs = 0;
    this->songs = new Song*[this->num_songs];

}

void Playlist::pasteAttributes(const Playlist& playlist){

    this->title = playlist.title;
    this->creator = playlist.creator;
    this->creationDate = playlist.creationDate;
    this->max_songs = playlist.max_songs;
    this->num_songs = playlist.num_songs;
    this->songs = new Song*[playlist.max_songs];

    for(int i = 0; i < playlist.num_songs; i++)
        this->songs[i] = playlist.songs[i];

    this->privacy = playlist.privacy;

}

Playlist::Playlist(){

    this->title = "New playlist";
    this->creator = new User();
    this->creationDate = Date();
    this->init();
    this->privacy = PUBLIC;

}

Playlist::Playlist(string title, User* creator, Date creationDate, PlaylistPrivacy privacy){

    this->title = title;
    this->creator = creator;
    this->creationDate = creationDate;
    this->init();
    this->privacy = privacy;

}

Playlist::~Playlist(){

    this->creator = nullptr;

    delete[] this->songs;
    this->songs = nullptr;

}

bool Playlist::addSong(Song* song, User* whoAddsIt){

    if(whoAddsIt != this->creator)  return false;

    // Doblar si está lleno
        
    if(this->num_songs == this->max_songs){

        if(this->num_songs == 0 && this->max_songs == 0)    this->max_songs = 1;
        else                                                this->max_songs *= 2;

        Song** aux = new Song*[this->max_songs];

        for(int i = 0; i < this->num_songs; i++)
            aux[i] = this->songs[i];

        delete[] this->songs;
        this->songs = aux;

    }

    // Añadir el nuevo elemento

    this->songs[this->num_songs] = song;
    this->num_songs++;

    return true;

}

bool Playlist::deleteSong(Song* song, User* whoRemovesIt){

    if(whoRemovesIt != this->creator)  return false;

    int pos = -1;

    // Encontrar la posición

    for(int i = 0; i < this->num_songs && pos == -1; i++)
        if(this->songs[i] == song)  pos = i;

    if(pos == -1)   return false;

    // Desplazar los elementos de la derecha 1 posición a la izquierda

    for(int i = pos; i < this->num_songs - 1; i++)
        this->songs[i] = this->songs[i + 1];

    // Eliminar el último elemento

    this->songs[this->num_songs - 1] = nullptr;
    this->num_songs--;

    // Reducir si se queda a menos de la mitad del máximo

    if(this->num_songs < this->max_songs / 2){

        this->max_songs /= 2;

        Song** aux = new Song*[this->max_songs];

        for(int i = 0; i < this->num_songs; i++)
            aux[i] = this->songs[i];

        delete[] this->songs;
        this->songs = aux;

    }

    return true;

}

Playlist& Playlist::operator=(const Playlist& playlist){

    if(&playlist != this){

        delete[] this->songs;
        this->pasteAttributes(playlist);

    }

    return *this;

}

ostream& operator<<(ostream& flujo, const Playlist& playlist){

    flujo << playlist.getTitle() << " | "
          << playlist.getNumSongs() << " songs" << endl << "Created by "
          << playlist.getCreator().getName() << " on "
          << playlist.getCreationDate() << endl;

    for(int i = 0; i < playlist.getNumSongs(); i++)
        flujo << playlist[i] << endl;

    return flujo;

}