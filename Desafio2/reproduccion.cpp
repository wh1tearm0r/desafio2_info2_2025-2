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
int cargarAnuncios(Anuncio anuncios[], const string &archivoPublicidad){
    ifstream archivo(archivoPublicidad);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo de publicidad: " << archivoPublicidad << endl;
        return 0;
    }

    int totalAnuncios = 0;
    string linea;

    while (getline(archivo, linea) && totalAnuncios < 50) {
        if (linea.empty()) continue;

        // Formato: PRIORIDAD|MENSAJE
        size_t separador = linea.find('|');
        if (separador == string::npos || separador == 0) {
            continue;
        }

        char prioridad = linea[0];

        // Validar prioridad
        if (prioridad != 'A' && prioridad != 'B' && prioridad != 'C') {
            continue;
        }

        string mensaje = linea.substr(separador + 1);

        // Crear anuncio
        anuncios[totalAnuncios].id = totalAnuncios + 1;
        anuncios[totalAnuncios].prioridad = prioridad;

        // Copiar mensaje (máximo 500 caracteres)
        int i;
        for (i = 0; i < 500 && i < (int)mensaje.length(); i++) {
            anuncios[totalAnuncios].mensaje[i] = mensaje[i];
        }
        anuncios[totalAnuncios].mensaje[i] = '\0';

        totalAnuncios++;
    }

    cout << "La cantidad de memoria utilizada para cargar los anuncios es de " << sizeof(Anuncio) * totalAnuncios << " bytes." << endl;

    archivo.close();
    return totalAnuncios;
}
int seleccionarAnuncioAleatorio(Anuncio anuncios[], int totalAnuncios, int ultimoIdMostrado)
{
    if (totalAnuncios == 0) return -1;
    if (totalAnuncios == 1) return 0;

    // Crear arreglo de índices disponibles (excluyendo el último mostrado)
    int indicesDisponibles[50];
    int pesos[50];
    int cantDisponibles = 0;

    for (int i = 0; i < totalAnuncios; i++) {
        if (anuncios[i].id != ultimoIdMostrado) {
            indicesDisponibles[cantDisponibles] = i;

            // Asignar peso según prioridad
            switch(anuncios[i].prioridad) {
            case 'A': pesos[cantDisponibles] = 5; break;
            case 'B': pesos[cantDisponibles] = 3; break;
            case 'C': pesos[cantDisponibles] = 1; break;
            default: pesos[cantDisponibles] = 1;
            }

            cantDisponibles++;
            cout << "Se utilizaron " << cantDisponibles << " espacios de memoria para anuncios disponibles." << endl;
            cout << "Se hicieron " << i + 1 << " comparaciones para excluir el ultimo anuncio mostrado." << endl;
        }
    }

    // Si todos fueron excluidos (solo había uno igual al último), incluir todos
    if (cantDisponibles == 0) {
        for (int i = 0; i < totalAnuncios; i++) {
            indicesDisponibles[i] = i;
            switch(anuncios[i].prioridad) {
            case 'A': pesos[i] = 5; break;
            case 'B': pesos[i] = 3; break;
            case 'C': pesos[i] = 1; break;
            default: pesos[i] = 1;
            cout << "Se utilizaron " << i + 1 << " espacios de memoria para anuncios disponibles." << endl;
            cout << "Se hicieron " << i + 1 << " comparaciones para incluir todos los anuncios." << endl;
            }
        }
        cantDisponibles = totalAnuncios;

    }

    // Calcular peso total
    int pesoTotal = 0;
    for (int i = 0; i < cantDisponibles; i++) {
        pesoTotal += pesos[i];
    }

    // Selección ponderada
    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<int> distrib(1, pesoTotal);
    int valorAleatorio = distrib(generador);

    int acumulado = 0;
    for (int i = 0; i < cantDisponibles; i++) {
        acumulado += pesos[i];
        if (valorAleatorio <= acumulado) {
            return indicesDisponibles[i];
        }
    }

    cout << "La cantidad de memoria utilizada para la seleccion del anuncio es de " << sizeof(indicesDisponibles) + sizeof(pesos) << " bytes." << endl;

    // Fallback
    return indicesDisponibles[0];
}

void mostrarPublicidad(Anuncio anuncios[], int totalAnuncios, int &ultimoIdMostrado)
{
    if (totalAnuncios == 0) {
        cout << "\n[Sin publicidad disponible]\n" << endl;
        return;
    }

    int indiceSeleccionado = seleccionarAnuncioAleatorio(anuncios, totalAnuncios, ultimoIdMostrado);

    if (indiceSeleccionado < 0 || indiceSeleccionado >= totalAnuncios) {
        return;
    }

    Anuncio& anuncio = anuncios[indiceSeleccionado];
    ultimoIdMostrado = anuncio.id;

    // Mostrar la publicidad
    cout << "\n" << string(60, '=') << endl;
    cout << "   PUBLICIDAD [Prioridad " << anuncio.prioridad << "]" << endl;
    cout << string(60, '=') << endl;
    cout << anuncio.mensaje << endl;
    cout << string(60, '=') << endl;
    cout << "\nReproduciendo en 3 segundos..." << endl;

    this_thread::sleep_for(chrono::seconds(3));
    cout << endl;
}

int reproduccionAleatoria(bool premium, const string &NombreArchivo, int total, Anuncio anuncios[], int totalAnuncios, int &ultimoIdAnuncio)
{
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
            lineaSeleccionada = stoi(linea);
            break;
        }
        actual++;
    }
    archivo.close();

    // IMPORTANTE: Mostrar publicidad ANTES de reproducir la canción
    // Solo para usuarios no premium
    if (!premium && totalAnuncios > 0) {
        mostrarPublicidad(anuncios, totalAnuncios, ultimoIdAnuncio);
    }

    // Ahora sí, reproducir la canción
    cout << ">> Reproduciendo cancion seleccionada <<" << endl;
    GestorArchivos ga;
    ga.buscarCancionCompleta(lineaSeleccionada, premium);

    return lineaSeleccionada;
}

int reproduccionLista(bool premium, const string &NombreArchivo, int total, Anuncio anuncios[], int totalAnuncios, int &ultimoIdAnuncio, int &siguiente)
{
    ifstream archivo(NombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir la lista: " << NombreArchivo << endl;
        return 0;
    }

    string linea;
    int actual = 1;
    int lineaSeleccionada = 0;

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (actual == siguiente) {
            lineaSeleccionada = stoi(linea);
            break;
        }
        actual++;
    }
    archivo.close();

    if (!premium && totalAnuncios > 0) {
        mostrarPublicidad(anuncios, totalAnuncios, ultimoIdAnuncio);
    }

    GestorArchivos ga;
    ga.buscarCancionCompleta(lineaSeleccionada, premium);

    return lineaSeleccionada;
}

void detenerReproduccion() {
    cout << "La reproduccion se ha detenido" << endl;
}

void continuarReproduccion() {
    cout << "Reproduccion iniciada" << endl;
}

void inicializarHistorial(Historial& h, int maxR) {
    h.capacidad = 6;
    h.cantidad = 0;
    h.maxRetroceso = maxR;
    h.canciones = new int[h.capacidad];
}

void agregarCancion(Historial& h, int id) {

    if (h.cantidad == h.capacidad) {
        int nuevaCapacidad = h.capacidad + 2;
        int* nuevoArreglo = new int[nuevaCapacidad];

        for (int i = 0; i < h.cantidad; i++) {
            nuevoArreglo[i] = h.canciones[i];
        }

        delete[] h.canciones;
        h.canciones = nuevoArreglo;
        h.capacidad = nuevaCapacidad;
    }

    if (h.cantidad == 0 || h.canciones[h.cantidad - 1] != id) {
        h.canciones[h.cantidad] = id;
        h.cantidad++;
    }
}

int retrocederCancion(const Historial& h, int retroceder) {
    if (h.cantidad == 0) {
        cout << "No hay canciones en el historial." << endl;
        return -1;
    }

    if (retroceder <= 0 || retroceder > h.maxRetroceso || retroceder > h.cantidad - 1) {
        cout << "No se puede retroceder " << retroceder << " canciones." << endl;
        return -1;
    }

    int indice = h.cantidad - 1 - retroceder;
    return h.canciones[indice];
}

void liberarHistorial(Historial& h) {
    delete[] h.canciones;
    h.canciones = nullptr;
    h.cantidad = 0;
    h.capacidad = 0;
}

int repetirCancion(const Historial& h) {
    if (h.cantidad == 0) {
        cout << "No hay canción para repetir." << endl;
        return -1;
    }
    return h.canciones[h.cantidad - 1];
}
