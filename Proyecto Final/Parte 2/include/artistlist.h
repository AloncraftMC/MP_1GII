#ifndef ARTISTLIST_H
#define ASRTSTLIST_H

#include <iostream>
#include "artist.h"

using namespace std;

const int MAX_ARTISTS = 1000;

class ArtistList{

    private:

        int current_size;
        Artist* list[MAX_ARTISTS];

    public:

        ArtistList(string file_path);
        ~ArtistList();

        inline int     getCurrentSize() const       { return this->current_size; }
        inline Artist* getArtistById(int i) const   { return this->list[i]; }

};

#endif