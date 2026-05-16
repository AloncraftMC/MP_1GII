/**
 * @file artistlist.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase ArtistList.
 */

#include <fstream>
#include <sstream>
#include "artistlist.h"

/**
 * @brief Constructor con parámetros.
 * @param file_path Ruta del archivo .txt con los datos de los artistas.
 */
ArtistList::ArtistList(string file_path){

    this->current_size = 0;

    // Lectura del archivo de álbumes para cargar los artistas en la lista

    ifstream file(file_path);

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
    
        string albumTitle;
        string albumReleaseDate;
        string name;

        getline(dataSS, albumTitle, ';');
        getline(dataSS, albumReleaseDate, ';');
        getline(dataSS, name, ';');

        // Búsqueda del artista en la lista de artistas

        bool found = false;

        for(int i = 0; i < this->current_size; i++)
            if(this->list[i]->getName() == name)
                found = true;

        // Creación del artista y adición a la lista de artistas si no se encuentra

        if(!found && this->current_size < MAX_ARTISTS)
            this->list[this->current_size++] = new Artist(name);

    }

    file.close();

}

/**
 * @brief Destructor.
 */
ArtistList::~ArtistList() {

    for (int i = 0; i < this->current_size; i++)
        delete this->list[i];

}