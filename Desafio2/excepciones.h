// Agregar estas excepciones personalizadas en un archivo de header
// Por ejemplo: excepciones.h

#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <exception>
#include <string>

// Excepción para lista vacía
class ListaVaciaException : public std::exception {
private:
    std::string mensaje;
public:
    ListaVaciaException(const std::string& msg = "La lista de reproduccion esta vacia")
        : mensaje(msg) {}

    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

// Excepción para índice fuera de rango
class IndiceInvalidoException : public std::exception {
private:
    std::string mensaje;
public:
    IndiceInvalidoException(int indice, int max) {
        mensaje = "Indice " + std::to_string(indice) +
                  " fuera de rango (0-" + std::to_string(max-1) + ")";
    }

    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

// Excepción para archivo no encontrado
class ArchivoNoEncontradoException : public std::exception {
private:
    std::string mensaje;
public:
    ArchivoNoEncontradoException(const std::string& archivo) {
        mensaje = "No se pudo abrir el archivo: " + archivo;
    }

    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

// Excepción para fin de lista alcanzado
class FinDeListaException : public std::exception {
private:
    std::string mensaje;
public:
    FinDeListaException(const std::string& msg = "Se ha alcanzado el fin de la lista de reproduccion")
        : mensaje(msg) {}

    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

#endif // EXCEPCIONES_H
