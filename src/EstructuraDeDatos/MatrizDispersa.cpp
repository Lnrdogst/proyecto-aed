/*
Archivo: MatrizDispersa.cpp
Responsabilidad: implementar la matriz dispersa con enlaces cruzados, usando std::string como tipo de dato.
Relación: usa Nodo.h y expone la lógica que consumen GUI y Core.
*/
#include "MatrizDispersa.h"
#include <iostream>
#include <stdexcept>
#include <string>

// valida que el string sea un número
bool MatrizDispersa::esNumero(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    try {
        std::stod(s);
        return true;
    } catch (...) {
        return false;
    }
}

// convierte string a número retorna 0.0 si no es número
double MatrizDispersa::comoNumero(const std::string& s) {
    if (esNumero(s)) {
        return std::stod(s);
    }
    return 0.0;
}

MatrizDispersa::MatrizDispersa(int filas, int columnas) :
    filas(filas), columnas(columnas), cabezasFila(filas, nullptr),
    cabezasColumna(columnas, nullptr) {}

MatrizDispersa::~MatrizDispersa() {
    // limpia filas y columnas eliminando cada nodo.
    for (int f = 0; f < filas; ++f) {
        Nodo* actual = cabezasFila[f];
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguienteColumna;
            delete actual;
            actual = siguiente;
        }
    }
}


void MatrizDispersa::insertar(const std::string& valor, int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range
        throw std::out_of_range("Índices fuera de rango");
    }
    
    // insertar en la lista de la fila 
    Nodo* anteriorFila = nullptr;
    Nodo* actualFila = cabezasFila[fila];
    while (actualFila != nullptr && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }
    
    // verifica que exista la celda exacta para actualizar su valor
    if (actualFila != nullptr && actualFila->columna == columna) {
        actualFila->valor = valor;
        return;
    }

    Nodo* nuevoNodo = new Nodo(valor, fila, columna);
    // insersion del nodo en la lista
    // asegura que exista anterior para enlazar
    //si no existe, el nuevo nodo se convierte en la cabeza de la fila 
    if (anteriorFila == nullptr) {
        //asigna null al siguiente del nuevo nodo 
        nuevoNodo->siguienteColumna = cabezasFila[fila];
        //actualiza la cabeza de la fila al nuevo nodo
        cabezasFila[fila] = nuevoNodo;
    }
    //si existe, se inserta entre anterior y actual
    else {
        nuevoNodo->siguienteColumna = anteriorFila->siguienteColumna;
        anteriorFila->siguienteColumna = nuevoNodo;
    }

    // Insertar en la lista de la columna (orden por fila).
    Nodo* anteriorColumna = nullptr;
    Nodo* actualColumna = cabezasColumna[columna];
    while (actualColumna != nullptr && actualColumna->fila < fila) {
        anteriorColumna = actualColumna;
        actualColumna = actualColumna->siguienteFila;
    }

    if (anteriorColumna == nullptr) {
        //asigna null al siguiente del nuevo nodo
        nuevoNodo->siguienteFila = cabezasColumna[columna];
        //actualiza la cabeza de la columna con el nuevo nodo
        cabezasColumna[columna] = nuevoNodo;
    }
    //asigna el siguiente del anterior al nuevo nodo y el nuevo nodo  
    else {
        nuevoNodo->siguienteFila = anteriorColumna->siguienteFila;
        //actualiza al siguiente del anterior con el nuevo nodo 
        anteriorColumna->siguienteFila = nuevoNodo;
    }
}


// verifica la existencia de un nodo en una posición específica,
// devuelve true si existe y false si no existe
bool MatrizDispersa::existe(int fila, int columna) const {
    //verifica que los indices esten dentro del rango
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    //recorre la fila buscando la columna deseada
    Nodo* actual = cabezasFila[fila];
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    if (actual != nullptr && actual->columna == columna) {
        return true;
    }

    return false;
}

// obtiene el valor de una celda específica, devuelve el valor en std::string
// o cadena vacía si no se encuentra
std::string MatrizDispersa::obtener(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range 
        throw std::out_of_range("Índices fuera de rango");
    }

    //recorre la fila buscando la columna deseada
    Nodo* actual = cabezasFila[fila];
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    // si encontro la columna, devuelve su valor
    if (actual != nullptr && actual->columna == columna) {
        return actual->valor;
    }

    //devuelve cadena vacía si no se encuentra el nodo
    return "";
}

void MatrizDispersa::eliminar(int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range
        throw std::out_of_range("Índices fuera de rango");
    }

    // quita de la lista de fila.
    Nodo* anteriorFila = nullptr;
    Nodo* actualFila = cabezasFila[fila];
    while (actualFila != nullptr && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }

    if (actualFila == nullptr || actualFila->columna != columna) {
        return;
    }

    if (anteriorFila == nullptr) {
        cabezasFila[fila] = actualFila->siguienteColumna;
    } else {
        anteriorFila->siguienteColumna = actualFila->siguienteColumna;
    }

    // quita de la lista de columna.
    Nodo* anteriorColumna = nullptr;
    Nodo* actualColumna = cabezasColumna[columna];
    while (actualColumna != nullptr && actualColumna != actualFila) {
        anteriorColumna = actualColumna;
        actualColumna = actualColumna->siguienteFila;
    }

    if (actualColumna != nullptr) {
        if (anteriorColumna == nullptr) {
            cabezasColumna[columna] = actualColumna->siguienteFila;
        } else {
            anteriorColumna->siguienteFila = actualColumna->siguienteFila;
        }
    }

    delete actualFila;
}