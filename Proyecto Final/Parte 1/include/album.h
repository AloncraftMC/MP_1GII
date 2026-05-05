#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include "artist.h"
#include "date.h"
#include "song.h"

using namespace std;

class Album {

    private:

        string title;
        Artist* artist;
        Date releaseDate;
        int num_songs;
        Song** songs;

        void pasteAttributes(const Album& album);

    public:

        Album();
        Album(string title, Artist* artist, Date releaseDate, Song** songs, int num_songs);
        Album(const Album& album) { this->pasteAttributes(album); }
        ~Album();

        inline string getTitle() const      { return this->title; }
        inline Artist getArtist() const     { return *this->artist; }
        inline Date getReleaseDate() const  { return this->releaseDate; }
        inline int getNumSongs() const      { return this->num_songs; }

        inline void setTitle(string title)              { this->title = title; }
        inline void setArtist(Artist* artist)           { this->artist = artist; }
        inline void setReleaseDate(Date releaseDate)    { this->releaseDate = releaseDate; }
               void setNewSongs(int num_songs, Song** songs);

                     Album& operator= (const Album& album);
        inline const Song&  operator[](int i) const { return *this->songs[i]; }

};

ostream& operator<<(ostream& flujo, const Album& album);

#endif