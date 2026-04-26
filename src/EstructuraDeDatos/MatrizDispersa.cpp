
#include "EstructuraDeDatos/MatrizDispersa.h"
#include <iostream>
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
    cabezasColumna(columnas, nullptr) {}

MatrizDispersa::~MatrizDispersa() {
    // limpia filas y columnas eliminando cada nodo.
    for (int f = 0; f < filas; ++f) {
        Nodo* actual = cabezasFila[f];
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguienteColumna;
            delete actual;
            actual = siguiente;
        }
    }
}


void MatrizDispersa::insertar(const std::string& valor, int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range
        throw std::out_of_range("Índices fuera de rango");
    }
    
    // insertar en la lista de la fila 
    Nodo* anteriorFila = nullptr;
    Nodo* actualFila = cabezasFila[fila];
    while (actualFila != nullptr && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }
    
    // verifica que exista la celda exacta para actualizar su valor
    if (actualFila != nullptr && actualFila->columna == columna) {
        actualFila->valor = valor;
        return;
    }

    Nodo* nuevoNodo = new Nodo(valor, fila, columna);
    // insersion del nodo en la lista
    // asegura que exista anterior para enlazar
    //si no existe, el nuevo nodo se convierte en la cabeza de la fila 
    if (anteriorFila == nullptr) {
        //asigna null al siguiente del nuevo nodo 
        nuevoNodo->siguienteColumna = cabezasFila[fila];
        //actualiza la cabeza de la fila al nuevo nodo
        cabezasFila[fila] = nuevoNodo;
    }
    //si existe, se inserta entre anterior y actual
    else {
        nuevoNodo->siguienteColumna = anteriorFila->siguienteColumna;
        anteriorFila->siguienteColumna = nuevoNodo;
    }

    // Insertar en la lista de la columna (orden por fila).
    Nodo* anteriorColumna = nullptr;
    Nodo* actualColumna = cabezasColumna[columna];
    while (actualColumna != nullptr && actualColumna->fila < fila) {
        anteriorColumna = actualColumna;
        actualColumna = actualColumna->siguienteFila;
    }

    if (anteriorColumna == nullptr) {
        //asigna null al siguiente del nuevo nodo
        nuevoNodo->siguienteFila = cabezasColumna[columna];
        //actualiza la cabeza de la columna con el nuevo nodo
        cabezasColumna[columna] = nuevoNodo;
    }
    //asigna el siguiente del anterior al nuevo nodo y el nuevo nodo  
    else {
        nuevoNodo->siguienteFila = anteriorColumna->siguienteFila;
        //actualiza al siguiente del anterior con el nuevo nodo 
        anteriorColumna->siguienteFila = nuevoNodo;
    }
}


// verifica la existencia de un nodo en una posición específica,
// devuelve true si existe y false si no existe
bool MatrizDispersa::existe(int fila, int columna) const {
    //verifica que los indices esten dentro del rango
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    //recorre la fila buscando la columna deseada
    Nodo* actual = cabezasFila[fila];
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    if (actual != nullptr && actual->columna == columna) {
        return true;
    }

    return false;
}

// obtiene el valor de una celda específica, devuelve el valor en std::string
// o cadena vacía si no se encuentra
std::string MatrizDispersa::obtener(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        //manejo de errores con out_of_range 
        throw std::out_of_range("Índices fuera de rango");
    }

    //recorre la fila buscando la columna deseada
    Nodo* actual = cabezasFila[fila];
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    // si encontro la columna, devuelve su valor
    if (actual != nullptr && actual->columna == columna) {
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

    // quita de la lista de fila.
    Nodo* anteriorFila = nullptr;
    Nodo* actualFila = cabezasFila[fila];
    while (actualFila != nullptr && actualFila->columna < columna) {
        anteriorFila = actualFila;
        actualFila = actualFila->siguienteColumna;
    }

    if (actualFila == nullptr || actualFila->columna != columna) {
        return;
    }

    if (anteriorFila == nullptr) {
        cabezasFila[fila] = actualFila->siguienteColumna;
    } else {
        anteriorFila->siguienteColumna = actualFila->siguienteColumna;
    }

    // quita de la lista de columna.
    Nodo* anteriorColumna = nullptr;
    Nodo* actualColumna = cabezasColumna[columna];
    while (actualColumna != nullptr && actualColumna != actualFila) {
        anteriorColumna = actualColumna;
        actualColumna = actualColumna->siguienteFila;
    }

    if (actualColumna != nullptr) {
        if (anteriorColumna == nullptr) {
            cabezasColumna[columna] = actualColumna->siguienteFila;
        } else {
            anteriorColumna->siguienteFila = actualColumna->siguienteFila;
        }
    }

    delete actualFila;
}

// elimina todos los nodos de una fila y actualiza las columnas afectadas
void MatrizDispersa::eliminarFila(int fila) {
    //manejo de errores con out_of_range
    if (fila < 0 || fila >= filas) {
        throw std::out_of_range("Índices fuera de rango");
    }
    // nodo que se va quitar
    Nodo* actual = cabezasFila[fila];
    //recorre la lista de fila
    while (actual != nullptr) {
        //guarda el siguiente nodo antes de eliminar el actual
        Nodo* siguiente = actual->siguienteColumna;
        // columna del nodo actual para actualizar la lista de esa columna
        int columna = actual->columna;

        // quitar de la lista de la columna correspondiente
        Nodo* anteriorColumna = nullptr;
        Nodo* actualColumna = cabezasColumna[columna];
        // recorre la columna buscando el nodo a eliminar
        while (actualColumna != nullptr && actualColumna != actual) {
            // guarda el nodo anterior para actualizar su enlace después de eliminar el nodo actual
            anteriorColumna = actualColumna;
            actualColumna = actualColumna->siguienteFila;
        }

        if (actualColumna != nullptr) {
            // si era caveza de la columna, actualiza la cabeza al siguiente nodo
            if (anteriorColumna == nullptr) {

                cabezasColumna[columna] = actualColumna->siguienteFila;
            } 
            // si no era cabeza el puntero del nodo anterior se actualiza para saltar el nodo actual
            else {
                anteriorColumna->siguienteFila = actualColumna->siguienteFila;
            }
        }
        //se elimina el nodo actual
        delete actual;
        actual = siguiente;
    }

    cabezasFila[fila] = nullptr;
}

// elimina todos los nodos de una columna y actualiza las filas 
//logica similar a elminiarfila pero recorre columna y actualiza filas 
void MatrizDispersa::eliminarColumna(int columna) {

    if (columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índices fuera de rango");
    }

    Nodo* actual = cabezasColumna[columna];
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguienteFila;
        int fila = actual->fila;

        // quitar de la lista de la fila correspondiente
        Nodo* anteriorFila = nullptr;
        Nodo* actualFila = cabezasFila[fila];
        while (actualFila != nullptr && actualFila != actual) {
            anteriorFila = actualFila;
            actualFila = actualFila->siguienteColumna;
        }

        if (actualFila != nullptr) {
            // si era cabeza de la fila se actualiza la cabeza al siguiente
            if (anteriorFila == nullptr) {
                cabezasFila[fila] = actualFila->siguienteColumna;
            } else {
                anteriorFila->siguienteColumna = actualFila->siguienteColumna;
            }
        }

        delete actual;
        actual = siguiente;
    }

    cabezasColumna[columna] = nullptr;
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
        Nodo* anteriorFila = nullptr;
        Nodo* actualFila = cabezasFila[f];

        while (actualFila != nullptr && actualFila->columna < cMin) {
            anteriorFila = actualFila;
            actualFila = actualFila->siguienteColumna;
        }

        while (actualFila != nullptr && actualFila->columna <= cMax) {
            Nodo* nodoAEliminar = actualFila;
            actualFila = actualFila->siguienteColumna;

            if (anteriorFila == nullptr) {
                cabezasFila[f] = actualFila;
            } else {
                anteriorFila->siguienteColumna = actualFila;
            }

            int columna = nodoAEliminar->columna;
            Nodo* anteriorColumna = nullptr;
            Nodo* actualColumna = cabezasColumna[columna];
            while (actualColumna != nullptr && actualColumna != nodoAEliminar) {
                anteriorColumna = actualColumna;
                actualColumna = actualColumna->siguienteFila;
            }

            if (actualColumna != nullptr) {
                if (anteriorColumna == nullptr) {
                    cabezasColumna[columna] = actualColumna->siguienteFila;
                } else {
                    anteriorColumna->siguienteFila = actualColumna->siguienteFila;
                }
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
        Nodo* actual = cabezasFila[f];
        // recorre cada nodo en la fila
        while (actual != nullptr) {
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
    Nodo* actual = cabezasFila[fila];
    while (actual != nullptr) {
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
    Nodo* actual = cabezasColumna[columna];
    while (actual != nullptr) {
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
    
    // asegurar f1 <= f2 y c1 <= c2
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
        Nodo* actual = cabezasFila[f];
        // recorre los nodos de esa fila y filtra por columna
        while (actual != nullptr) {
            if (actual->columna >= cMin && actual->columna <= cMax) {
                resultado.push_back({actual->fila, actual->columna, actual->valor});
            }
            // si columna ya es mayor que cMax, no hay más nodos relevantes
            if (actual->columna > cMax) {
                break;
            }
            actual = actual->siguienteColumna;
        }
    }
    
    return resultado;
}