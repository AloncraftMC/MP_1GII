#ifndef USERLIST_H
#define USERLIST_H

#include <iostream>
#include "user.h"
#include "playlist.h"

using namespace std;

const int MAX_USERS = 1000;
const int MAX_PLAYLISTS = 2000;

class UserList{

    private:

        int current_size;
        User* list[MAX_USERS];

        int number_of_playlists;
        Playlist* playlists[MAX_PLAYLISTS];

    public:

        UserList(string users_file_path, string spotifry_db_file_path);
        ~UserList();

        User* getUserByEmail(string email);

        inline int getCurrentSize()         { return this->current_size; }
        inline int getNumberOfPlaylists()   { return this->number_of_playlists; }

        bool addUser(User* user_to_add);
        bool addPlaylist(Playlist* playlist_to_add);

};

#endif