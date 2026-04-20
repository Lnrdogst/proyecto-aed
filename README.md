Proyecto universitario de Hoja de Calculo en C++17 con matriz dispersa y SFML.

## Requisitos

- CMake 3.16 o superior.
- Un compilador compatible con C++17.
- SFML con los componentes `system`, `window` y `graphics` instalados y visibles para CMake.

## Compilacion

```bash
cmake -S . -B build
cmake --build build
```

## Ejecucion

```bash
./build/HojaCalculoAED
```

## Estructura

- `include/Core`: coordinacion general de la aplicacion.
- `include/EstructuraDeDatos`: nodo y matriz dispersa con listas cruzadas.
- `include/GUI`: interfaz grafica basada en SFML.
- `src/Core`: punto de entrada y orquestacion.
- `src/EstructuraDeDatos`: implementacion de la estructura de datos.
- `src/GUI`: implementacion de la interfaz.
