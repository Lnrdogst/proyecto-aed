#include "Core/Aplicacion.h"
#include <iostream>

Aplicacion::Aplicacion(QObject *parent) : QObject(parent) {
    // Inicializar matriz de 10x10 para el ejemplo visual
    matriz = new MatrizDispersa(10, 10);
    ventana = new VentanaPrincipal();

    // Conectar las señales de la UI con los slots del controlador
    connect(ventana, &VentanaPrincipal::eventoSumarRango, this, &Aplicacion::manejarSumarRango);
    connect(ventana, &VentanaPrincipal::eventoObtenerRango, this, &Aplicacion::manejarObtenerRango);
}

Aplicacion::~Aplicacion() {
    delete matriz;
    delete ventana;
}

void Aplicacion::iniciar() {
    poblarMatrizPrueba();
    
    // Configurar la tabla de la ventana con las dimensiones de la matriz
    ventana->inicializarTabla(matriz->getFilas(), matriz->getColumnas());
    
    // Pintar los datos actuales
    ventana->renderizarMatriz(matriz->listarOcupadas());
    
    // Mostrar la UI
    ventana->show();
}

void Aplicacion::manejarSumarRango(int f1, int c1, int f2, int c2) {
    try {
        double suma = matriz->sumarRango(f1, c1, f2, c2);
        ventana->mostrarResultadoSuma(suma);
    } catch (const std::exception& e) {
        ventana->mostrarResultadoSuma(0.0);
        std::cerr << "Error al sumar rango: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarObtenerRango(int f1, int c1, int f2, int c2) {
    try {
        std::vector<CeldaInfo> rango = matriz->obtenerRango(f1, c1, f2, c2);
        ventana->mostrarResultadoRango(rango);
    } catch (const std::exception& e) {
        ventana->mostrarResultadoRango(std::vector<CeldaInfo>());
        std::cerr << "Error al obtener rango: " << e.what() << std::endl;
    }
}

void Aplicacion::poblarMatrizPrueba() {
    matriz->insertar("5.5", 1, 1);
    matriz->insertar("10", 2, 3);
    matriz->insertar("texto", 4, 4); // Ignorado en suma
    matriz->insertar("2.5", 5, 5);
    matriz->insertar("7", 8, 9);
    matriz->insertar("15", 2, 8);
    matriz->insertar("20.1", 9, 1);
}