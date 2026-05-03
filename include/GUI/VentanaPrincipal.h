#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "EstructuraDeDatos/MatrizDispersa.h"

class VentanaPrincipal : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

    void inicializarTabla(int filas, int columnas);
    void renderizarMatriz(const std::vector<CeldaInfo>& ocupadas);
    void mostrarResultadoSuma(double suma);
    void mostrarResultadoRango(const std::vector<CeldaInfo>& rango);

signals:
    void eventoSumarRango(int f1, int c1, int f2, int c2);
    void eventoObtenerRango(int f1, int c1, int f2, int c2);

private slots:
    void onBtnSumarClicked();
    void onBtnObtenerClicked();

private:
    QTableWidget* tablaMatriz;
    QSpinBox* spinF1;
    QSpinBox* spinC1;
    QSpinBox* spinF2;
    QSpinBox* spinC2;
    QPushButton* btnSumar;
    QPushButton* btnObtener;
    QLabel* lblResultadoSuma;
    QLabel* lblResultadoRango;

    void configurarUI();
};

#endif // VENTANAPRINCIPAL_H