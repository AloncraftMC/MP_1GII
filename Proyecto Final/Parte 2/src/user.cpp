#include "user.h"

/**
 * @brief Inicializa los valores necesarios invocado por los constructores.
 */
void User::init(){

    this->max_saved_songs = 4;
    this->max_playlists = 4;

    this->num_saved_songs = 0;
    this->num_playlists = 0;

    this->saved_songs = new Song*[this->max_saved_songs];
    this->playlists = new Playlist*[this->max_playlists];

}

/**
 * @brief Pega los valores de otro objeto al implícito asumiendo que es vacío.
 * @param user El objeto User del cual se pegarán los valores.
 */
void User::pasteAttributes(const User& user){

    this->name = user.name;
    this->email = user.email;
    this->birthdate = user.birthdate;
    this->gender = user.gender;

    this->max_saved_songs = user.max_saved_songs;
    this->max_playlists = user.max_playlists;

    this->num_saved_songs = user.num_saved_songs;
    this->num_playlists = user.num_playlists;

    this->saved_songs = new Song*[user.max_saved_songs];

    for(int i = 0; i < user.num_saved_songs; i++)
        this->saved_songs[i] = user.saved_songs[i];

    this->playlists = new Playlist*[user.max_playlists];

    for(int i = 0; i < user.num_playlists; i++)
        this->playlists[i] = user.playlists[i];

}

/**
 * @brief Constructor por defecto.
 */
User::User(){

    this->name = "New user";
    this->email = "user@example.com";
    this->birthdate = Date();
    this->gender = Gender::OTHER;
    this->init();

}

/**
 * @brief Constructor con parámetros.
 * @param name Nombre y apellidos del usuario.
 * @param email Correo electrónico del usuario.
 * @param birthdate Fecha de nacimiento del usuario.
 * @param gender Género del usuario.
 */
User::User(string name, string email, Date birthdate, Gender gender){

    this->name = name;
    this->email = email;
    this->birthdate = birthdate;
    this->gender = gender;
    this->init();

}

/**
 * @brief Destructor.
 * @warning Sólo libera la memoria de los arrays de punteros a canciones y playlists, no de las canciones ni playlists en sí, ya que el usuario no es el propietario de esos objetos.
 */
User::~User(){

    for(int i = 0; i < this->num_playlists; i++)
        delete this->playlists[i];

    delete[] this->saved_songs;
    delete[] this->playlists;

    this->saved_songs = nullptr;
    this->playlists = nullptr;

}

/**
 * @brief Obtiene el género del usuario como string.
 * @return El género del usuario como string.
 */
string User::getGender() const {

    switch(gender){
        case Gender::FEMALE:    return "Female";
        case Gender::MALE:      return "Male";
        case Gender::OTHER:     return "Other";
        default:                return "Unknown";
    }

}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param user El objeto User que se asignará al implícito.
 * @return Una referencia al objeto User resultante de la asignación.
 */
User& User::operator=(const User& user){

    if(&user != this){

        delete[] this->saved_songs;
        delete[] this->playlists;
        this->pasteAttributes(user);

    }

    return *this;

}

/**
 * @brief Sobrecarga del operador de indexación `()` para acceder a las canciones de una playlist específica.
 * @param i El índice de la playlist a la que pertenece la canción.
 * @param j El índice de la canción dentro de la playlist.
 * @return Una referencia a la canción en la posición dada dentro de la playlist dada.
 */
const Song& User::operator()(int i, int j) const{
    return (*this->playlists[i])[j];
}

/**
 * @brief Añade una canción a las canciones guardadas por el usuario si no está ya guardada.
 * @param song_to_add Puntero a la canción que se añadirá.
 * @return true si la canción se añadió exitosamente, false en caso contrario.
 */
bool User::addSong(Song* song_to_add){

    // Ignorar si ya está guardada

    for(int i = 0; i < this->num_saved_songs; i++)
        if(this->saved_songs[i] == song_to_add) return false;
    
    // Doblar si está lleno

    if(this->num_saved_songs == this->max_saved_songs){

        if(this->max_saved_songs < 4)   this->max_saved_songs = 4;
        else                            this->max_saved_songs *= 2;

        Song** aux = new Song*[this->max_saved_songs];

        for(int i = 0; i < this->num_saved_songs; i++)
            aux[i] = this->saved_songs[i];

        delete[] this->saved_songs;
        this->saved_songs = aux;

    }

    // Añadir el nuevo elemento

    this->saved_songs[this->num_saved_songs] = song_to_add;
    this->num_saved_songs++;

    return true;

}

/**
 * @brief Añade una playlist a las playlists creadas por el usuario si no está ya añadida.
 * @param playlist_to_add Puntero a la playlist que se añadirá.
 * @return true si la playlist se añadió exitosamente, false en caso contrario.
 */
bool User::addPlaylist(Playlist* playlist_to_add){

    // Ignorar si ya está guardada

    for(int i = 0; i < this->num_playlists; i++)
        if(this->playlists[i] == playlist_to_add) return false;
    
    // Doblar si está lleno

    if(this->num_playlists == this->max_playlists){

        if(this->max_playlists < 4)   this->max_playlists = 4;
        else                          this->max_playlists *= 2;

        Playlist** aux = new Playlist*[this->max_playlists];

        for(int i = 0; i < this->num_playlists; i++)
            aux[i] = this->playlists[i];

        delete[] this->playlists;
        this->playlists = aux;

    }

    // Añadir el nuevo elemento

    this->playlists[this->num_playlists] = playlist_to_add;
    this->num_playlists++;

    return true;

}

/**
 * @brief Elimina una canción de las canciones guardadas por el usuario si está guardada.
 * @param song_to_delete Puntero a la canción que se eliminará.
 * @return true si la canción se eliminó exitosamente, false en caso contrario.
 */
bool User::deleteSong(Song* song_to_delete){

    // Encontrar la posición

    int pos = -1;

    for(int i = 0; i < this->num_saved_songs && pos == -1; i++)
        if(this->saved_songs[i] == song_to_delete)  pos = i;

    if(pos == -1) return false;

    // Desplazar los elementos de la derecha 1 posición a la izquierda

    for(int i = pos; i < this->num_saved_songs - 1; i++)
        this->saved_songs[i] = this->saved_songs[i + 1];

    // Eliminar el último elemento

    this->saved_songs[this->num_saved_songs - 1] = nullptr;
    this->num_saved_songs--;

    // Reducir si se queda a menos de la mitad del máximo

    if(this->num_saved_songs < this->max_saved_songs / 2){

        if(this->max_saved_songs / 2 < 4)   this->max_saved_songs = 4;
        else                                this->max_saved_songs /= 2;

        Song** aux = new Song*[this->max_saved_songs];

        for(int i = 0; i < this->num_saved_songs; i++)
            aux[i] = this->saved_songs[i];

        delete[] this->saved_songs;
        this->saved_songs = aux;

    }

    return true;

}

/**
 * @brief Elimina una playlist de las playlists creadas por el usuario si está creada.
 * @param playlist_to_delete Puntero a la playlist que se eliminará.
 * @return true si la playlist se eliminó exitosamente, false en caso contrario.
 */
bool User::deletePlaylist(Playlist* playlist_to_delete){

    // Encontrar la posición

    int pos = -1;

    for(int i = 0; i < this->num_playlists && pos == -1; i++)
        if(this->playlists[i] == playlist_to_delete)  pos = i;

    if(pos == -1) return false;

    // Desplazar los elementos de la derecha 1 posición a la izquierda

    for(int i = pos; i < this->num_playlists - 1; i++)
        this->playlists[i] = this->playlists[i + 1];

    // Eliminar el último elemento

    this->playlists[this->num_playlists - 1] = nullptr;
    this->num_playlists--;

    // Reducir si se queda a menos de la mitad del máximo

    if(this->num_playlists < this->max_playlists / 2){

        if(this->max_playlists / 2 < 4)   this->max_playlists = 4;
        else                              this->max_playlists /= 2;

        Playlist** aux = new Playlist*[this->max_playlists];

        for(int i = 0; i < this->num_playlists; i++)
            aux[i] = this->playlists[i];

        delete[] this->playlists;
        this->playlists = aux;

    }

    return true;

}

/**
 * @brief Crea una nueva playlist privada con las canciones dadas y la añade a las playlists creadas por el usuario.
 * @param songs Array de punteros a las canciones que se añadirán a la nueva playlist.
 * @param num_songs El número de canciones en el array `songs`.
 * @param title El título de la nueva playlist.
 * @return true si la playlist se creó y añadió exitosamente, false si no se pudo crear o añadir la playlist.
 */
bool User::createPlaylist(Song** songs, int num_songs, string title){

    Playlist* playlist = new Playlist(title, this, Date(), PRIVATE);

    for(int i = 0; i < num_songs; i++)
        playlist->addSong(songs[i], this);

    if(!this->addPlaylist(playlist)){

        delete playlist;
        return false;

    }

    return true;

}