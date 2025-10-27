#include "reproduccion.h"
#include "GestorArchivos.h"
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <fstream>

using namespace std;

void mostrarMenuReproduccion() {
    cout << " Menu de reproduccion: "<< endl;
    cout << "1. Reproduccion aleatoria " << endl;
    cout << "2. Reproduccion lista" << endl;
    cout << "3. Volver al menú principal" << endl;
}

int Totalcanciones(const string& NombreArchivo){
    int total = 0;
    string linea;
    ifstream archivo(NombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << NombreArchivo << endl;
        return 0;
    }

    while (getline(archivo, linea)) {
        total++;
    }

    archivo.close();
    return total;
}
int reproduccionAleatoria(bool premium, const string& NombreArchivo, int total ){

    string linea;
    int actual = 1;

    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<int> distrib(1, total);
    int numeroAleatorio = distrib(generador);

    ifstream archivo(NombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << NombreArchivo << endl;
        return 0;
    }

    int lineaSeleccionada = 0;
    while (getline(archivo, linea)) {
        if (actual == numeroAleatorio) {
            cout << "cancion aleatoria: " << linea << endl;
            lineaSeleccionada = stoi(linea);
            break;
        }
        actual++;
    }
    archivo.close();
    GestorArchivos ga;
    ga.buscarCancionCompleta(lineaSeleccionada, premium);

    return lineaSeleccionada;
}
    
