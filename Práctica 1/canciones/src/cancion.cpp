/**
 * @file Cancion
 * @brief Representa una canción con sus atributos y métodos para acceder a ellos.
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>
#include <string>
#include "cancion.h"

using namespace std;

Cancion::Cancion(){
    this->titulo = "Título";
    this->artista = "Artista";
    this->duracion = 0;
    this->genero = "Género";
    this->anio = 0;
}

Cancion::Cancion(const string& titulo, const string& artista, double duracion, const string& genero, int anio){
    this->titulo = titulo;
    this->artista = artista;
    this->duracion = duracion;
    this->genero = genero;
    this->anio = anio;
}

Cancion::Cancion(const string& datos){

    string utilDatos = datos;
    size_t posicionComa;
    
    posicionComa = utilDatos.find(',');
    this->titulo = utilDatos.substr(0, posicionComa);
    utilDatos = utilDatos.substr(posicionComa + 1);

    posicionComa = utilDatos.find(',');
    this->artista = utilDatos.substr(0, posicionComa);
    utilDatos = utilDatos.substr(posicionComa + 1);

    posicionComa = utilDatos.find(',');
    this->duracion = stod(utilDatos.substr(0, posicionComa));
    utilDatos = utilDatos.substr(posicionComa + 1);

    posicionComa = utilDatos.find(',');
    this->genero = utilDatos.substr(0, posicionComa);
    utilDatos = utilDatos.substr(posicionComa + 1);

    this->anio = stoi(utilDatos);

}

string Cancion::getTitulo() const {
    return this->titulo;
}

string Cancion::getArtista() const {
    return this->artista;
}

double Cancion::getDuracion() const {
    return this->duracion;
}

string Cancion::getGenero() const {
    return this->genero;
}

int Cancion::getAnio() const {
    return this->anio;
}

void Cancion::setTitulo(const string& titulo){
    this->titulo = titulo;
}

void Cancion::setArtista(const string& artista){
    this->artista = artista;
}

void Cancion::setDuracion(double duracion){
    this->duracion = duracion;
}

void Cancion::setGenero(const string& genero){
    this->genero = genero;
}

void Cancion::setAnio(int anio){
    this->anio = anio;
}

string Cancion::toString() const{
    return
        "Título: " + this->titulo + "\n" +
        "Artista: " + this->artista + "\n" +
        "Duración: " + to_string(this->duracion) + " min.\n" +
        "Género: " + this->genero + "\n" +
        "Año: " + to_string(this->anio) + "\n";
}

void filtrarCancionesPorAnio(const Cancion canciones[], int tamano, int anio, Cancion resultado[], int& resultadoTamano){

    resultadoTamano = 0;

    for(int i = 0; i < tamano; i++){
        
        if(canciones[i].getAnio() == anio){

            resultado[resultadoTamano] = canciones[i];
            resultadoTamano++;

        }

    }

}