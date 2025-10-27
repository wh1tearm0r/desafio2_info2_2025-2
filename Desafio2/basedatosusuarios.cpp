#include "baseDatosUsuarios.h"

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
            cout << "Se hicieron " << i + 1 << " comparaciones para encontrar el usuario." << endl;
            return &usuarios[i];
        }
    }
    return nullptr;
}

Usuario *baseDatosUsuarios::getUsuarioEn(int indice){
    if (indice >= 0 && indice < cantidadUsuarios) {
        return &usuarios[indice];
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
    string linea;
    cantidadUsuarios = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            cantidadUsuarios++;
        }
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
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (linea.size() >= 3 && //Ignorar caracteres que no corresponden a la codificacion de usuarios.txt en caso de problemas de autenticacion
            (unsigned char)linea[0] == 0xEF &&
            (unsigned char)linea[1] == 0xBB &&
            (unsigned char)linea[2] == 0xBF) {
            linea = linea.substr(3);
        }

        istringstream iss(linea);
        string nick, pass, ciudad, pais, usuarioSeguido = "";
        bool premium;
        int fecha;

        iss >> nick >> pass >> ciudad >> pais >> premium >> fecha;

        // Si hay un séptimo campo, es el usuario seguido
        if (iss >> usuarioSeguido) {
            // usuarioSeguido tiene valor
        } else {
            usuarioSeguido = "";
        }

        usuarios[i] = Usuario(nick, pass, ciudad, pais, premium, fecha, usuarioSeguido);
        i++;
    }

    archivo.close();
    cout << "Usuarios cargados exitosamente: " << cantidadUsuarios << endl;
    cout << "La memoria consumida por la base de datos de usuarios es de " << sizeof(usuarios) + (sizeof(Usuario) * cantidadUsuarios) << " bytes." << endl;
}

void baseDatosUsuarios::actualizarArchivo(string nombreArchivo)
{
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
        return;
    }

    for (short int i = 0; i < cantidadUsuarios; i++) {
        archivo << usuarios[i].getNickname() << " "
                << usuarios[i].getPassword() << " "
                << usuarios[i].getCiudad() << " "
                << usuarios[i].getPais() << " "
                << usuarios[i].getEsPremium() << " "
                << usuarios[i].getFechaInscripcion();

        // Solo agregar el usuario seguido si existe
        if (!usuarios[i].getUsuarioSeguido().empty()) {
            archivo << " " << usuarios[i].getUsuarioSeguido();
        }

        archivo << endl;
    }

    archivo.close();
    cout << "Base de datos actualizada exitosamente" << endl;
}

void baseDatosUsuarios::actualizarListaSeguidores(const string &usuarioQuePublica, const string &idCancion){
    for (short int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].sigueA(usuarioQuePublica)) {
            listaFavoritos& lista = usuarios[i].getListaFavoritos();
            if (!lista.existeCancion(idCancion)) {
                lista.agregarCancion(true, idCancion, nullptr);
            }
        }
    }
}
