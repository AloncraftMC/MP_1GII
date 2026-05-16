/**
 * @file song.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase Song.
 */

#include "song.h"

/**
 * @brief Constructor por defecto.
 */
Song::Song(){

    this->title = "New song";
    this->duration = 0;

}

/**
 * @brief Constructor con parámetros.
 * @param title El título de la canción.
 * @param genre El género de la canción.
 * @param duration La duración de la canción en segundos.
 */
Song::Song(string title, Genre genre, int duration){

    this->title = title;
    this->genre = genre;
    this->duration = duration;

}

/**
 * @brief Obtiene el género de la canción como una cadena de texto.
 * @return El género de la canción como una cadena de texto.
 */
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