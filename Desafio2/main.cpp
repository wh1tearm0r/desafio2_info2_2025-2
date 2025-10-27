#include <iostream>
#include "usuario.h"
#include "basedatosusuarios.h"
#include "listaFavoritos.h"
#include "GestorArchivos.h"
#include "reproduccion.h"
#include <string>

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
        cout << "2. Reproducir Aleatoriamente" << endl;
        if (usuario->getEsPremium()) {
            cout << "3. Ver Lista de Reproduccion" << endl;
            cout << "4. Agregar Cancion a Lista de Reproduccion" << endl;
            cout << "5. Eliminar Cancion de Lista de Reproduccion" << endl;
            cout << "6. Seguir Usuario" << endl;
            cout << "7. Dejar de Seguir Usuario" << endl;
        }
        int opcion;
        cin >> opcion;
        switch(opcion){
        case 1:
            usuario->verPerfil();
            break;
        case 2:
            //Implementar Reproduccion Aleatoria
            break;
        case 3:
            usuario->getListaFavoritos().mostrarLista(usuario->getEsPremium());
            break;
        case 4:{
                cout << "Ingrese el ID de la cancion a agregar: ";
                string idCancion;
                cin >> idCancion;
                if (usuario->getListaFavoritos().agregarCancion(usuario->getEsPremium(), idCancion, &bd)) {
                    cout << "Cancion agregada exitosamente!" << endl;
                }
                break;
        }
        case 5:{
                cout << "Ingrese el ID de la cancion a eliminar: ";
                string idCancion;
                cin >> idCancion;
                if (usuario->getListaFavoritos().eliminarCancion(usuario->getEsPremium(), idCancion, &bd)) {
                    cout << "Cancion eliminada exitosamente!" << endl;
                }
                break;
            }
        case 6:{
                cout << "Ingrese el nickname del usuario a seguir: ";
                string usuarioASeguir;
                cin >> usuarioASeguir;
                Usuario* otroUsuario = bd.buscarUsuario(usuarioASeguir);
                if (otroUsuario != nullptr) {
                    if (usuario->seguirUsuario(otroUsuario, &bd, "..\\..\\data\\usuarios.txt")) {
                        cout << "Ahora sigues a " << usuarioASeguir << endl;
                    }
                } else {
                    cout << "El usuario no existe." << endl;
                }
                break;
        }
        case 7:{
                if (usuario->dejarDeSeguir(&bd, "..\\..\\data\\usuarios.txt")) {
                    cout << "Has dejado de seguir al usuario." << endl;
                }
                break;
        }
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    } else {
        cout << "Error de autenticacion." << endl;
    }

    return 0;
}
