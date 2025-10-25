#include "Artista.h"

Artista::Artista() {
    idArtista = 0;
    nombre = "";
    edad = 0;
    pais = "";
    seguidores = 0;
    ranking = 0;
}

Artista::Artista(int _idArtista, string _nombre, int _edad,
                 string _pais, int _seguidores, int _ranking) {
    idArtista = _idArtista;
    nombre = _nombre;
    edad = _edad;
    pais = _pais;
    seguidores = _seguidores;
    ranking = _ranking;
}

int Artista::getIdArtista() const { return idArtista; }
string Artista::getNombre() const { return nombre; }
int Artista::getEdad() const { return edad; }
string Artista::getPais() const { return pais; }
int Artista::getSeguidores() const { return seguidores; }
int Artista::getRanking() const { return ranking; }


void Artista::mostrarInfo() const {
    cout << "\nArtista: " << nombre << endl;
    cout << "ID: " << idArtista << endl;
    cout << "Edad: " << edad << endl;
    cout << "Pais: " << pais << endl;
    cout << "Seguidores: " << seguidores << endl;
    cout << "Ranking global: " << ranking << endl;
}
