#include <iostream>
#include "usuario.h"
#include "basedatosusuarios.h"
#include "listaFavoritos.h"
#include "GestorArchivos.h"

using namespace std;

int main()
{
    baseDatosUsuarios bd;
    bd.cargarDesdeArchivo("..\\..\\data\\usuarios.txt");

    cout << "Ingrese su nickname: ";
    string nickname;
    cin >> nickname;

    cout << "Ingrese su contraseña: ";
    string password;
    cin >> password;

    Usuario* usuario = bd.buscarUsuario(nickname);

    if (usuario != nullptr && usuario->autenticarUsuario(password)) {
        cout << "Inicio de sesion exitoso!" << endl;
        cout << "Bienvenido/a, " << nickname << "!" << endl;
        cout << "1. Ver Perfil" << endl;
        cout << "2. Ver mi lista de favoritos" << endl;
        int opcion;
        cin >> opcion;
        switch(opcion){
        case 1:
            usuario->verPerfil();
            break;
        case 2:
            usuario->getListaFavoritos().mostrarLista(usuario->getEsPremium());
            break;
        case 3:
            cout << "Saliendo..." << endl;
            break;
        }
    } else {
        cout << "Error de autenticacion." << endl;
    }

    return 0;
}
