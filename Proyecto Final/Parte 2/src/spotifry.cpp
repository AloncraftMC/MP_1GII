#include <fstream>
#include <sstream>
#include "spotifry.h"

Spotifry::Spotifry(string albums_file_path, string songs_file_path, string users_file_path, string spotifry_db_file_path)
    : artists(albums_file_path),
      albums(albums_file_path, artists, songs),
      songs(songs_file_path, albums),
      users(users_file_path, "")
      {

    ifstream spotifryDBFile(spotifry_db_file_path);

    string line;

    while(getline(spotifryDBFile, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

        stringstream dataSS(line);
        string type;

        getline(dataSS, type, ';');

        if(type == "USER"){

            string email;
            string songsString;

            getline(dataSS, email, ';');
            getline(dataSS, songsString, ';');

            if(email.empty()) { cerr << "Error: Invalid row format." << endl; continue; }

            User* user = this->users.getUserByEmail(email);

            if(user && !songsString.empty()){

                stringstream songsSS(songsString);
                string songName;

                while(getline(songsSS, songName, '|')){

                    if(songName.empty()) continue;

                    int maxResults = 10;
                    int numResults = 0;
                    
                    Song** results = new Song*[maxResults];

                    if(this->songs.findSong(songName, Genre::UNKNOWN, -1, -1, results, maxResults, numResults)){

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

            User* user = this->users.getUserByEmail(creatorEmail);

            if(user){

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

                PlaylistPrivacy privacy;

                if(privacyString == "PUBLIC")       privacy = PlaylistPrivacy::PUBLIC;
                else if(privacyString == "PRIVATE") privacy = PlaylistPrivacy::PRIVATE;
                else                                { cerr << "Error: Invalid row format." << endl; continue; }

                int numSongsAux = 0;

                stringstream numSongsSS(songsString);
                string aux;

                while(getline(numSongsSS, aux, '|'))
                    if(!aux.empty())
                        numSongsAux++;

                Song** songs = new Song*[numSongsAux];

                int numSongs = 0;

                stringstream songsSS(songsString);
                string songName;

                while(getline(songsSS, songName, '|')){

                    if(songName.empty()) continue;

                    Song** results = new Song*[1];

                    int numResults = 0;

                    if(this->songs.findSong(songName, Genre::UNKNOWN, -1, -1, results, 1, numResults))
                        songs[numSongs++] = results[0];

                    delete[] results;

                }

                user->createPlaylist(songs, numSongs, title);

                int id = user->getNumPlaylists() - 1;
                Playlist& playlist = (*user)(id);

                playlist.setCreationDate(creationDate);
                playlist.setPrivacy(privacy);

                delete[] songs;
                
            }

        }

    }

    spotifryDBFile.close();

}

bool Spotifry::createPlaylist(string user_email, string playlist_title, int num_songs, string* song_names){

    User* user = this->users.getUserByEmail(user_email);

    if(user == nullptr) return false;

    Song** songs = new Song*[num_songs];
    
    int numSongs = 0;

    for(int i = 0; i < num_songs; i++){

        Song** results = new Song*[1];

        int numResults = 0;

        bool found = this->songs.findSong(song_names[i], Genre::UNKNOWN, -1, -1, results, 1, numResults);

        if(found && numResults > 0)
            songs[numSongs++] = results[0];

        delete[] results;

    }

    bool found = false;

    if(numSongs > 0)
        found = user->createPlaylist(songs, numSongs, playlist_title);

    delete[] songs;

    return found;

}

string Spotifry::leerArchivo(const string& nombre){

    ifstream f(nombre);

    stringstream buffer;

    buffer << f.rdbuf();

    return buffer.str();

}

string Spotifry::reemplazar(string html, const string& tag, const string& valor){

    int pos = (int)html.find(tag);

    while(pos != -1){

        html.replace(pos, (int)tag.length(), valor);
        pos = (int)html.find(tag, pos + (int)valor.length());

    }

    return html;

}

string Spotifry::leerTemplateHtml(string path){ 
    return this->leerArchivo(path);
}

int Spotifry::numPlaylists(string userEmail){ 
    
    User* user = this->users.getUserByEmail(userEmail);
    return (user != nullptr) ? user->getNumPlaylists() : 0;

}

int Spotifry::numSongs(string userEmail){ 
    
    User* user = this->users.getUserByEmail(userEmail);
    return (user != nullptr) ? user->getNumSavedSongs() : 0;

}

string Spotifry::artistaTop(string userEmail){ 
    
    User* user = this->users.getUserByEmail(userEmail);

    return "Coldplay";

}

string Spotifry::generarPlaylists(string userEmail){

    User* user = this->users.getUserByEmail(userEmail);

    if(!user) return "";

    string htmlList = "";

    for(int i = 0; i < user->getNumPlaylists(); i++){

        Playlist& playlist = (*user)(i);

        htmlList += "<div class=\"playlist\">";
        htmlList += "  <div class=\"play-title\">" + playlist.getTitle() + "</div>";
        htmlList += "  <div class=\"play-info\">" + to_string(playlist.getNumSongs()) + " canciones</div>";
        htmlList += "</div>";

    }

    return htmlList;

}

string Spotifry::generarCanciones(string userEmail){

    User* user = this->users.getUserByEmail(userEmail);

    if(!user) return "";

    string htmlList = "";

    for(int i = 0; i < user->getNumSavedSongs(); i++){

        Song& song = (*user)[i];

        string name = "Unknown";
        bool found = false;

        for(int j = 0; j < this->albums.getCurrentSize() && !found; j++){

            Album* album = this->albums.getAlbumById(j);

            for(int k = 0; k < album->getNumSongs() && !found; k++){

                if(album->getSong(k) == &song){

                    if(album->getArtist() != nullptr)
                        name = album->getArtist()->getName();

                    found = true;

                }

            }

        }

        int minutes = song.getDuration() / 60;
        int seconds = song.getDuration() % 60;
        string durationString = to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);

        htmlList += "<tr>";
        htmlList += "  <td>🎵</td>";
        htmlList += "  <td>" + song.getTitle() + "</td>";
        htmlList += "  <td>" + name + "</td>";
        htmlList += "  <td>" + durationString + "</td>";
        htmlList += "</tr>";

    }

    return htmlList;

}