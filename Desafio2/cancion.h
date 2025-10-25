#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>
using namespace std;

class Cancion {
private:
    int idCancion;       // ID completo (9 dígitos)
    int idArtista;       // ID del artista (primeros 5 dígitos)
    int idAlbum;         // ID del álbum (siguientes 2 dígitos)
    string nombre;       // Nombre de la canción
    string duracion;     // Ejemplo: "3:14"
    float puntuacion;    // Calificación de los usuarios
    string ruta128;      // Ruta del archivo .ogg en 128 kbps
    string ruta320;      // Ruta del archivo .ogg en 320 kbps
    int reproducciones;  // Número de veces reproducida

public:
    // Constructor vacío
    Cancion();

    // Constructor con parámetros
    Cancion(int _idCancion, int _idArtista, int _idAlbum, string _nombre,
            string _duracion, float _puntuacion, string _ruta128,
            string _ruta320, int _reproducciones);

    // Getters
    int getIdCancion() const;
    int getIdArtista() const;
    int getIdAlbum() const;
    string getNombre() const;
    string getDuracion() const;
    float getPuntuacion() const;
    string getRuta128() const;
    string getRuta320() const;
    int getReproducciones() const;

    // Setters (si deseas actualizar el número de reproducciones o puntuación)
    void setPuntuacion(float nuevaPuntuacion);
    void aumentarReproducciones();

    // Mostrar información general
    void mostrarInfo() const;

    // Simular reproducción (muestra rutas y metadatos)
    void reproducir(bool premium, const string& portadaAlbum, const string& nombreAlbum, const string& nombreArtista);
};

#endif // CANCION_H
