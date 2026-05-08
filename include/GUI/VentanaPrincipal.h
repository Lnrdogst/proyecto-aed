#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <vector>
#include "EstructuraDeDatos/MatrizDispersa.h"

class VentanaPrincipal : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

    void inicializarTabla(int filas, int columnas);
    void renderizarMatriz(const std::vector<CeldaInfo>& ocupadas);

    // resultados de agregación
    void mostrarResultadoSuma(double suma);
    void mostrarResultadoPromedio(double promedio);
    void mostrarResultadoMaximo(double maximo);
    void mostrarResultadoMinimo(double minimo);

    // resultados de visualización
    void mostrarResultadoRango(const std::vector<CeldaInfo>& rango);
    void mostrarListadoOcupadas(const std::vector<CeldaInfo>& ocupadas);
    void mostrarVistaFilaColumna(const std::vector<CeldaInfo>& datos, const QString& titulo);

signals:
    // operaciones de agregación por rango
    void eventoSumarRango(int f1, int c1, int f2, int c2);
    void eventoPromediarRango(int f1, int c1, int f2, int c2);
    void eventoMaximoRango(int f1, int c1, int f2, int c2);
    void eventoMinimoRango(int f1, int c1, int f2, int c2);
    void eventoObtenerRango(int f1, int c1, int f2, int c2);

    // gestión de estructura
    void eventoEliminarFila(int fila);
    void eventoEliminarColumna(int columna);
    void eventoEliminarRango(int f1, int c1, int f2, int c2);

    // visualización
    void eventoListarOcupadas();
    void eventoVerFila(int fila);
    void eventoVerColumna(int columna);

    // edición directa de celda
    void eventoCeldaModificada(int fila, int columna, QString valor);

private slots:
    // agregación
    void onBtnSumarClicked();
    void onBtnPromediarClicked();
    void onBtnMaximoClicked();
    void onBtnMinimoClicked();
    void onBtnObtenerClicked();

    // gestión de estructura
    void onBtnEliminarFilaClicked();
    void onBtnEliminarColumnaClicked();
    void onBtnEliminarRangoClicked();

    // visualización
    void onBtnListarOcupadasClicked();
    void onBtnVerFilaClicked();
    void onBtnVerColumnaClicked();

    // edición directa
    void onCeldaCambiada(int fila, int columna);

private:
    // tabla principal
    QTableWidget* tablaMatriz;

    // spinboxes de rango (compartidos por agregación y eliminar rango)
    QSpinBox* spinF1;
    QSpinBox* spinC1;
    QSpinBox* spinF2;
    QSpinBox* spinC2;

    // botones de agregación
    QPushButton* btnSumar;
    QPushButton* btnPromedio;
    QPushButton* btnMaximo;
    QPushButton* btnMinimo;
    QPushButton* btnObtener;

    // gestión de estructura
    QSpinBox* spinFilaEliminar;
    QSpinBox* spinColumnaEliminar;
    QPushButton* btnEliminarFila;
    QPushButton* btnEliminarColumna;
    QPushButton* btnEliminarRango;

    // visualización
    QSpinBox* spinFilaVer;
    QSpinBox* spinColumnaVer;
    QPushButton* btnListarOcupadas;
    QPushButton* btnVerFila;
    QPushButton* btnVerColumna;
    QTextEdit* txtListado;

    // labels de resultados
    QLabel* lblResultadoSuma;
    QLabel* lblResultadoPromedio;
    QLabel* lblResultadoMaximo;
    QLabel* lblResultadoMinimo;
    QLabel* lblResultadoRango;

    // flag para evitar signals falsos durante renderizado
    bool bloqueandoSignals;

    void configurarUI();
};

#endif // VENTANAPRINCIPAL_H