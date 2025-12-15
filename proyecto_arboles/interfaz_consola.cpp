// interfaz_consola.cpp
#include "interfaz_consola.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

InterfazCompleta::InterfazCompleta() : ejecutando(true) {}

void InterfazCompleta::iniciar() {
    mostrarBanner();
    mostrarAyudaInicial();
    
    while (ejecutando) {
        mostrarPrompt();
        std::string comandoLinea;
        std::getline(std::cin, comandoLinea);
        
        if (!comandoLinea.empty()) {
            agregarAlHistorial(comandoLinea);
            procesarComando(comandoLinea);
        }
    }
}

void InterfazCompleta::ejecutarDemo() {
    sistema.ejecutarDemo();
}

// Métodos privados
void InterfazCompleta::mostrarBanner() {
    std::cout << "╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║      SISTEMA DE GESTION DE ARBOLES - VERSIÓN FINAL   ║" << std::endl;
    std::cout << "║                                                      ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

void InterfazCompleta::mostrarAyudaInicial() {
    std::cout << "Escriba 'ayuda' para ver todos los comandos disponibles." << std::endl;
    std::cout << "Escriba 'demo' para ejecutar una demostracion completa." << std::endl;
    std::cout << "Escriba 'pruebas' para ejecutar pruebas de integracion." << std::endl;
    std::cout << std::endl;
}

void InterfazCompleta::mostrarPrompt() {
    std::cout << "fs> ";
}

void InterfazCompleta::agregarAlHistorial(const std::string& comando) {
    historial.push_back(comando);
}

void InterfazCompleta::procesarComando(const std::string& comandoLinea) {
    std::vector<std::string> partes = parsearComando(comandoLinea);
    
    if (partes.empty()) return;
    
    std::string cmd = partes[0];
    
    try {
        if (cmd == "mkdir") {
            if (partes.size() >= 2) {
                std::string ruta = partes.size() > 2 ? partes[2] : "";
                sistema.mkdir(partes[1], ruta);
            } else {
                std::cout << "Uso: mkdir <nombre> [ruta]" << std::endl;
            }
        }
        else if (cmd == "touch") {
            if (partes.size() >= 2) {
                std::string ruta = partes.size() > 2 ? partes[2] : "";
                std::string contenido = partes.size() > 3 ? partes[3] : "";
                sistema.touch(partes[1], ruta, contenido);
            } else {
                std::cout << "Uso: touch <nombre> [ruta] [contenido]" << std::endl;
            }
        }
        else if (cmd == "ls") {
            std::string ruta = "";
            bool detallado = false;
            bool recursivo = false;
            bool ocultos = false;
            
            for (size_t i = 1; i < partes.size(); i++) {
                if (partes[i] == "-l") detallado = true;
                else if (partes[i] == "-r") recursivo = true;
                else if (partes[i] == "-a") ocultos = true;
                else if (partes[i][0] != '-') ruta = partes[i];
            }
            
            sistema.ls(ruta, detallado, recursivo, ocultos);
        }
        else if (cmd == "cd") {
            std::string ruta = partes.size() > 1 ? partes[1] : "";
            sistema.cd(ruta);
        }
        else if (cmd == "mv") {
            if (partes.size() >= 3) {
                sistema.mv(partes[1], partes[2]);
            } else {
                std::cout << "Uso: mv <origen> <destino>" << std::endl;
            }
        }
        else if (cmd == "ren") {
            if (partes.size() >= 3) {
                bool forzar = false;
                for (size_t i = 3; i < partes.size(); i++) {
                    if (partes[i] == "-f") forzar = true;
                }
                sistema.renombrar(partes[1], partes[2], forzar);
            } else {
                std::cout << "Uso: ren <ruta> <nuevoNombre> [-f]" << std::endl;
            }
        }
        else if (cmd == "rm") {
            if (partes.size() >= 2) {
                bool forzar = false;
                std::string motivo = "";
                
                for (size_t i = 2; i < partes.size(); i++) {
                    if (partes[i] == "-f") forzar = true;
                    else if (partes[i].substr(0, 9) == "--motivo=") {
                        motivo = partes[i].substr(9);
                    }
                }
                
                sistema.rm(partes[1], forzar, motivo);
            } else {
                std::cout << "Uso: rm <ruta> [-f] [--motivo=texto]" << std::endl;
            }
        }
        else if (cmd == "buscar") {
            if (partes.size() >= 2) {
                std::string tipo = partes.size() > 2 ? partes[2] : "prefijo";
                sistema.buscar(partes[1], tipo);
            } else {
                std::cout << "Uso: buscar <texto> [prefijo|contenido]" << std::endl;
            }
        }
        else if (cmd == "autocompletar") {
            if (partes.size() >= 2) {
                sistema.autocompletar(partes[1]);
            } else {
                std::cout << "Uso: autocompletar <prefijo>" << std::endl;
            }
        }
        else if (cmd == "export") {
            if (partes.size() >= 2) {
                std::string ruta = partes.size() > 2 && partes[2][0] != '-' ? partes[2] : "";
                bool metadatos = false;
                
                for (size_t i = 2; i < partes.size(); i++) {
                    if (partes[i] == "-m") metadatos = true;
                }
                
                sistema.exportarPreorden(partes[1], ruta, metadatos);
            } else {
                std::cout << "Uso: export <archivo> [ruta] [-m]" << std::endl;
            }
        }
        else if (cmd == "guardar") {
            if (partes.size() >= 2) {
                sistema.guardarJSON(partes[1]);
            } else {
                std::cout << "Uso: guardar <archivo.json>" << std::endl;
            }
        }
        else if (cmd == "cargar") {
            if (partes.size() >= 2) {
                sistema.cargarJSON(partes[1]);
            } else {
                std::cout << "Uso: cargar <archivo.json>" << std::endl;
            }
        }
        else if (cmd == "papelera") {
            bool detallado = true;
            for (size_t i = 1; i < partes.size(); i++) {
                if (partes[i] == "-s") detallado = false;
            }
            sistema.mostrarPapelera(detallado);
        }
        else if (cmd == "recuperar") {
            if (partes.size() >= 2) {
                sistema.recuperarPapelera(partes[1]);
            } else {
                std::cout << "Uso: recuperar <indice|todos>" << std::endl;
            }
        }
        else if (cmd == "vaciarpapelera") {
            bool forzar = false;
            for (size_t i = 1; i < partes.size(); i++) {
                if (partes[i] == "-f") forzar = true;
            }
            sistema.vaciarPapelera(forzar);
        }
        else if (cmd == "pwd") {
            sistema.pwd();
        }
        else if (cmd == "info") {
            sistema.info();
        }
        else if (cmd == "metricas") {
            sistema.mostrarMetricas();
        }
        else if (cmd == "pruebas") {
            sistema.ejecutarPruebasIntegracion();
        }
        else if (cmd == "performance") {
            int tamaño = 1000;
            if (partes.size() >= 2) {
                try {
                    tamaño = std::stoi(partes[1]);
                } catch (...) {
                    std::cout << "Tamaño invalido, usando 1000 por defecto." << std::endl;
                }
            }
            sistema.ejecutarPruebaPerformance(tamaño);
        }
        else if (cmd == "consistencia") {
            sistema.verificarConsistencia();
        }
        else if (cmd == "demo") {
            ejecutarDemo();
        }
        else if (cmd == "ayuda") {
            sistema.ayuda();
        }
        else if (cmd == "historial") {
            mostrarHistorial();
        }
        else if (cmd == "clear" || cmd == "cls") {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        else if (cmd == "salir" || cmd == "exit") {
            std::cout << "¿Guardar antes de salir? (s/n): ";
            char respuesta;
            std::cin >> respuesta;
            std::cin.ignore();
            
            if (std::tolower(respuesta) == 's') {
                sistema.guardarJSON("backup_salida.json");
            }
            
            std::cout << "Saliendo..." << std::endl;
            ejecutando = false;
        }
        else {
            std::cout << "Comando no reconocido: '" << cmd << "'" << std::endl;
            std::cout << "Escriba 'ayuda' para ver comandos disponibles." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

std::vector<std::string> InterfazCompleta::parsearComando(const std::string& comandoLinea) {
    std::vector<std::string> partes;
    std::string parte;
    bool entreComillas = false;
    
    for (char c : comandoLinea) {
        if (c == '"') {
            entreComillas = !entreComillas;
        } else if (c == ' ' && !entreComillas) {
            if (!parte.empty()) {
                partes.push_back(parte);
                parte.clear();
            }
        } else {
            parte += c;
        }
    }
    
    if (!parte.empty()) {
        partes.push_back(parte);
    }
    
    return partes;
}

void InterfazCompleta::mostrarHistorial() {
    if (historial.empty()) {
        std::cout << "Historial vacio." << std::endl;
        return;
    }
    
    std::cout << "Historial de comandos:" << std::endl;
    for (size_t i = 0; i < historial.size(); i++) {
        std::cout << std::setw(3) << i + 1 << ": " << historial[i] << std::endl;
    }
}
