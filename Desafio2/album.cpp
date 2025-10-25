#include "album.h"

Album::Album() {
    idAlbum = 0;
    idArtista = 0;
    nombre = "";
    genero1 = "";
    genero2 = "";
    genero3 = "";
    genero4 = "";
    fecha = "";
    duracion = "";
    sello = "";
    portada = "";
    puntuacion = 0.0;
}

Album::Album(int _idAlbum, int _idArtista, string _nombre, string _genero1,
             string _genero2, string _genero3, string _genero4, string _fecha, string _duracion, string _sello,
             string _portada, float _puntuacion) {
    idAlbum = _idAlbum;
    idArtista = _idArtista;
    nombre = _nombre;
    genero1 = _genero1;
    genero2 = _genero2;
    genero3 = _genero3;
    genero4 = _genero4;
    fecha = _fecha;
    duracion = _duracion;
    sello = _sello;
    portada = _portada;
    puntuacion = _puntuacion;
}

int Album::getIdAlbum() const { return idAlbum; }
int Album::getIdArtista() const { return idArtista; }
string Album::getNombre() const { return nombre; }
string Album::getGenero1() const { return genero1; }
string Album::getGenero2() const { return genero2; }
string Album::getGenero3() const { return genero3; }
string Album::getGenero4() const { return genero4; }
string Album::getFecha() const { return fecha; }
string Album::getDuracion() const { return duracion; }
string Album::getSello() const { return sello; }
string Album::getPortada() const { return portada; }
float Album::getPuntuacion() const { return puntuacion; }

void Album::mostrarInfo() const {
    cout << "\n Album: " << nombre << endl;
    cout << "ID Album: " << idAlbum << " | Artista ID: " << idArtista << endl;
    cout << "Generos: " << genero1;
    if (!genero2.empty()) cout << ", " << genero2;
    cout << endl;
    cout << "Lanzamiento: " << fecha << endl;
    cout << "Duracion total: " << duracion << endl;
    cout << "Sello: " << sello << endl;
    cout << "Portada: " << portada << endl;
    cout << "Puntuacion: " << puntuacion << endl;
}
