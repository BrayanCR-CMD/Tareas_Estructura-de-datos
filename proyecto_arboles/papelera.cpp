// papelera.cpp
#include "papelera.h"
#include "nodo.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <random>
#include <ctime>

PapeleraAvanzada::ElementoPapelera::ElementoPapelera(std::shared_ptr<NodoAvanzado> n, 
                                                    std::shared_ptr<NodoAvanzado> p, 
                                                    int pos, const std::string& mot)
    : nodo(n), padreOriginal(p), posicionOriginal(pos), motivo(mot) {
    fechaEliminacion = time(nullptr);
    tamaño = n->tamaño;
    
    if (n->tipo == "archivo") {
        fechaExpiracion = fechaEliminacion + (30 * 24 * 3600); // 30 días
    } else {
        fechaExpiracion = fechaEliminacion + (14 * 24 * 3600); // 14 días
    }
}

bool PapeleraAvanzada::ElementoPapelera::estaExpirado() const {
    return difftime(time(nullptr), fechaExpiracion) > 0;
}

double PapeleraAvanzada::ElementoPapelera::tiempoRestanteHoras() const {
    return difftime(fechaExpiracion, time(nullptr)) / 3600.0;
}

PapeleraAvanzada::PapeleraAvanzada() : capacidadMaximaBytes(100 * 1024 * 1024), 
                                      espacioUtilizado(0), maxElementos(100) {}

void PapeleraAvanzada::configurarLimites(size_t maxBytes, int maxElem) {
    capacidadMaximaBytes = maxBytes;
    maxElementos = maxElem;
    aplicarLimites();
}

bool PapeleraAvanzada::agregar(std::shared_ptr<NodoAvanzado> nodo, 
                              std::shared_ptr<NodoAvanzado> padre, 
                              int posicion, const std::string& motivo) {
    limpiarExpirados();
    
    if (elementos.size() >= maxElementos || 
        espacioUtilizado + nodo->tamaño > capacidadMaximaBytes) {
        if (!liberarEspacio(nodo->tamaño)) {
            std::cout << "Papelera llena. No se puede agregar '" << nodo->nombre << "'" << std::endl;
            return false;
        }
    }
    
    ElementoPapelera elem(nodo, padre, posicion, motivo);
    elementos.push_back(elem);
    espacioUtilizado += nodo->tamaño;
    
    std::cout << "Papelera: agregado '" << nodo->nombre << "' (" 
             << formatoTamaño(nodo->tamaño) << ")" << std::endl;
    std::cout << "  Espacio usado: " << formatoTamaño(espacioUtilizado) << " / " 
             << formatoTamaño(capacidadMaximaBytes) << std::endl;
    
    return true;
}

void PapeleraAvanzada::listarDetallado(bool mostrarExpirados) {
    limpiarExpirados();
    
    if (elementos.empty()) {
        std::cout << "Papelera vacia." << std::endl;
        return;
    }
    
    std::cout << "=== PAPELERA ===" << std::endl;
    std::cout << "Elementos: " << elementos.size() << " / " << maxElementos << std::endl;
    std::cout << "Espacio: " << formatoTamaño(espacioUtilizado) << " / " 
             << formatoTamaño(capacidadMaximaBytes) << std::endl;
    std::cout << "----------------" << std::endl;
    
    for (size_t i = 0; i < elementos.size(); i++) {
        const auto& elem = elementos[i];
        
        if (!mostrarExpirados && elem.estaExpirado()) {
            continue;
        }
        
        double horasRestantes = elem.tiempoRestanteHoras();
        
        std::cout << i + 1 << ". " << elem.nodo->nombre 
                 << " [" << elem.nodo->tipo << "]" << std::endl;
        std::cout << "    Tamaño: " << formatoTamaño(elem.tamaño) << std::endl;
        std::cout << "    Eliminado: " << formatearFecha(elem.fechaEliminacion) << std::endl;
        
        if (horasRestantes > 0) {
            std::cout << "    Expira en: " << std::fixed << std::setprecision(1) 
                     << horasRestantes << " horas" << std::endl;
        } else {
            std::cout << "    [EXPIRADO]" << std::endl;
        }
        
        std::cout << "    Motivo: " << elem.motivo << std::endl;
        std::cout << std::endl;
    }
}

bool PapeleraAvanzada::recuperar(int indice) {
    if (indice < 1 || indice > elementos.size()) {
        std::cout << "Indice invalido." << std::endl;
        return false;
    }
    
    ElementoPapelera& elem = elementos[indice - 1];
    
    if (elem.estaExpirado()) {
        std::cout << "No se puede recuperar: el elemento ha expirado." << std::endl;
        return false;
    }
    
    if (!elem.padreOriginal) {
        std::cout << "No se puede recuperar: el directorio padre ya no existe." << std::endl;
        return false;
    }
    
    if (elem.padreOriginal->buscarHijo(elem.nodo->nombre, true)) {
        std::cout << "Ya existe un elemento con el nombre '" << elem.nodo->nombre 
                 << "' en el directorio destino." << std::endl;
        return false;
    }
    
    elem.padreOriginal->hijos.insert(
        elem.padreOriginal->hijos.begin() + elem.posicionOriginal,
        elem.nodo
    );
    elem.nodo->padre = elem.padreOriginal;
    elem.nodo->actualizarFechaModificacion();
    
    espacioUtilizado -= elem.tamaño;
    
    std::cout << " Recuperado: " << elem.nodo->obtenerRutaCompleta() << std::endl;
    
    elementos.erase(elementos.begin() + (indice - 1));
    return true;
}

int PapeleraAvanzada::recuperarTodos() {
    int recuperados = 0;
    limpiarExpirados();
    
    for (int i = elementos.size(); i >= 1; i--) {
        if (recuperar(i)) {
            recuperados++;
        }
    }
    
    std::cout << "Recuperados " << recuperados << " elementos." << std::endl;
    return recuperados;
}

bool PapeleraAvanzada::vaciar(bool forzar) {
    if (elementos.empty()) {
        std::cout << "La papelera ya esta vacia." << std::endl;
        return true;
    }
    
    if (!forzar) {
        std::cout << "Esta a punto de eliminar " << elementos.size() 
                 << " elementos (" << formatoTamaño(espacioUtilizado) 
                 << ") permanentemente." << std::endl;
        std::cout << "¿Continuar? (s/n): ";
        char respuesta;
        std::cin >> respuesta;
        std::cin.ignore();
        
        if (std::tolower(respuesta) != 's') {
            std::cout << "Operacion cancelada." << std::endl;
            return false;
        }
    }
    
    int eliminados = elementos.size();
    elementos.clear();
    espacioUtilizado = 0;
    
    std::cout << "Papelera vaciada. " << eliminados << " elementos eliminados permanentemente." << std::endl;
    return true;
}

void PapeleraAvanzada::mostrarEstadisticas() {
    limpiarExpirados();
    
    int carpetas = 0;
    int archivos = 0;
    int expirados = 0;
    size_t tamañoExpirados = 0;
    
    auto ahora = time(nullptr);
    
    for (const auto& elem : elementos) {
        if (elem.nodo->tipo == "carpeta") {
            carpetas++;
        } else {
            archivos++;
        }
        
        if (elem.estaExpirado()) {
            expirados++;
            tamañoExpirados += elem.tamaño;
        }
    }
    
    std::cout << "=== ESTADISTICAS PAPELERA ===" << std::endl;
    std::cout << "Total elementos: " << elementos.size() << std::endl;
    std::cout << "  Carpetas: " << carpetas << std::endl;
    std::cout << "  Archivos: " << archivos << std::endl;
    std::cout << "  Expirados: " << expirados << " (" << formatoTamaño(tamañoExpirados) << ")" << std::endl;
    std::cout << "Espacio utilizado: " << formatoTamaño(espacioUtilizado) << std::endl;
    std::cout << "Limite: " << formatoTamaño(capacidadMaximaBytes) << " (" 
             << (capacidadMaximaBytes > 0 ? (espacioUtilizado * 100 / capacidadMaximaBytes) : 0) 
             << "%)" << std::endl;
    std::cout << "Limite elementos: " << elementos.size() << " / " << maxElementos 
             << " (" << (elementos.size() * 100 / std::max(maxElementos, 1)) << "%)" << std::endl;
}

void PapeleraAvanzada::llenarConDatosAleatorios(int cantidad) {
    std::cout << "Generando " << cantidad << " elementos aleatorios para papelera..." << std::endl;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> tipoDist(0, 1);
    std::uniform_int_distribution<> tamañoDist(100, 10000);
    
    for (int i = 0; i < cantidad; i++) {
        std::string nombre = "test_" + std::to_string(i) + (tipoDist(gen) ? ".txt" : "");
        std::string tipo = tipoDist(gen) ? "archivo" : "carpeta";
        
        auto nodo = std::make_shared<NodoAvanzado>(i + 1000, nombre, tipo);
        
        if (tipo == "archivo") {
            std::string contenido(tamañoDist(gen), 'X');
            nodo->setContenido(contenido);
        }
        
        auto padre = std::make_shared<NodoAvanzado>(999, "temp", "carpeta");
        agregar(nodo, padre, 0, "Prueba de performance");
    }
    
    std::cout << "Papelera llena con " << cantidad << " elementos." << std::endl;
}

// Métodos privados
bool PapeleraAvanzada::liberarEspacio(size_t espacioNecesario) {
    std::sort(elementos.begin(), elementos.end(),
        [](const ElementoPapelera& a, const ElementoPapelera& b) {
            return a.fechaExpiracion < b.fechaExpiracion;
        });
    
    size_t espacioLiberado = 0;
    int eliminados = 0;
    
    while (!elementos.empty() && 
           (elementos.size() >= maxElementos || 
            espacioUtilizado - espacioLiberado + espacioNecesario > capacidadMaximaBytes)) {
        espacioLiberado += elementos.front().tamaño;
        eliminados++;
        elementos.erase(elementos.begin());
    }
    
    if (eliminados > 0) {
        espacioUtilizado -= espacioLiberado;
        std::cout << "Papelera: liberados " << eliminados 
                 << " elementos más antiguos (" << formatoTamaño(espacioLiberado) << ")" << std::endl;
    }
    
    return (elementos.size() < maxElementos && 
            espacioUtilizado + espacioNecesario <= capacidadMaximaBytes);
}

void PapeleraAvanzada::aplicarLimites() {
    while (elementos.size() > maxElementos || espacioUtilizado > capacidadMaximaBytes) {
        if (elementos.empty()) break;
        
        espacioUtilizado -= elementos.front().tamaño;
        elementos.erase(elementos.begin());
    }
}

void PapeleraAvanzada::limpiarExpirados() {
    auto ahora = time(nullptr);
    size_t espacioLiberado = 0;
    int eliminados = 0;
    
    auto it = std::remove_if(elementos.begin(), elementos.end(),
        [&espacioLiberado, &eliminados, ahora](const ElementoPapelera& elem) {
            if (difftime(ahora, elem.fechaExpiracion) > 0) {
                espacioLiberado += elem.tamaño;
                eliminados++;
                return true;
            }
            return false;
        });
    
    if (it != elementos.end()) {
        elementos.erase(it, elementos.end());
        espacioUtilizado -= espacioLiberado;
        
        if (eliminados > 0) {
            std::cout << "Papelera: limpiados " << eliminados 
                     << " elementos expirados (" << formatoTamaño(espacioLiberado) << ")" << std::endl;
        }
    }
}

std::string PapeleraAvanzada::formatoTamaño(size_t bytes) {
    const char* unidades[] = {"B", "KB", "MB", "GB"};
    int unidad = 0;
    double tamaño = bytes;
    
    while (tamaño >= 1024 && unidad < 3) {
        tamaño /= 1024;
        unidad++;
    }
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << tamaño << " " << unidades[unidad];
    return ss.str();
}

std::string PapeleraAvanzada::formatearFecha(time_t tiempo) {
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&tiempo));
    return std::string(buffer);
}
