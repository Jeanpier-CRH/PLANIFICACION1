# Planificador FCFS
Programa en C++17 que simula la planificación de procesos mediante el algoritmo **FCFS** (*First-Come, First-Served*), también llamado **Primero en llegar, primero en servirse**.

El proyecto corresponde a la práctica de planificación de procesos descrita en `docs/P09_Planificacion_de_procesos.md`.

## Información del estudiante
Completar los siguientes datos antes de entregar la práctica:

- **Estudiante:** Alex Jeanpier Chata Chino
- **Código universitario:** 2024-119012
- **Curso o asignatura:** Sistemas Operativos

## Estructura del proyecto
```text
PlanificadorFCFS/
├── docs/
│   └── P09_Planificacion_de_procesos.md
├── src/
│   └── fcfs.cpp
├── .vscode/
└── README.md
```

## Características
El programa:

- Solicita entre 3 y 5 procesos.
- Permite ingresar identificador, tiempo de llegada y tiempo de servicio.
- Valida que el tiempo de llegada sea mayor o igual que cero.
- Valida que el tiempo de servicio sea positivo.
- Almacena los procesos usando un `struct` y un `vector`.
- Ordena por tiempo de llegada.
- Mantiene el orden de ingreso cuando dos procesos tienen la misma llegada.
- Considera los intervalos en que el procesador permanece ocioso.
- Calcula los siguientes tiempos:
  - Tiempo de llegada (`TL`)
  - Tiempo de servicio (`Ts`)
  - Tiempo de comienzo (`TC`)
  - Tiempo de finalización (`TF`)
  - Tiempo de espera (`TE`)
  - Tiempo de estancia (`Tr`)
  - Tiempo de estancia normalizado (`Tr/Ts`)
- Muestra promedios de espera, estancia y estancia normalizada.
- Muestra una secuencia temporal tipo Gantt en texto.

## Fórmulas utilizadas
Las fórmulas corresponden a la guía de la práctica:

```text
TC = max(TL, tiempo actual)
TF = TC + Ts
TE = TC - TL
Tr = TF - TL
Tr/Ts = Tr / Ts
```

Cuando no hay un proceso disponible, el reloj de simulación avanza hasta el tiempo de llegada del siguiente proceso.

## Compilación
Desde la raíz del proyecto, ejecutar:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic src/fcfs.cpp -o fcfs
```

El programa utiliza únicamente bibliotecas estándar de C++17.

## Ejecución
En Linux o macOS:

```bash
./fcfs
```

En Windows, después de compilar con MinGW:

```text
fcfs.exe
```

## Escenario 1: ejemplo de Stallings
Los datos indicados en la guía son:

| Proceso | Tiempo de llegada | Tiempo de servicio |
|---|---:|---:|
| A | 0 | 3 |
| B | 2 | 6 |
| C | 4 | 4 |
| D | 6 | 5 |
| E | 8 | 2 |

Deben ingresarse en ese orden cuando se quiera reproducir el ejemplo. El resultado esperado es:

| Proceso | TL | Ts | TC | TF | TE | Tr | Tr/Ts |
|---|---:|---:|---:|---:|---:|---:|---:|
| A | 0 | 3 | 0 | 3 | 0 | 3 | 1.00 |
| B | 2 | 6 | 3 | 9 | 1 | 7 | 1.17 |
| C | 4 | 4 | 9 | 13 | 5 | 9 | 2.25 |
| D | 6 | 5 | 13 | 18 | 7 | 12 | 2.40 |
| E | 8 | 2 | 18 | 20 | 10 | 12 | 6.00 |

Promedios esperados:

```text
Espera promedio: 4.60
Estancia promedio: 8.60
Estancia normalizada promedio: 2.56
```

No hay intervalos ociosos en este escenario.

## Escenario 2: datos personalizados
Primero se debe calcular `K` con el último dígito del código universitario. Después, ingresar los procesos en el orden mostrado:

| Proceso | Tiempo de llegada | Tiempo de servicio |
|---|---:|---:|
| P1 | K + 8 | 2 |
| P2 | K | 4 |
| P3 | K + 1 | 3 |
| P4 | K + 8 | 1 |

Para comprobar el apartado 4.5 de la guía, modificar después el tiempo de llegada de P4:

```text
P4: K + 8  ->  K + 6
```

En ambos casos se debe comprobar el orden de ejecución, los intervalos ociosos, los tiempos calculados y los promedios.

## Estado de comprobación
Se verificó localmente:

- Compilación con `g++ -std=c++17 -Wall -Wextra -Wpedantic`.
- Escenario de Stallings.
- Escenario personalizado para `K = 1`, `K = 2` y `K = 3`.
- Modificación de P4 a `K + 6`.
- Empates en tiempos de llegada.
- Intervalos de inactividad del procesador.
- Rechazo de tiempos negativos, tiempos de servicio no positivos y entradas con formato inválido.

## Datos pendientes de comprobar
Antes de entregar la práctica, completar y revisar:

1. El valor calculado de `K`.
2. Las capturas o evidencias solicitadas por la guía.
3. El diagrama de Gantt requerido para el escenario personalizado.
4. La resolución escrita de las preguntas de análisis de resultados.

## Referencia
La guía completa de la práctica se encuentra en:

```text
docs/P09_Planificacion_de_procesos.md
```
