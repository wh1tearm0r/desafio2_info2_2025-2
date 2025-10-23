TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        basedatosusuarios.cpp \
        cancion.cpp \
        listareproduccion.cpp \
        main.cpp \
        publicidad.cpp \
        reproductor.cpp \
        usuario.cpp

HEADERS += \
    basedatosusuarios.h \
    cancion.h \
    listareproduccion.h \
    publicidad.h \
    reproductor.h \
    usuario.h

DISTFILES += \
    data/usuarios.txt
