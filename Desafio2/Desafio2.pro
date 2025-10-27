TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        GestorArchivos.cpp \
        album.cpp \
        artista.cpp \
        basedatosusuarios.cpp \
        cancion.cpp \
        listaFavoritos.cpp \
        main.cpp \
        reproduccion.cpp \
        usuario.cpp

HEADERS += \
    GestorArchivos.h \
    album.h \
    artista.h \
    basedatosusuarios.h \
    cancion.h \
    listaFavoritos.h \
    reproduccion.h \
    usuario.h

DISTFILES += \
    data/albumes.txt \
    data/artistas.txt \
    data/biblioteca/albumes.txt \
    data/biblioteca/artistas.txt \
    data/biblioteca/canciones.txt \
    data/canciones.txt \
    data/usuarios.txt
