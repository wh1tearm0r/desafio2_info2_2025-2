#include "usuario.h"
#include "baseDatosUsuarios.h"

// Constructor por defecto

Usuario::Usuario() {
    nickname = "";
    password = "";
    ciudad = "";
    pais = "";
    esPremium = false;
    fechaInscripcion = 0;
    usuarioSeguido = "";
}

// Constructor con parámetros
Usuario::Usuario(string nick, string pass, string c, string p, bool premium, int fecha, string seguido) {
    nickname = nick;
    password = pass;
    ciudad = c;
    pais = p;
    esPremium = premium;
    usuarioSeguido = seguido;

    if (fecha == 0) {
        fechaInscripcion = time(0);  // Timestamp actual
    } else {
        fechaInscripcion = fecha;
    }

    miLista.setNombreUsuario(nick);
    miLista.cargarDesdeArchivo();
}

// Método de autenticación
bool Usuario::autenticarUsuario(const string& passwordIngresada) {
    return password == passwordIngresada;
}

// Mostrar perfil
void Usuario::verPerfil() {
    cout << "\n========================================" << endl;
    cout << "           PERFIL DE USUARIO" << endl;
    cout << "========================================" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Pais: " << pais << endl;
    cout << "Tipo de cuenta: " << (esPremium ? "PREMIUM" : "GRATUITA") << endl;

    // Convertir timestamp a fecha legible
    if (fechaInscripcion > 0) {
        time_t tiempo = fechaInscripcion;
        cout << "Fecha de inscripcion: " << ctime(&tiempo);
    }
    cout << "========================================\n" << endl;
}

bool Usuario::seguirUsuario(Usuario* otroUsuario, baseDatosUsuarios* bd, const string& archivoUsuarios){
    if (!esPremium) {
        cout << "Esta funcion solo esta disponible para usuarios premium" << endl;
        return false;
    }

    if (otroUsuario == nullptr) {
        cout << "Usuario no encontrado" << endl;
        return false;
    }

    if (otroUsuario->getNickname() == nickname) {
        cout << "No puedes seguirte a ti mismo" << endl;
        return false;
    }

    if (!usuarioSeguido.empty()) {
        cout << "Ya estas siguiendo a " << usuarioSeguido << endl;
        return false;
    }

    // Establecer relación de seguimiento
    usuarioSeguido = otroUsuario->getNickname();

    // Copiar todas las canciones del usuario seguido
    listaFavoritos& listaDelSeguido = otroUsuario->getListaFavoritos();
    int cancionesCopiadas = 0;

    for (int i = 0; i < listaDelSeguido.getCantidadCanciones(); i++) {
        string idCancion = listaDelSeguido.getCancionEn(i);
        if (!miLista.existeCancion(idCancion)) {
            if (miLista.agregarCancion(true, idCancion, nullptr)) {
                cancionesCopiadas++;
            }
        }
    }

    cout << "\nAhora sigues a " << usuarioSeguido << endl;
    cout << "Se copiaron " << cancionesCopiadas << " canciones a tu lista" << endl;

    // Guardar cambios en el archivo
    if (bd != nullptr && !archivoUsuarios.empty()) {
        bd->actualizarArchivo(archivoUsuarios);
    }

    return true;
}

bool Usuario::dejarDeSeguir(baseDatosUsuarios* bd, const string& archivoUsuarios){
    if (!esPremium) {
        cout << "Esta funcion solo esta disponible para usuarios premium" << endl;
        return false;
    }

    if (usuarioSeguido.empty()) {
        cout << "No estas siguiendo a ningun usuario" << endl;
        return false;
    }

    cout << "Dejaste de seguir a " << usuarioSeguido << endl;
    usuarioSeguido = "";

    // Guardar cambios en el archivo
    if (bd != nullptr && !archivoUsuarios.empty()) {
        bd->actualizarArchivo(archivoUsuarios);
    }

    return true;
}

bool Usuario::sigueA(const string &nickname) const
{
    return usuarioSeguido == nickname;
}

// Getters y setters

string Usuario::getNickname() const {
    return nickname;
}

string Usuario::getPassword() const{
    return password;
}

bool Usuario::getEsPremium() const {
    return esPremium;
}

string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

int Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

string Usuario::getUsuarioSeguido() const{
    return usuarioSeguido;
}

listaFavoritos &Usuario::getListaFavoritos() {
    return miLista;
}

void Usuario::setEsPremium(bool premium) {
    esPremium = premium;
}

void Usuario::setCiudad(string c) {
    ciudad = c;
}

void Usuario::setPais(string p) {
    pais = p;
}
