#ifndef PAPELERA_H_INCLUDED
#define PAPELERA_H_INCLUDED

// papelera.hpp

#include <memory>
#include <vector>
#include <string>

// Declaración anticipada para evitar dependencia circular
class Nodo;

class Papelera {
private:
    struct ElementoPapelera {
        std::shared_ptr<Nodo> nodo;
        std::shared_ptr<Nodo> padreOriginal;
        int posicionOriginal;
    };

    std::vector<ElementoPapelera> elementos;
    static const int MAX_ELEMENTOS = 10;

public:
    void agregar(std::shared_ptr<Nodo> nodo, std::shared_ptr<Nodo> padre, int posicion);
    void listar();
    bool recuperar(int indice);
    void vaciar();
};

#endif // PAPELERA_H_INCLUDED
