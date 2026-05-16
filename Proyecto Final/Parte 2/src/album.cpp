/**
 * @file album.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase Album.
 */

#include "album.h"

/**
 * @brief Copia los atributos de otro álbum a este álbum.
 * @param album El álbum del cual se copian los atributos.
 */
void Album::pasteAttributes(const Album& album){

    this->title = album.title;
    this->artist = album.artist;
    this->releaseDate = album.releaseDate;
    this->num_songs = album.num_songs;
    this->songs = new Song*[album.num_songs];

    for(int i = 0; i < album.num_songs; i++)
        this->songs[i] = album.songs[i];

}

/**
 * @brief Constructor por defecto.
 */
Album::Album(){

    this->title = "New album";
    this->artist = new Artist();
    this->releaseDate = Date();
    this->num_songs = 0;
    this->songs = nullptr;

}

/**
 * @brief Constructor con parámetros.
 * @param title Título del álbum.
 * @param artist Puntero al artista del álbum.
 * @param releaseDate Fecha de lanzamiento del álbum.
 * @param songs Array de punteros a las canciones del álbum.
 * @param num_songs Número de canciones en el álbum.
 */
Album::Album(string title, Artist* artist, Date releaseDate, Song** songs, int num_songs){

    this->title = title;
    this->artist = artist;
    this->releaseDate = releaseDate;
    this->num_songs = num_songs;
    
    if(num_songs > 0){

        this->songs = new Song*[num_songs];
        
        for(int i = 0; i < num_songs; i++)
            this->songs[i] = songs[i];

    }else{
        
        this->songs = nullptr;

    }

}

/**
 * @brief Destructor.
 * @warning Sólo libera la memoria del array de punteros a canciones, no de las canciones ni del artista, ya que el álbum no es el propietario de esos objetos.
 */
Album::~Album(){

    this->artist = nullptr;

    delete[] this->songs;
    this->songs = nullptr;

}

/**
 * @brief Establece las canciones del álbum.
 * @param num_songs El número de canciones en el álbum.
 * @param songs El array de punteros a las canciones del álbum.
 */
void Album::setNewSongs(int num_songs, Song** songs){

    this->num_songs = num_songs;

    delete[] this->songs;
    
    if(num_songs > 0){

        this->songs = new Song*[num_songs];

        for(int i = 0; i < num_songs; i++)
            this->songs[i] = songs[i];

    }else{

        this->songs = nullptr;

    }

}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param album El álbum a asignar.
 * @return Referencia al álbum asignado.
 */
Album& Album::operator=(const Album& album){

    if(&album != this){

        delete[] this->songs;
        this->pasteAttributes(album);

    }

    return *this;

}

/**
 * @brief Añade una canción al álbum.
 * @param song Puntero a la canción a añadir.
 * @return true si la canción se añadió correctamente, false en caso contrario.
 */
bool Album::addSong(Song* song) {
    
    for(int i = 0; i < this->num_songs; i++) {

        if(this->songs[i] == nullptr) {
        
            this->songs[i] = song;
            return true;
        
        }
    
    }

    return false;

}

/**
 * @brief Sobrecarga del operador de inserción para imprimir un álbum.
 * @param flujo Flujo de salida.
 * @param album Álbum a imprimir.
 * @return Referencia al flujo de salida con la información del álbum.
 */
ostream& operator<<(ostream& flujo, const Album& album){

    flujo << album.getTitle() << " - "
          << album.getArtist() << " ("
          << album.getReleaseDate() << ")" << endl << "["
          << album.getNumSongs() << " songs]" << endl;

    for(int i = 0; i < album.getNumSongs(); i++)
        flujo << i + 1 << ". " << album[i] << endl;

    return flujo;

}