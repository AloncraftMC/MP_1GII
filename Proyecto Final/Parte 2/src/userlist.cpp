#include <fstream>
#include <sstream>
#include "userlist.h"

UserList::UserList(string users_file_path, string spotifry_db_file_path){

    this->current_size = 0;
    this->number_of_playlists = 0;

    ifstream usersFile(users_file_path, ios::in);

    if(!usersFile.is_open()){
        
        cerr << "Error: File could not be opened." << endl;
        return;

    }

    string line;

    while(getline(usersFile, line)){

        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;

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

        Gender gender;

        if(genderString == "MALE")          gender = Gender::MALE;
        else if(genderString == "FEMALE")   gender = Gender::FEMALE;
        else                                gender = Gender::OTHER;

        User* user = new User(name, email, birthdate, gender);

        if(!this->addUser(user)){
            
            cerr << "Error: User could not be added." << endl;
            delete user;

        }

    }

    usersFile.close();

}

UserList::~UserList(){

    for(int i = 0; i < this->current_size; i++)
        delete this->list[i];

}

User* UserList::getUserByEmail(string email){

    for(int i = 0; i < this->current_size; i++)
        if(this->list[i]->getEmail() == email)
            return this->list[i];

    return nullptr;

}

bool UserList::addUser(User* user_to_add){

    if(this->current_size == MAX_USERS) return false;

    this->list[this->current_size++] = user_to_add;

    return true;

}

bool UserList::addPlaylist(Playlist* playlist_to_add){

    if(this->number_of_playlists == MAX_PLAYLISTS)  return false;

    this->playlists[this->number_of_playlists++] = playlist_to_add;

    return true;

}