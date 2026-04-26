/*
Archivo: Nodo.h
Responsabilidad: describir el nodo base de la matriz dispersa con enlaces cruzados.
Relación: se usa desde MatrizDispersa.h y sus implementaciones en src/EstructuraDeDatos/.
*/
#include <string>

class Nodo {
public:
    std::string valor;
    int fila;
    int columna;
    Nodo* siguienteFila;
    Nodo* siguienteColumna;
    Nodo(std::string valor, int fila, int columna) : valor(valor),
    fila(fila), columna(columna), siguienteFila(nullptr),
    siguienteColumna(nullptr) {}
};