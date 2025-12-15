// main.cpp
#include "interfaz_consola.h"

/**
 * Este programa implementa un sistema de archivos jerárquico con las siguientes características:
 * - Crear, mover, renombrar y eliminar nodos (carpetas/archivos)
 * - Búsqueda por prefijo con autocompletado usando Trie
 * - Papelera temporal para recuperación de elementos eliminados
 * - Exportación de recorridos en preorden
 * - Persistencia en archivos JSON
 * - Interfaz de consola interactiva
 *
 */
int main() {
    try {
        // Crear e iniciar la interfaz de consola
        InterfazConsola interfaz;
        interfaz.iniciar();

        return 0;
    }
    catch (const std::exception& e) {
        return 1;
    }
    catch (...) {

        return 1;
    }
}
