#ifndef APLICACION_H
#define APLICACION_H

#include <QObject>
#include "EstructuraDeDatos/MatrizDispersa.h"
#include "GUI/VentanaPrincipal.h"

class Aplicacion : public QObject {
    Q_OBJECT

public:
    explicit Aplicacion(QObject *parent = nullptr);
    ~Aplicacion();

    void iniciar();

private slots:
    void manejarSumarRango(int f1, int c1, int f2, int c2);
    void manejarObtenerRango(int f1, int c1, int f2, int c2);

private:
    MatrizDispersa* matriz;
    VentanaPrincipal* ventana;

    void poblarMatrizPrueba();
};

#endif // APLICACION_H