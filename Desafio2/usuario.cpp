#include "Usuario.h"
#include <iostream>
#include <ctime>

using namespace std;

// Constructor por defecto

Usuario::Usuario() {
    nickname = "";
    password = "";
    ciudad = "";
    pais = "";
    esPremium = false;
    fechaInscripcion = 0;
}

// Constructor con parámetros
Usuario::Usuario(string nick, string pass, string c, string p, bool premium, int fecha) {
    nickname = nick;
    password = pass;
    ciudad = c;
    pais = p;
    esPremium = premium;

    if (fecha == 0) {
        fechaInscripcion = time(0);  // Timestamp actual
    } else {
        fechaInscripcion = fecha;
    }
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

// Getters
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

// Setters
void Usuario::setEsPremium(bool premium) {
    esPremium = premium;
}

void Usuario::setCiudad(string c) {
    ciudad = c;
}

void Usuario::setPais(string p) {
    pais = p;
}
