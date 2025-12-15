// interfaz_consola.cpp
#include "interfaz_consola.h"
#include <iostream>
#include <sstream>

InterfazConsola::InterfazConsola() : ejecutando(true) {}

void InterfazConsola::iniciar() {
    std::cout << "========================================" << std::endl;
    std::cout << "   MINI-SUITE DE GESTION DE ARBOLES     " << std::endl;
    std::cout << "   Implementacion MVP (Dias 1-9)        " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    mostrarAyuda();

    sistema.cargarJSON("ejemplo_inicial.json");

    while (ejecutando) {
        std::string comando;
        std::cout << "> ";
        std::getline(std::cin, comando);

        procesarComando(comando);
    }
}

void InterfazConsola::procesarComando(const std::string& comandoLinea) {
    std::vector<std::string> partes = dividirComando(comandoLinea);

    if (partes.empty()) {
        return;
    }

    std::string comando = partes[0];

    if (comando == "mkdir") {
        if (partes.size() >= 2) {
            std::string ruta = partes.size() > 2 ? partes[2] : "";
            sistema.mkdir(partes[1], ruta);
        } else {
            std::cout << "Uso: mkdir <nombre> [ruta]" << std::endl;
        }
    }
    else if (comando == "touch") {
        if (partes.size() >= 2) {
            std::string ruta = partes.size() > 2 ? partes[2] : "";
            sistema.touch(partes[1], ruta);
        } else {
            std::cout << "Uso: touch <nombre> [ruta]" << std::endl;
        }
    }
    else if (comando == "ls") {
        std::string ruta = partes.size() > 1 ? partes[1] : "";
        sistema.ls(ruta);
    }
    else if (comando == "cd") {
        std::string ruta = partes.size() > 1 ? partes[1] : "";
        sistema.cd(ruta);
    }
    else if (comando == "mv") {
        if (partes.size() >= 3) {
            sistema.mv(partes[1], partes[2]);
        } else {
            std::cout << "Uso: mv <origen> <destino>" << std::endl;
        }
    }
    else if (comando == "ren") {
        if (partes.size() >= 3) {
            sistema.renombrar(partes[1], partes[2]);
        } else {
            std::cout << "Uso: ren <ruta> <nuevoNombre>" << std::endl;
        }
    }
    else if (comando == "rm") {
        if (partes.size() >= 2) {
            sistema.rm(partes[1]);
        } else {
            std::cout << "Uso: rm <ruta>" << std::endl;
        }
    }
    else if (comando == "buscar") {
        if (partes.size() >= 2) {
            sistema.buscarPrefijo(partes[1]);
        } else {
            std::cout << "Uso: buscar <prefijo>" << std::endl;
        }
    }
    else if (comando == "export") {
        if (partes.size() >= 2) {
            std::string ruta = partes.size() > 2 ? partes[2] : "";
            sistema.exportarPreorden(partes[1], ruta);
        } else {
            std::cout << "Uso: export <archivo> [ruta]" << std::endl;
        }
    }
    else if (comando == "guardar") {
        if (partes.size() >= 2) {
            sistema.guardarJSON(partes[1]);
        } else {
            std::cout << "Uso: guardar <archivo.json>" << std::endl;
        }
    }
    else if (comando == "cargar") {
        if (partes.size() >= 2) {
            sistema.cargarJSON(partes[1]);
        } else {
            std::cout << "Uso: cargar <archivo.json>" << std::endl;
        }
    }
    else if (comando == "papelera") {
        sistema.mostrarPapelera();
    }
    else if (comando == "recuperar") {
        if (partes.size() >= 2) {
            try {
                int indice = std::stoi(partes[1]);
                sistema.recuperarPapelera(indice);
            } catch (...) {
                std::cout << "Indice invalido." << std::endl;
            }
        } else {
            std::cout << "Uso: recuperar <indice>" << std::endl;
        }
    }
    else if (comando == "vaciarpapelera") {
        sistema.vaciarPapelera();
    }
    else if (comando == "pwd") {
        sistema.pwd();
    }
    else if (comando == "info") {
        sistema.info();
    }
    else if (comando == "ayuda") {
        mostrarAyuda();
    }
    else if (comando == "salir") {
        std::cout << "Saliendo del programa..." << std::endl;
        ejecutando = false;
    }
    else {
        std::cout << "Comando no reconocido. Escribe 'ayuda' para ver comandos disponibles." << std::endl;
    }
}

std::vector<std::string> InterfazConsola::dividirComando(const std::string& comandoLinea) {
    std::vector<std::string> partes;
    std::string parteActual;
    bool entreComillas = false;

    for (size_t i = 0; i < comandoLinea.length(); i++) {
        char c = comandoLinea[i];

        if (c == '"') {
            entreComillas = !entreComillas;
        } else if (c == ' ' && !entreComillas) {
            if (!parteActual.empty()) {
                partes.push_back(parteActual);
                parteActual.clear();
            }
        } else {
            parteActual += c;
        }
    }

    if (!parteActual.empty()) {
        partes.push_back(parteActual);
    }

    return partes;
}

void InterfazConsola::mostrarAyuda() {
    std::cout << "Comandos disponibles:" << std::endl;
    std::cout << "  mkdir <nombre> [ruta]     Crear carpeta" << std::endl;
    std::cout << "  touch <nombre> [ruta]     Crear archivo" << std::endl;
    std::cout << "  ls [ruta]                 Listar contenido" << std::endl;
    std::cout << "  cd [ruta]                 Cambiar directorio" << std::endl;
    std::cout << "  mv <origen> <destino>     Mover nodo" << std::endl;
    std::cout << "  ren <ruta> <nuevoNombre>  Renombrar nodo" << std::endl;
    std::cout << "  rm <ruta>                 Eliminar nodo (a papelera)" << std::endl;
    std::cout << "  buscar <prefijo>          Buscar por prefijo" << std::endl;
    std::cout << "  export <archivo> [ruta]   Exportar preorden" << std::endl;
    std::cout << "  guardar <archivo.json>    Guardar sistema" << std::endl;
    std::cout << "  cargar <archivo.json>     Cargar sistema" << std::endl;
    std::cout << "  papelera                  Mostrar papelera" << std::endl;
    std::cout << "  recuperar <indice>        Recuperar de papelera" << std::endl;
    std::cout << "  vaciarpapelera            Vaciar papelera" << std::endl;
    std::cout << "  pwd                       Mostrar ruta actual" << std::endl;
    std::cout << "  info                      Informacion del sistema" << std::endl;
    std::cout << "  ayuda                     Mostrar esta ayuda" << std::endl;
    std::cout << "  salir                     Salir del programa" << std::endl;
    std::cout << std::endl;
}
