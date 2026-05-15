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
        case Genre::POP:            return "POP";
        case Genre::ROCK:           return "ROCK";
        case Genre::HIPHOP:         return "HIPHOP";
        case Genre::COUNTRY:        return "COUNTRY";
        case Genre::JAZZ:           return "JAZZ";
        case Genre::BLUES:          return "BLUES";
        case Genre::ELECTRONIC:     return "ELECTRONIC";
        case Genre::REGGAE:         return "REGGAE";
        case Genre::CLASSICAL:      return "CLASSICAL";
        case Genre::FOLK:           return "FOLK";
        case Genre::METAL:          return "METAL";
        default:                    return "UNKNOWN";
    }

}