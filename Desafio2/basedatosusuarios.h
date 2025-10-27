#ifndef BASEDATOSUSUARIOS_H
#define BASEDATOSUSUARIOS_H

#include "usuario.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Usuario;

using namespace std;

class baseDatosUsuarios {
private:
    Usuario* usuarios;
    short int cantidadUsuarios;

public:
    baseDatosUsuarios();
    baseDatosUsuarios(string nombreArchivo);
    ~baseDatosUsuarios();

    Usuario* buscarUsuario(const string& nickname);
    Usuario* getUsuarioEn(int indice);
    short int getCantidadUsuarios() const;
    void cargarDesdeArchivo(string nombreArchivo);
    void actualizarArchivo(string nombreArchivo);
    void actualizarListaSeguidores(const string& usuarioQuePublica, const string& idCancion);
};

#endif // BASEDATOSUSUARIOS_H
