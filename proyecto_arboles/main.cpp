// main.cpp
#include "interfaz_consola.h"
#include <iostream>

/**
 * @brief Programa principal del Proyecto Final de Árboles
 *
 * Este proyecto implementa una mini-suite para gestion de jerarquías de archivos
 * con todas las funcionalidades requeridas para los días 1-14 del cronograma.
 *
 * Características principales:
 * 1. Crear, mover, renombrar y eliminar nodos (carpetas/archivos)
 * 2. Papelera temporal con recuperación
 * 3. Búsqueda por prefijo con autocompletado (Trie avanzado)
 * 4. Exportación de recorridos en preorden
 * 5. Persistencia en archivos JSON
 * 6. Pruebas de integración y performance
 * 7. Interfaz de consola completa
 * 8. Sistema de métricas y estadísticas
 *
 * Días implementados:
 * - Días 1-9: MVP con funcionalidades básicas
 * - Días 10-11: Pruebas de integracion y casos limite
 * - Día 12: Documentacion y metricas
 * - Día 13: Demo y script de ejecucion
 * - Día 14: Presentacion y retroalimentacion
 *
 * @return int 0 si se ejecuta correctamente, 1 en caso de error
 */
int main() {
    try {
        std::cout << "========================================" << std::endl;
        std::cout << "   PROYECTO FINAL - GESTION DE ARBOLES  " << std::endl;
        std::cout << "   Universidad UAS - Estructuras de Datos   " << std::endl;
        std::cout << "            Días 1-14 Completos  " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::endl;

        std::cout << "Comandos especiales para evaluacion:" << std::endl;
        std::cout << "  pruebas        - Ejecutar todas las pruebas de integracion" << std::endl;
        std::cout << "  demo           - Ejecutar demostracion completa" << std::endl;
        std::cout << "  performance    - Pruebas de rendimiento con arbol grande" << std::endl;
        std::cout << "  consistencia   - Verificar consistencia del arbol" << std::endl;
        std::cout << "  metricas       - Mostrar estadisticas del sistema" << std::endl;
        std::cout << std::endl;

        InterfazCompleta interfaz;
        interfaz.iniciar();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\nERROR CRITICO: " << e.what() << std::endl;
        std::cerr << "El programa se cerrara." << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "\nERROR DESCONOCIDO" << std::endl;
        std::cerr << "El programa se cerrara." << std::endl;
        return 1;
    }
}
