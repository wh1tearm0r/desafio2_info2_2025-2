#include "GestorArchivos.h"

Artista* GestorArchivos::buscarArtista(int idArtista) {
    ifstream archivo("artistas.txt");
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir artistas.txt" << endl;
        return nullptr;
    }

    string linea;
    while (getline(archivo, linea)) {
        int pos = linea.find('|');
        int id = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        string nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        int edad = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        string pais = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        int seguidores = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        int ranking = stoi(linea);

        if (id == idArtista) {
            archivo.close();
            return new Artista(id, nombre, edad, pais, seguidores, ranking);
        }
    }

    archivo.close();
    return nullptr;
}

Album* GestorArchivos::buscarAlbum(int idArtista, int idAlbum) {
    ifstream archivo("albumes.txt");
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir albumes.txt" << endl;
        return nullptr;
    }

    string linea;
    while (getline(archivo, linea)) {
        int pos = linea.find('|');
        int id = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        int artistaEnArchivo = id / 100;
        int albumEnArchivo = id % 100;

        if (artistaEnArchivo == idArtista && albumEnArchivo == idAlbum) {
            pos = linea.find('|');
            string nombre = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string genero1 = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string genero2 = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string genero3 = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string genero4 = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string fecha = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string duracion = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string sello = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string portada = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            float puntuacion = stof(linea);

            archivo.close();
            return new Album(id, idArtista, nombre, genero1, genero2, genero3, genero4, fecha,
                             duracion, sello, portada, puntuacion);
        }
    }

    archivo.close();
    return nullptr;
}

Cancion* GestorArchivos::buscarCancionCompleta(int idCancion, bool premium) {

    string idStr = to_string(idCancion);
    int idArtista = stoi(idStr.substr(0, 5));
    int idAlbum = stoi(idStr.substr(5, 2));

    // Buscar artista y álbum
    Artista* artista = buscarArtista(idArtista);
    Album* album = buscarAlbum(idArtista, idAlbum);

    ifstream archivo("canciones.txt");
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir canciones.txt"<< endl;
        return nullptr;
    }

    string linea;
    while (getline(archivo, linea)) {
        int pos = linea.find('|');
        int id = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        if (id == idCancion) {
            pos = linea.find('|');
            string nombre = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string duracion = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            float puntuacion = stof(linea.substr(0, pos));
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string ruta128 = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find('|');
            string ruta320 = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            int reproducciones = stoi(linea);

            Cancion* c = new Cancion(id, idArtista, idAlbum, nombre, duracion,
                                     puntuacion, ruta128, ruta320, reproducciones);

            cout << "Resultado de busqueda:" << endl;
            c->reproducir(premium, album->getPortada(), album->getNombre(), artista->getNombre());
            archivo.close();
            return c;
        }
    }

    archivo.close();
    return nullptr;
}
