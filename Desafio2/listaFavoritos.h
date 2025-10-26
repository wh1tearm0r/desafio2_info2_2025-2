#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class listaFavoritos
{
private:
    static const int MAX_CANCIONES = 10000;
    string canciones[MAX_CANCIONES];
    int cantidadCanciones;
    string nombreUsuario;
public:
    listaFavoritos();
    listaFavoritos(const string &usuario);

    bool agregarCancion(const string &idCancion);
    bool eliminarCancion(const string &idCancion);
    bool existeCancion(const string &idCancion) const;
    void mostrarLista(bool premium) const;

    int getCantidadCanciones() const;
    string getCancionEn(int posicion) const;

    void actualizarArchivo() const;
    void cargarDesdeArchivo();
    void setNombreUsuario(const string& usuario);
};

#endif // LISTAFAVORITOS_H
