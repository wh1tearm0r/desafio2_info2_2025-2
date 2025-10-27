#include "listaFavoritos.h"
#include "baseDatosUsuarios.h"
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

bool listaFavoritos::agregarCancion(bool premium, const string& idCancion, baseDatosUsuarios *bd) {
    if (!premium) {
        cout << "Esta funcion solo esta disponible para usuarios premium" << endl;
        return false;
    }

    // Validar que el ID sea numérico
    for (char c : idCancion) {
        if (!isdigit(c)) {
            cout << "Error: El ID de la cancion debe ser numerico" << endl;
            return false;
        }
    }

    // Validar que la canción exista en la base de datos
    try {
        int id = stoi(idCancion);
        GestorArchivos gestor;
        Cancion* cancionValidacion = gestor.buscarCancionCompleta(id, premium);

        if (cancionValidacion == nullptr) {
            cout << "Error: La cancion con ID " << idCancion << " no existe en la base de datos" << endl;
            return false;
        }

        cout << "Cancion encontrada: " << cancionValidacion->getNombre() << endl;
        delete cancionValidacion;
    } catch (...) {
        cout << "Error: ID de cancion invalido" << endl;
        return false;
    }

    if(existeCancion(idCancion)) {
        cout << "Esta cancion ya esta en tu lista" << endl;
        return false;
    }

    if(cantidadCanciones >= MAX_CANCIONES) {
        cout << "Has alcanzado el limite de canciones" << endl;
        cout << "En este momento hay " << cantidadCanciones << " canciones en tu lista y se consumieron " << sizeof(canciones)/sizeof(canciones[0]) << " espacios en total." << endl;
        return false;
    }

    canciones[cantidadCanciones] = idCancion;
    cantidadCanciones++;
    actualizarArchivo();

    cout << "Cancion agregada exitosamente!" << endl;

    // Propagar a seguidores si se proporciona la base de datos
    if (bd != nullptr && !nombreUsuario.empty()) {
        int cantidadUsuarios = bd->getCantidadUsuarios();
        int seguidoresActualizados = 0;

        cout << "Buscando seguidores para propagar la cancion..." << endl;

        for (int i = 0; i < cantidadUsuarios; i++) {
            Usuario* usuario = bd->getUsuarioEn(i);
            if (usuario != nullptr && usuario->sigueA(nombreUsuario)) {
                cout << "Propagando cancion a " << usuario->getNickname() << "..." << endl;
                listaFavoritos& listaDelSeguidor = usuario->getListaFavoritos();
                if (!listaDelSeguidor.existeCancion(idCancion)) {
                    // Agregar sin propagación recursiva (nullptr)
                    if (listaDelSeguidor.agregarCancion(true, idCancion, nullptr)) {
                        seguidoresActualizados++;
                    }
                }
            }
        }

        if (seguidoresActualizados > 0) {
            cout << "La cancion se agrego tambien a " << seguidoresActualizados << " seguidores" << endl;
        } else {
            cout << "No hay seguidores activos para propagar" << endl;
        }
    }

    return true;
}

bool listaFavoritos::eliminarCancion(bool premium, const string& idCancion, baseDatosUsuarios* bd) {
    if (!premium) {
        cout << "Esta funcion solo esta disponible para usuarios premium" << endl;
        return false;
    }

    int posicion = -1;
    for(int i = 0; i < cantidadCanciones; i++) {
        if(canciones[i] == idCancion) {
            cout << "Se hicieron " << i + 1 << " comparaciones para encontrar la cancion." << endl;
            posicion = i;
            break;
        }
    }

    if(posicion == -1) {
        cout << "La cancion no se encuentra en tu lista" << endl;
        return false;
    }

    // Desplazar elementos
    for(int i = posicion; i < cantidadCanciones - 1; i++) {
        canciones[i] = canciones[i + 1];
        cout << "Se hicieron " << i + 1 << " desplazamientos para eliminar la cancion." << endl;
    }

    canciones[cantidadCanciones - 1] = "";
    cantidadCanciones--;
    actualizarArchivo();

    cout << "Cancion eliminada exitosamente!" << endl;

    // Propagar eliminación a seguidores si se proporciona la base de datos
    if (bd != nullptr && !nombreUsuario.empty()) {
        int cantidadUsuarios = bd->getCantidadUsuarios();
        int seguidoresActualizados = 0;

        cout << "Buscando seguidores para propagar la eliminacion..." << endl;

        for (int i = 0; i < cantidadUsuarios; i++) {
            Usuario* usuario = bd->getUsuarioEn(i);
            if (usuario != nullptr && usuario->sigueA(nombreUsuario)) {
                cout << "Propagando eliminacion a " << usuario->getNickname() << "..." << endl;
                listaFavoritos& listaDelSeguidor = usuario->getListaFavoritos();
                if (listaDelSeguidor.existeCancion(idCancion)) {
                    // Eliminar sin propagación recursiva (nullptr)
                    if (listaDelSeguidor.eliminarCancion(true, idCancion, nullptr)) {
                        seguidoresActualizados++;
                    }
                }
            }
        }

        if (seguidoresActualizados > 0) {
            cout << "La cancion se elimino tambien de " << seguidoresActualizados << " seguidores" << endl;
        } else {
            cout << "No hay seguidores activos para propagar" << endl;
        }
    }

    return true;
}

bool listaFavoritos::existeCancion(const string& idCancion) const {
    for(int i = 0; i < cantidadCanciones; i++) {
        if(canciones[i] == idCancion) {
            cout << "Se hicieron " << i + 1 << " comparaciones para verificar la existencia de la cancion." << endl;
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
        cout << "Los espacios de memoria que consume la lista es de " << sizeof(canciones) << " bytes." << endl;
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
        cout << "Se usaron " << i + 1 << " escrituras para actualizar la lista." << endl;
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
        cout << "Se usaron " << i + 1 << " lecturas para cargar la lista." << endl;
    }

    archivo.close();
}
