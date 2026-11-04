// Simulador FCFS: C++17, sin dependencias externas.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Proceso {
    std::string id;
    int llegada = 0;
    int servicio = 0;
    long long  comienzo = 0;
    long long  finalizacion = 0;
    long long  espera = 0;
    long long  estancia = 0;
    double estanciaNormalizada = 0.0;
};

// Fase 1: leer lineas completas para rechazar datos parciales como "3abc".
std::string leerLinea(const std::string& mensaje) {
    std::cout << mensaje;
    std::string linea;
    if (!std::getline(std::cin, linea)) {
        throw std::runtime_error("Entrada interrumpida: faltan datos.");
    }
    return linea;
}

int leerEntero(const std::string& mensaje, int minimo, int maximo) {
    while (true) {
        std::istringstream entrada(leerLinea(mensaje));
        int valor = 0;
        if ((entrada >> valor) && (entrada >> std::ws).eof()
            && valor >= minimo && valor <= maximo) {
            return valor;
        }
        std::cout << "Entrada invalida. Ingrese un entero entre "
                  << minimo << " y " << maximo << ".\n";
    }
}

// Fase 2: captura de procesos y validacion de sus restricciones.
std::string leerIdentificador(int numero) {
    while (true) {
        const std::string id = leerLinea("  Identificador del proceso "
                                         + std::to_string(numero) + ": ");
        if (!id.empty() && id.find_first_not_of(" \t") != std::string::npos) {
            return id;
        }
        std::cout << "El identificador no puede estar vacio.\n";
    }
}

std::vector<Proceso> ingresarProcesos() {
    const int cantidad = leerEntero("Cantidad de procesos (3-5): ", 3, 5);
    std::vector<Proceso> procesos;
    procesos.reserve(static_cast<std::size_t>(cantidad));

    for (int i = 0; i < cantidad; ++i) {
        Proceso proceso;
        proceso.id = leerIdentificador(i + 1);
        proceso.llegada = leerEntero("  Tiempo de llegada (>= 0): ", 0,
                                     std::numeric_limits<int>::max());
        proceso.servicio = leerEntero("  Tiempo de servicio (> 0): ", 1,
                                      std::numeric_limits<int>::max());
        procesos.push_back(proceso);
    }
    return procesos;
}

// Fase 3: stable_sort conserva el orden de ingreso cuando hay empate.
void ordenarPorLlegada(std::vector<Proceso>& procesos) {
    std::stable_sort(procesos.begin(), procesos.end(),
                     [](const Proceso& primero, const Proceso& segundo) {
                         return primero.llegada < segundo.llegada;
                     });
}

// Fase 4: avanzar el reloj hasta la llegada si el procesador esta ocioso.
void calcularPlanificacion(std::vector<Proceso>& procesos) {
    long long  reloj = 0;
    for (Proceso& proceso : procesos) {
        const long long  llegada = proceso.llegada;
        const long long  servicio = proceso.servicio;
        proceso.comienzo = std::max(reloj, llegada);
        proceso.finalizacion = proceso.comienzo + servicio;
        proceso.espera = proceso.comienzo - llegada;
        proceso.estancia = proceso.finalizacion - llegada;
        proceso.estanciaNormalizada =
            static_cast<double>(proceso.estancia) / servicio;
        reloj = proceso.finalizacion;
    }
}

// Fase 5: mostrar resultados y promedios.
void mostrarResultados(const std::vector<Proceso>& procesos) {
    long long  totalEspera = 0;
    long long  totalEstancia = 0;
    double totalNormalizada = 0.0;
    std::size_t anchoId = 12;
    for (const Proceso& proceso : procesos) {
        anchoId = std::max(anchoId, proceso.id.size() + 2);
    }
    const int anchoProceso = static_cast<int>(anchoId);

    std::cout << "\nResultados FCFS\n"
              << std::left << std::setw(anchoProceso) << "Proceso"
              << std::right << std::setw(14) << "TL"
              << std::setw(14) << "TS"
              << std::setw(14) << "TC"
              << std::setw(14) << "TF"
              << std::setw(14) << "TE"
              << std::setw(14) << "Tr"
              << std::setw(12) << "Tr/Ts" << '\n';
    std::cout << std::string(anchoId + 96, '-') << '\n';

    for (const Proceso& proceso : procesos) {
        totalEspera += proceso.espera;
        totalEstancia += proceso.estancia;
        totalNormalizada += proceso.estanciaNormalizada;
        std::cout << std::left << std::setw(anchoProceso) << proceso.id
                  << std::right << std::setw(14) << proceso.llegada
                  << std::setw(14) << proceso.servicio
                  << std::setw(14) << proceso.comienzo
                  << std::setw(14) << proceso.finalizacion
                  << std::setw(14) << proceso.espera
                  << std::setw(14) << proceso.estancia
                  << std::setw(12) << std::fixed << std::setprecision(2)
                  << proceso.estanciaNormalizada << '\n';
    }

    const double cantidad = static_cast<double>(procesos.size());
    std::cout << "\nPromedio de espera: "
              << std::fixed << std::setprecision(2)
              << totalEspera / cantidad << '\n'
              << "Promedio de estancia: " << totalEstancia / cantidad << '\n'
              << "Promedio de estancia normalizada: "
              << totalNormalizada / cantidad << '\n'
              << "TL: llegada; Ts: servicio; TC: comienzo; TF: finalizacion;\n"
              << "TE: espera; Tr: estancia; Tr/Ts: estancia normalizada.\n";

    // Intervalos [inicio, fin): incluye inactividad inicial e intermedia.
    std::cout << "\nSecuencia temporal (Gantt textual, sin escala):\n";
    long long  reloj = 0;
    long long  totalOcioso = 0;
    for (const Proceso& proceso : procesos) {
        if (reloj < proceso.comienzo) {
            std::cout << '[' << reloj << ", " << proceso.comienzo
                      << ") OCIOSO\n";
            totalOcioso += proceso.comienzo - reloj;
        }
        std::cout << '[' << proceso.comienzo << ", " << proceso.finalizacion
                  << ") " << proceso.id << '\n';
        reloj = proceso.finalizacion;
    }
    std::cout << "Tiempo ocioso total: " << totalOcioso << '\n';
}

int main() {
    std::cout << "=== Planificador FCFS ===\n"
              << "Los empates de llegada conservan el orden de ingreso.\n";
    try {
        std::vector<Proceso> procesos = ingresarProcesos();
        ordenarPorLlegada(procesos);
        calcularPlanificacion(procesos);
        mostrarResultados(procesos);
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
