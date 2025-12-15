// nodo.cpp
#include "nodo.h"
#include <algorithm>

Nodo::Nodo(int id, std::string nombre, std::string tipo, std::shared_ptr<Nodo> padre)
    : id(id), nombre(nombre), tipo(tipo), padre(padre) {
    if (tipo == "carpeta") {
        contenido = "";
    }
}

void Nodo::agregarHijo(std::shared_ptr<Nodo> hijo) {
    hijos.push_back(hijo);
    hijo->padre = shared_from_this();
}

bool Nodo::eliminarHijo(std::string nombreHijo) {
    auto it = std::find_if(hijos.begin(), hijos.end(),
        [&nombreHijo](const std::shared_ptr<Nodo>& nodo) {
            return nodo->nombre == nombreHijo;
        });

    if (it != hijos.end()) {
        hijos.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Nodo> Nodo::buscarHijo(std::string nombreHijo) {
    for (auto& hijo : hijos) {
        if (hijo->nombre == nombreHijo) {
            return hijo;
        }
    }
    return nullptr;
}

std::string Nodo::obtenerRutaCompleta() {
    std::vector<std::string> partes;
    std::shared_ptr<Nodo> actual = shared_from_this();

    while (actual != nullptr) {
        partes.push_back(actual->nombre);
        actual = actual->padre;
    }

    std::reverse(partes.begin(), partes.end());
    std::string ruta;
    for (size_t i = 0; i < partes.size(); i++) {
        ruta += partes[i];
        if (i < partes.size() - 1) {
            ruta += "/";
        }
    }
    return ruta;
}
