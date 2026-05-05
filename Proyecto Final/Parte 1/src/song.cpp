#include "song.h"

string Song::genreToString(Genre genre) {

    switch(genre){
        case POP:           return "Pop";
        case ROCK:          return "Rock";
        case HIPHOP:        return "Hiphop";
        case COUNTRY:       return "Country";
        case JAZZ:          return "Jazz";
        case BLUES:         return "Blues";
        case ELECTRONIC:    return "Electronic";
        case REGGAE:        return "Reggae";
        case CLASSICAL:     return "Classical";
        case FOLK:          return "Folk";
        case METAL:         return "Metal";
        default:            return "Unknown";
    }

}

Song::Song(){

    this->title = "Nueva canción";
    this->duration = 0;

}

Song::Song(string title, Genre genre, int duration){

    this->title = title;
    this->genre = genre;
    this->duration = duration;

}