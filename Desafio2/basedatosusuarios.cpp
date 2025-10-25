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

// Iniciar sesión
void baseDatosUsuarios::iniciarSesion() {
    string nickname;
    string password;

    cout << "\n========================================" << endl;
    cout << "         INICIO DE SESION" << endl;
    cout << "========================================" << endl;

    cout << "Nickname: ";
    cin >> nickname;

    cout << "Contrasena: ";
    cin >> password;

    // Buscar el usuario
    Usuario* usuario = buscarUsuario(nickname);

    if (usuario == nullptr) {
        cout << "\n Usuario no encontrado." << endl;
        cout << "Por favor, verifique el nickname ingresado." << endl;
        return;
    }

    // Autenticar
    if (usuario->autenticarUsuario(password)) {
        cout << "\n Inicio de sesion exitoso!" << endl;
        cout << "Bienvenido/a, " << nickname << "!" << endl;
        cout << "========================================\n" << endl;
        usuario->verPerfil();
    } else {
        cout << "\n Contrasena incorrecta." << endl;
        cout << "Por favor, intente nuevamente." << endl;
    }
}

// Obtener cantidad de usuarios
short int baseDatosUsuarios::getCantidadUsuarios() const {
    return cantidadUsuarios;
}

// Listar todos los usuarios
void baseDatosUsuarios::listarUsuarios() const {
    cout << "\n========================================" << endl;
    cout << "         LISTA DE USUARIOS" << endl;
    cout << "========================================" << endl;
    cout << "Total de usuarios registrados: " << cantidadUsuarios << endl;
    cout << "----------------------------------------" << endl;

    if (cantidadUsuarios == 0) {
        cout << "No hay usuarios registrados." << endl;
    } else {
        for (short int i = 0; i < cantidadUsuarios; i++) {
            cout << (i + 1) << ". " << usuarios[i].getNickname();
            if (usuarios[i].getEsPremium()) {
                cout << " [PREMIUM]";
            }
            cout << " - " << usuarios[i].getCiudad()
                 << ", " << usuarios[i].getPais() << endl;
        }
    }
    cout << "========================================\n" << endl;
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
