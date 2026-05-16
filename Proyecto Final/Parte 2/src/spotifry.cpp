/**
 * @file spotifry.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase Spotifry.
 */

#include <fstream>
#include <sstream>
#include "spotifry.h"

/**
 * @brief Constructor con parámetros.
 * @param albums_file_path Ruta del archivo .txt con los datos de los álbumes.
 * @param songs_file_path Ruta del archivo .txt con los datos de las canciones.
 * @param users_file_path Ruta del archivo .txt con los datos de los usuarios.
 * @param spotifry_db_file_path Ruta del archivo .txt con los datos de las canciones y playlists de los usuarios.
 */
Spotifry::Spotifry(string albums_file_path, string songs_file_path, string users_file_path, string spotifry_db_file_path)
    : artists(albums_file_path),
      albums(albums_file_path, artists, songs),
      songs(songs_file_path, albums),
      users(users_file_path, "")
      {

    // Lectura del archivo de base de datos de Spotifry para asociar canciones guardadas a los usuarios y crear las playlists de los usuarios

    ifstream file(spotifry_db_file_path);

    if(!file.is_open()){
        
        cerr << "Error: File could not be opened." << endl;
        return;

    }

    // Lectura de líneas

    string line;

    while(getline(file, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

        // Lectura de tipo de fila (USER o PLAYLIST)

        stringstream dataSS(line);
        string type;

        getline(dataSS, type, ';');

        if(type == "USER"){

            // Lectura de campos USER

            string email;
            string songsString;

            getline(dataSS, email, ';');
            getline(dataSS, songsString, ';');

            if(email.empty()) { cerr << "Error: Invalid row format." << endl; continue; }

            // Asociar canciones guardadas al usuario correspondiente

            User* user = this->users.getUserByEmail(email);

            if(user && !songsString.empty()){

                // Lectura de canciones guardadas por el usuario

                stringstream songsSS(songsString);
                string songName;

                while(getline(songsSS, songName, '|')){

                    if(songName.empty()) continue;

                    // Búsqueda de la canción por título en la lista de canciones para asociarla al usuario

                    int maxResults = 10;
                    int numResults = 0;
                    
                    Song** results = new Song*[maxResults];

                    if(this->songs.findSong(songName, Genre::UNKNOWN, -1, -1, results, maxResults, numResults)){

                        // Búsqueda de la canción entre los resultados encontrados para asociarla al usuario

                        bool found = false;

                        for(int i = 0; i < numResults && !found; i++){

                            if(results[i]->getTitle() == songName){
                                
                                user->addSong(results[i]);
                                found = true;

                            }

                        }

                    }

                    delete[] results;

                }

            }

        }else if(type == "PLAYLIST"){

            // Lectura de campos PLAYLIST

            string title;
            string creatorEmail;
            string creationDateString;
            string privacyString;
            string songsString;

            getline(dataSS, title, ';');
            getline(dataSS, creatorEmail, ';');
            getline(dataSS, creationDateString, ';');
            getline(dataSS, privacyString, ';');
            getline(dataSS, songsString, ';');

            if(title.empty())               { cerr << "Error: Invalid row format." << endl; continue; }
            if(creatorEmail.empty())        { cerr << "Error: Invalid row format." << endl; continue; }
            if(creationDateString.empty())  { cerr << "Error: Invalid row format." << endl; continue; }
            if(privacyString.empty())       { cerr << "Error: Invalid row format." << endl; continue; }

            // Búsqueda del usuario creador de la playlist en la lista de usuarios para asociarla playlist al usuario

            User* user = this->users.getUserByEmail(creatorEmail);

            if(user){

                // Lectura de campos de fecha

                stringstream creationDateSS(creationDateString);

                string yearString;
                string monthString;
                string dayString;

                getline(creationDateSS, yearString, '/');
                getline(creationDateSS, monthString, '/');
                getline(creationDateSS, dayString, '/');

                if(yearString.empty())  { cerr << "Error: Invalid row format." << endl; continue; }
                if(monthString.empty()) { cerr << "Error: Invalid row format." << endl; continue; }
                if(dayString.empty())   { cerr << "Error: Invalid row format." << endl; continue; }

                int year = stoi(yearString);
                int month = stoi(monthString);
                int day = stoi(dayString);

                Date creationDate = Date(day, month, year);

                // Lectura de campo de privacidad

                PlaylistPrivacy privacy;

                if(privacyString == "PUBLIC")       privacy = PlaylistPrivacy::PUBLIC;
                else if(privacyString == "PRIVATE") privacy = PlaylistPrivacy::PRIVATE;
                else                                { cerr << "Error: Invalid row format." << endl; continue; }

                // Conteo de canciones de la playlist

                stringstream numSongsSS(songsString);
                string aux;
                
                int numSongsAux = 0;

                while(getline(numSongsSS, aux, '|'))
                    if(!aux.empty())
                        numSongsAux++;

                // Lectura de canciones de la playlist

                stringstream songsSS(songsString);
                string songName;

                Song** songs = new Song*[numSongsAux];

                int numSongs = 0;

                while(getline(songsSS, songName, '|')){

                    if(songName.empty()) continue;

                    // Búsqueda de la canción por título en la lista de canciones para asociarla a la playlist

                    Song** results = new Song*[1];

                    int numResults = 0;

                    if(this->songs.findSong(songName, Genre::UNKNOWN, -1, -1, results, 1, numResults))
                        songs[numSongs++] = results[0];

                    delete[] results;

                }

                // Creación de la playlist

                user->createPlaylist(songs, numSongs, title);

                // Obtención de la playlist recién creada para establecer su fecha de creación y configuración de privacidad

                int id = user->getNumPlaylists() - 1;
                Playlist& playlist = (*user)(id);

                playlist.setCreationDate(creationDate);
                playlist.setPrivacy(privacy);

                delete[] songs;
                
            }

        }

    }

    file.close();

}

/**
 * @brief Crea una nueva playlist para un usuario dado su email, el título de la playlist y los nombres de las canciones a incluir en la playlist.
 * @param user_email El email del usuario para el cual se creará la playlist.
 * @param playlist_title El título de la nueva playlist.
 * @param num_songs El número de canciones a incluir en la playlist.
 * @param song_names Un array de strings con los nombres de las canciones a incluir en la playlist.
 * @return true si la playlist se creó correctamente, false en caso contrario.
 */
bool Spotifry::createPlaylist(string user_email, string playlist_title, int num_songs, string* song_names){

    // Búsqueda del usuario por email en la lista de usuarios para asociar la playlist al usuario

    User* user = this->users.getUserByEmail(user_email);

    if(user == nullptr) return false;

    // Creación de un array de punteros a las canciones de la playlist

    Song** songs = new Song*[num_songs];

    // Búsqueda de las canciones por título en la lista de canciones para inclurlas en la playlist
    
    int numSongs = 0;

    for(int i = 0; i < num_songs; i++){

        Song** results = new Song*[1];

        int numResults = 0;

        bool found = this->songs.findSong(song_names[i], Genre::UNKNOWN, -1, -1, results, 1, numResults);

        if(found && numResults > 0)
            songs[numSongs++] = results[0];

        delete[] results;

    }

    // Creación de la playlist

    bool found = false;

    if(numSongs > 0)
        found = user->createPlaylist(songs, numSongs, playlist_title);

    delete[] songs;

    return found;

}

/**
 * @brief Lee el contenido de un archivo.
 * @param nombre Ruta del archivo a leer.
 * @return Contenido del archivo.
 */
string Spotifry::leerArchivo(const string& nombre){

    ifstream f(nombre);

    stringstream buffer;

    buffer << f.rdbuf();

    return buffer.str();

}

/**
 * @brief Reemplaza una etiqueta en un string HTML por un valor dado.
 * @param html El string HTML donde se realizará el reemplazo.
 * @param tag La etiqueta a reemplazar (formato "{{TAG}}").
 * @param valor El valor que reemplazará a la etiqueta en el string HTML.
 * @return El string HTML resultante después de realizar el reemplazo.
 */
string Spotifry::reemplazar(string html, const string& tag, const string& valor){

    // Encontrar la posición de la primera ocurrencia de la etiqueta en el string HTML

    int pos = (int)html.find(tag);

    while(pos != -1){

        // Reemplazar la etiqueta por el valor dado en el string HTML

        html.replace(pos, (int)tag.length(), valor);

        // Encontrar la posición de la siguiente ocurrencia de la etiqueta en el string HTML a partir de la posición actual

        pos = (int)html.find(tag, pos + (int)valor.length());

    }

    return html;

}

/**
 * @brief Lee una plantilla HTML desde un archivo y devuelve su contenido como un string.
 * @param path Ruta del archivo de la plantilla HTML a leer.
 * @return Contenido de la plantilla HTML como un string.
 */
string Spotifry::leerTemplateHtml(string path){ 
    return this->leerArchivo(path);
}

/**
 * @brief Genera un string HTML con la información de un álbum dado su título.
 * @param albumTitle El título del álbum para el cual se generará el HTML.
 * @return Un string HTML con la información del álbum, o un mensaje de error si el álbum no se encuentra.
 */
int Spotifry::numPlaylists(string userEmail){ 
    
    User* user = this->users.getUserByEmail(userEmail);
    return (user != nullptr) ? user->getNumPlaylists() : 0;

}

/**
 * @brief Obtiene el número de canciones guardadas por un usuario dado su email.
 * @param userEmail El email del usuario para el cual se obtendrá el número de canciones guardadas.
 * @return El número de canciones guardadas por el usuario, o -1 si el usuario no se encuentra.
 */
int Spotifry::numSongs(string userEmail){ 
    
    User* user = this->users.getUserByEmail(userEmail);
    return (user != nullptr) ? user->getNumSavedSongs() : 0;

}

/**
 * @brief Obtiene un ejemplo de el artista más escuchado por un usuario dado su email.
 * @param userEmail El email del usuario para el cual se obtendrá el artista más escuchado.
 * @return Coldplay
 */
string Spotifry::artistaTop(string userEmail){ 
    
    User* user = this->users.getUserByEmail(userEmail);

    return "Coldplay";

}

/**
 * @brief Genera un string HTML con la información de las playlists de un usuario dado su email.
 * @param userEmail El email del usuario para el cual se generará el HTML de las playlists.
 * @return Un string HTML con la información de las playlists del usuario, o una cadena vacía si el usuario no se encuentra o no tiene playlists.
 */
string Spotifry::generarPlaylists(string userEmail){

    // Búsqueda del usuario por email en la lista de usuarios para obtener sus playlists

    User* user = this->users.getUserByEmail(userEmail);

    if(!user) return "";

    // Generación de un string HTML con la información de las playlists del usuario

    string htmlList = "";

    for(int i = 0; i < user->getNumPlaylists(); i++){

        Playlist& playlist = (*user)(i);

        htmlList += "<div class=\"playlist\">";
        htmlList += "   <div class=\"play-title\">" + playlist.getTitle() + "</div>";
        htmlList += "   <div class=\"play-info\">" + to_string(playlist.getNumSongs()) + " canciones</div>";
        htmlList += "</div>";

    }

    return htmlList;

}

/**
 * @brief Genera un string HTML con la información de las canciones guardadas de un usuario dado su email.
 * @param userEmail El email del usuario para el cual se generará el HTML de las canciones guardadas.
 * @return Un string HTML con la información de las canciones guardadas del usuario, o una cadena vacía si el usuario no se encuentra o no tiene canciones guardadas.
 */
string Spotifry::generarCanciones(string userEmail){

    // Búsqueda del usuario por email en la lista de usuarios para obtener sus canciones guardadas

    User* user = this->users.getUserByEmail(userEmail);

    if(!user) return "";

    // Generación de un string HTML con la información de las canciones guardadas del usuario

    string htmlList = "";

    for(int i = 0; i < user->getNumSavedSongs(); i++){

        // Obtención de la canción guardada por el usuario

        Song& song = (*user)[i];

        // Búsqueda del artista de la canción a través de la lista de álbumes

        string artistName = "Unknown";
        bool found = false;

        for(int j = 0; j < this->albums.getCurrentSize() && !found; j++){

            Album* album = this->albums.getAlbumById(j);

            for(int k = 0; k < album->getNumSongs() && !found; k++){

                if(album->getSong(k) == &song){

                    if(album->getArtist() != nullptr)
                        artistName = album->getArtist()->getName();

                    found = true;

                }

            }

        }

        // Formateo de la duración de la canción en minutos y segundos para mostrarla en el HTML

        int minutes = song.getDuration() / 60;
        int seconds = song.getDuration() % 60;
        string durationString = to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);

        htmlList += "<tr>";
        htmlList += "   <td>🎵</td>";
        htmlList += "   <td>" + song.getTitle() + "</td>";
        htmlList += "   <td>" + artistName + "</td>";
        htmlList += "   <td>" + durationString + "</td>";
        htmlList += "</tr>";

    }

    return htmlList;

}