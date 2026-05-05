#ifndef ARTIST_H
#define ARTIST_H

#include <iostream>

using namespace std;

class Artist {

    private:

        string name;

    public:

        Artist() { this->name = "Nuevo artista"; }
        Artist(string name) { this->name = name; }

        inline string getName() const { return this->name; }
        
        inline void setName(string name) { this->name = name; }

};

inline ostream& operator<<(ostream& flujo, const Artist& artist) { return flujo << artist.getName(); }

#endif