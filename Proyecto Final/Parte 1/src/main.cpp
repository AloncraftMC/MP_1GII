#include <iostream>
#include "playlist.h"
#include "song.h"
#include "user.h"
#include "date.h"

using namespace std;

int main(){

    // =========================
    // USER (solo constructor)
    // =========================
    User creator("Alonso", "alonso@email.com", Date(15,3,2004), MALE);
    User other("Intruso", "intruso@email.com", Date(1,1,2000), OTHER);

    // =========================
    // SONGS
    // =========================
    Song* s1 = new Song("Track 1", ROCK, 200);
    Song* s2 = new Song("Track 2", ELECTRONIC, 300);
    Song* s3 = new Song("Track 3", POP, 180);
    Song* s4 = new Song("Track 4", JAZZ, 240);

    // =========================
    // CONSTRUCTOR PARAMETRIZADO
    // =========================
    Playlist p1("Mi Playlist", &creator, Date(1,1,2024), PUBLIC);

    cout << "Playlist recién creada:\n";
    cout << p1 << endl;

    // =========================
    // ADD SONG (correcto)
    // =========================
    cout << "Añadiendo canciones con el creador:\n";
    cout << p1.addSong(s1, &creator) << endl;
    cout << p1.addSong(s2, &creator) << endl;
    cout << p1.addSong(s3, &creator) << endl;

    cout << p1 << endl;
    
    // =========================
    // ADD SONG (usuario incorrecto)
    // =========================
    cout << "Intento de añadir con otro usuario (debe dar 0):\n";
    cout << p1.addSong(s4, &other) << endl << endl;

    // =========================
    // OPERATOR []
    // =========================
    cout << "Acceso con operator[]:\n";
    for(int i = 0; i < p1.getNumSongs(); i++)
        cout << p1[i] << endl;

    cout << endl;

    // =========================
    // DELETE SONG (correcto)
    // =========================
    cout << "Eliminando Track 2:\n";
    cout << p1.deleteSong(s2, &creator) << endl;
    cout << p1 << endl;

    // =========================
    // DELETE SONG (no existe)
    // =========================
    cout << "Intento borrar canción inexistente:\n";
    cout << p1.deleteSong(s4, &creator) << endl << endl;

    // =========================
    // COPY CONSTRUCTOR
    // =========================
    cout << "Probando constructor de copia:\n";
    Playlist p2(p1);
    cout << p2 << endl;

    // =========================
    // OPERATOR =
    // =========================
    cout << "Probando operator=:\n";
    Playlist p3;
    p3 = p1;
    cout << p3 << endl;

    // =========================
    // INDEPENDENCIA DE COPIAS
    // =========================
    cout << "Modificando p1 (debe NO afectar a p2 ni p3):\n";
    p1.deleteSong(s1, &creator);

    cout << "p1:\n" << p1 << endl;
    cout << "p2:\n" << p2 << endl;
    cout << "p3:\n" << p3 << endl;

    // =========================
    // SETTERS + GETTERS
    // =========================
    cout << "Probando setters:\n";
    p1.setTitle("Nueva Playlist");
    p1.setPrivacy(PRIVATE);

    cout << p1.getTitle() << endl;
    cout << "Privacidad: " << p1.getPrivacy() << endl;
    cout << "NumSongs: " << p1.getNumSongs() << endl;
    cout << "MaxSongs: " << p1.getMaxSongs() << endl;
    cout << "Creador: " << p1.getCreator().getName() << endl;

    // =========================
    // LIMPIEZA
    // =========================
    delete s1;
    delete s2;
    delete s3;
    delete s4;

    return 0;
}