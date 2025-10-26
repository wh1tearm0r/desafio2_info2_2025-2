#include "baseDatosUsuarios.h"
#include "Usuario.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor por defecto
baseDatosUsuarios::baseDatosUsuarios() {
    usuarios = nullptr;
    cantidadUsuarios = 0;
}

// Constructor que carga desde archivo
baseDatosUsuarios::baseDatosUsuarios(string nombreArchivo) {
    usuarios = nullptr;
    cantidadUsuarios = 0;
    cargarDesdeArchivo(nombreArchivo);
}

// Destructor
baseDatosUsuarios::~baseDatosUsuarios() {
    if (usuarios != nullptr) {
        delete[] usuarios;
        usuarios = nullptr;
    }
}

// Buscar usuario por nickname
Usuario* baseDatosUsuarios::buscarUsuario(const string& nickname) {
    for (short int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].getNickname() == nickname) {
            return &usuarios[i];
        }
    }
    return nullptr;
}

// Obtener cantidad de usuarios
short int baseDatosUsuarios::getCantidadUsuarios() const {
    return cantidadUsuarios;
}

// Cargar usuarios desde archivo
void baseDatosUsuarios::cargarDesdeArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    // Primera pasada: contar usuarios
    string nick, pass, ciudad, pais;
    bool premium;
    int fecha;

    cantidadUsuarios = 0;
    while (archivo >> nick >> pass >> ciudad >> pais >> premium >> fecha) {
        cantidadUsuarios++;
    }

    // Si no hay usuarios, salir
    if (cantidadUsuarios == 0) {
        cout << "El archivo no contiene usuarios." << endl;
        archivo.close();
        return;
    }

    // Crear array con tamaño exacto
    usuarios = new Usuario[cantidadUsuarios];

    // Reiniciar el archivo para segunda pasada
    archivo.clear();
    archivo.seekg(0);

    // Segunda pasada: cargar usuarios
    short int i = 0;
    while (archivo >> nick >> pass >> ciudad >> pais >> premium >> fecha) {
        usuarios[i] = Usuario(nick, pass, ciudad, pais, premium, fecha);
        i++;
    }

    archivo.close();
    cout << "Usuarios cargados exitosamente: " << cantidadUsuarios << endl;
}
