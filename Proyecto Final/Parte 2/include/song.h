#ifndef SONG_H
#define SONG_H

#include <iostream>

using namespace std;

enum Genre {POP, ROCK, HIPHOP, COUNTRY, JAZZ, BLUES, ELECTRONIC, REGGAE, CLASSICAL, FOLK, METAL, UNKNOWN};

class Song {

    private:

        string title;
        Genre genre;
        int duration;

    public:

        Song();
        Song(string title, Genre genre, int duration);

        inline string getTitle() const      { return this->title; }
               string getGenre() const;
        inline int    getDuration() const   { return this->duration; }

        inline void setTitle(string title)      { this->title = title; }
        inline void setGenre(Genre genre)       { this->genre = genre; }
        inline void setDuration(int duration)   { this->duration = duration; }

        inline bool operator==(const Song& song) const {
            return this->title == song.title &&
                   this->genre == song.genre &&
                   this->duration == song.duration;
        }
        inline bool operator!=(const Song& song) const { return !(*this == song); }

};

inline ostream& operator<<(ostream& flujo, const Song& song){
    return flujo <<  song.getTitle() << " ("
                 <<  song.getDuration() / 60 << ":"             // Minutos
                 << (song.getDuration() % 60 < 10 ? "0" : "")   // Mostrar 0 en decenas si seg < 10
                 <<  song.getDuration() % 60 << ") | "          // Segundos
                 <<  song.getGenre();
}

#endif