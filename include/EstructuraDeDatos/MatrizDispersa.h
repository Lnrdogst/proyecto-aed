/*
Archivo: MatrizDispersa.h
Responsabilidad: definir la interfaz de la matriz dispersa basada en listas enlazadas cruzadas.
Relación: depende de Nodo.h y alimenta a GUI/VentanaPrincipal.h y Core/Aplicacion.h.
*/
#include "Nodo.h"
#include <stdexcept>
#include <vector>
#include <string>
#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

// estructura para representar una celda ocupada con sus coordenadas y valor
struct CeldaInfo {
    int fila;
    int columna;
    std::string valor;
};

class MatrizDispersa {
private:
    int filas;
    int columnas;
    std::vector<Nodo*> cabezasFila;
    std::vector<Nodo*> cabezasColumna;
    
    // Funciones helper privadas para validar tipo de dato
    static bool esNumero(const std::string& s);
    static double comoNumero(const std::string& s);
    
public:
    MatrizDispersa(int filas, int columnas);
    ~MatrizDispersa();
    
    void insertar(const std::string& valor, int fila, int columna);
    bool existe(int fila, int columna) const;
    std::string obtener(int fila, int columna) const;
    void eliminar(int fila, int columna);
    
    
    // operaciones de visualización
    std::vector<CeldaInfo> listarOcupadas() const;
    std::vector<CeldaInfo> obtenerFila(int fila) const;
    std::vector<CeldaInfo> obtenerColumna(int columna) const;
    std::vector<CeldaInfo> obtenerRango(int f1, int c1, int f2, int c2) const;
    

    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
};

#endif