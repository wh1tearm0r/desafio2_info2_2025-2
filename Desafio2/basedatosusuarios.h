#ifndef BASEDATOSUSUARIOS_H
#define BASEDATOSUSUARIOS_H

#include <string>
using namespace std;

class Usuario;  // Forward declaration

class baseDatosUsuarios {
private:
    Usuario* usuarios;
    short int cantidadUsuarios;

public:
    baseDatosUsuarios();
    baseDatosUsuarios(string nombreArchivo);
    ~baseDatosUsuarios();

    Usuario* buscarUsuario(const string& nickname);
    void iniciarSesion();

    short int getCantidadUsuarios() const;
    void listarUsuarios() const;

    // Cargar usuarios desde archivo
    void cargarDesdeArchivo(string nombreArchivo);
};

#endif
