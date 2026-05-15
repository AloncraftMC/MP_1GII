// main.cpp
#include <iostream>
#include "artist.h"
#include "album.h"
#include "song.h"
#include "date.h"
#include "user.h"
#include "playlist.h"

#include "spotifry.h"
#include <fstream>

using namespace std;

/**
 * TEST DE INTEGRACIÓN PARTE 2: "SPOTIFRY PERSISTENCIA Y BÚSQUEDA"
 */
int main(int argc, char* argv[]) {
    cout << "--- Iniciando Test Parte 2: Carga de Datos ---" << endl;

    // Verificación de argumentos: users, songs, albums, db
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <users.txt> <songs.txt> <albums.txt> <spotifry_db.txt>" << endl;
        return 1;
    }

    
    Spotifry platform(argv[3], argv[2], argv[1], argv[4]);
    cout << "[OK] Carga de ficheros finalizada." << endl;

    
    

    // 2. Test de Búsqueda (SongList::findSong)
    // Probamos filtro por género y duración
    int maxResults = 5;
    int numResults = 0;
    Song** searchBuffer = new Song*[maxResults];

    cout << "Buscando canciones de ELECTRONIC entre 200 y 400 segundos..." << endl;

    bool found = platform.getSongList().findSong("", ELECTRONIC, 200, 400, searchBuffer, maxResults, numResults);

    if (found && numResults > 0) {
        cout << "Encontradas " << numResults << " canciones." << endl;
        for(int i = 0; i < numResults; i++) {
            cout << " - " << searchBuffer[i]->getTitle() << endl;
        }
    } else {
        cout << "[ERROR] No se encontraron canciones que cumplan el criterio." << endl;
    }

    
    cout << "Buscando canciones que contengan 'Time' en el título, sin filtro de género ni duración máxima..." << endl;
    found = platform.getSongList().findSong("Time", UNKNOWN, 300, -1, searchBuffer, maxResults, numResults);
    if (found && numResults > 0) {
        cout << "Encontradas " << numResults << " canciones que contienen 'Time' en el título." << endl;
        for(int i = 0; i < numResults; i++) {
            cout << " - " << searchBuffer[i]->getTitle() << endl;
        }
    } else {
        cout << "[ERROR] No se encontraron canciones que contengan 'Time' en el título." << endl;
    }

    


    // 3. Test de Creación de Playlist con validación de existencia
    string canciones_nuevas[] = {"One More Time", "Digital Love"};
    bool pl_creada = platform.createPlaylist("alice.j@mail.com", "Daft Punk Essentials", 2, canciones_nuevas);
    
    if (pl_creada) {
        cout << "[OK] Playlist creada correctamente validando existencia de canciones y usuario." << endl;
    } else {
        cout << "[ERROR] Falló la creación de playlist (¿Faltan datos en los ficheros?)." << endl;
    }

    // 4. Test de adicion Canciones a Álbumes

    bool added1 = platform.getSongList().addSong("Breed", ROCK, 210, platform.getAlbumList(), "Nevermind");
    bool added2 = platform.getSongList().addSong("On a plane", ROCK, 180, platform.getAlbumList(), "Nevermind");
    if (added1 && added2) {
        cout << "[OK] Canciones añadidas correctamente al álbum y a la lista global." << endl;
    } else {
        cout << "[ERROR] Falló la adición de canciones al álbum (¿Falt  an datos en los ficheros?)." << endl;
    }

    added1 = platform.getSongList().addSong("Breed", ROCK, 210, platform.getAlbumList(), "NoExiste");
    if (!added1) {
        cout << "[OK] No se pudo añadir canción a álbum inexistente, como se esperaba." << endl;
    } else {
        cout << "[ERROR] Se añadió canción a álbum inexistente, lo cual no debería suceder." << endl;
    }

    //6. Test de impresión de álbum para verificar que las canciones se añadieron correctamente
    cout << "\nImprimiendo álbum 'Nevermind' para verificar canciones añadidas:" << endl;
    platform.getAlbumList().printAlbum("Nevermind");

    
    

    //5. Test de Volcado (Dump)
    cout << "\nProbando persistencia de álbumes..." << endl;
    if (platform.getAlbumList().dump("data/backup_albums.txt")) {
        cout << "[OK] Fichero de backup generado." << endl;
    } else {
        cout << "[ERROR] Falló la generación del fichero de backup." << endl;
    }

    
    delete[] searchBuffer;

    string html ="";

    html = platform.leerTemplateHtml("data/template.txt");
    cout << "Template HTML leído correctamente." << endl;
    cout << "Generando HTML dinámico para el usuario..." << endl;

    /* ===== REEMPLAZOS ===== */

    html = platform.reemplazar(html,
                       "{{USUARIO}}",
                       "Alice Johnson");
    

    html = platform.reemplazar(html,
                       "{{NUM_PLAYLISTS}}",
                       to_string(platform.numPlaylists("alice.j@mail.com")));

    html = platform.reemplazar(html,
                       "{{NUM_FAVORITAS}}",
                       to_string(platform.numSongs("alice.j@mail.com")));

    html = platform.reemplazar(html,
                       "{{ARTISTA_TOP}}",
                       platform.artistaTop("alice.j@mail.com"));

    html = platform.reemplazar(html,
                       "{{PLAYLISTS}}",
                       platform.generarPlaylists("alice.j@mail.com"));

    html = platform.reemplazar(html,
                       "{{CANCIONES}}",
                       platform.generarCanciones("alice.j@mail.com"));

    html = platform.reemplazar(html,
                       "{{CANCION_ACTUAL}}",
                       "Viva la Vida");

    html = platform.reemplazar(html,
                       "{{ARTISTA_ACTUAL}}",
                       "Coldplay");

    html = platform.reemplazar(html,
                       "{{TIEMPO}}",
                       "1:32 / 4:03");

    /* ===== EXPORTAR HTML ===== */

    ofstream out("data/usuario_alice.html");

    out << html;

    out.close();

    cout << "Archivo usuario_alice.html generado correctamente\n";
    cout << "Abre el archivo 'data/usuario_alice.html' para ver el resultado." << endl;


    cout << "\n--- Tests de la Parte 2 finalizados ---" << endl;
}
