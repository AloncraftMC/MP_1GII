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
        case Genre::POP:            return "Pop";
        case Genre::ROCK:           return "Rock";
        case Genre::HIPHOP:         return "Hiphop";
        case Genre::COUNTRY:        return "Country";
        case Genre::JAZZ:           return "Jazz";
        case Genre::BLUES:          return "Blues";
        case Genre::ELECTRONIC:     return "Electronic";
        case Genre::REGGAE:         return "Reggae";
        case Genre::CLASSICAL:      return "Classical";
        case Genre::FOLK:           return "Folk";
        case Genre::METAL:          return "Metal";
        default:                    return "Unknown";
    }

}