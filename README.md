# Proyecto AED: Hoja de Cálculo con Matriz Dispersa y UI en Qt

Proyecto universitario de Hoja de Cálculo escrito en **C++17**. Utiliza una implementación propia de **matriz dispersa con listas enlazadas cruzadas circulares** para optimizar el uso de memoria, junto con una interfaz gráfica interactiva desarrollada con **Qt Widgets**.

Al arrancar, la aplicación carga automáticamente unos datos de prueba en la matriz y muestra la hoja de cálculo lista para usarse.

---

## Requisitos

| Herramienta | Versión mínima | Notas |
|---|---|---|
| Compilador C++ | GCC 9 / Clang 10 | Con soporte a C++17 |
| Qt | 5.12 o Qt 6.x | Componente `Widgets` obligatorio |
| CMake | 3.16 | **Método recomendado** |
| qmake | Qt5/Qt6 | Alternativa a CMake |

Para instalar las dependencias en Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev
# O si usas Qt5:
sudo apt install build-essential cmake qtbase5-dev
```

---

## Compilar y ejecutar con CMake (Recomendado)

El binario ya compilado puede encontrarse en `build/HojaCalculoAED` si el proyecto fue compilado previamente. Para compilar desde cero:

```bash
# 1. Desde la raíz del proyecto, genera los archivos de build
cmake -S . -B build

# 2. Compila (usa todos los núcleos disponibles)
cmake --build build -j$(nproc)

# 3. Ejecuta la aplicación
./build/HojaCalculoAED
```

---

## Compilar y ejecutar con qmake (Alternativa)

```bash
# 1. Crea un directorio de build separado y entra en él
mkdir -p build_qt && cd build_qt

# 2. Genera el Makefile
qmake ../proyecto-aed.pro

# 3. Compila
make -j$(nproc)

# 4. Ejecuta la aplicación (el binario queda en bin/)
./bin/HojaCalculoAED
```

---

## Estructura del proyecto

```
proyecto-aed/
├── include/
│   ├── Core/
│   │   └── Aplicacion.h          # Controlador central (conecta datos ↔ UI)
│   ├── EstructuraDeDatos/
│   │   ├── MatrizDispersa.h      # Interfaz de la matriz dispersa
│   │   └── Nodo.h                # Nodo con enlaces cruzados
│   └── GUI/
│       └── VentanaPrincipal.h    # Ventana Qt principal
├── src/
│   ├── Core/
│   │   ├── main.cpp              # Punto de entrada
│   │   └── Aplicacion.cpp        # Lógica del controlador y slots Qt
│   ├── EstructuraDeDatos/
│   │   ├── MatrizDispersa.cpp    # Implementación de la matriz dispersa
│   │   └── Nodo.cpp              # Implementación del nodo
│   └── GUI/
│       └── VentanaPrincipal.cpp  # Implementación de la interfaz gráfica
├── docs/
│   └── informe.tex               # Informe técnico (LaTeX)
├── CMakeLists.txt                # Configuración de build con CMake
├── proyecto-aed.pro              # Configuración de build con qmake
└── README.md
```

### Descripción de componentes

- **`EstructuraDeDatos/`** — Implementación pura de la matriz dispersa y el nodo base. **Sin dependencias de Qt**; lógica 100% aislada e independiente de la UI.
- **`Core/Aplicacion`** — Controlador que instancia la matriz y la ventana, conecta las señales Qt de la UI con los métodos de la matriz (patrón MVC).
- **`GUI/VentanaPrincipal`** — Interfaz gráfica con `QTableWidget`. Emite señales para cada acción del usuario; no accede directamente a la matriz.

---

## Funcionalidades de la UI

- Edición directa de celdas haciendo doble clic
- Operaciones de rango: **Suma, Promedio, Máximo, Mínimo**
- Eliminación de fila, columna o rango rectangular
- Visualización de celdas ocupadas en una fila o columna específica
- Listado de todas las celdas ocupadas de la hoja
