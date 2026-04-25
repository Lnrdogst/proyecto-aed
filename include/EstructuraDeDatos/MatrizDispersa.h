/*
Archivo: MatrizDispersa.h
Responsabilidad: definir la interfaz de la matriz dispersa basada en listas enlazadas cruzadas.
Relación: depende de Nodo.h y alimenta a GUI/VentanaPrincipal.h y Core/Aplicacion.h.
*/
#include "Nodo.h"
#include <stdexcept>
#include <vector>
#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H
template <typename T>
class MatrizDispersa {
private:
    int filas;
    int columnas;
    std::vector<Nodo<T>*> cabezasFila;
    std::vector<Nodo<T>*> cabezasColumna;
public:
    MatrizDispersa(int filas, int columnas);
    ~MatrizDispersa();
    //metodos a implementar en el cpp
    void insertar(T valor, int fila, int columna);
    bool existe(int fila, int columna) const;
    T obtener(int fila, int columna) const;
    void eliminar(int fila, int columna);
    //getters
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
};

#endif 