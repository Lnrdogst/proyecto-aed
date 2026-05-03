#include <QApplication>
#include "Core/Aplicacion.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Aplicacion aplicacion;
    aplicacion.iniciar();

    return app.exec();
}