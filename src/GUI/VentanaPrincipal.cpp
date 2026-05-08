#include "GUI/VentanaPrincipal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent), bloqueandoSignals(false) {
    configurarUI();
}

VentanaPrincipal::~VentanaPrincipal() {
}

void VentanaPrincipal::configurarUI() {
    this->setWindowTitle("Hoja de Cálculo — Matriz Dispersa");
    this->resize(900, 750);

    QWidget* widgetCentral = new QWidget(this);
    this->setCentralWidget(widgetCentral);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(widgetCentral);

    // ── Tabla principal (editable con doble clic) ──
    tablaMatriz = new QTableWidget(this);
    tablaMatriz->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    layoutPrincipal->addWidget(tablaMatriz);

    // ── Grupo: Operaciones por Rango ──
    QGroupBox* gbRango = new QGroupBox("Operaciones por Rango", this);
    QVBoxLayout* layoutRango = new QVBoxLayout(gbRango);

    // fila de spinboxes
    QHBoxLayout* layoutSpins = new QHBoxLayout();
    spinF1 = new QSpinBox(this); spinF1->setPrefix("F1: ");
    spinC1 = new QSpinBox(this); spinC1->setPrefix("C1: ");
    spinF2 = new QSpinBox(this); spinF2->setPrefix("F2: ");
    spinC2 = new QSpinBox(this); spinC2->setPrefix("C2: ");
    layoutSpins->addWidget(spinF1);
    layoutSpins->addWidget(spinC1);
    layoutSpins->addWidget(spinF2);
    layoutSpins->addWidget(spinC2);
    layoutRango->addLayout(layoutSpins);

    // fila de botones de agregación
    QHBoxLayout* layoutBtnsAgregacion = new QHBoxLayout();
    btnObtener = new QPushButton("Obtener Rango", this);
    btnSumar = new QPushButton("Sumar", this);
    btnPromedio = new QPushButton("Promedio", this);
    btnMaximo = new QPushButton("Máximo", this);
    btnMinimo = new QPushButton("Mínimo", this);
    btnEliminarRango = new QPushButton("Eliminar Rango", this);
    layoutBtnsAgregacion->addWidget(btnObtener);
    layoutBtnsAgregacion->addWidget(btnSumar);
    layoutBtnsAgregacion->addWidget(btnPromedio);
    layoutBtnsAgregacion->addWidget(btnMaximo);
    layoutBtnsAgregacion->addWidget(btnMinimo);
    layoutBtnsAgregacion->addWidget(btnEliminarRango);
    layoutRango->addLayout(layoutBtnsAgregacion);

    layoutPrincipal->addWidget(gbRango);

    // ── Grupo: Gestión de Estructura ──
    QGroupBox* gbEstructura = new QGroupBox("Gestión de Estructura", this);
    QHBoxLayout* layoutEstructura = new QHBoxLayout(gbEstructura);

    spinFilaEliminar = new QSpinBox(this); spinFilaEliminar->setPrefix("Fila: ");
    btnEliminarFila = new QPushButton("Eliminar Fila", this);
    layoutEstructura->addWidget(spinFilaEliminar);
    layoutEstructura->addWidget(btnEliminarFila);

    spinColumnaEliminar = new QSpinBox(this); spinColumnaEliminar->setPrefix("Col: ");
    btnEliminarColumna = new QPushButton("Eliminar Columna", this);
    layoutEstructura->addWidget(spinColumnaEliminar);
    layoutEstructura->addWidget(btnEliminarColumna);

    layoutPrincipal->addWidget(gbEstructura);

    // ── Grupo: Visualización ──
    QGroupBox* gbVisualizacion = new QGroupBox("Visualización", this);
    QVBoxLayout* layoutVisualizacion = new QVBoxLayout(gbVisualizacion);

    QHBoxLayout* layoutBtnsVis = new QHBoxLayout();
    btnListarOcupadas = new QPushButton("Listar Celdas Ocupadas", this);
    layoutBtnsVis->addWidget(btnListarOcupadas);

    spinFilaVer = new QSpinBox(this); spinFilaVer->setPrefix("Fila: ");
    btnVerFila = new QPushButton("Ver Fila", this);
    layoutBtnsVis->addWidget(spinFilaVer);
    layoutBtnsVis->addWidget(btnVerFila);

    spinColumnaVer = new QSpinBox(this); spinColumnaVer->setPrefix("Col: ");
    btnVerColumna = new QPushButton("Ver Columna", this);
    layoutBtnsVis->addWidget(spinColumnaVer);
    layoutBtnsVis->addWidget(btnVerColumna);
    layoutVisualizacion->addLayout(layoutBtnsVis);

    txtListado = new QTextEdit(this);
    txtListado->setReadOnly(true);
    txtListado->setMaximumHeight(120);
    txtListado->setPlaceholderText("Aquí se mostrarán los resultados de visualización...");
    layoutVisualizacion->addWidget(txtListado);

    layoutPrincipal->addWidget(gbVisualizacion);

    // ── Grupo: Resultados ──
    QGroupBox* gbResultados = new QGroupBox("Resultados", this);
    QVBoxLayout* layoutResultados = new QVBoxLayout(gbResultados);

    lblResultadoSuma = new QLabel("Suma: -", this);
    lblResultadoPromedio = new QLabel("Promedio: -", this);
    lblResultadoMaximo = new QLabel("Máximo: -", this);
    lblResultadoMinimo = new QLabel("Mínimo: -", this);
    lblResultadoRango = new QLabel("Valores en Rango: -", this);
    lblResultadoRango->setWordWrap(true);

    layoutResultados->addWidget(lblResultadoSuma);
    layoutResultados->addWidget(lblResultadoPromedio);
    layoutResultados->addWidget(lblResultadoMaximo);
    layoutResultados->addWidget(lblResultadoMinimo);
    layoutResultados->addWidget(lblResultadoRango);
    layoutPrincipal->addWidget(gbResultados);

    // ── Conexiones de botones ──
    // Agregación
    connect(btnSumar, &QPushButton::clicked, this, &VentanaPrincipal::onBtnSumarClicked);
    connect(btnPromedio, &QPushButton::clicked, this, &VentanaPrincipal::onBtnPromediarClicked);
    connect(btnMaximo, &QPushButton::clicked, this, &VentanaPrincipal::onBtnMaximoClicked);
    connect(btnMinimo, &QPushButton::clicked, this, &VentanaPrincipal::onBtnMinimoClicked);
    connect(btnObtener, &QPushButton::clicked, this, &VentanaPrincipal::onBtnObtenerClicked);

    // Gestión de estructura
    connect(btnEliminarFila, &QPushButton::clicked, this, &VentanaPrincipal::onBtnEliminarFilaClicked);
    connect(btnEliminarColumna, &QPushButton::clicked, this, &VentanaPrincipal::onBtnEliminarColumnaClicked);
    connect(btnEliminarRango, &QPushButton::clicked, this, &VentanaPrincipal::onBtnEliminarRangoClicked);

    // Visualización
    connect(btnListarOcupadas, &QPushButton::clicked, this, &VentanaPrincipal::onBtnListarOcupadasClicked);
    connect(btnVerFila, &QPushButton::clicked, this, &VentanaPrincipal::onBtnVerFilaClicked);
    connect(btnVerColumna, &QPushButton::clicked, this, &VentanaPrincipal::onBtnVerColumnaClicked);

    // Edición directa de celdas
    connect(tablaMatriz, &QTableWidget::cellChanged, this, &VentanaPrincipal::onCeldaCambiada);
}

// ── Slots de botones ──

void VentanaPrincipal::onBtnSumarClicked() {
    emit eventoSumarRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnPromediarClicked() {
    emit eventoPromediarRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnMaximoClicked() {
    emit eventoMaximoRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnMinimoClicked() {
    emit eventoMinimoRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnObtenerClicked() {
    emit eventoObtenerRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnEliminarFilaClicked() {
    emit eventoEliminarFila(spinFilaEliminar->value());
}

void VentanaPrincipal::onBtnEliminarColumnaClicked() {
    emit eventoEliminarColumna(spinColumnaEliminar->value());
}

void VentanaPrincipal::onBtnEliminarRangoClicked() {
    emit eventoEliminarRango(spinF1->value(), spinC1->value(), spinF2->value(), spinC2->value());
}

void VentanaPrincipal::onBtnListarOcupadasClicked() {
    emit eventoListarOcupadas();
}

void VentanaPrincipal::onBtnVerFilaClicked() {
    emit eventoVerFila(spinFilaVer->value());
}

void VentanaPrincipal::onBtnVerColumnaClicked() {
    emit eventoVerColumna(spinColumnaVer->value());
}

void VentanaPrincipal::onCeldaCambiada(int fila, int columna) {
    if (bloqueandoSignals) return;

    QTableWidgetItem* item = tablaMatriz->item(fila, columna);
    if (item) {
        emit eventoCeldaModificada(fila, columna, item->text());
    }
}

// ── Inicialización y renderizado de tabla ──

void VentanaPrincipal::inicializarTabla(int filas, int columnas) {
    bloqueandoSignals = true;

    tablaMatriz->setRowCount(filas);
    tablaMatriz->setColumnCount(columnas);

    // límites de los spinboxes de rango
    spinF1->setMaximum(filas > 0 ? filas - 1 : 0);
    spinF2->setMaximum(filas > 0 ? filas - 1 : 0);
    spinC1->setMaximum(columnas > 0 ? columnas - 1 : 0);
    spinC2->setMaximum(columnas > 0 ? columnas - 1 : 0);

    // límites de spinboxes de estructura y visualización
    spinFilaEliminar->setMaximum(filas > 0 ? filas - 1 : 0);
    spinColumnaEliminar->setMaximum(columnas > 0 ? columnas - 1 : 0);
    spinFilaVer->setMaximum(filas > 0 ? filas - 1 : 0);
    spinColumnaVer->setMaximum(columnas > 0 ? columnas - 1 : 0);

    // encabezados
    QStringList headersFila, headersCol;
    for (int i = 0; i < filas; ++i) headersFila << QString::number(i);
    for (int j = 0; j < columnas; ++j) headersCol << QString::number(j);
    tablaMatriz->setVerticalHeaderLabels(headersFila);
    tablaMatriz->setHorizontalHeaderLabels(headersCol);

    for (int r = 0; r < filas; ++r) {
        for (int c = 0; c < columnas; ++c) {
            QTableWidgetItem* item = new QTableWidgetItem("");
            tablaMatriz->setItem(r, c, item);
        }
    }

    bloqueandoSignals = false;
}

void VentanaPrincipal::renderizarMatriz(const std::vector<CeldaInfo>& ocupadas) {
    bloqueandoSignals = true;

    // reset: todas las celdas en blanco con fondo blanco
    for (int r = 0; r < tablaMatriz->rowCount(); ++r) {
        for (int c = 0; c < tablaMatriz->columnCount(); ++c) {
            QTableWidgetItem* item = tablaMatriz->item(r, c);
            if (item) {
                item->setText("");
                item->setBackground(QBrush(Qt::white));
            }
        }
    }

    // resaltar solo las celdas ocupadas
    for (const auto& celda : ocupadas) {
        QTableWidgetItem* item = tablaMatriz->item(celda.fila, celda.columna);
        if (item) {
            item->setText(QString::fromStdString(celda.valor));
            item->setBackground(QBrush(QColor(144, 238, 144))); 
        }
    }

    bloqueandoSignals = false;
}

// ── Métodos para mostrar resultados de agregación ──

void VentanaPrincipal::mostrarResultadoSuma(double suma) {
    lblResultadoSuma->setText("Suma: " + QString::number(suma));
}

void VentanaPrincipal::mostrarResultadoPromedio(double promedio) {
    if (promedio == 0.0) {
        lblResultadoPromedio->setText("Promedio: 0 — No hay valores numéricos en el rango");
    } else {
        lblResultadoPromedio->setText("Promedio: " + QString::number(promedio));
    }
}

void VentanaPrincipal::mostrarResultadoMaximo(double maximo) {
    if (maximo == 0.0) {
        lblResultadoMaximo->setText("Máximo: 0 — No hay valores numéricos en el rango");
    } else {
        lblResultadoMaximo->setText("Máximo: " + QString::number(maximo));
    }
}

void VentanaPrincipal::mostrarResultadoMinimo(double minimo) {
    if (minimo == 0.0) {
        lblResultadoMinimo->setText("Mínimo: 0 — No hay valores numéricos en el rango");
    } else {
        lblResultadoMinimo->setText("Mínimo: " + QString::number(minimo));
    }
}

// ── Métodos para mostrar resultados de visualización ──

void VentanaPrincipal::mostrarResultadoRango(const std::vector<CeldaInfo>& rango) {
    QString resultado = "Valores en Rango: ";
    if (rango.empty()) {
        resultado += "Ninguno (rango vacío)";
    } else {
        for (const auto& c : rango) {
            resultado += QString("[%1,%2]=%3 ").arg(c.fila).arg(c.columna).arg(QString::fromStdString(c.valor));
        }
    }
    lblResultadoRango->setText(resultado);
}

void VentanaPrincipal::mostrarListadoOcupadas(const std::vector<CeldaInfo>& ocupadas) {
    txtListado->clear();
    if (ocupadas.empty()) {
        txtListado->setText("No hay celdas ocupadas en la matriz.");
        return;
    }

    QString texto = "=== Listado de Celdas Ocupadas ===\n";
    texto += QString("Total: %1 celda(s)\n\n").arg(ocupadas.size());
    for (const auto& c : ocupadas) {
        texto += QString("  [Fila %1, Col %2] = %3\n")
            .arg(c.fila).arg(c.columna).arg(QString::fromStdString(c.valor));
    }
    txtListado->setText(texto);
}

void VentanaPrincipal::mostrarVistaFilaColumna(const std::vector<CeldaInfo>& datos, const QString& titulo) {
    txtListado->clear();
    if (datos.empty()) {
        txtListado->setText("=== " + titulo + " ===\nNo hay celdas ocupadas.");
        return;
    }

    QString texto = "=== " + titulo + " ===\n";
    texto += QString("Celdas ocupadas: %1\n\n").arg(datos.size());
    for (const auto& c : datos) {
        texto += QString("  [Fila %1, Col %2] = %3\n")
            .arg(c.fila).arg(c.columna).arg(QString::fromStdString(c.valor));
    }
    txtListado->setText(texto);
}
