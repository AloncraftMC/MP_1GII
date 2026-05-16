/**
 * @file userlist.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase UserList.
 */

#include <fstream>
#include <sstream>
#include "userlist.h"

/**
 * @brief Constructor con parámetros.
 * @param users_file_path Ruta del archivo .txt con los datos de los usuarios.
 * @param spotifry_db_file_path Ruta del archivo .txt con los datos de las canciones y playlists de los usuarios.
 */
UserList::UserList(string users_file_path, string spotifry_db_file_path){

    this->current_size = 0;
    this->number_of_playlists = 0;

    // Lectura del archivo de usuarios

    ifstream usersFile(users_file_path, ios::in);

    if(!usersFile.is_open()){
        
        cerr << "Error: File could not be opened." << endl;
        return;

    }

    // Lectura de líneas

    string line;

    while(getline(usersFile, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

        // Lectura de campos

        stringstream dataSS(line);

        string name;
        string email;
        string birthdateString;
        string genderString;

        getline(dataSS, name, ';');
        getline(dataSS, email, ';');
        getline(dataSS, birthdateString, ';');
        getline(dataSS, genderString, ';');

        if(name.empty())            { cerr << "Error: Invalid row format." << endl; continue; }
        if(email.empty())           { cerr << "Error: Invalid row format." << endl; continue; }
        if(birthdateString.empty()) { cerr << "Error: Invalid row format." << endl; continue; }
        if(genderString.empty())    { cerr << "Error: Invalid row format." << endl; continue; }

        // Lectura de campos de fecha

        stringstream birthdateSS(birthdateString);

        string yearString;
        string monthString;
        string dayString;

        getline(birthdateSS, yearString, '/');
        getline(birthdateSS, monthString, '/');
        getline(birthdateSS, dayString, '/');

        if(yearString.empty())  { cerr << "Error: Invalid row format." << endl; continue; }
        if(monthString.empty()) { cerr << "Error: Invalid row format." << endl; continue; }
        if(dayString.empty())   { cerr << "Error: Invalid row format." << endl; continue; }

        int year = stoi(yearString);
        int month = stoi(monthString);
        int day = stoi(dayString);

        Date birthdate = Date(day, month, year);

        // Lectura de género

        Gender gender;

        if(genderString == "MALE")          gender = Gender::MALE;
        else if(genderString == "FEMALE")   gender = Gender::FEMALE;
        else                                gender = Gender::OTHER;

        // Creación del usuario y adición a la lista de usuarios

        User* user = new User(name, email, birthdate, gender);

        if(!this->addUser(user)){
            
            cerr << "Error: User could not be added." << endl;
            delete user;

        }

    }

    usersFile.close();

}

/**
 * @brief Destructor.
 */
UserList::~UserList(){

    for(int i = 0; i < this->current_size; i++)
        delete this->list[i];

}

/**
 * @brief Obtiene un puntero al usuario con el email dado.
 * @param email El email del usuario a buscar.
 * @return Un puntero al usuario con el email dado, o nullptr si no se encuentra ningún usuario con ese email.
 */
User* UserList::getUserByEmail(string email){

    for(int i = 0; i < this->current_size; i++)
        if(this->list[i]->getEmail() == email)
            return this->list[i];

    return nullptr;

}

/**
 * @brief Añade un usuario a la lista de usuarios si no se ha alcanzado el límite máximo de usuarios.
 * @param user_to_add Un puntero al usuario que se desea añadir.
 * @return true si el usuario se añadió exitosamente, false en caso contrario.
 */
bool UserList::addUser(User* user_to_add){

    if(this->current_size == MAX_USERS) return false;

    this->list[this->current_size++] = user_to_add;

    return true;

}

/**
 * @brief Añade una playlist a la lista de playlists si no se ha alcanzado el límite máximo de playlists.
 * @param playlist_to_add Un puntero a la playlist que se desea añadir.
 * @return true si la playlist se añadió exitosamente, false en caso contrario.
 */
bool UserList::addPlaylist(Playlist* playlist_to_add){

    if(this->number_of_playlists == MAX_PLAYLISTS)  return false;

    this->playlists[this->number_of_playlists++] = playlist_to_add;

    return true;

}