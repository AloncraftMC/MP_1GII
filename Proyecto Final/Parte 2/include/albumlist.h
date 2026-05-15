#ifndef ALBUMLIST_H
#define ALBUMLIST_H

#include <iostream>
#include "album.h"

using namespace std;

const int MAX_ALBUMS = 1000;

class SongList;
class ArtistList;

class AlbumList{

    private:

        int current_size;
        Album* list[MAX_ALBUMS];

    public:

        AlbumList(string file_path, ArtistList& artistList, SongList& songList);
        ~AlbumList();

        inline int    getCurrentSize() const        { return this->current_size; }
        inline Album* getAlbumById(int id) const    { return this->list[id]; }

        bool dump(string file_path);
        void printAlbum(string title) const;

};

#endif