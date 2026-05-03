TEMPLATE = app
CONFIG += c++17
QT += core gui widgets

TARGET = HojaCalculoAED
DESTDIR = bin

INCLUDEPATH += include

SOURCES += \
    src/Core/main.cpp \
    src/Core/Aplicacion.cpp \
    src/GUI/VentanaPrincipal.cpp \
    src/EstructuraDeDatos/MatrizDispersa.cpp \
    src/EstructuraDeDatos/Nodo.cpp

HEADERS += \
    include/Core/Aplicacion.h \
    include/GUI/VentanaPrincipal.h \
    include/EstructuraDeDatos/MatrizDispersa.h \
    include/EstructuraDeDatos/Nodo.h
