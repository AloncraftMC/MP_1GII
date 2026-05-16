/**
 * @file songlist.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase SongList.
 */

#include <fstream>
#include <sstream>
#include "songlist.h"

/**
 * @brief Constructor con parámetros.
 * @param file_path Ruta del archivo .txt con los datos de las canciones.
 * @param albumList Referencia a la lista de álbumes para asociar las canciones a los álbumes.
 */
SongList::SongList(string file_path, AlbumList& albumList){

    this->firstBlock = nullptr;
    this->lastBlock = nullptr;

    // Lectura del archivo de canciones

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
        string genreString;
        string durationString;
        string album;

        getline(dataSS, title, ';');
        getline(dataSS, genreString, ';');
        getline(dataSS, durationString, ';');
        getline(dataSS, album, ';');

        if(title.empty())           { cerr << "Error: Invalid row format." << endl; continue; }
        if(genreString.empty())     { cerr << "Error: Invalid row format." << endl; continue; }
        if(durationString.empty())  { cerr << "Error: Invalid row format." << endl; continue; }
        if(album.empty())           { cerr << "Error: Invalid row format." << endl; continue; }

        Genre genre;

        if(genreString == "POP")                genre = Genre::POP;
        else if(genreString == "ROCK")          genre = Genre::ROCK;
        else if(genreString == "HIPHOP")        genre = Genre::HIPHOP;
        else if(genreString == "COUNTRY")       genre = Genre::COUNTRY;
        else if(genreString == "JAZZ")          genre = Genre::JAZZ;
        else if(genreString == "BLUES")         genre = Genre::BLUES;
        else if(genreString == "ELECTRONIC")    genre = Genre::ELECTRONIC;
        else if(genreString == "REGGAE")        genre = Genre::REGGAE;
        else if(genreString == "CLASSICAL")     genre = Genre::CLASSICAL;
        else if(genreString == "FOLK")          genre = Genre::FOLK;
        else if(genreString == "METAL")         genre = Genre::METAL;
        else                                    genre = Genre::UNKNOWN;

        int duration = stoi(durationString);

        if(!this->addSong(title, genre, duration, albumList, album)) cerr << "Error: Song was not found and could not be added." << endl;

    }

    file.close();

}

/**
 * @brief Destructor.
 */
SongList::~SongList(){

    Block* block = firstBlock;

    while(block != nullptr){

        for(int i = 0; i < block->current_size; i++)
            delete block->list[i];

        Block* next = block->next;
        delete block;
        block = next;
        
    }
    
}

/**
 * @brief Añade una nueva canción a la lista.
 * @param title El título de la canción.
 * @param genre El género de la canción.
 * @param duration La duración de la canción en segundos.
 * @param albumList Referencia a la lista de álbumes para asociar la canción al álbum correspondiente.
 * @param album El título del álbum al que pertenece la canción.
 * @return true si la canción se añadió correctamente, false en caso contrario.
 */
bool SongList::addSong(string title, Genre genre, int duration, AlbumList& albumList, string album){

    // Búsqueda del álbum en la lista de álbumes

    bool found = false;
    Album* albumPtr = nullptr;

    for(int i = 0; i < albumList.getCurrentSize() && !found; i++){

        if(albumList.getAlbumById(i)->getTitle() == album){

            found = true;
            albumPtr =  albumList.getAlbumById(i);

        }

    }

    if(!found)  return false;

    // Creación de la canción y adición al álbum correspondiente

    Song* song = new Song(title, genre, duration);

    albumPtr->addSong(song);

    // Crear primer bloque si la lista de canciones está vacía

    if(this->lastBlock == nullptr){

        Block* first = new Block();

        first->current_size = 0;
        first->next = nullptr;

        this->lastBlock = first;
        this->firstBlock = first;

    }

    // Crear nuevo bloque si el último bloque de la lista de canciones está lleno

    Block* last = this->lastBlock;

    if(last->current_size == BLOCK_MAX_SIZE){

        Block* other = new Block();
        
        other->current_size = 0;
        other->next = nullptr;

        last->next = other;
        this->lastBlock = other;
        last = other;

    }

    // Añadir la canción al último bloque de la lista de canciones

    last->list[last->current_size++] = song;

    return true;

}

/**
 * @brief Busca canciones en la lista que coincidan con los criterios de búsqueda.
 * @param searchTerm El término de búsqueda para el título de la canción (puede ser una subcadena).
 * @param genre El género de la canción a buscar (puede ser UNKNOWN para no filtrar por género).
 * @param durationMin La duración mínima de la canción en segundos (puede ser -1 para no filtrar por duración mínima).
 * @param durationMax La duración máxima de la canción en segundos (puede ser -1 para no filtrar por duración máxima).
 * @param results Array de punteros a canciones donde se almacenarán los resultados encontrados.
 * @param maxResults El tamaño máximo del array de resultados.
 * @param numResults Variable donde se almacenará el número de resultados encontrados.
 * @return true si se encontraron canciones que coincidan con los criterios, false en caso contrario.
 */
bool SongList::findSong(string searchTerm, Genre genre, int durationMin, int durationMax, Song** results, int maxResults, int& numResults){

    numResults = 0;

    string genreString;

    switch(genre){

        case Genre::POP:            genreString = "POP"; break;
        case Genre::ROCK:           genreString = "ROCK"; break;
        case Genre::HIPHOP:         genreString = "HIPHOP"; break;
        case Genre::COUNTRY:        genreString = "COUNTRY"; break;
        case Genre::JAZZ:           genreString = "JAZZ"; break;
        case Genre::BLUES:          genreString = "BLUES"; break;
        case Genre::ELECTRONIC:     genreString = "ELECTRONIC"; break;
        case Genre::REGGAE:         genreString = "REGGAE"; break;
        case Genre::CLASSICAL:      genreString = "CLASSICAL"; break;
        case Genre::FOLK:           genreString = "FOLK"; break;
        case Genre::METAL:          genreString = "METAL"; break;
        default:                    genreString = "UNKNOWN"; break;
        
    }

    // Recorrido por bloques de la lista de canciones

    Block* block = this->firstBlock;

    while(block != nullptr){

        // Recorrido por canciones del bloque actual

        for(int i = 0; i < block->current_size; i++){

            if(numResults == maxResults)    return true;

            Song* song = block->list[i];

            if(!searchTerm.empty() && song->getTitle().find(searchTerm) == string::npos)    continue;
            if(genre != Genre::UNKNOWN && song->getGenre() != genreString)                  continue;
            if(durationMin != -1 && song->getDuration() < durationMin)                      continue;
            if(durationMax != -1 && song->getDuration() > durationMax)                      continue;

            // Añadir canción a resultados si coincide con criterios de búsqueda

            results[numResults++] = song;

        }

        block = block->next;

    }

    return numResults > 0;

}