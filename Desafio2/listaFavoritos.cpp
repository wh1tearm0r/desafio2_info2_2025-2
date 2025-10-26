#include "listaFavoritos.h"
#include "GestorArchivos.h"

listaFavoritos::listaFavoritos()
{
    cantidadCanciones = 0;
    nombreUsuario = "";
    for(int i = 0; i < MAX_CANCIONES; i++) {
        canciones[i] = "";
    }
}

listaFavoritos::listaFavoritos(const string &usuario)
{
    cantidadCanciones = 0;
    nombreUsuario = usuario;
    for(int i = 0; i < MAX_CANCIONES; i++) {
        canciones[i] = "";
    }
}

void listaFavoritos::setNombreUsuario(const string& usuario) {
    nombreUsuario = usuario;
}

bool listaFavoritos::agregarCancion(const string& idCancion) {
    if(existeCancion(idCancion)) {
        cout << "Esta cancion ya esta en tu lista" << endl;
        return false;
    }

    if(cantidadCanciones >= MAX_CANCIONES) {
        cout << "Has alcanzado el limite de canciones" << endl;
        return false;
    }

    canciones[cantidadCanciones] = idCancion;
    cantidadCanciones++;
    actualizarArchivo();
    return true;
}

bool listaFavoritos::eliminarCancion(const string& idCancion) {
    int posicion = -1;

    for(int i = 0; i < cantidadCanciones; i++) {
        if(canciones[i] == idCancion) {
            posicion = i;
            break;
        }
    }

    if(posicion == -1) {
        return false;
    }

    // Desplazar elementos
    for(int i = posicion; i < cantidadCanciones - 1; i++) {
        canciones[i] = canciones[i + 1];
    }

    canciones[cantidadCanciones - 1] = "";
    cantidadCanciones--;
    actualizarArchivo();
    return true;
}

bool listaFavoritos::existeCancion(const string& idCancion) const {
    for(int i = 0; i < cantidadCanciones; i++) {
        if(canciones[i] == idCancion) {
            return true;
        }
    }
    return false;
}

void listaFavoritos::mostrarLista(bool premium) const {

    if (!premium){
        cout << "Esta funcion solo esta disponible para usuarios premium" << endl;
    }
    else if(cantidadCanciones == 0) {
        cout << "Tu lista esta vacia" << endl;
        return;
    }
    else{
        GestorArchivos gestor;
        cout << "\n=== MI LISTA DE REPRODUCCION ===" << endl;
        cout << "Total de canciones: " << cantidadCanciones << endl;
        cout << "-------------------------------------------" << endl;

        for(int i = 0; i < cantidadCanciones; i++) {
            cout << (i+1) << ". ";

            // Buscar la canción para mostrar detalles
            int id = stoi(canciones[i]);
            Cancion* cancion = gestor.buscarCancionCompleta(id, premium);

            if(cancion != nullptr) {
                cout << cancion->getNombre() << " - ID: " << id << endl;
                delete cancion;
            } else {
                cout << "ID: " << canciones[i] << " (no encontrada)" << endl;
            }
        }
    }
}

int listaFavoritos::getCantidadCanciones() const{
    return cantidadCanciones;
}

string listaFavoritos::getCancionEn(int posicion) const
{
    if(posicion >= 0 && posicion < cantidadCanciones) {
        return canciones[posicion];
    }
    return "";
}

void listaFavoritos::actualizarArchivo() const{
    if(nombreUsuario.empty()) {
        return;
    }


    string nombreArchivo = "..\\..\\data\\lista_" + nombreUsuario + ".txt";
    ofstream archivo(nombreArchivo);

    if(!archivo.is_open()) {
        cout << "Error al guardar la lista" << endl;
        return;
    }

    archivo << cantidadCanciones << endl;

    for(int i = 0; i < cantidadCanciones; i++) {
        archivo << canciones[i] << endl;
    }

    archivo.close();
}

void listaFavoritos::cargarDesdeArchivo(){
    if(nombreUsuario.empty()) {
        return;
    }

    string nombreArchivo = "..\\..\\data\\lista_" + nombreUsuario + ".txt";
    ifstream archivo(nombreArchivo);

    if(!archivo.is_open()) {
        // Archivo no existe, lista vacía
        cantidadCanciones = 0;
        return;
    }

    archivo >> cantidadCanciones;

    if(cantidadCanciones > MAX_CANCIONES) {
        cantidadCanciones = MAX_CANCIONES;
    }

    for(int i = 0; i < cantidadCanciones; i++) {
        archivo >> canciones[i];
    }

    archivo.close();
}
