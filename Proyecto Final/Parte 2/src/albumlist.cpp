#include <fstream>
#include <sstream>
#include "albumlist.h"
#include "artistlist.h"

AlbumList::AlbumList(string file_path, ArtistList& artistList, SongList& songList){

    this->current_size = 0;

    ifstream file(file_path, ios::in);

    if(!file.is_open()){
        
        cerr << "Error: File could not be opened." << endl;
        return;

    }

    string line;

    while(getline(file, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

        stringstream dataSS(line);

        string title;
        string releaseDateString;
        string artistString;
        string numSongsString;

        getline(dataSS, title, ';');
        getline(dataSS, releaseDateString, ';');
        getline(dataSS, artistString, ';');
        getline(dataSS, numSongsString, ';');

        if(title.empty())               { cerr << "Error: Invalid row format." << endl; continue; }
        if(releaseDateString.empty())   { cerr << "Error: Invalid row format." << endl; continue; }
        if(artistString.empty())        { cerr << "Error: Invalid row format." << endl; continue; }
        if(numSongsString.empty())      { cerr << "Error: Invalid row format." << endl; continue; }

        stringstream releaseDateSS(releaseDateString);

        string dayString;
        string monthString;
        string yearString;

        getline(releaseDateSS, yearString, '/');
        getline(releaseDateSS, monthString, '/');
        getline(releaseDateSS, dayString, '/');
        
        if(yearString.empty())  { cerr << "Error: Invalid row format." << endl; continue; }
        if(monthString.empty()) { cerr << "Error: Invalid row format." << endl; continue; }
        if(dayString.empty())   { cerr << "Error: Invalid row format." << endl; continue; }

        int day = stoi(dayString);
        int month = stoi(monthString);
        int year = stoi(yearString);

        Date releaseDate = Date(day, month, year);

        int numSongs = stoi(numSongsString);

        string* songsString = new string[numSongs];
        bool empty = false;

        for(int i = 0; i < numSongs && !empty; i++){

            getline(dataSS, songsString[i], ';');

            if(songsString[i].empty()) empty = true;

        }

        if(empty){
            
            cerr << "Error: Invalid row format." << endl;
            delete[] songsString;    
            continue;
        
        }

        Artist* artistPtr = nullptr;
        bool found = false;

        for(int i = 0; i < artistList.getCurrentSize() && !found; i++)
            if(artistList.getArtistById(i)->getName() == artistString)
                artistPtr = artistList.getArtistById(i);

        Song** emptySongs = new Song*[numSongs];

        for(int i = 0; i < numSongs; i++)
            emptySongs[i] = nullptr;

        Album* albumPtr = new Album(title, artistPtr, releaseDate, emptySongs, numSongs);

        this->list[this->current_size++] = albumPtr;

        delete[] emptySongs;
        delete[] songsString;

    }

    file.close();

}

AlbumList::~AlbumList(){

    for(int i = 0; i < this->current_size; i++)
        delete this->list[i];

}

bool AlbumList::dump(string file_path){

    ofstream file(file_path);

    if(!file.is_open()) return false;

    for(int i = 0; i < this->current_size; i++){

        Album* album = this->list[i];

        if(album == nullptr) continue;

        file <<  album->getTitle() << ";"
             <<  album->getReleaseDate().getYear() << "/"
             <<  album->getReleaseDate().getMonth() << "/"
             <<  album->getReleaseDate().getDay() << ";"
             << (album->getArtist() ? album->getArtist()->getName() : "Unknown") << ";"
             <<  album->getNumSongs();

        for(int j = 0; j < album->getNumSongs(); j++){

            Song* song = album->getSong(j);

            if(song != nullptr)
                file << ";" << song->getTitle();
            else
                file << ";[X]";

        }

        file << endl;

    }

    file.close();

    return true;

}

void AlbumList::printAlbum(string title) const {

    bool found = false;

    for(int i = 0; i < this->current_size && !found; i++){

        if(this->list[i] != nullptr && this->list[i]->getTitle() == title){
        
            found = true;

            Album* album = this->list[i];

            cout << "Album: " << album->getTitle();

            if(album->getArtist() != nullptr)
                cout << ", Artist: " << album->getArtist()->getName();
            else
                cout << ", Artist: Unknown";

            cout << ", Release Date: " << album->getReleaseDate() << endl;
            cout << "Songs:" << endl;
            
            for(int j = 0; j < album->getNumSongs(); j++){

                Song* song = album->getSong(j);

                if(song != nullptr)
                    cout << "  - " << song->getTitle()
                         << "\tGenre: " << song->getGenre()
                         << ", Duration: "
                         << song->getDuration() / 60 << "m "            // Minutos
                         << song->getDuration() % 60 << "s" << endl;    // Segundos

            }

        }

    }

    if(!found) cout << "Album \"" << title << "\" was not found." << endl;

}