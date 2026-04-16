#ifndef CANCIONES_H
#define CANCIONES_H

#include <string>

/**
 * @class Cancion
 * @brief Clase que representa una canción musical.
 */
class Cancion {
private:
    std::string titulo; ///< Título de la canción
    std::string artista; ///< Nombre del artista
    double duracion; ///< Duración en minutos
    std::string genero; ///< Género musical
    int anio; ///< Año de lanzamiento

public:
    /**
     * @brief Constructor por defecto
     */
    Cancion();
    
    /**
     * @brief Constructor con parámetros
     * @param titulo Título de la canción
     * @param artista Nombre del artista
     * @param duracion Duración en minutos
     * @param genero Género musical
     * @param anio Año de lanzamiento
     */
    Cancion(const std::string& titulo, const std::string& artista, double duracion, const std::string& genero, int anio);

    /**
     * @brief Constructor que crea un objeto Cancion a partir de una cadena de datos.
     * @param datos Una cadena con los datos de la canción separados por comas (titulo, artista, duracion, genero, anio). Usar las funciones strfind y substr para separar los distintos campos
     */
    Cancion(const std::string& datos);

    /** @brief Obtiene el título de la canción */
    std::string getTitulo() const;
    
    /** @brief Obtiene el nombre del artista */
    std::string getArtista() const;
    
    /** @brief Obtiene la duración de la canción en minutos */
    double getDuracion() const;
    
    /** @brief Obtiene el género de la canción */
    std::string getGenero() const;
    
    /** @brief Obtiene el año de lanzamiento de la canción */
    int getAnio() const;

    /** @brief Establece el título de la canción */
    void setTitulo(const std::string& titulo);
    
    /** @brief Establece el nombre del artista */
    void setArtista(const std::string& artista);
    
    /** @brief Establece la duración de la canción en minutos */
    void setDuracion(double duracion);
    
    /** @brief Establece el género de la canción */
    void setGenero(const std::string& genero);
    
    /** @brief Establece el año de lanzamiento de la canción */
    void setAnio(int anio);

    /** @brief Obtiene una cadena con la información de la canción */
    std::string toString() const;
};

/**
 * @brief Filtra canciones por año.
 * @param canciones Un array de objetos Cancion.
 * @param tamano Número de elementos en el array.
 * @param anio Año a buscar.
 * @param resultado Array con las canciones que coincidan con el año dado.
 * @param resultadoTamano Referencia a un entero donde se almacenará el número de canciones encontradas.
 */
void filtrarCancionesPorAnio(const Cancion canciones[], int tamano, int anio, Cancion resultado[], int& resultadoTamano);

#endif // CANCIONES_H
