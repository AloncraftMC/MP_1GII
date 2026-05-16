/**
 * @file albumlist.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase AlbumList.
 */

#include <fstream>
#include <sstream>
#include "albumlist.h"
#include "artistlist.h"

/**
 * @brief Constructor con parámetros.
 * @param file_path Ruta del archivo .txt con los datos de los álbumes.
 * @param artistList Referencia a la lista de artistas para asociar los artistas a los álbumes.
 * @param songList Referencia a la lista de canciones para asociar las canciones a los álbumes.
 */
AlbumList::AlbumList(string file_path, ArtistList& artistList, SongList& songList){

    this->current_size = 0;

    // Lectura del archivo de álbumes

    ifstream file(file_path, ios::in);

    if(!file.is_open()){
        
        cerr << "Error: File could not be opened." << endl;
        return;

    }

    // Lectura de líneas

    string line;

    while(getline(file, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

        // Lectura de campos

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

        // Lectura de campos de fecha

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

        // Lectura de canciones

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

        // Búsqueda del artista en la lista de artistas

        Artist* artistPtr = nullptr;
        bool found = false;

        for(int i = 0; i < artistList.getCurrentSize() && !found; i++)
            if(artistList.getArtistById(i)->getName() == artistString)
                artistPtr = artistList.getArtistById(i);

        // Búsqueda de las canciones en la lista de canciones

        Song** emptySongs = new Song*[numSongs];

        for(int i = 0; i < numSongs; i++)
            emptySongs[i] = nullptr;

        // Creación del álbum y adición a la lista de álbumes

        Album* albumPtr = new Album(title, artistPtr, releaseDate, emptySongs, numSongs);

        this->list[this->current_size++] = albumPtr;

        delete[] emptySongs;
        delete[] songsString;

    }

    file.close();

}

/**
 * @brief Destructor.
 */
AlbumList::~AlbumList(){

    for(int i = 0; i < this->current_size; i++)
        delete this->list[i];

}

/**
 * @brief Guarda la lista de álbumes en un archivo .txt.
 * @param file_path Ruta del archivo .txt donde se guardarán los datos de los álbumes.
 * @return true si la operación fue exitosa, false en caso contrario.
 */
bool AlbumList::dump(string file_path){

    // Escritura del archivo de álbumes

    ofstream file(file_path);

    if(!file.is_open()) return false;

    for(int i = 0; i < this->current_size; i++){

        // Álbum actual

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

/**
 * @brief Imprime la información de un álbum dado su título.
 * @param title El título del álbum a imprimir.
 */
void AlbumList::printAlbum(string title) const {

    // Búsqueda del álbum por título

    bool found = false;

    for(int i = 0; i < this->current_size && !found; i++){

        if(this->list[i] != nullptr && this->list[i]->getTitle() == title){

            // Álbum encontrado
        
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