#ifndef INTERFAZ_CONSOLA_H_INCLUDED
#define INTERFAZ_CONSOLA_H_INCLUDED

// interfaz_consola.hpp

#include <string>
#include <vector>
#include "sistema_archivos.h"

class InterfazConsola {
private:
    SistemaArchivos sistema;
    bool ejecutando;

    void procesarComando(const std::string& comandoLinea);
    std::vector<std::string> dividirComando(const std::string& comandoLinea);
    void mostrarAyuda();

public:
    InterfazConsola();
    void iniciar();
};

#endif // INTERFAZ_CONSOLA_H_INCLUDED
