#ifndef REPRODUCCION_H
#define REPRODUCCION_H

#include <string>
using namespace std;

struct Anuncio {
    int id;
    char prioridad;
    char mensaje[501];
};

struct Historial {
    int* canciones;
    int cantidad;
    int capacidad;
    int maxRetroceso;
};

void mostrarMenuReproduccion();
int Totalcanciones(const string& NombreArchivo);
int cargarAnuncios(Anuncio anuncios[], const string& archivoPublicidad);
int seleccionarAnuncioAleatorio(Anuncio anuncios[], int totalAnuncios, int ultimoIdMostrado);
void mostrarPublicidad(Anuncio anuncios[], int totalAnuncios, int& ultimoIdMostrado);
int reproduccionAleatoria(bool premium, const string& NombreArchivo, int total, Anuncio anuncios[], int totalAnuncios, int& ultimoIdAnuncio);
int reproduccionLista(bool premium, const string &NombreArchivo, int total, Anuncio anuncios[], int totalAnuncios, int &ultimoIdAnuncio, int &siguiente);
void inicializarHistorial(Historial& h, int maxRetroceso);
void agregarCancion(Historial& h, int idCancion);
int retrocederCancion(const Historial& h, int pasos);
void liberarHistorial(Historial& h);
int repetirCancion(const Historial& h);

#endif // REPRODUCCION_H
