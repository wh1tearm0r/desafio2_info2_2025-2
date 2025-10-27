#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>
#include <ctime>
#include "listaFavoritos.h"

using namespace std;

class baseDatosUsuarios;

class Usuario {
private:
    string nickname;
    bool esPremium;
    string password;
    string ciudad;
    string pais;
    int fechaInscripcion;

    listaFavoritos miLista;
    string usuarioSeguido;

public:
    Usuario();
    Usuario(string nick, string pass, string c, string p, bool premium = false, int fecha = 0, string seguido = "");

    bool autenticarUsuario(const string& passwordIngresada);
    void verPerfil();
    bool seguirUsuario(Usuario* otroUsuario, baseDatosUsuarios *bd, const string &archivoUsuarios);
    bool dejarDeSeguir(baseDatosUsuarios *bd, const string &archivoUsuarios);
    bool sigueA(const string& nickname) const;

    string getNickname() const;
    bool getEsPremium() const;
    string getCiudad() const;
    string getPais() const;
    int getFechaInscripcion() const;
    string getUsuarioSeguido() const;

    listaFavoritos& getListaFavoritos();

    void setEsPremium(bool premium);
    void setCiudad(string c);
    void setPais(string p);
    string getPassword() const;
    void setPassword(const string &newPassword);
};

#endif // USUARIO_H
