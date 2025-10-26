#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "listaFavoritos.h"
using namespace std;

class Usuario {
private:
    string nickname;
    bool esPremium;
    string password;
    string ciudad;
    string pais;
    int fechaInscripcion;

    listaFavoritos miLista;

public:
    // Constructores
    Usuario();
    Usuario(string nick, string pass, string c, string p, bool premium = false, int fecha = 0);

    // Métodos principales
    bool autenticarUsuario(const string& passwordIngresada);
    void verPerfil();

    // Getters
    string getNickname() const;
    bool getEsPremium() const;
    string getCiudad() const;
    string getPais() const;
    int getFechaInscripcion() const;

    listaFavoritos& getListaFavoritos();

    // Setters (opcional)
    void setEsPremium(bool premium);
    void setCiudad(string c);
    void setPais(string p);
    string getPassword() const;
    void setPassword(const string &newPassword);
};

#endif
