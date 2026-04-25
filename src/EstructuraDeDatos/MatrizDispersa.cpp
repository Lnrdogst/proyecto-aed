/*
Archivo: MatrizDispersa.cpp
Responsabilidad: implementar la matriz dispersa con enlaces cruzados.
Relación: usa Nodo.h y expone la lógica que consumen GUI y Core.
*/
#include "MatrizDispersa.h"
#include <iostream>

template <typename T>
MatrizDispersa<T>::MatrizDispersa(int filas, int columnas) :
    filas(filas), columnas(columnas), cabezasFila(filas, nullptr),
     cabezasColumna(columnas, nullptr) {}

template <typename T>
MatrizDispersa<T>::~MatrizDispersa() {
    // limpia filas y columnas eliminando cada nodo.
    for (int f = 0; f < filas; ++f) {
        Nodo<T>* actual = cabezasFila[f];
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguienteColumna;
            delete actual;
            actual = siguiente;
        }
    }
}

template <typename T>
void MatrizDispersa<T>::insertar(T valor, int fila, int columna){
    // Evita error de indices fuera de rango.
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range 
        throw std::out_of_range("Índices fuera de rango");
    }
    // insertar en la lista de la fila 
    Nodo<T>* anteriorFila = nullptr;
    Nodo<T>* actualFila = cabezasFila[fila];
    while (actualFila != nullptr && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }
    // verifica que exista la celda exacta para actualizar su valor
    if (actualFila != nullptr && actualFila->columna == columna) {
        actualFila->valor = valor;
        return;
    }

    Nodo<T>* nuevoNodo = new Nodo<T>(valor, fila, columna);
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
    Nodo<T>* anteriorColumna = nullptr;
    Nodo<T>* actualColumna = cabezasColumna[columna];
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

// template para verificar la existencia de un nodo en una posición específica,
// devuelve true si existe y false si no existe
template <typename T>
bool MatrizDispersa<T>::existe(int fila, int columna) const {
    //verifica que los indices esten dentro del rango
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }
//recorre la fila buscando la columna deseada
    Nodo<T>* actual = cabezasFila[fila];
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }
    //si encontro la columna, devuelve true
    if (actual != nullptr && actual->columna == columna) {
        return true;
    }
    //si no se encuentra el nodo false
    return false;
}


// template para obtener el valor de una celda específica, devuelve el valor en 
//cualquier tipo de dato 

template <typename T>
T MatrizDispersa<T>::obtener(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range 
        throw std::out_of_range("Índices fuera de rango");
    }
    //recorre la fila buscando la columna deseada
    Nodo<T>* actual = cabezasFila[fila];
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }
    // si encontro la columna, devuelve su valor
    if (actual != nullptr && actual->columna == columna) {
        return actual->valor;
    }
    //devuelve el valor por defecto del tipo T si no se encuentra el nodo (cero lógico)
    return T{};
}

template <typename T>
void MatrizDispersa<T>::eliminar(int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range
        throw std::out_of_range("Índices fuera de rango");
    }

    // quita de la lista de fila.
    Nodo<T>* anteriorFila = nullptr;
    Nodo<T>* actualFila = cabezasFila[fila];
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
    Nodo<T>* anteriorColumna = nullptr;
    Nodo<T>* actualColumna = cabezasColumna[columna];
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