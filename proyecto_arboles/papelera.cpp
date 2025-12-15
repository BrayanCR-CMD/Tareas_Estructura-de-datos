// papelera.cpp
#include "papelera.h"
#include "nodo.h"
#include <iostream>

void Papelera::agregar(std::shared_ptr<Nodo> nodo, std::shared_ptr<Nodo> padre, int posicion) {
    if (elementos.size() >= MAX_ELEMENTOS) {
        elementos.erase(elementos.begin());
    }

    ElementoPapelera elem;
    elem.nodo = nodo;
    elem.padreOriginal = padre;
    elem.posicionOriginal = posicion;
    elementos.push_back(elem);
}

void Papelera::listar() {
    if (elementos.empty()) {
        std::cout << "Papelera vacia." << std::endl;
        return;
    }

    std::cout << "Elementos en la papelera:" << std::endl;
    for (size_t i = 0; i < elementos.size(); i++) {
        std::cout << i + 1 << ". " << elementos[i].nodo->nombre
                 << " (" << elementos[i].nodo->tipo << ")" << std::endl;
    }
}

bool Papelera::recuperar(int indice) {
    if (indice < 1 || indice > elementos.size()) {
        std::cout << "Índice inválido." << std::endl;
        return false;
    }

    ElementoPapelera elem = elementos[indice - 1];

    if (elem.padreOriginal && elem.posicionOriginal >= 0) {
        elem.padreOriginal->hijos.insert(
            elem.padreOriginal->hijos.begin() + elem.posicionOriginal,
            elem.nodo
        );
        elem.nodo->padre = elem.padreOriginal;
        std::cout << "Recuperado: " << elem.nodo->nombre << std::endl;

        elementos.erase(elementos.begin() + (indice - 1));
        return true;
    }

    return false;
}

void Papelera::vaciar() {
    elementos.clear();
    std::cout << "Papelera vaciada." << std::endl;
}
