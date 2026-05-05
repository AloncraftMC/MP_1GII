#include "song.h"

Song::Song(){

    this->title = "New song";
    this->duration = 0;

}

Song::Song(string title, Genre genre, int duration){

    this->title = title;
    this->genre = genre;
    this->duration = duration;

}

string Song::getGenre() const {

    switch(this->genre){
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