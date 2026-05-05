#include "album.h"

void Album::pasteAttributes(const Album& album){

    this->title = album.title;
    this->artist = album.artist;
    this->releaseDate = album.releaseDate;
    this->num_songs = album.num_songs;
    this->songs = new Song*[album.num_songs];

    for(int i = 0; i < album.num_songs; i++)
        this->songs[i] = album.songs[i];

}

Album::Album(){

    this->title = "New album";
    this->artist = new Artist();
    this->releaseDate = Date();
    this->num_songs = 0;
    this->songs = nullptr;

}

Album::Album(string title, Artist* artist, Date releaseDate, Song** songs, int num_songs){

    this->title = title;
    this->artist = artist;
    this->releaseDate = releaseDate;
    this->num_songs = num_songs;
    
    if(num_songs > 0){

        this->songs = new Song*[num_songs];
        
        for(int i = 0; i < num_songs; i++)
            this->songs[i] = songs[i];

    }else{
        
        this->songs = nullptr;

    }

}

Album::~Album(){

    this->artist = nullptr;

    delete[] this->songs;
    this->songs = nullptr;

}

void Album::setNewSongs(int num_songs, Song** songs){

    this->num_songs = num_songs;

    delete[] this->songs;
    
    if(num_songs > 0){

        this->songs = new Song*[num_songs];

        for(int i = 0; i < num_songs; i++)
            this->songs[i] = songs[i];

    }else{

        this->songs = nullptr;

    }

}

Album& Album::operator=(const Album& album){

    if(&album != this){

        delete[] this->songs;
        this->pasteAttributes(album);

    }

    return *this;

}

ostream& operator<<(ostream& flujo, const Album& album){

    flujo << album.getTitle() << " - "
          << album.getArtist() << " ("
          << album.getReleaseDate() << ")" << endl << "["
          << album.getNumSongs() << " songs]" << endl;

    for(int i = 0; i < album.getNumSongs(); i++)
        flujo << i + 1 << ". " << album[i] << endl;

    return flujo;

}