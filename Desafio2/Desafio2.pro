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
        listareproduccion.cpp \
        main.cpp \
        publicidad.cpp \
        reproductor.cpp \
        usuario.cpp

HEADERS += \
    GestorArchivos.h \
    album.h \
    artista.h \
    basedatosusuarios.h \
    cancion.h \
    listareproduccion.h \
    publicidad.h \
    reproductor.h \
    usuario.h

DISTFILES += \
    data/albumes.txt \
    data/artistas.txt \
    data/canciones.txt \
    data/usuarios.txt
