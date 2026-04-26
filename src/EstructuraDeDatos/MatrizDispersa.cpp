
#include "EstructuraDeDatos/MatrizDispersa.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
// valida que el string sea un número
bool MatrizDispersa::esNumero(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    try {
        std::stod(s);
        return true;
    } catch (...) {
        return false;
    }
}

// convierte string a número retorna 0.0 si no es número
double MatrizDispersa::comoNumero(const std::string& s) {
    if (esNumero(s)) {
        return std::stod(s);
    }
    return 0.0;
}

MatrizDispersa::MatrizDispersa(int filas, int columnas) :
    filas(filas), columnas(columnas), cabezasFila(filas, nullptr),
    cabezasColumna(columnas, nullptr) {
    // inicializa para fila lista circular
    for (int f = 0; f < filas; ++f) {
        cabezasFila[f] = new Nodo("", -1, -1);
        cabezasFila[f]->siguienteColumna = cabezasFila[f];
    }

    // inicializa nodos para columna lista circular
    for (int c = 0; c < columnas; ++c) {
        cabezasColumna[c] = new Nodo("", -1, -1);
        cabezasColumna[c]->siguienteFila = cabezasColumna[c];
    }
}

MatrizDispersa::~MatrizDispersa() {
    // limpia todos los nodos de datos por filas.
    for (int f = 0; f < filas; ++f) {
        Nodo* cabeza = cabezasFila[f];
        Nodo* actual = cabeza->siguienteColumna;
        while (actual != cabeza) {
            Nodo* siguiente = actual->siguienteColumna;
            delete actual;
            actual = siguiente;
        }
        delete cabeza;
    }

    // elimina cabeceras de columnas.
    for (int c = 0; c < columnas; ++c) {
        delete cabezasColumna[c];
    }
}


void MatrizDispersa::insertar(const std::string& valor, int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range
        throw std::out_of_range("Índices fuera de rango");
    }
    
    Nodo* cabezaFila = cabezasFila[fila];

    // insertar en la lista circular de la fila
    Nodo* anteriorFila = cabezaFila;
    Nodo* actualFila = cabezaFila->siguienteColumna;
    while (actualFila != cabezaFila && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }
    
    // verifica que exista la celda exacta para actualizar su valor
    if (actualFila != cabezaFila && actualFila->columna == columna) {
        actualFila->valor = valor;
        return;
    }

    Nodo* nuevoNodo = new Nodo(valor, fila, columna);

    // insercion entre anterior y actual en fila
    nuevoNodo->siguienteColumna = actualFila;
    anteriorFila->siguienteColumna = nuevoNodo;

    Nodo* cabezaColumna = cabezasColumna[columna];

    // insertar en la lista circular de la columna (orden por fila)
    Nodo* anteriorColumna = cabezaColumna;
    Nodo* actualColumna = cabezaColumna->siguienteFila;
    while (actualColumna != cabezaColumna && actualColumna->fila < fila) {
        anteriorColumna = actualColumna;
        actualColumna = actualColumna->siguienteFila;
    }

    nuevoNodo->siguienteFila = actualColumna;
    anteriorColumna->siguienteFila = nuevoNodo;
}


// verifica la existencia de un nodo en una posición específica,
// devuelve true si existe y false si no existe
bool MatrizDispersa::existe(int fila, int columna) const {
    //verifica que los indices esten dentro del rango
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    //recorre la fila buscando la columna deseada
    Nodo* cabezaFila = cabezasFila[fila];
    Nodo* actual = cabezaFila->siguienteColumna;
    while (actual != cabezaFila && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    if (actual != cabezaFila && actual->columna == columna) {
        return true;
    }

    return false;
}

// obtiene el valor de una celda específica
// o cadena vacía si no se encuentra
std::string MatrizDispersa::obtener(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range 
        throw std::out_of_range("Índices fuera de rango");
    }

    //recorre la fila buscando la columna deseada
    Nodo* cabezaFila = cabezasFila[fila];
    Nodo* actual = cabezaFila->siguienteColumna;
    while (actual != cabezaFila && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    // si encontro la columna, devuelve su valor
    if (actual != cabezaFila && actual->columna == columna) {
        return actual->valor;
    }
    //devuelve cadena vacía si no se encuentra el nodo
    return "";
}

void MatrizDispersa::eliminar(int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range
        throw std::out_of_range("Índices fuera de rango");
    }

    Nodo* cabezaFila = cabezasFila[fila];

    // quita de la lista circular de fila.
    Nodo* anteriorFila = cabezaFila;
    Nodo* actualFila = cabezaFila->siguienteColumna;
    while (actualFila != cabezaFila && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }

    if (actualFila == cabezaFila || actualFila->columna != columna) {
        return;
    }

    anteriorFila->siguienteColumna = actualFila->siguienteColumna;

    Nodo* cabezaColumna = cabezasColumna[columna];

    // quita de la lista circular de columna.
    Nodo* anteriorColumna = cabezaColumna;
    Nodo* actualColumna = cabezaColumna->siguienteFila;
    while (actualColumna != cabezaColumna && actualColumna != actualFila) {
        anteriorColumna = actualColumna;
        actualColumna = actualColumna->siguienteFila;
    }

    if (actualColumna != cabezaColumna) {
        anteriorColumna->siguienteFila = actualColumna->siguienteFila;
    }

    delete actualFila;
}

// elimina todos los nodos de una fila y actualiza las columnas afectadas
void MatrizDispersa::eliminarFila(int fila) {
    //manejo de errores con out_of_range
    if (fila < 0 || fila >= filas) {
        throw std::out_of_range("Índices fuera de rango");
    }
    Nodo* cabezaFila = cabezasFila[fila];

    // nodo que se va quitar
    Nodo* actual = cabezaFila->siguienteColumna;
    //recorre la lista de fila
    while (actual != cabezaFila) {
        //guarda el siguiente nodo antes de eliminar el actual
        Nodo* siguiente = actual->siguienteColumna;
        // columna del nodo actual para actualizar la lista de esa columna
        int columna = actual->columna;

        Nodo* cabezaColumna = cabezasColumna[columna];

        // quitar de la lista de la columna correspondiente
        Nodo* anteriorColumna = cabezaColumna;
        Nodo* actualColumna = cabezaColumna->siguienteFila;
        // recorre la columna buscando el nodo a eliminar
        while (actualColumna != cabezaColumna && actualColumna != actual) {
            // guarda el nodo anterior para actualizar su enlace después de eliminar el nodo actual
            anteriorColumna = actualColumna;
            actualColumna = actualColumna->siguienteFila;
        }

        if (actualColumna != cabezaColumna) {
            anteriorColumna->siguienteFila = actualColumna->siguienteFila;
        }
        //se elimina el nodo actual
        delete actual;
        actual = siguiente;
    }

    cabezaFila->siguienteColumna = cabezaFila;
}

// elimina todos los nodos de una columna y actualiza las filas 
//logica similar a elminiarfila pero recorre columna y actualiza filas 
void MatrizDispersa::eliminarColumna(int columna) {

    if (columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    Nodo* cabezaColumna = cabezasColumna[columna];

    Nodo* actual = cabezaColumna->siguienteFila;
    while (actual != cabezaColumna) {
        Nodo* siguiente = actual->siguienteFila;
        int fila = actual->fila;

        Nodo* cabezaFila = cabezasFila[fila];

        // quitar de la lista de la fila correspondiente
        Nodo* anteriorFila = cabezaFila;
        Nodo* actualFila = cabezaFila->siguienteColumna;
        while (actualFila != cabezaFila && actualFila != actual) {
            anteriorFila = actualFila;
            actualFila = actualFila->siguienteColumna;
        }

        if (actualFila != cabezaFila) {
            anteriorFila->siguienteColumna = actualFila->siguienteColumna;
        }

        delete actual;
        actual = siguiente;
    }

    cabezaColumna->siguienteFila = cabezaColumna;
}

// elimina todas las celdas dentro de un rango rectangular [f1,c1] a [f2,c2]
void MatrizDispersa::eliminarRango(int f1, int c1, int f2, int c2) {
    //verificar rango de los indicese 
    if (f1 < 0 || f1 >= filas || f2 < 0 || f2 >= filas ||
        c1 < 0 || c1 >= columnas || c2 < 0 || c2 >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    // establece f1 <= f2 y c1 <= c2

    int fMin;
    int fMax;
    int cMin;
    int cMax;

    if (f1 < f2) {
        fMin = f1;
        fMax = f2;
    } else {
        fMin = f2;
        fMax = f1;
    }

    if (c1 < c2) {
        cMin = c1;
        cMax = c2;
    } else {
        cMin = c2;
        cMax = c1;
    }

    // recorre filas del rango y elimina nodos con columna dentro del rango
    for (int f = fMin; f <= fMax; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* anteriorFila = cabezaFila;
        Nodo* actualFila = cabezaFila->siguienteColumna;

        while (actualFila != cabezaFila && actualFila->columna < cMin) {
            anteriorFila = actualFila;
            actualFila = actualFila->siguienteColumna;
        }

        while (actualFila != cabezaFila && actualFila->columna <= cMax) {
            Nodo* nodoAEliminar = actualFila;
            actualFila = actualFila->siguienteColumna;

            anteriorFila->siguienteColumna = actualFila;

            int columna = nodoAEliminar->columna;
            Nodo* cabezaColumna = cabezasColumna[columna];
            Nodo* anteriorColumna = cabezaColumna;
            Nodo* actualColumna = cabezaColumna->siguienteFila;
            while (actualColumna != cabezaColumna && actualColumna != nodoAEliminar) {
                anteriorColumna = actualColumna;
                actualColumna = actualColumna->siguienteFila;
            }

            if (actualColumna != cabezaColumna) {
                anteriorColumna->siguienteFila = actualColumna->siguienteFila;
            }

            delete nodoAEliminar;
        }
    }
}

// lista todas las celdas ocupadas (no vacías) con sus coordenadas y valores
std::vector<CeldaInfo> MatrizDispersa::listarOcupadas() const {
    std::vector<CeldaInfo> resultado;
    
    // recorre cada fila
    for (int f = 0; f < filas; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* actual = cabezaFila->siguienteColumna;
        // recorre cada nodo en la fila
        while (actual != cabezaFila) {
            resultado.push_back({actual->fila, actual->columna, actual->valor});
            actual = actual->siguienteColumna;
        }
    }
    
    return resultado;
}

// obtiene todas las celdas ocupadas de una fila específica
std::vector<CeldaInfo> MatrizDispersa::obtenerFila(int fila) const {
    if (fila < 0 || fila >= filas) {
        throw std::out_of_range("Índices fuera de rango");
    }
    
    std::vector<CeldaInfo> resultado;
    
    // recorre los nodos ocupados de esa fila
    Nodo* cabezaFila = cabezasFila[fila];
    Nodo* actual = cabezaFila->siguienteColumna;
    while (actual != cabezaFila) {
        resultado.push_back({actual->fila, actual->columna, actual->valor});
        actual = actual->siguienteColumna;
    }
    
    return resultado;
}

// obtiene todas las celdas ocupadas de una columna específica
std::vector<CeldaInfo> MatrizDispersa::obtenerColumna(int columna) const {
    if (columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }
    
    std::vector<CeldaInfo> resultado;
    
    // recorre los nodos ocupados de esa columna
    Nodo* cabezaColumna = cabezasColumna[columna];
    Nodo* actual = cabezaColumna->siguienteFila;
    while (actual != cabezaColumna) {
        resultado.push_back({actual->fila, actual->columna, actual->valor});
        actual = actual->siguienteFila;
    }
    
    return resultado;
}

// obtiene todas las celdas ocupadas dentro de un rango rectangular [f1,c1] a [f2,c2]
std::vector<CeldaInfo> MatrizDispersa::obtenerRango(int f1, int c1, int f2, int c2) const {
    if (f1 < 0 || f1 >= filas || f2 < 0 || f2 >= filas ||
        c1 < 0 || c1 >= columnas || c2 < 0 || c2 >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }
    
    // asegura que f1 <= f2 y c1 <= c2
    int fMin;
    int fMax;
    int cMin;
    int cMax;

    if (f1 < f2) {
        fMin = f1;
        fMax = f2;
    } else {
        fMin = f2;
        fMax = f1;
    }

    if (c1 < c2) {
        cMin = c1;
        cMax = c2;
    } else {
        cMin = c2;
        cMax = c1;
    }
    
    std::vector<CeldaInfo> resultado;
    
    // recorre solo las filas dentro del rango
    for (int f = fMin; f <= fMax; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* actual = cabezaFila->siguienteColumna;
        // recorre los nodos de esa fila y filtra por columna
        while (actual != cabezaFila) {
            if (actual->columna >= cMin && actual->columna <= cMax) {
                resultado.push_back({actual->fila, actual->columna, actual->valor});
            }
            // si columna ya es mayor que cMax no hay más nodos que importen
            if (actual->columna > cMax) {
                break;
            }
            actual = actual->siguienteColumna;
        }
    }
    
    return resultado;
}

// suma valores numéricos dentro de un rango rectangular [f1,c1] a [f2,c2]
double MatrizDispersa::sumarRango(int f1, int c1, int f2, int c2) const {
    if (f1 < 0 || f1 >= filas || f2 < 0 || f2 >= filas ||
        c1 < 0 || c1 >= columnas || c2 < 0 || c2 >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }
    //
    int fMin;
    int fMax;
    int cMin;
    int cMax;

    if (f1 < f2) {
        fMin = f1;
        fMax = f2;
    } else {
        fMin = f2;
        fMax = f1;
    }

    if (c1 < c2) {
        cMin = c1;
        cMax = c2;
    } else {
        cMin = c2;
        cMax = c1;
    }

    double suma = 0.0;

    for (int f = fMin; f <= fMax; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* actual = cabezaFila->siguienteColumna;

        while (actual != cabezaFila) {
            if (actual->columna >= cMin && actual->columna <= cMax && esNumero(actual->valor)) {
                suma += comoNumero(actual->valor);
            }
            if (actual->columna > cMax) {
                break;
            }
            actual = actual->siguienteColumna;
        }
    }

    return suma;
}

// promedia valores numéricos dentro de un rango rectangular [f1,c1] a [f2,c2]
double MatrizDispersa::promediarRango(int f1, int c1, int f2, int c2) const {
    if (f1 < 0 || f1 >= filas || f2 < 0 || f2 >= filas ||
        c1 < 0 || c1 >= columnas || c2 < 0 || c2 >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    int fMin;
    int fMax;
    int cMin;
    int cMax;

    if (f1 < f2) {
        fMin = f1;
        fMax = f2;
    } else {
        fMin = f2;
        fMax = f1;
    }

    if (c1 < c2) {
        cMin = c1;
        cMax = c2;
    } else {
        cMin = c2;
        cMax = c1;
    }

    double suma = 0.0;
    int cantidad = 0;

    for (int f = fMin; f <= fMax; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* actual = cabezaFila->siguienteColumna;

        while (actual != cabezaFila) {
            if (actual->columna >= cMin && actual->columna <= cMax && esNumero(actual->valor)) {
                suma += comoNumero(actual->valor);
                cantidad++;
            }
            if (actual->columna > cMax) {
                break;
            }
            actual = actual->siguienteColumna;
        }
    }

    if (cantidad == 0) {
        return 0.0;
    }

    return suma / cantidad;
}

// obtiene el valor máximo numérico dentro de un rango rectangular [f1,c1] a [f2,c2]
double MatrizDispersa::maximoRango(int f1, int c1, int f2, int c2) const {
    if (f1 < 0 || f1 >= filas || f2 < 0 || f2 >= filas ||
        c1 < 0 || c1 >= columnas || c2 < 0 || c2 >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    int fMin;
    int fMax;
    int cMin;
    int cMax;

    if (f1 < f2) {
        fMin = f1;
        fMax = f2;
    } else {
        fMin = f2;
        fMax = f1;
    }

    if (c1 < c2) {
        cMin = c1;
        cMax = c2;
    } else {
        cMin = c2;
        cMax = c1;
    }

    double maximo = std::numeric_limits<double>::lowest();
    bool hayNumero = false;

    for (int f = fMin; f <= fMax; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* actual = cabezaFila->siguienteColumna;

        while (actual != cabezaFila) {
            if (actual->columna >= cMin && actual->columna <= cMax && esNumero(actual->valor)) {
                double valor = comoNumero(actual->valor);
                if (valor > maximo) {
                    maximo = valor;
                }
                hayNumero = true;
            }
            if (actual->columna > cMax) {
                break;
            }
            actual = actual->siguienteColumna;
        }
    }

    if (!hayNumero) {
        return 0.0;
    }

    return maximo;
}

// obtiene el valor mínimo numérico dentro de un rango rectangular [f1,c1] a [f2,c2]
double MatrizDispersa::minimoRango(int f1, int c1, int f2, int c2) const {
    if (f1 < 0 || f1 >= filas || f2 < 0 || f2 >= filas ||
        c1 < 0 || c1 >= columnas || c2 < 0 || c2 >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    int fMin;
    int fMax;
    int cMin;
    int cMax;

    if (f1 < f2) {
        fMin = f1;
        fMax = f2;
    } else {
        fMin = f2;
        fMax = f1;
    }

    if (c1 < c2) {
        cMin = c1;
        cMax = c2;
    } else {
        cMin = c2;
        cMax = c1;
    }
    //inicializa con un numero muy pequeño con limits
    double minimo = std::numeric_limits<double>::max();
    bool hayNumero = false;

    for (int f = fMin; f <= fMax; ++f) {
        Nodo* cabezaFila = cabezasFila[f];
        Nodo* actual = cabezaFila->siguienteColumna;

        while (actual != cabezaFila) {
            if (actual->columna >= cMin && actual->columna <= cMax && esNumero(actual->valor)) {
                double valor = comoNumero(actual->valor);
                if (valor < minimo) {
                    minimo = valor;
                }
                hayNumero = true;
            }
            if (actual->columna > cMax) {
                break;
            }
            actual = actual->siguienteColumna;
        }
    }

    if (!hayNumero) {
        return 0.0;
    }

    return minimo;
}