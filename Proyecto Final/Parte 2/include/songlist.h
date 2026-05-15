#ifndef SONGLIST_H
#define SONGLIST_H

#include <iostream>
#include "albumlist.h"
#include "song.h"

using namespace std;

const int BLOCK_MAX_SIZE = 10;

struct Block{

    Song* list[BLOCK_MAX_SIZE];
    int current_size;
    Block* next;

};

class AlbumList;

class SongList{

    private:

        Block* firstBlock;
        Block* lastBlock;

    public:

        SongList(string file_path, AlbumList& albumList); //MOD
        ~SongList();

        bool addSong(string title, Genre genre, int duration, AlbumList &albumList, string album);
        bool findSong(string searchTerm, Genre genre, int durationMin, int durationMax, Song** results, int maxResults, int& numResults);

};

#endif