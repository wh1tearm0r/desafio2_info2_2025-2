#include "Cancion.h"

Cancion::Cancion() {
    idCancion = 0;
    idArtista = 0;
    idAlbum = 0;
    nombre = "";
    duracion = "";
    puntuacion = 0.0;
    ruta128 = "";
    ruta320 = "";
    reproducciones = 0;
}

Cancion::Cancion(int _idCancion, int _idArtista, int _idAlbum, string _nombre,
                 string _duracion, float _puntuacion, string _ruta128,
                 string _ruta320, int _reproducciones) {
    idCancion = _idCancion;
    idArtista = _idArtista;
    idAlbum = _idAlbum;
    nombre = _nombre;
    duracion = _duracion;
    puntuacion = _puntuacion;
    ruta128 = _ruta128;
    ruta320 = _ruta320;
    reproducciones = _reproducciones;
}

int Cancion::getIdCancion() const { return idCancion; }
int Cancion::getIdArtista() const { return idArtista; }
int Cancion::getIdAlbum() const { return idAlbum; }
string Cancion::getNombre() const { return nombre; }
string Cancion::getDuracion() const { return duracion; }
float Cancion::getPuntuacion() const { return puntuacion; }
string Cancion::getRuta128() const { return ruta128; }
string Cancion::getRuta320() const { return ruta320; }
int Cancion::getReproducciones() const { return reproducciones; }

void Cancion::mostrarInfo() const {
    cout << "\nCancion: " << nombre << endl;
    cout << "ID: " << idCancion << " (Artista: " << idArtista << ", Album: " << idAlbum << ")" << endl;
    cout << "Duracion: " << duracion << " Puntuación: " << puntuacion << endl;
    cout << "Reproducciones: " << reproducciones << endl;
}

void Cancion::reproducir(bool premium, const string& portadaAlbum, const string& nombreAlbum, const string& nombreArtista) {
    //cout << endl << "Reproduciendo cancion..." << endl;
    cout << "Artista: " << nombreArtista << endl;
    cout << "Album: " << nombreAlbum << endl;
    cout << "Ruta a la Portada del album: " << portadaAlbum << endl << endl;
    cout << "Titulo: " << nombre << endl;

    if (premium)
        cout << "Ruta del archivo de audio: " << ruta320 << endl;
    else
        cout << "Ruta del archivo de audio: " << ruta128 << endl;

    cout << "Duracion: " << duracion << endl;
    cout << "Reproduciendo..." << endl;
}
