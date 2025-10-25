#include <iostream>
#include "basedatosusuarios.h"
#include "usuario.h"
#include "GestorArchivos.h"

using namespace std;

int main()
{
    //baseDatosUsuarios bd("usuarios.txt");
    baseDatosUsuarios bd;
    bd.cargarDesdeArchivo("..\\..\\Data\\usuarios.txt");
    GestorArchivos ga;

    int opcion;
    cout << "Ingresa una opcion" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Listar usuarios registrados" << endl;
    cout << "3. Salir" << endl;
    cin >> opcion;

    switch(opcion) {
    case 1: {
        // bd.iniciarSesion();
        bool esPremium = true;
        int id;
        cout << "ingrese el id de la cancion: ";
        cin >> id;

        Cancion* c = ga.buscarCancionCompleta(id, esPremium);
        break;
    }
    case 2: {
        bd.listarUsuarios();
        break;
    }
    case 3: {
        cout << "\nGracias por usar el sistema. Hasta luego!" << endl;
        break;
    }
    default: {
        cout << "\n[ERROR] Opcion invalida. Intente nuevamente." << endl;
    }

    return 0;
    }
}
