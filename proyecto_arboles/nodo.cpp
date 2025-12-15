// nodo.cpp
#include "nodo.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>

NodoAvanzado::NodoAvanzado(int id, std::string nombre, std::string tipo, 
                          std::shared_ptr<NodoAvanzado> padre) 
    : id(id), nombre(nombre), tipo(tipo), padre(padre), tamaño(0), oculto(false) {
    
    time_t ahora = time(nullptr);
    fechaCreacion = ahora;
    fechaModificacion = ahora;
    
    if (tipo == "carpeta") {
        contenido = "";
    }
}

void NodoAvanzado::agregarHijo(std::shared_ptr<NodoAvanzado> hijo) {
    hijos.push_back(hijo);
    hijo->padre = shared_from_this();
    actualizarFechaModificacion();
    actualizarTamaño();
    actualizarFechaAcceso();
}

bool NodoAvanzado::eliminarHijo(std::string nombreHijo) {
    auto it = std::find_if(hijos.begin(), hijos.end(), 
        [&nombreHijo](const std::shared_ptr<NodoAvanzado>& nodo) {
            return nodo->nombre == nombreHijo;
        });
    
    if (it != hijos.end()) {
        hijos.erase(it);
        actualizarFechaModificacion();
        actualizarTamaño();
        return true;
    }
    return false;
}

std::shared_ptr<NodoAvanzado> NodoAvanzado::buscarHijo(std::string nombreHijo, bool incluirOcultos) {
    for (auto& hijo : hijos) {
        if ((incluirOcultos || !hijo->oculto) && hijo->nombre == nombreHijo) {
            return hijo;
        }
    }
    return nullptr;
}

std::string NodoAvanzado::obtenerRutaCompleta() const {
    std::vector<std::string> partes;
    std::shared_ptr<const NodoAvanzado> actual = shared_from_this();
    
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

std::string NodoAvanzado::obtenerInfo() const {
    std::stringstream ss;
    ss << nombre << " [" << tipo << "] ";
    ss << "Tamaño: " << formatoTamaño(tamaño) << " ";
    
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&fechaModificacion));
    ss << "Modificado: " << buffer;
    
    if (oculto) {
        ss << " [OCULTO]";
    }
    
    return ss.str();
}

void NodoAvanzado::actualizarFechaModificacion() {
    fechaModificacion = time(nullptr);
    if (padre) {
        padre->actualizarFechaModificacion();
    }
}

void NodoAvanzado::actualizarFechaAcceso() {
    // Para implementación futura
}

void NodoAvanzado::actualizarTamaño() {
    if (tipo == "archivo") {
        tamaño = contenido.size();
    } else {
        tamaño = 0;
        for (auto& hijo : hijos) {
            tamaño += hijo->tamaño;
        }
    }
    
    if (padre) {
        padre->actualizarTamaño();
    }
}

bool NodoAvanzado::setContenido(const std::string& nuevoContenido) {
    if (tipo != "archivo") {
        return false;
    }
    
    contenido = nuevoContenido;
    actualizarFechaModificacion();
    actualizarTamaño();
    return true;
}

void NodoAvanzado::marcarOculto(bool esOculto) {
    oculto = esOculto;
    actualizarFechaModificacion();
}

std::string NodoAvanzado::formatoTamaño(size_t bytes) const {
    const char* unidades[] = {"B", "KB", "MB", "GB"};
    int unidad = 0;
    double tamaño = bytes;
    
    while (tamaño >= 1024 && unidad < 3) {
        tamaño /= 1024;
        unidad++;
    }
    
    std::stringstream ss;
    if (unidad == 0) {
        ss << bytes << " " << unidades[unidad];
    } else {
        ss << std::fixed << std::setprecision(2) << tamaño << " " << unidades[unidad];
    }
    return ss.str();
}
