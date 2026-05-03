# Proyecto AED: Hoja de Cálculo con Matriz Dispersa y UI en Qt

Proyecto universitario de Hoja de Cálculo escrito en C++17. Utiliza una implementación propia de matriz dispersa basada en listas doblemente enlazadas ortogonales (circulares) para la optimización de memoria, junto con una Interfaz Gráfica interactiva desarrollada en **Qt (Widgets)**.

## Requisitos

- Un compilador compatible con C++17 (e.g. GCC, Clang).
- **Qt5 o Qt6** instalados en el sistema (componente `Widgets`).
- **qmake** o **CMake** (3.16 o superior) para orquestar la compilación.

## Cómo compilar y ejecutar (Paso a Paso)

Puedes compilar el proyecto de dos formas distintas, dependiendo de la herramienta que prefieras:

### Opción A: Usando `qmake` (Recomendado para Linux)

1. **Abre tu terminal y posicionate en la raíz del proyecto.**
2. **Crea una carpeta de compilación aislada y entra en ella:**
   ```bash
   mkdir -p build_qt
   cd build_qt
   ```
3. **Genera el Makefile usando qmake:**
   ```bash
   qmake ../proyecto-aed.pro
   ```
4. **Compila el proyecto (aprovechando todos los núcleos de tu CPU):**
   ```bash
   make -j$(nproc)
   ```
5. **Ejecuta la aplicación:**
   ```bash
   ./bin/HojaCalculoAED
   ```

### Opción B: Usando `CMake`

Si tu equipo prefiere usar CMake, el proyecto también está configurado para ello:

1. **Abre tu terminal y posicionate en la raíz del proyecto.**
2. **Genera los archivos de construcción en la carpeta build:**
   ```bash
   cmake -S . -B build
   ```
3. **Compila el proyecto:**
   ```bash
   cmake --build build -j$(nproc)
   ```
4. **Ejecuta la aplicación:**
   ```bash
   ./build/HojaCalculoAED
   ```

## Estructura del Proyecto

- `include/Core` y `src/Core`: Contiene el punto de entrada (`main.cpp`) y el controlador central (`Aplicacion`) que coordina la vista y los datos.
- `include/EstructuraDeDatos` y `src/EstructuraDeDatos`: Implementación pura de la Matriz Dispersa y el Nodo base. (Lógica 100% aislada e independiente de la UI).
- `include/GUI` y `src/GUI`: Lógica de la interfaz gráfica (`VentanaPrincipal`) construida sobre la clase `QTableWidget`.

## Documentación Adicional
Puedes encontrar la explicación a profundidad de la estructura de la matriz y el análisis algorítmico de tiempo (Big O) de todos sus métodos en el archivo de texto `Documentacion_MatrizDispersa.txt` generado para auditoría.
