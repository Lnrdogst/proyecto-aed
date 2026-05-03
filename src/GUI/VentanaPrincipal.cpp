#include "GUI/VentanaPrincipal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent) {
    configurarUI();
}

VentanaPrincipal::~VentanaPrincipal() {
}

void VentanaPrincipal::configurarUI() {
    this->setWindowTitle("Visor de Matriz Dispersa");
    this->resize(800, 600);

    QWidget* widgetCentral = new QWidget(this);
    this->setCentralWidget(widgetCentral);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(widgetCentral);

    // Tabla
    tablaMatriz = new QTableWidget(this);
    tablaMatriz->setEditTriggers(QAbstractItemView::NoEditTriggers); // Solo lectura
    layoutPrincipal->addWidget(tablaMatriz);

    // Controles inferiores
    QGroupBox* gbControles = new QGroupBox("Operaciones por Rango", this);
    QHBoxLayout* layoutControles = new QHBoxLayout(gbControles);

    // Entradas de rango
    spinF1 = new QSpinBox(this); spinF1->setPrefix("F1: ");
    spinC1 = new QSpinBox(this); spinC1->setPrefix("C1: ");
    spinF2 = new QSpinBox(this); spinF2->setPrefix("F2: ");
    spinC2 = new QSpinBox(this); spinC2->setPrefix("C2: ");

    layoutControles->addWidget(spinF1);
    layoutControles->addWidget(spinC1);
    layoutControles->addWidget(spinF2);
    layoutControles->addWidget(spinC2);

    // Botones
    btnObtener = new QPushButton("Obtener Rango", this);
    btnSumar = new QPushButton("Sumar Rango", this);
    layoutControles->addWidget(btnObtener);
    layoutControles->addWidget(btnSumar);

    layoutPrincipal->addWidget(gbControles);

    // Resultados
    QGroupBox* gbResultados = new QGroupBox("Resultados", this);
    QVBoxLayout* layoutResultados = new QVBoxLayout(gbResultados);
    lblResultadoSuma = new QLabel("Suma: -", this);
    lblResultadoRango = new QLabel("Valores en Rango: -", this);
    lblResultadoRango->setWordWrap(true);
    
    layoutResultados->addWidget(lblResultadoSuma);
    layoutResultados->addWidget(lblResultadoRango);
    layoutPrincipal->addWidget(gbResultados);

    // Conexiones
    connect(btnSumar, &QPushButton::clicked, this, &VentanaPrincipal::onBtnSumarClicked);
    connect(btnObtener, &QPushButton::clicked, this, &VentanaPrincipal::onBtnObtenerClicked);
}

void VentanaPrincipal::onBtnSumarClicked() {
    emit eventoSumarRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnObtenerClicked() {
    emit eventoObtenerRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::inicializarTabla(int filas, int columnas) {
    tablaMatriz->setRowCount(filas);
    tablaMatriz->setColumnCount(columnas);
    spinF1->setMaximum(filas > 0 ? filas - 1 : 0);
    spinF2->setMaximum(filas > 0 ? filas - 1 : 0);
    spinC1->setMaximum(columnas > 0 ? columnas - 1 : 0);
    spinC2->setMaximum(columnas > 0 ? columnas - 1 : 0);

    // Configurar cabeceras
    QStringList headersFila, headersCol;
    for (int i = 0; i < filas; ++i) headersFila << QString::number(i);
    for (int j = 0; j < columnas; ++j) headersCol << QString::number(j);
    tablaMatriz->setVerticalHeaderLabels(headersFila);
    tablaMatriz->setHorizontalHeaderLabels(headersCol);

    // Inicializar celdas vacias
    for (int r = 0; r < filas; ++r) {
        for (int c = 0; c < columnas; ++c) {
            QTableWidgetItem* item = new QTableWidgetItem("");
            tablaMatriz->setItem(r, c, item);
        }
    }
}

void VentanaPrincipal::renderizarMatriz(const std::vector<CeldaInfo>& ocupadas) {
    // Primero, limpiar estilos de toda la tabla
    for (int r = 0; r < tablaMatriz->rowCount(); ++r) {
        for (int c = 0; c < tablaMatriz->columnCount(); ++c) {
            QTableWidgetItem* item = tablaMatriz->item(r, c);
            if (item) {
                item->setText("");
                item->setBackground(QBrush(Qt::white));
            }
        }
    }

    // Pintar ocupadas
    for (const auto& celda : ocupadas) {
        QTableWidgetItem* item = tablaMatriz->item(celda.fila, celda.columna);
        if (item) {
            item->setText(QString::fromStdString(celda.valor));
            // Resaltado visual en verde claro para celdas ocupadas
            item->setBackground(QBrush(QColor(144, 238, 144))); 
        }
    }
}

void VentanaPrincipal::mostrarResultadoSuma(double suma) {
    lblResultadoSuma->setText("Suma: " + QString::number(suma));
}

void VentanaPrincipal::mostrarResultadoRango(const std::vector<CeldaInfo>& rango) {
    QString resultado = "Valores en Rango: ";
    if (rango.empty()) {
        resultado += "Ninguno";
    } else {
        for (const auto& c : rango) {
            resultado += QString("[%1,%2]=%3 ").arg(c.fila).arg(c.columna).arg(QString::fromStdString(c.valor));
        }
    }
    lblResultadoRango->setText(resultado);
}
