#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include "date.h"
#include "song.h"
#include "user.h"

using namespace std;

enum PlaylistPrivacy {PUBLIC, PRIVATE};

class User;

class Playlist {

    private:

        string title;
        User* creator;
        Date creationDate;
        int max_songs;
        int num_songs;
        Song** songs;
        PlaylistPrivacy privacy;

        void init();
        void pasteAttributes(const Playlist& playlist);

    public:

        Playlist();
        Playlist(string title, User* creator, Date creationDate, PlaylistPrivacy privacy);
        Playlist(const Playlist& playlist) { this->pasteAttributes(playlist); }
        ~Playlist();

        inline       string          getTitle() const         { return this->title; }
        inline const User&           getCreator() const       { return *this->creator; }
        inline       Date            getCreationDate() const  { return this->creationDate; }
        inline       int             getMaxSongs() const      { return this->max_songs; }
        inline       int             getNumSongs() const      { return this->num_songs; }
        inline       PlaylistPrivacy getPrivacy() const       { return this->privacy; }

        inline void setTitle(string title)              { this->title = title; }
        inline void setCreationDate(Date creationDate)  { this->creationDate = creationDate; }
        inline void setPrivacy(PlaylistPrivacy privacy) { this->privacy = privacy; }

        bool addSong(Song* song, User* whoAddsIt);
        bool deleteSong(Song* song, User* whoRemovesIt);

                     Playlist& operator= (const Playlist& playlist);
        inline       bool      operator==(const Playlist& playlist) { return this->title == playlist.title && this->creator == playlist.creator; }
        inline       bool      operator!=(const Playlist& playlist) { return !(*this == playlist); }
        inline const Song&     operator[](int i) const              { return *this->songs[i]; }

};

ostream& operator<<(ostream& flujo, const Playlist& playlist);

#endif