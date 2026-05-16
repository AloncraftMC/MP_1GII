/**
 * @file playlist.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase Playlist.
 */

#include "playlist.h"

/**
 * @brief Inicializa la lista de canciones vacía y los contadores relacionados.
 */
void Playlist::init(){

    this->max_songs = 0;
    this->num_songs = 0;
    this->songs = new Song*[this->num_songs];

}

/**
 * @brief Copia los atributos de otra playlist a esta, asumiendo que esta está vacía.
 * @param playlist La playlist de la que se copiarán los atributos.
 * @warning Este método no libera la memoria del array `songs`, por lo que debe ser llamado solo en constructores o después de liberar la memoria del array.
 */
void Playlist::pasteAttributes(const Playlist& playlist){

    this->title = playlist.title;
    this->creator = playlist.creator;
    this->creationDate = playlist.creationDate;
    this->max_songs = playlist.max_songs;
    this->num_songs = playlist.num_songs;
    this->songs = new Song*[playlist.max_songs];

    for(int i = 0; i < playlist.num_songs; i++)
        this->songs[i] = playlist.songs[i];

    this->privacy = playlist.privacy;

}

/**
 * @brief Constructor por defecto.
 */
Playlist::Playlist(){

    this->title = "New playlist";
    this->creator = new User();
    this->creationDate = Date();
    this->init();
    this->privacy = PlaylistPrivacy::PUBLIC;

}

/**
 * @brief Constructor con parámetros.
 * @param title El título de la playlist.
 * @param creator El usuario creador de la playlist.
 * @param creationDate La fecha de creación de la playlist.
 * @param privacy La configuración de privacidad de la playlist.
 */
Playlist::Playlist(string title, User* creator, Date creationDate, PlaylistPrivacy privacy){

    this->title = title;
    this->creator = creator;
    this->creationDate = creationDate;
    this->init();
    this->privacy = privacy;

}

/**
 * @brief Destructor.
 * @warning Sólo libera la memoria del array de punteros a canciones, no de las canciones ni del creador, ya que la playlist no es el propietario de esos objetos.
 */
Playlist::~Playlist(){

    this->creator = nullptr;

    delete[] this->songs;
    this->songs = nullptr;

}

/**
 * @brief Añade una canción a la playlist si el usuario que la agrega es el creador de la playlist.
 * @param song La canción a añadir.
 * @param whoAddsIt El usuario que intenta añadir la canción.
 * @return true si la canción fue añadida exitosamente, false en caso contrario.
 */
bool Playlist::addSong(Song* song, User* whoAddsIt){

    if(whoAddsIt != this->creator)  return false;

    // Doblar si está lleno
        
    if(this->num_songs == this->max_songs){

        if(this->num_songs == 0 && this->max_songs == 0)    this->max_songs = 1;
        else                                                this->max_songs *= 2;

        Song** aux = new Song*[this->max_songs];

        for(int i = 0; i < this->num_songs; i++)
            aux[i] = this->songs[i];

        delete[] this->songs;
        this->songs = aux;

    }

    // Añadir el nuevo elemento

    this->songs[this->num_songs] = song;
    this->num_songs++;

    return true;

}

/**
 * @brief Elimina una canción de la playlist si el usuario que la elimina es el creador de la playlist.
 * @param song La canción a eliminar.
 * @param whoRemovesIt El usuario que intenta eliminar la canción.
 * @return true si la canción fue eliminada exitosamente, false en caso contrario.
 */
bool Playlist::deleteSong(Song* song, User* whoRemovesIt){

    if(whoRemovesIt != this->creator)  return false;

    int pos = -1;

    // Encontrar la posición

    for(int i = 0; i < this->num_songs && pos == -1; i++)
        if(this->songs[i] == song)  pos = i;

    if(pos == -1)   return false;

    // Desplazar los elementos de la derecha 1 posición a la izquierda

    for(int i = pos; i < this->num_songs - 1; i++)
        this->songs[i] = this->songs[i + 1];

    // Eliminar el último elemento

    this->songs[this->num_songs - 1] = nullptr;
    this->num_songs--;

    // Reducir si se queda a menos de la mitad del máximo

    if(this->num_songs < this->max_songs / 2){

        this->max_songs /= 2;

        Song** aux = new Song*[this->max_songs];

        for(int i = 0; i < this->num_songs; i++)
            aux[i] = this->songs[i];

        delete[] this->songs;
        this->songs = aux;

    }

    return true;

}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param playlist La playlist a asignar a esta.
 * @return Una referencia a esta playlist después de la asignación.
 */
Playlist& Playlist::operator=(const Playlist& playlist){

    if(&playlist != this){

        delete[] this->songs;
        this->pasteAttributes(playlist);

    }

    return *this;

}

/**
 * @brief Sobrecarga del operador de inserción para imprimir una playlist.
 * @param flujo Flujo de salida.
 * @param playlist Playlist a imprimir.
 * @return Referencia al flujo de salida.
 */
ostream& operator<<(ostream& flujo, const Playlist& playlist){

    flujo << playlist.getTitle() << " | "
          << playlist.getNumSongs() << " songs" << endl << "Created by "
          << playlist.getCreator().getName() << " on "
          << playlist.getCreationDate() << endl;

    for(int i = 0; i < playlist.getNumSongs(); i++)
        flujo << playlist[i] << endl;

    return flujo;

}