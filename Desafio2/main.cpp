#include <iostream>
#include "usuario.h"
#include "basedatosusuarios.h"
#include "listaFavoritos.h"
#include "GestorArchivos.h"
#include "reproduccion.h"
#include <string>
#include <limits>
#include <chrono>
#include <thread>

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
            {
            cout << " MODO DE REPRODUCCION ALEATORIA" << endl;
            bool continuar1 = true;
            Historial historial;
            if (usuario->getEsPremium()){
                inicializarHistorial(historial, 4);
            }
            while(continuar1){
                cout << " Que quieres hacer ahora?" << endl;
                cout << "1. Reproduccion aleatoria" << endl;
                cout << "2. Retroceder cancion" << endl;
                cout << "3. Repetir cancion" << endl;
                cout << "4. Salir" << endl;
                cout << "Selecciona una opcion: ";
                int opcion1;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> opcion1;

                switch (opcion1) {
                case 1: {
                    continuar1 = true;
                    int K = 0;
                    while(K < 5) {

                        int totalCanciones = Totalcanciones("..\\..\\data\\cancionesglobales.txt");
                        if (totalCanciones > 0) {
                            continuarReproduccion();
                            int id = reproduccionAleatoria(usuario->getEsPremium(), "..\\..\\data\\cancionesglobales.txt", totalCanciones, anuncios, totalAnuncios, ultimoIdAnuncio);
                            agregarCancion(historial, id);
                            std::this_thread::sleep_for(std::chrono::seconds(3));
                        }
                        else {
                            cout << "No hay canciones disponibles." << endl;
                            continuar1 = false;
                        }
                        K++;
                    }
                }

                case 2: {
                    if (!usuario->getEsPremium()) {
                        cout << "Solo los usuarios Premium pueden retroceder canciones." << endl;
                        break;
                    }

                    int pasos;
                    cout << "¿Cuántas canciones deseas retroceder? ";
                    cin >> pasos;

                    int idPrevio = retrocederCancion(historial, pasos);
                    if (idPrevio != -1) {
                        cout << "Reproduciendo cancion previa..." << endl;
                        GestorArchivos::buscarCancionCompleta(idPrevio, usuario->getEsPremium());
                    }
                    break;
                }

                case 3: {
                    int idRepetir = repetirCancion(historial);
                    if (idRepetir != -1) {
                        cout << "Repitiendo canción actual..." << endl;
                        GestorArchivos::buscarCancionCompleta(idRepetir, usuario->getEsPremium());
                    }
                    break;
                }

                case 4:{
                    cout << "Reproduccion aleatoria finalizada.";
                    liberarHistorial(historial);
                    continuar1 = false;
                    break;

                default:
                    break;
                }

                }
            }
            break;
        }

        case 3:{
            int siguiente = 2;
            cout << "TU lista de reproduccion: " << endl;

            usuario->getListaFavoritos().mostrarLista(usuario->getEsPremium());

            bool continuar2 = true;

            while(continuar2) {

                cout << "Que Qiieres hacer?. " << endl;
                cout << "1. Reproducir de forma aleatoria." << endl;
                cout << "2. Reproducir en orden. " << endl;
                cout << "3. Salir." << endl;
                cout << "elige: ";
                int cual;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> cual;

                string nombreArchivo = "";

                if (cual == 1) {
                    bool continuar3 = true;
                    while(continuar3) {

                        cout << "Opciones: " << endl;
                        cout << "1. Siguiente cancion " << endl;
                        cout << "2. Regresar cancion " << endl;
                        cout << "2. Repetir cancion " << endl;
                        cout << "2. Pausar cancion " << endl;
                        cout << "Elige: ";

                        int opcion3;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> opcion3;


                        nombreArchivo = "..\\..\\data\\lista_" + nickname + ".txt";

                        int total = Totalcanciones(nombreArchivo);

                        if (total > 0) {
                            int id = reproduccionAleatoria(esPremium, nombreArchivo, total, anuncios, totalAnuncios, ultimoIdAnuncio);
                            agregarCancion(historial, id);
                        } else {
                            cout << "No hay canciones disponibles." << endl;
                        }

                    }

                }
                else if (cual == 2) {
                    int total = Totalcanciones(nombreArchivo);

                    if (siguiente > total) {
                        cout << "Fin de la lista de reproduccion." << endl;
                        siguiente = 2;
                        break;
                    }
                    if (total > 0) {
                        int id = reproduccionLista(esPremium, nombreArchivo, total, anuncios, totalAnuncios, ultimoIdAnuncio, siguiente);
                        agregarCancion(historial, id);
                        siguiente++;
                    } else {
                        cout << "No hay canciones disponibles." << endl;
                    }
                    break;
                }
                else if (cual == 3) {
                    cout << "Saliendo del sistema de lista de favoritos" << endl;
                    continuar2 = false;
                    break;
                }
                else {
                    cout << "Opcion invalida." << endl;
                    continuar2 = false;
                    break;
                }
            }

            break;
        }
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
}












//     bool esPremium = true;
//     int opcion;
//     Historial historial;

//     if (esPremium){
//         inicializarHistorial(historial, 4);
//     }
//     int siguiente = 2;


//     do {
//         cout << "MENU PRINCIPAL" << endl;
//         cout << "1. Reproduccion aleatoria" << endl;
//         cout << "2. Retroceder cancion" << endl;
//         cout << "3. Repetir cancion" << endl;
//         cout << "4. Salir" << endl;
//         cout << "Selecciona una opcion: ";
//         cin >> opcion;

//         switch (opcion) {
//         case 1: {
//             cout << "Que deseas reproducir?. " << endl;
//             cout << "1. Canciones GLobales." << endl;
//             cout << "2. Lista de reproduccion." << endl;
//             cout << "3. lista de reproduccion en orden. " << endl;
//             cout << "elige: ";

//             int cual;
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             cin >> cual;

//             string nombreArchivo = "";

//             if (cual == 1) {
//                 nombreArchivo = "..\\..\\data\\cancionesglobales.txt";
//             }
//             else if (cual == 2) {
//                 nombreArchivo = "..\\..\\data\\lista_" + nickname + ".txt";
//             }
//             else if (cual == 3) {
//                 nombreArchivo = "..\\..\\data\\lista_" + nickname + ".txt";
//                 int total = Totalcanciones(nombreArchivo);

//                 cout << "CUANto VALE SIGUIENTE: " << siguiente << endl;
//                 if (siguiente > total) {
//                     cout << "Fin de la lista de reproduccion." << endl;
//                     siguiente = 2;
//                     break;
//                 }
//                 if (total > 0) {
//                     int id = reproduccionLista(esPremium, nombreArchivo, total, anuncios, totalAnuncios, ultimoIdAnuncio, siguiente);
//                     agregarCancion(historial, id);
//                     siguiente++;
//                 } else {
//                     cout << "No hay canciones disponibles." << endl;
//                 }

//                 break;
//             }
//             else {
//                 cout << "Opcion invalida." << endl;
//                 continue;
//             }

//             int total = Totalcanciones(nombreArchivo);

//             if (total > 0) {
//                 int id = reproduccionAleatoria(esPremium, nombreArchivo, total, anuncios, totalAnuncios, ultimoIdAnuncio);
//                 agregarCancion(historial, id);
//             } else {
//                 cout << "No hay canciones disponibles." << endl;
//             }
//             break;
//         }

//         case 2: {
//             if (!esPremium) {
//                 cout << "Solo los usuarios Premium pueden retroceder canciones." << endl;
//                 break;
//             }

//             int pasos;
//             cout << "¿Cuántas canciones deseas retroceder? ";
//             cin >> pasos;

//             int idPrevio = retrocederCancion(historial, pasos);
//             if (idPrevio != -1) {
//                 cout << "Reproduciendo cancion previa..." << endl;
//                 GestorArchivos::buscarCancionCompleta(idPrevio, esPremium);
//             }
//             break;
//         }

//         case 3: {
//             int idRepetir = repetirCancion(historial);
//             if (idRepetir != -1) {
//                 cout << "Repitiendo canción actual..." << endl;
//                 GestorArchivos::buscarCancionCompleta(idRepetir, esPremium);
//             }
//             break;
//         }

//         case 4:
//             cout << "Finalizar programa";
//             liberarHistorial(historial);
//             break;

//         default:
//             break;
//         }

//     } while (opcion != 4);

//     return 0;
// }
