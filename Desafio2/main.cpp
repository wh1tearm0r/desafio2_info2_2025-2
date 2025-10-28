#include <iostream>
#include "usuario.h"
#include "basedatosusuarios.h"
#include "listaFavoritos.h"
#include "GestorArchivos.h"
#include "reproduccion.h"
#include "excepciones.h"
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
    int ultimoIdAnuncio = -1;

    Historial historial;
    int siguiente = 2;

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
                    try {
                        int K = 0;
                        while(K < 5) {
                            try {
                                int totalCanciones = Totalcanciones("..\\..\\data\\cancionesglobales.txt");
                                continuarReproduccion();
                                int id = reproduccionAleatoria(usuario->getEsPremium(),
                                                               "..\\..\\data\\cancionesglobales.txt",
                                                               totalCanciones, anuncios,
                                                               totalAnuncios, ultimoIdAnuncio);
                                agregarCancion(historial, id);
                                std::this_thread::sleep_for(std::chrono::seconds(3));
                                K++;
                            } catch (const ListaVaciaException& e) {
                                cout << "Error: " << e.what() << endl;
                                continuar1 = false;
                                break;
                            } catch (const ArchivoNoEncontradoException& e) {
                                cout << "Error: " << e.what() << endl;
                                continuar1 = false;
                                break;
                            } catch (const IndiceInvalidoException& e) {
                                cout << "Error: " << e.what() << endl;
                            }
                        }
                    } catch (const exception& e) {
                        cout << "Error inesperado: " << e.what() << endl;
                        continuar1 = false;
                    }
                    break;
                }

                case 2: {
                    if (!usuario->getEsPremium()) {
                        cout << "Solo los usuarios Premium pueden retroceder canciones." << endl;
                        break;
                    }

                    try {
                        int pasos;
                        cout << "¿Cuántas canciones deseas retroceder? ";
                        cin >> pasos;

                        int idPrevio = retrocederCancion(historial, pasos);
                        if (idPrevio != -1) {
                            cout << "Reproduciendo cancion previa..." << endl;
                            GestorArchivos::buscarCancionCompleta(idPrevio, usuario->getEsPremium());
                        }
                    } catch (const exception& e) {
                        cout << "Error al retroceder: " << e.what() << endl;
                    }
                    break;
                }

                case 3: {
                    try {
                        int idRepetir = repetirCancion(historial);
                        if (idRepetir != -1) {
                            cout << "Repitiendo canción actual..." << endl;
                            GestorArchivos::buscarCancionCompleta(idRepetir, usuario->getEsPremium());
                        }
                    } catch (const exception& e) {
                        cout << "Error al repetir: " << e.what() << endl;
                    }
                    break;
                }

                case 4:{
                    cout << "Reproduccion aleatoria finalizada." << endl;
                    liberarHistorial(historial);
                    continuar1 = false;
                    break;
                }

                default:
                    cout << "Opcion invalida." << endl;
                    break;
                }
            }
            break;
        }

        case 3:{
            cout << "TU lista de reproduccion: " << endl;
            usuario->getListaFavoritos().mostrarLista(usuario->getEsPremium());

            bool continuar2 = true;

            while(continuar2) {
                cout << "Que Quieres hacer?. " << endl;
                cout << "1. Reproducir de forma aleatoria." << endl;
                cout << "2. Reproducir en orden. " << endl;
                cout << "3. Salir." << endl;
                cout << "elige: ";
                int cual;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> cual;

                string nombreArchivo = "..\\..\\data\\lista_" + nickname + ".txt";

                if (cual == 1) {
                    try {
                        bool continuar3 = true;
                        while(continuar3) {
                            cout << "Opciones: " << endl;
                            cout << "1. Siguiente cancion " << endl;
                            cout << "2. Regresar cancion " << endl;
                            cout << "3. Repetir cancion " << endl;
                            cout << "4. Pausar cancion " << endl;
                            cout << "5. Salir " << endl;
                            cout << "Elige: ";

                            int opcion3;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin >> opcion3;

                            if (opcion3 == 1) {
                                try {
                                    int total = Totalcanciones(nombreArchivo);
                                    int id = reproduccionAleatoria(usuario->getEsPremium(),
                                                                   nombreArchivo, total,
                                                                   anuncios, totalAnuncios,
                                                                   ultimoIdAnuncio);
                                    agregarCancion(historial, id);
                                } catch (const ListaVaciaException& e) {
                                    cout << "Error: " << e.what() << endl;
                                    cout << "Agrega canciones a tu lista primero." << endl;
                                    continuar3 = false;
                                } catch (const ArchivoNoEncontradoException& e) {
                                    cout << "Error: " << e.what() << endl;
                                    cout << "No tienes una lista de reproduccion aun." << endl;
                                    continuar3 = false;
                                }
                            } else if (opcion3 == 5) {
                                continuar3 = false;
                            }
                        }
                    } catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                }
                else if (cual == 2) {
                    try {
                        int total = Totalcanciones(nombreArchivo);

                        if (siguiente > total) {
                            throw FinDeListaException();
                        }

                        int id = reproduccionLista(usuario->getEsPremium(),
                                                   nombreArchivo, total,
                                                   anuncios, totalAnuncios,
                                                   ultimoIdAnuncio, siguiente);
                        agregarCancion(historial, id);
                        siguiente++;

                    } catch (const FinDeListaException& e) {
                        cout << "Error: " << e.what() << endl;
                        cout << "Reiniciando la lista desde el principio..." << endl;
                        siguiente = 2;
                    } catch (const ListaVaciaException& e) {
                        cout << "Error: " << e.what() << endl;
                        cout << "Tu lista de favoritos esta vacia." << endl;
                    } catch (const ArchivoNoEncontradoException& e) {
                        cout << "Error: " << e.what() << endl;
                        cout << "No se encontro tu lista de reproduccion." << endl;
                    } catch (const IndiceInvalidoException& e) {
                        cout << "Error: " << e.what() << endl;
                        siguiente = 2;
                    } catch (const exception& e) {
                        cout << "Error inesperado: " << e.what() << endl;
                    }
                }
                else if (cual == 3) {
                    cout << "Saliendo del sistema de lista de favoritos" << endl;
                    continuar2 = false;
                }
                else {
                    cout << "Opcion invalida." << endl;
                }
            }
            break;
        }

        case 4:{
            try {
                cout << "Ingrese el ID de la cancion a agregar: ";
                string idCancion;
                cin >> idCancion;
                if (usuario->getListaFavoritos().agregarCancion(usuario->getEsPremium(),
                                                                idCancion, &bd)) {
                    cout << "Cancion agregada exitosamente!" << endl;
                }
            } catch (const exception& e) {
                cout << "Error al agregar cancion: " << e.what() << endl;
            }
            break;
        }

        case 5:{
            try {
                cout << "Ingrese el ID de la cancion a eliminar: ";
                string idCancion;
                cin >> idCancion;
                if (usuario->getListaFavoritos().eliminarCancion(usuario->getEsPremium(),
                                                                 idCancion, &bd)) {
                    cout << "Cancion eliminada exitosamente!" << endl;
                }
            } catch (const exception& e) {
                cout << "Error al eliminar cancion: " << e.what() << endl;
            }
            break;
        }

        case 6:{
            try {
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
            } catch (const exception& e) {
                cout << "Error al seguir usuario: " << e.what() << endl;
            }
            break;
        }

        case 7:{
            try {
                if (usuario->dejarDeSeguir(&bd, "..\\..\\data\\usuarios.txt")) {
                    cout << "Has dejado de seguir al usuario." << endl;
                }
            } catch (const exception& e) {
                cout << "Error al dejar de seguir: " << e.what() << endl;
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
