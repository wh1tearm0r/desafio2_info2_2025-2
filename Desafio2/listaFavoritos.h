#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class baseDatosUsuarios;

class listaFavoritos{
private:
    static const int MAX_CANCIONES = 10000;
    string canciones[MAX_CANCIONES];
    int cantidadCanciones;
    string nombreUsuario;
public:
    listaFavoritos();
    listaFavoritos(const string &usuario);

    bool agregarCancion(bool premium, const string& idCancion, baseDatosUsuarios* bd = nullptr);
    bool eliminarCancion(bool premium, const string &idCancion, baseDatosUsuarios *bd);
    bool existeCancion(const string &idCancion) const;
    void mostrarLista(bool premium) const;
    void actualizarArchivo() const;
    void cargarDesdeArchivo();

    void setNombreUsuario(const string& usuario);
    int getCantidadCanciones() const;
    string getCancionEn(int posicion) const;
};

#endif // LISTAFAVORITOS_H
