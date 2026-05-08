#include "Core/Aplicacion.h"
#include <iostream>

Aplicacion::Aplicacion(QObject *parent) : QObject(parent) {
    matriz = new MatrizDispersa(10, 10);
    ventana = new VentanaPrincipal();

    // conexiones de agregación
    connect(ventana, &VentanaPrincipal::eventoSumarRango, this, &Aplicacion::manejarSumarRango);
    connect(ventana, &VentanaPrincipal::eventoPromediarRango, this, &Aplicacion::manejarPromediarRango);
    connect(ventana, &VentanaPrincipal::eventoMaximoRango, this, &Aplicacion::manejarMaximoRango);
    connect(ventana, &VentanaPrincipal::eventoMinimoRango, this, &Aplicacion::manejarMinimoRango);
    connect(ventana, &VentanaPrincipal::eventoObtenerRango, this, &Aplicacion::manejarObtenerRango);

    // conexiones de gestión de estructura
    connect(ventana, &VentanaPrincipal::eventoEliminarFila, this, &Aplicacion::manejarEliminarFila);
    connect(ventana, &VentanaPrincipal::eventoEliminarColumna, this, &Aplicacion::manejarEliminarColumna);
    connect(ventana, &VentanaPrincipal::eventoEliminarRango, this, &Aplicacion::manejarEliminarRango);

    // conexiones de visualización
    connect(ventana, &VentanaPrincipal::eventoListarOcupadas, this, &Aplicacion::manejarListarOcupadas);
    connect(ventana, &VentanaPrincipal::eventoVerFila, this, &Aplicacion::manejarVerFila);
    connect(ventana, &VentanaPrincipal::eventoVerColumna, this, &Aplicacion::manejarVerColumna);

    // conexión de edición directa
    connect(ventana, &VentanaPrincipal::eventoCeldaModificada, this, &Aplicacion::manejarCeldaModificada);
}

Aplicacion::~Aplicacion() {
    delete matriz;
    delete ventana;
}

void Aplicacion::iniciar() {
    poblarMatrizPrueba();

    ventana->inicializarTabla(matriz->getFilas(), matriz->getColumnas());
    
    
    ventana->renderizarMatriz(matriz->listarOcupadas());
    

    ventana->show();
}

// ── Slots de agregación ──

void Aplicacion::manejarSumarRango(int f1, int c1, int f2, int c2) {
    try {
        double suma = matriz->sumarRango(f1, c1, f2, c2);
        ventana->mostrarResultadoSuma(suma);
    } catch (const std::exception& e) {
        ventana->mostrarResultadoSuma(0.0);
        std::cerr << "Error al sumar rango: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarPromediarRango(int f1, int c1, int f2, int c2) {
    try {
        double promedio = matriz->promediarRango(f1, c1, f2, c2);
        ventana->mostrarResultadoPromedio(promedio);
    } catch (const std::exception& e) {
        ventana->mostrarResultadoPromedio(0.0);
        std::cerr << "Error al promediar rango: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarMaximoRango(int f1, int c1, int f2, int c2) {
    try {
        double maximo = matriz->maximoRango(f1, c1, f2, c2);
        ventana->mostrarResultadoMaximo(maximo);
    } catch (const std::exception& e) {
        ventana->mostrarResultadoMaximo(0.0);
        std::cerr << "Error al obtener máximo: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarMinimoRango(int f1, int c1, int f2, int c2) {
    try {
        double minimo = matriz->minimoRango(f1, c1, f2, c2);
        ventana->mostrarResultadoMinimo(minimo);
    } catch (const std::exception& e) {
        ventana->mostrarResultadoMinimo(0.0);
        std::cerr << "Error al obtener mínimo: " << e.what() << std::endl;
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

// ── Slots de gestión de estructura ──

void Aplicacion::manejarEliminarFila(int fila) {
    try {
        matriz->eliminarFila(fila);
        ventana->renderizarMatriz(matriz->listarOcupadas());
    } catch (const std::exception& e) {
        std::cerr << "Error al eliminar fila: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarEliminarColumna(int columna) {
    try {
        matriz->eliminarColumna(columna);
        ventana->renderizarMatriz(matriz->listarOcupadas());
    } catch (const std::exception& e) {
        std::cerr << "Error al eliminar columna: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarEliminarRango(int f1, int c1, int f2, int c2) {
    try {
        matriz->eliminarRango(f1, c1, f2, c2);
        ventana->renderizarMatriz(matriz->listarOcupadas());
    } catch (const std::exception& e) {
        std::cerr << "Error al eliminar rango: " << e.what() << std::endl;
    }
}

// ── Slots de visualización ──

void Aplicacion::manejarListarOcupadas() {
    try {
        std::vector<CeldaInfo> ocupadas = matriz->listarOcupadas();
        ventana->mostrarListadoOcupadas(ocupadas);
    } catch (const std::exception& e) {
        ventana->mostrarListadoOcupadas(std::vector<CeldaInfo>());
        std::cerr << "Error al listar ocupadas: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarVerFila(int fila) {
    try {
        std::vector<CeldaInfo> datos = matriz->obtenerFila(fila);
        ventana->mostrarVistaFilaColumna(datos, QString("Fila %1").arg(fila));
    } catch (const std::exception& e) {
        ventana->mostrarVistaFilaColumna(std::vector<CeldaInfo>(), QString("Fila %1").arg(fila));
        std::cerr << "Error al ver fila: " << e.what() << std::endl;
    }
}

void Aplicacion::manejarVerColumna(int columna) {
    try {
        std::vector<CeldaInfo> datos = matriz->obtenerColumna(columna);
        ventana->mostrarVistaFilaColumna(datos, QString("Columna %1").arg(columna));
    } catch (const std::exception& e) {
        ventana->mostrarVistaFilaColumna(std::vector<CeldaInfo>(), QString("Columna %1").arg(columna));
        std::cerr << "Error al ver columna: " << e.what() << std::endl;
    }
}

// ── Slot de edición directa ──

void Aplicacion::manejarCeldaModificada(int fila, int columna, QString valor) {
    try {
        if (valor.trimmed().isEmpty()) {
            // si el usuario borró el contenido, eliminar la celda de la matriz
            matriz->eliminar(fila, columna);
        } else {
            // insertar o actualizar el valor
            matriz->insertar(valor.toStdString(), fila, columna);
        }
        // re-renderizar para actualizar resaltado dinámico
        ventana->renderizarMatriz(matriz->listarOcupadas());
    } catch (const std::exception& e) {
        std::cerr << "Error al modificar celda: " << e.what() << std::endl;
        ventana->renderizarMatriz(matriz->listarOcupadas());
    }
}

void Aplicacion::poblarMatrizPrueba() {
    matriz->insertar("5.5", 1, 1);
    matriz->insertar("10", 2, 3);
    matriz->insertar("texto", 4, 4); 
    matriz->insertar("2.5", 5, 5);
    matriz->insertar("7", 8, 9);
    matriz->insertar("15", 2, 8);
    matriz->insertar("20.1", 9, 1);
}