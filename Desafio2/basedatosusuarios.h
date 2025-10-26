#ifndef BASEDATOSUSUARIOS_H
#define BASEDATOSUSUARIOS_H

#include "Usuario.h"
#include <string>

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
    short int getCantidadUsuarios() const;
    void cargarDesdeArchivo(string nombreArchivo);
};

#endif
