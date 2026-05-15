#include <fstream>
#include <sstream>
#include "artistlist.h"

ArtistList::ArtistList(string file_path){

    this->current_size = 0;

    ifstream file(file_path);

    string line;

    while(getline(file, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

        stringstream dataSS(line);
    
        string albumTitle;
        string albumReleaseDate;
        string name;

        getline(dataSS, albumTitle, ';');
        getline(dataSS, albumReleaseDate, ';');
        getline(dataSS, name, ';');

        bool found = false;

        for(int i = 0; i < this->current_size; i++)
            if(this->list[i]->getName() == name)
                found = true;

        if(!found && this->current_size < MAX_ARTISTS)
            this->list[this->current_size++] = new Artist(name);

    }

    file.close();

}

ArtistList::~ArtistList() {

    for (int i = 0; i < this->current_size; i++)
        delete this->list[i];

}