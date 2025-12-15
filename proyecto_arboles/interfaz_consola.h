#ifndef INTERFAZ_CONSOLA_H_INCLUDED
#define INTERFAZ_CONSOLA_H_INCLUDED

// interfaz_consola.hpp

#include <string>
#include <vector>
#include "sistema_archivos.h"

class InterfazCompleta {
private:
    SistemaCompleto sistema;
    bool ejecutando;
    std::vector<std::string> historial;
    
    void procesarComando(const std::string& comandoLinea);
    std::vector<std::string> parsearComando(const std::string& comandoLinea);
    void mostrarBanner();
    void mostrarAyudaInicial();
    void mostrarPrompt();
    void agregarAlHistorial(const std::string& comando);
    void mostrarHistorial();
    
public:
    InterfazCompleta();
    void iniciar();
    
    // Comandos específicos
    void ejecutarDemo();
};

#endif // INTERFAZ_CONSOLA_H_INCLUDED

