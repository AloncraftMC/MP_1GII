// main.cpp
#include <iostream>
#include "artist.h"
#include "album.h"
#include "song.h"
#include "date.h"
#include "user.h"
#include "playlist.h"

#include <iostream>
#include <string>
#include "artist.h"
#include "album.h"
#include "song.h"
#include "date.h"
#include "user.h"
#include "playlist.h"

using namespace std;

int main() {
    cout << "--- SPOTIFRY: EXPANDED DATABASE & STRESS TEST ---" << endl;



    //1. creación de artistas 
    Artist a1("Rosalía");
    Artist a2("Metallica");
    Artist a3("Daft Punk");
    Artist a4("Taylor Swift");

    //2. creación de canciones
    Song s1("One More Time", Genre::ELECTRONIC, 320);
    Song s2("Get Lucky", Genre::ELECTRONIC, 248);
    Song s3("Harder, Better, Faster, Stronger", Genre::ELECTRONIC, 224);
    
   
    Song s4("Enter Sandman", Genre::METAL, 331);
    Song s5("Nothing Else Matters", Genre::METAL, 388);
    Song s6("Master of Puppets", Genre::METAL, 515);
    

    Song s7("Malamente", Genre::POP, 150);
    Song s8("SAOKO", Genre::POP, 137);
    Song s9("Candy", Genre::POP, 193);
    
    
    Song s10("Shake It Off", Genre::POP, 219);
    Song s11("All Too Well", Genre::COUNTRY, 613);

    Song s12("Blank Space", Genre::POP, 231);
    Song s13("Bad Blood", Genre::POP, 211);
    Song s14("Style", Genre::POP, 231);
    Song s15("Lover", Genre::POP, 221);
    Song s16("You Belong With Me", Genre::COUNTRY, 230);
    Song s17("Love Story", Genre::COUNTRY, 235);
    Song s18("Look What You Made Me Do", Genre::POP, 210);
    Song s19("Delicate  ", Genre::POP, 220);

    // 3. ÁLBUMES (Probando el operador [])
    Song* songs_daft[] = {&s1, &s2, &s3};
    Album alb_daft("Discovery", &a3, Date(12, 3, 2001), songs_daft, 3);

    Song* songs_rosalia[] = {&s7, &s8, &s9};
    Album alb_rosalia("MOTOMAMI", &a1, Date(18, 3, 2022), songs_rosalia, 3);

    cout << "\n[INFO] Album: " << alb_rosalia.getTitle() << " - Cancion 2: " << alb_rosalia[1].getTitle() << endl;
     cout << "\n[INFO] Album: " << alb_daft.getTitle() << " - Cancion 3: " << alb_daft[2].getTitle() << endl;

    // 4. USUARIO Y PRUEBA DE RESIZE (Crecimiento de memoria) 
    User* user1 = new User("Alice", "alice@example.com", Date(1, 1, 1996), FEMALE);
    User* user2 = new User("Bob", "bob@example.com", Date(1, 1, 2000), MALE);

    // Test Constructor de Copia 
    {
        User temp_user(*user1); // Llama al constructor copia
        temp_user.addSong(&s11);  // Modifica la copia
        cout << "[OK] Constructor copia de User ejecutado." << endl;
    } // Aquí se destruye temp_user. Si no hay copia profunda, user1 puede quedar corrupto.
    
    cout << "\n--- Test de Crecimiento de Memoria (User: saved_songs) ---" << endl;
    Song* tracklist[] = {&s1, &s2, &s3, &s4, &s5, &s2, &s7, &s3, &s9, &s10};

    for (int i = 0; i < 10; ++i) {
        if (user1->addSong(tracklist[i])) {
            cout << "[OK] Canción '" << tracklist[i]->getTitle() << "' añadida a las canciones guardadas del usuario." << endl;

        } else {
            cout << "[ERROR] No se pudo añadir la canción '" << tracklist[i]->getTitle() << "' a las canciones guardadas del usuario." << endl;
        }
    }

    Song* tracklist2[] = {&s6, &s5, &s5, &s3, &s2, &s1, &s10, &s9, &s8, &s7, &s12, &s13, &s7, &s15, &s16, &s17, &s18, &s19};

    for (int i = 0; i < 10; ++i) {
        if (user2->addSong(tracklist2[i])) {
            cout << "[OK] Canción '" << tracklist2[i]->getTitle() << "' añadida a las canciones guardadas del usuario." << endl;
        } else {
            cout << "[ERROR] No se pudo añadir la canción '" << tracklist2[i]->getTitle() << "' a las canciones guardadas del usuario." << endl;
        }
    }

    // 5. PLAYLISTS PÚBLICAS Y PRIVADAS
    Playlist* pl_gym = new Playlist("Gym Energy", user1, Date(5, 5, 2026), PUBLIC);

    

    if(pl_gym->addSong(&s4, user1)) {
        cout << "\n[OK] Canción '" << s4.getTitle() << "' añadida a la playlist pública 'Gym Energy' por el usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo añadir la canción '" << s4.getTitle() << "' a la playlist pública 'Gym Energy' por el usuario." << endl;
    }

    if(pl_gym->addSong(&s5, user1)) {      
        cout << "\n[OK] Canción '" << s5.getTitle() << "' añadida a la playlist pública 'Gym Energy' por el usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo añadir la canción '" << s5.getTitle() << "' a la playlist pública 'Gym Energy' por el usuario." << endl;

    }
    
    if(pl_gym->addSong(&s7, user2)) {
        cout << "\n[OK] Canción '" << s7.getTitle() << "' añadida a la playlist pública 'Gym Energy' por el usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo añadir la canción '" << s7.getTitle() << "' a la playlist pública 'Gym Energy' por el usuario." << endl;
    }

    if(pl_gym->deleteSong(&s4, user1)) {
        cout << "\n[OK] Canción '" << s7.getTitle() << "' eliminada de la playlist pública 'Gym Energy' por el usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo eliminar la canción '" << s7.getTitle() << "' de la playlist pública 'Gym Energy' por el usuario." << endl;
    }

    if(pl_gym->deleteSong(&s5, user2)) {
        cout << "\n[OK] Canción '" << s4.getTitle() << "' eliminada de la playlist pública 'Gym Energy' por el usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo eliminar la canción '" << s4.getTitle() << "' de la playlist pública 'Gym Energy' por el usuario." << endl;
    }

    
    // El usuario crea una playlist privada a través de su propio método
    Song* selection[] = {&s4, &s6}; // Solo Metal para el gimnasio
    if(user1->createPlaylist(selection, 2, "Heavy Gym")) {
        cout << "\n[OK] Playlist privada 'Heavy Gym' creada correctamente por el usuario." << endl;
    }

    
    if(user1->addPlaylist(pl_gym)) {
        cout << "\n[OK] Playlist pública 'Gym Energy' añadida a las playlists del usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo añadir la playlist pública 'Gym Energy' a las playlists del usuario." << endl;
    }
    
    if(user1->addPlaylist(pl_gym)) {
        cout << "\n[OK] Playlist pública 'Gym Energy' añadida a las playlists del usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo añadir la playlist pública 'Gym Energy' a las playlists del usuario porque ya existe." << endl;
    }
   
    if(user2->addPlaylist(pl_gym)) {
        cout << "\n[OK] Playlist pública 'Gym Energy' añadida a las playlists del usuario." << endl;
    } else {
        cout << "\n[ERROR] No se pudo añadir la playlist pública 'Gym Energy' a las playlists del usuario." << endl;
    }

    // ---------------------------------------------------------
    // TEST DE OPERADORES DE FECHA (DATE)
    // ---------------------------------------------------------
    cout << "\n--- Test de Logica Temporal (Clase Date) ---" << endl;

    Date fechaMaster = alb_daft.getReleaseDate();   // 12/3/2001
    Date fechaMoto = alb_rosalia.getReleaseDate(); // 18/3/2022

    // Prueba de operador de menor (<)
    if (fechaMaster < fechaMoto) {
        cout << "[OK] " << alb_daft.getTitle() << " es mas antiguo que " << alb_rosalia.getTitle() << endl;
    } else {
        cout << "[ERROR] La comparacion de fechas (<) ha fallado." << endl;
    }

    // Prueba de igualdad (==) con fechas críticas
    Date d1(18, 3, 2022);
    if (d1 == fechaMoto) {
        cout << "[OK] El operador (==) reconoce fechas identicas." << endl;
    }

    // Prueba de "Falso Positivo" (Mismo año y mes, distinto día)
    Date d2(17, 3, 2022); // Un día antes de MOTOMAMI
    if (d2 < fechaMoto) {
        cout << "[OK] El operador (<) distingue dias en el mismo mes/anio." << endl;
    } else {
        cout << "[ERROR] Fallo: el operador solo compara anios o meses." << endl;
    }


    cout << "\n[INFO] Estado actual del usuario '" << user1->getName() << "': " << endl;
    cout << "Canciones guardadas: " << user1->getNumSavedSongs() << endl;
    for (int i = 0; i < user1->getNumSavedSongs(); i++) {
        cout << " - " << (*user1)[i].getTitle() << " (" << (*user1)[i].getGenre() << ", " << (*user1)[i].getDuration() << "s)" << endl;
    }
    cout << "Playlists: " << user1->getNumPlaylists() << endl;
    for (int i = 0; i < user1->getNumPlaylists(); i++) {
            cout << "Playlist " << i+1 <<" - " << (*user1)(i).getTitle() << " (Privacidad: " << ((*user1)(i).getPrivacy() == PlaylistPrivacy::PUBLIC ? "Publica" : "Privada") << ")" << endl;
            for (int j = 0; j < (*user1)(i).getNumSongs(); j++) {
                cout << "  - " << (*user1)(i, j).getTitle() << " (" << (*user1)(i, j).getGenre() << ", " << (*user1)(i, j).getDuration() << "s)" << endl;
            }
    }


    cout << "\n[INFO] Estado actual del usuario '" << user2->getName() << "': " << endl;
    cout << "Canciones guardadas: " << user2->getNumSavedSongs() << endl;
    for (int i = 0; i < user2->getNumSavedSongs(); i++) {
        cout << " - " << (*user2)[i].getTitle() << " (" << (*user2)[i].getGenre() << ", " << (*user2)[i].getDuration() << "s)" << endl;
    }
    cout << "Playlists: " << user2->getNumPlaylists() << endl;
    for (int i = 0; i < user2->getNumPlaylists(); i++) {
            cout << "Playlist " << i+1 <<" - " << (*user2)(i).getTitle() << " (Privacidad: " << ((*user2)(i).getPrivacy() == PlaylistPrivacy::PUBLIC ? "Publica" : "Privada") << ")" << endl;
            for (int j = 0; j < (*user2)(i).getNumSongs(); j++) {
                cout << "  - " << (*user2)(i, j).getTitle() << " (" << (*user2)(i, j).getGenre() << ", " << (*user2)(i, j).getDuration() << "s)" << endl;
            }
    }


    // 6. TEST DE ELIMINACIÓN Y REDUCCIÓN DE MEMORIA
    cout << "\n--- Test de Reduccion de Memoria (Downsize) ---" << endl;
    user1->deleteSong(&s1);
    user1->deleteSong(&s2);
    user1->deleteSong(&s3);
    user1->deleteSong(&s3);
    user1->deleteSong(&s5);
    user1->deleteSong(&s6);


    cout << "\n[INFO] Estado actual del usuario '" << user1->getName() << "': " << endl;
    cout << "Canciones guardadas: " << user1->getNumSavedSongs() << endl;
    for (int i = 0; i < user1->getNumSavedSongs(); i++) {
       
        cout << " - " << (*user1)[i].getTitle() << " (" << (*user1)[i].getGenre() << ", " << (*user1)[i].getDuration() << "s)" << endl;
    }
    cout << "Playlists: " << user1->getNumPlaylists() << endl;
    for (int i = 0; i < user1->getNumPlaylists(); i++) {
            cout << "Playlist " << i+1 <<" - " << (*user1)(i).getTitle() << " (Privacidad: " << ((*user1)(i).getPrivacy() == PlaylistPrivacy::PUBLIC ? "Publica" : "Privada") << ")" << endl;
            for (int j = 0; j < (*user1)(i).getNumSongs(); j++) {
                cout << "  - " << (*user1)(i, j).getTitle() << " (" << (*user1)(i, j).getGenre() << ", " << (*user1)(i, j).getDuration() << "s)" << endl;
            }
    }
  
    // 7. LIMPIEZA
    delete user1;
    delete user2;
    delete pl_gym;


    cout << "\n--- PRUEBAS FINALIZADAS ---" << endl;
    return 0;
}
