#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include <iostream>
using namespace std;

class Album {
private:
    int idAlbum;        // ID completo (7 dígitos: 5 artista + 2 álbum)
    int idArtista;      // ID del artista dueño del álbum
    string nombre;      // Nombre del álbum
    string genero1;     // Primer género musical
    string genero2;     // Segundo género musical (opcional)
    string genero3;
    string genero4;
    string fecha;       // Fecha de lanzamiento
    string duracion;    // Duración total (por ejemplo, "45:00")
    string sello;       // Sello discográfico
    string portada;     // Nombre del archivo PNG de la portada
    float puntuacion;   // Puntuación promedio (1 a 10)

public:
    // Constructor vacío
    Album();

    // Constructor con parámetros
    Album(int _idAlbum, int _idArtista, string _nombre, string _genero1,
          string _genero2, string _genero3, string _genero4, string _fecha, string _duracion, string _sello,
          string _portada, float _puntuacion);

    // Getters
    int getIdAlbum() const;
    int getIdArtista() const;
    string getNombre() const;
    string getGenero1() const;
    string getGenero2() const;
    string getGenero3() const;
    string getGenero4() const;
    string getFecha() const;
    string getDuracion() const;
    string getSello() const;
    string getPortada() const;
    float getPuntuacion() const;

    // Mostrar información del álbum (para depuración o interfaz)
    void mostrarInfo() const;
};

#endif // ALBUM_H
