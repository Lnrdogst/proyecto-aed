/*
Archivo: Nodo.h
Responsabilidad: describir el nodo base de la matriz dispersa con enlaces cruzados.
Relación: se usa desde MatrizDispersa.h y sus implementaciones en src/EstructuraDeDatos/.
*/
template <typename T>
class Nodo {
public:
    T valor;
    int fila;
    int columna;
    Nodo<T>* siguienteFila;
    Nodo<T>* siguienteColumna;
    Nodo(T valor, int fila, int columna) : valor(valor),
    fila(fila), columna(columna), siguienteFila(nullptr),
    siguienteColumna(nullptr) {}
};