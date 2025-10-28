#include <iostream>
#include "usuario.h"
#include "basedatosusuarios.h"
#include "listaFavoritos.h"
#include "GestorArchivos.h"
#include "reproduccion.h"
#include <string>
#include <limits>

using namespace std;

int main()
{
    baseDatosUsuarios bd;
    bd.cargarDesdeArchivo("..\\..\\data\\usuarios.txt");

    Anuncio anuncios[50];
    int totalAnuncios = cargarAnuncios(anuncios, "..\\..\\data\\publicidad.txt");
    int ultimoIdAnuncio = -1; // Para rastrear el último anuncio mostrado

    cout << "Ingrese su nickname: ";
    string nickname;
    cin >> nickname;

    // cout << "Ingrese su contraseña: ";
    // string password;
    // cin >> password;

    // Usuario* usuario = bd.buscarUsuario(nickname);

    // if (usuario != nullptr && usuario->autenticarUsuario(password)) {
    //     cout << "Inicio de sesion exitoso!" << endl;
    //     cout << "Bienvenido/a, " << nickname << "!" << endl;
    //     cout << "1. Ver Perfil" << endl;
    //     cout << "2. Reproducir Aleatoriamente" << endl;
    //     if (usuario->getEsPremium()) {
    //         cout << "3. Ver Lista de Reproduccion" << endl;
    //         cout << "4. Agregar Cancion a Lista de Reproduccion" << endl;
    //         cout << "5. Eliminar Cancion de Lista de Reproduccion" << endl;
    //         cout << "6. Seguir Usuario" << endl;
    //         cout << "7. Dejar de Seguir Usuario" << endl;
    //     }
    //     int opcion;
    //     cin >> opcion;
    //     switch(opcion){
    //     case 1:
    //         usuario->verPerfil();
    //         break;
    //     case 2:
    //         {
    //         int totalCanciones = Totalcanciones("..\\..\\data\\cancionesglobales.txt");
    //         if (totalCanciones > 0) {
    //         reproduccionAleatoria(usuario->getEsPremium(), "..\\..\\data\\cancionesglobales.txt", totalCanciones, anuncios, totalAnuncios, ultimoIdAnuncio);
    //         }
    //         else {
    //             cout << "No hay canciones disponibles." << endl;
    //         }
    //         break;
    //         }
    //         break;
    //     case 3:
    //         usuario->getListaFavoritos().mostrarLista(usuario->getEsPremium());
    //         break;
    //     case 4:{
    //             cout << "Ingrese el ID de la cancion a agregar: ";
    //             string idCancion;
    //             cin >> idCancion;
    //             if (usuario->getListaFavoritos().agregarCancion(usuario->getEsPremium(), idCancion, &bd)) {
    //                 cout << "Cancion agregada exitosamente!" << endl;
    //             }
    //             break;
    //     }
    //     case 5:{
    //             cout << "Ingrese el ID de la cancion a eliminar: ";
    //             string idCancion;
    //             cin >> idCancion;
    //             if (usuario->getListaFavoritos().eliminarCancion(usuario->getEsPremium(), idCancion, &bd)) {
    //                 cout << "Cancion eliminada exitosamente!" << endl;
    //             }
    //             break;
    //         }
    //     case 6:{
    //             cout << "Ingrese el nickname del usuario a seguir: ";
    //             string usuarioASeguir;
    //             cin >> usuarioASeguir;
    //             Usuario* otroUsuario = bd.buscarUsuario(usuarioASeguir);
    //             if (otroUsuario != nullptr) {
    //                 if (usuario->seguirUsuario(otroUsuario, &bd, "..\\..\\data\\usuarios.txt")) {
    //                     cout << "Ahora sigues a " << usuarioASeguir << endl;
    //                 }
    //             } else {
    //                 cout << "El usuario no existe." << endl;
    //             }
    //             break;
    //     }
    //     case 7:{
    //             if (usuario->dejarDeSeguir(&bd, "..\\..\\data\\usuarios.txt")) {
    //                 cout << "Has dejado de seguir al usuario." << endl;
    //             }
    //             break;
    //     }
    //     default:
    //         cout << "Opcion invalida." << endl;
    //         break;
    //     }
    // } else {
    //     cout << "Error de autenticacion." << endl;
    // }

    bool esPremium = true;
    int opcion;
    Historial historial;

    if (esPremium)
        inicializarHistorial(historial, 4);

    do {
        cout << "MENU PRINCIPAL" << endl;
        cout << "1. Reproduccion aleatoria" << endl;
        cout << "2. Retroceder cancion" << endl;
        cout << "3. Repetir cancion" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        int siguiente = 1;

        switch (opcion) {
        case 1: {
            cout << "Que deseas reproducir?. " << endl;
            cout << "1. Canciones GLobales." << endl;
            cout << "2. Lista de reproduccion." << endl;
            cout << "3. lista de reproduccion en orden. " << endl;
            cout << "elige: ";

            int cual;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> cual;

            string nombreArchivo = "";

            if (cual == 1) {
                nombreArchivo = "..\\..\\data\\cancionesglobales.txt";
            }
            else if (cual == 2) {
                nombreArchivo = "..\\..\\data\\lista_" + nickname + ".txt";
            }
            else if (cual == 3) {
                nombreArchivo = "..\\..\\data\\lista_" + nickname + ".txt";
                int total = Totalcanciones(nombreArchivo);
                siguiente++;
                if (total > 0) {
                    int id = reproduccionLista(esPremium, nombreArchivo, total, anuncios, totalAnuncios, ultimoIdAnuncio, siguiente);
                    agregarCancion(historial, id);
                    if (siguiente >= total) {
                        cout << "Fin de la lista de reproduccion." << endl;
                        siguiente = 1;
                    }
                } else {
                    cout << "No hay canciones disponibles." << endl;
                }

                break;
            }
            else {
                cout << "Opcion invalida." << endl;
                continue;
            }

            int total = Totalcanciones(nombreArchivo);

            if (total > 0) {
                int id = reproduccionAleatoria(esPremium, nombreArchivo, total, anuncios, totalAnuncios, ultimoIdAnuncio);
                agregarCancion(historial, id);
            } else {
                cout << "No hay canciones disponibles." << endl;
            }
            break;
        }

        case 2: {
            if (!esPremium) {
                cout << "Solo los usuarios Premium pueden retroceder canciones." << endl;
                break;
            }

            int pasos;
            cout << "¿Cuántas canciones deseas retroceder? ";
            cin >> pasos;

            int idPrevio = retrocederCancion(historial, pasos);
            if (idPrevio != -1) {
                cout << "Reproduciendo cancion previa..." << endl;
                GestorArchivos::buscarCancionCompleta(idPrevio, esPremium);
            }
            break;
        }

        case 3: {
            int idRepetir = repetirCancion(historial);
            if (idRepetir != -1) {
                cout << "Repitiendo canción actual..." << endl;
                GestorArchivos::buscarCancionCompleta(idRepetir, esPremium);
            }
            break;
        }

        case 4:
            cout << "Finalizar programa";
            liberarHistorial(historial);
            break;

        default:
            break;
        }

    } while (opcion != 4);

    return 0;
}
