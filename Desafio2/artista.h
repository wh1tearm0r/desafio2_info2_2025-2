#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include <iostream>
using namespace std;

class Artista {
private:
    int idArtista;       // Identificador de 5 dígitos (ej. 10001)
    string nombre;       // Nombre del artista (ej. Claudia_Lorelle)
    int edad;            // Edad del artista
    string pais;         // País de origen
    int seguidores;      // Cantidad de seguidores
    int ranking;         // Posición en la lista de tendencias global

public:
    // Constructor vacío (opcional, útil para crear objetos temporales)
    Artista();

    // Constructor con parámetros
    Artista(int _idArtista, string _nombre, int _edad,
            string _pais, int _seguidores, int _ranking);

    // Getters
    int getIdArtista() const;
    string getNombre() const;
    int getEdad() const;
    string getPais() const;
    int getSeguidores() const;
    int getRanking() const;

    // Mostrar información del artista (útil para depuración o interfaz)
    void mostrarInfo() const;
};


#endif // ARTISTA_H
