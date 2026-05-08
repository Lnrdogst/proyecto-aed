#ifndef APLICACION_H
#define APLICACION_H

#include <QObject>
#include "EstructuraDeDatos/MatrizDispersa.h"
#include "GUI/VentanaPrincipal.h"

// definicion de la aplicacionn

class Aplicacion : public QObject {
    Q_OBJECT

public:
    explicit Aplicacion(QObject *parent = nullptr);
    ~Aplicacion();

    void iniciar();

private slots:
    // agregación
    void manejarSumarRango(int f1, int c1, int f2, int c2);
    void manejarPromediarRango(int f1, int c1, int f2, int c2);
    void manejarMaximoRango(int f1, int c1, int f2, int c2);
    void manejarMinimoRango(int f1, int c1, int f2, int c2);
    void manejarObtenerRango(int f1, int c1, int f2, int c2);

    // gestión de estructura
    void manejarEliminarFila(int fila);
    void manejarEliminarColumna(int columna);
    void manejarEliminarRango(int f1, int c1, int f2, int c2);

    // visualización
    void manejarListarOcupadas();
    void manejarVerFila(int fila);
    void manejarVerColumna(int columna);

    // edición directa
    void manejarCeldaModificada(int fila, int columna, QString valor);

private:
    MatrizDispersa* matriz;
    VentanaPrincipal* ventana;

    void poblarMatrizPrueba();
};

#endif // APLICACION_H