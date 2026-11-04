**PRÁCTICA: “**PLANIFICACIÓN DE PROCESOS (I)”

**OBJETIVOS**

* Comprender el funcionamiento de la planificación a corto plazo en un sistema uniprocesador.  
* Implementar en C++ el algoritmo de planificación Primero en llegar, primero en servirse (FCFS).  
* Calcular los tiempos de comienzo, finalización, espera, estancia y estancia normalizado de los procesos.  
* Representar gráficamente la secuencia de ejecución mediante diagramas de Gantt.  
* Analizar el comportamiento de FCFS ante diferentes tiempos de llegada y de servicio.

**FUNDAMENTO TEÓRICO**

**Planificación a corto plazo**

La planificación a corto plazo es la función del sistema operativo encargada de decidir cuál de los procesos que se encuentran en estado Listo será seleccionado para ejecutarse en el procesador.

La política de planificación determina el orden de ejecución de los procesos, influyendo en el rendimiento del sistema, los tiempos de espera y el aprovechamiento del procesador.

**Primero en llegar, primero en servirse (FCFS)**

El algoritmo First-Come, First-Served (FCFS), denominado **Primero en llegar, primero en servirse**, es una de las políticas de planificación más sencillas.

Su funcionamiento se basa en los siguientes principios:

* Los procesos ingresan en la cola de listos según su orden de llegada.  
* Cuando el procesador queda disponible, se selecciona el proceso que lleva más tiempo esperando en dicha cola.  
* FCFS utiliza un modo de decisión sin expulsión: una vez que un proceso comienza a ejecutarse, no es desplazado por otro proceso que llegue posteriormente.  
* En esta simulación, cada proceso utiliza el procesador hasta completar su tiempo de servicio.

Una de sus principales limitaciones es que los procesos cortos pueden experimentar tiempos de espera elevados cuando se encuentran detrás de procesos con tiempos de servicio prolongados.

**Métricas de planificación**

Para evaluar el comportamiento del algoritmo se utilizarán las siguientes métricas:

| Métrica | Descripción y cálculo |
| ----- | ----- |
| Tiempo de llegada (TL) | Instante en que el proceso ingresa a la cola de listos. |
| Tiempo de servicio (Ts) | Tiempo total de procesador requerido por el proceso. |
| Tiempo de comienzo (TC) | max(TL, tiempo actual) |
| Tiempo de finalización (TF) | Instante en que el proceso termina de ejecutarse. |
| Tiempo de espera (TE) | TE \= TC − TL |
| Tiempo de estancia (Tr) | Tr \= TF − TL |
| Tiempo de estancia normalizado | Tr / Ts |

Para esta simulación se utilizarán las relaciones:

TC=max(TL,tiempo actual)   
TF=TC+Ts 

El tiempo de estancia comprende el tiempo que un proceso permanece en el sistema desde su llegada hasta su finalización.

El tiempo de estancia normalizado expresa la relación entre el tiempo de estancia y el tiempo de servicio. Su valor mínimo es 1; cuanto mayor sea, mayor será el retardo relativo experimentado por el proceso.

Además, se calcularán los valores promedio de los tiempos de espera, estancia y estancia normalizado.

**PROCEDIMIENTO**

### **4.1. Preparación del entorno**

### 

### Abra una terminal de Ubuntu y verifique la disponibilidad del compilador de C++:

```sh
g++ --version
```

### 

### Cree el directorio de trabajo:

```sh
mkdir -p ~/PlanificacionFCFS
cd ~/PlanificacionFCFS
```

### 

### **4.2. Resolución manual del algoritmo FCFS** 

### 

### Considere el siguiente conjunto de procesos, tomado del ejemplo de planificación presentado por Stallings.

| Proceso | Tiempo de llegada | Tiempo de servicio |
| ----- | ----: | ----: |
| A | 0 | 3 |
| B | 2 | 6 |
| C | 4 | 4 |
| D | 6 | 5 |
| E | 8 | 2 |

### 

### **Actividades:**

1. ### Determine el orden de ejecución de los procesos según FCFS.

2. ### Elabore manualmente el diagrama de Gantt.

3. ### Calcule los tiempos de comienzo, finalización, espera y estancia.

4. ### Determine el tiempo de espera promedio y el tiempo de estancia promedio.

### 

### Registre los resultados en su cuaderno o en una hoja, que posteriormente utilizará para contrastarlos con su programa.

### **4.3. Implementación del algoritmo FCFS en C++ (35 minutos)**

### 

### Desarrolle un programa denominado `fcfs.cpp` que simule la planificación de procesos mediante el algoritmo FCFS.

### **Requisitos del programa:**

1. ### Solicitar el número de procesos (entre 3 y 5).

2. ### Permitir el ingreso del identificador, tiempo de llegada y tiempo de servicio de cada proceso.

3. ### Almacenar la información utilizando una estructura (`struct`) y un `vector` de C++.

4. ### Ordenar los procesos según su tiempo de llegada. En caso de empate, respetar el orden de ingreso.

5. ### Calcular el tiempo de comienzo, finalización, espera y estancia de cada proceso.

6. ### Calcular el tiempo de estancia normalizado.

7. ### Mostrar una tabla con los resultados y los promedios de espera y estancia.

8. ### Considerar los intervalos en que el procesador permanece ocioso.

### 

### Para representar los procesos puede utilizar la siguiente estructura:

```c
struct Proceso {
    string id;
    int llegada;
    int servicio;
    int comienzo;
    int finalizacion;
    int espera;
    int estancia;
    double estanciaNormalizada;
};
```

### 

### **Orientaciones:**

* ### Utilice las bibliotecas necesarias de C++, como `<iostream>`, `<vector>` y `<algorithm>`.

* ### El programa debe funcionar aunque los procesos sean ingresados en un orden diferente al de sus tiempos de llegada.

* ### Cuando no existan procesos listos para ejecutarse, el tiempo de simulación debe avanzar hasta la llegada del siguiente proceso.

* ### El tiempo de servicio debe ser positivo y el tiempo de llegada no puede ser negativo.

### 

### **Compilación y ejecución:**

```sh
g++ -std=c++17 -Wall -Wextra fcfs.cpp -o fcfs
./fcfs
```

### 

### El programa deberá producir una tabla similar a la siguiente, con los valores calculados para cada proceso:

| Proceso | TL | Ts | TC | TF | TE | Tr | Tr/Ts |
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
| ... | ... | ... | ... | ... | ... | ... | ... |

### 

### **4.4. Ejecución y validación de escenarios**

### **Escenario 1: Ejemplo de Stallings**

### 

### Ejecute el programa utilizando los cinco procesos del apartado 4.2.

### Compare los resultados de la simulación con los cálculos que realizó manualmente.

### Compruebe que los tiempos de espera y estancia sean correctos.

### **Escenario 2: Datos personalizados**

### 

### Cada estudiante utilizará el último dígito de su código universitario para obtener el valor de K:

### `K = (último dígito MOD 3) + 1`

### A partir de dicho valor, utilice los siguientes datos:

| Proceso | Tiempo de llegada | Tiempo de servicio |
| ----- | ----- | ----: |
| P1 | K \+ 8 | 2 |
| P2 | K | 4 |
| P3 | K \+ 1 | 3 |
| P4 | K \+ 8 | 1 |

### 

### Ingrese los procesos en el orden mostrado.

### Realice las siguientes actividades:

1. ### Ejecute la simulación y verifique el orden de ejecución.

2. ### Identifique los intervalos en que el procesador permanece ocioso.

3. ### Elabore el diagrama de Gantt, incluyendo dichos intervalos.

4. ### Calcule el tiempo de espera promedio y el tiempo de estancia promedio.

### 

### **4.5. Verificación individual del programa** 

### 

### Para demostrar la comprensión del algoritmo implementado, realice el siguiente cambio sobre el escenario 2:

### **Modifique el tiempo de llegada de P4 de `K + 8` a `K + 6`.**

### 

### Antes de ejecutar nuevamente el programa:

* ### Escriba cuál considera que será el nuevo orden de ejecución.

* ### Indique si el intervalo de inactividad del procesador cambiará y explique por qué.

### 

### Posteriormente, modifique los datos, compile y ejecute nuevamente el programa para verificar su predicción.

**ANÁLISIS DE RESULTADOS**

### Responda brevemente las siguientes preguntas:

1. ### ¿Por qué FCFS se considera un algoritmo de planificación sin expulsión?

2. ### En el escenario 1, ¿qué sucede con el tiempo de espera de los procesos que llegan después de un proceso con un tiempo de servicio elevado?

3. ### En el escenario 2, ¿por qué el procesador permanece ocioso en determinados intervalos?

4. ### ¿Qué utilidad tiene el tiempo de estancia normalizado frente al tiempo de estancia?

### 

### Sustente sus respuestas utilizando los resultados de las simulaciones.

**EVIDENCIAS**  
Al finalizar la práctica deberá presentar:

**1\. Código fuente:** Archivo `fcfs.cpp` debidamente organizado y comentado.

**2\. Informe breve (máximo 3 páginas):**

* Resolución manual del escenario 1, mediante fotografía de la hoja de trabajo.  
* Capturas de pantalla de la compilación y de los resultados de ambos escenarios.  
* Diagrama de Gantt del escenario 2\.  
* Respuestas a las cuatro preguntas del análisis de resultados.


**3\. Evidencia de desarrollo y verificación:** Una captura del código durante su implementación, antes de completar el programa.

**Entrega:** Suba al aula virtual el enlace a su repo de GitHub.

**REFERENCIAS BIBLIOGRÁFICAS**

Deitel, H. M., Deitel, P. J., & Choffnes, D. R. (2004). Sistemas Operativos (3.ª ed.). Pearson Educación.  
Milonas, P. (2011). Sistemas Operativos: Una Visión Aplicada (1.ª ed.). Alfaomega.  
Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). *Operating System Concepts* (10th ed.). Wiley.  
Tanenbaum, A. S., & Bos, H. (2014). *Modern Operating Systems* (4th ed.). Pearson.  
