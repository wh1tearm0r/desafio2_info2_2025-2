#ifndef REPRODUCCION_H
#define REPRODUCCION_H

#include <string>
using namespace std;

struct Anuncio {
    int id;
    char prioridad;
    char mensaje[501];
};

void mostrarMenuReproduccion();
int Totalcanciones(const string& NombreArchivo);
int cargarAnuncios(Anuncio anuncios[], const string& archivoPublicidad);
int seleccionarAnuncioAleatorio(Anuncio anuncios[], int totalAnuncios, int ultimoIdMostrado);
void mostrarPublicidad(Anuncio anuncios[], int totalAnuncios, int& ultimoIdMostrado);
int reproduccionAleatoria(bool premium, const string& NombreArchivo, int total, Anuncio anuncios[], int totalAnuncios, int& ultimoIdAnuncio);

#endif // REPRODUCCION_H
