#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <iostream>
#include <fstream>
#include <string>
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
using namespace std;

class GestorArchivos {
public:
    // Busca un artista por ID en artistas.txt
    static Artista* buscarArtista(int idArtista);

    // Busca un álbum por ID de artista y de álbum en albumes.txt
    static Album* buscarAlbum(int idArtista, int idAlbum);

    // Busca una canción completa (canción + álbum + artista)
    static Cancion* buscarCancionCompleta(int idCancion, bool premium);
};

#endif // GESTORARCHIVOS_H
