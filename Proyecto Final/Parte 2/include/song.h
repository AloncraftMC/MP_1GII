/**
 * @file song.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase Song.
 */

#ifndef SONG_H
#define SONG_H

#include <iostream>

using namespace std;

/**
 * @brief Enum para los géneros musicales.
 */
enum Genre {POP, ROCK, HIPHOP, COUNTRY, JAZZ, BLUES, ELECTRONIC, REGGAE, CLASSICAL, FOLK, METAL, UNKNOWN};

/**
 * @class Song
 * @brief Representa una canción con un título, un género y una duración.
 */
class Song {

    private:

        string title;       ///< Título de la canción
        Genre genre;        ///< Género de la canción
        int duration;       ///< Duración de la canción en segundos

    public:

        // CONSTRUCTORES

        /**
         * @brief Constructor por defecto.
         */
        Song();

        /**
         * @brief Constructor con parámetros.
         * @param title El título de la canción.
         * @param genre El género de la canción.
         * @param duration La duración de la canción en segundos.
         */
        Song(string title, Genre genre, int duration);

        // GETTERS

        /**
         * @brief Obtiene el título de la canción.
         * @return El título de la canción.
         */
        inline string getTitle() const { return this->title; }
        
        /**
         * @brief Obtiene el género de la canción como una cadena de texto.
         * @return El género de la canción como una cadena de texto.
         */
        string getGenre() const;

        /**
         * @brief Obtiene la duración de la canción en segundos.
         * @return La duración de la canción en segundos.
         */
        inline int getDuration() const { return this->duration; }

        // SETTERS

        /**
         * @brief Establece el título de la canción.
         * @param title El nuevo título de la canción.
         */
        inline void setTitle(string title) { this->title = title; }
        
        /**
         * @brief Establece el género de la canción.
         * @param genre El nuevo género de la canción.
         */
        inline void setGenre(Genre genre) { this->genre = genre; }

        /**
         * @brief Establece la duración de la canción.
         * @param duration La nueva duración de la canción en segundos.
         */
        inline void setDuration(int duration) { this->duration = duration; }

        // SOBRECARGAS DE OPERADORES

        /**
         * @brief Sobrecarga del operador de igualdad.
         * @param song La canción a comparar con esta.
         * @return true si las canciones son iguales (título, género y duración), false en caso contrario.
         */
        inline bool operator==(const Song& song) const {
            return this->title == song.title &&
                   this->genre == song.genre &&
                   this->duration == song.duration;
        }
        /**
         * @brief Sobrecarga del operador de desigualdad para comparar dos canciones.
         * @param song La canción a comparar con esta.
         * @return true si las canciones son diferentes, false en caso contrario.
         */
        inline bool operator!=(const Song& song) const { return !(*this == song); }

};

/**
 * @brief Sobrecarga del operador de inserción para imprimir una canción.
 * @param flujo Flujo de salida.
 * @param song Canción a imprimir.
 * @return Referencia al flujo de salida.
 */
inline ostream& operator<<(ostream& flujo, const Song& song){
    return flujo <<  song.getTitle() << " ("
                 <<  song.getDuration() / 60 << ":"             // Minutos
                 << (song.getDuration() % 60 < 10 ? "0" : "")   // Mostrar 0 en decenas si seg < 10
                 <<  song.getDuration() % 60 << ") | "          // Segundos
                 <<  song.getGenre();
}

#endif