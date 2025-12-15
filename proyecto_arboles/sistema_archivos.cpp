// sistema_archivos.cpp
#include "sistema_archivos.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

SistemaArchivos::SistemaArchivos() : siguienteID(1) {
    raiz = std::make_shared<Nodo>(0, "raiz", "carpeta");
    directorioActual = raiz;
    mapaNodos[0] = raiz;
}

// ============ MÉTODOS AUXILIARES PRIVADOS ============

std::shared_ptr<Nodo> SistemaArchivos::obtenerNodoDesdeRuta(const std::string& ruta) {
    if (ruta.empty()) {
        return directorioActual;
    }

    if (ruta[0] == '/') {
        return obtenerNodoDesdeRutaRelativa(raiz, ruta.substr(1));
    } else {
        return obtenerNodoDesdeRutaRelativa(directorioActual, ruta);
    }
}

std::shared_ptr<Nodo> SistemaArchivos::obtenerNodoDesdeRutaRelativa(std::shared_ptr<Nodo> nodoBase, const std::string& ruta) {
    if (ruta.empty()) {
        return nodoBase;
    }

    std::vector<std::string> partes = dividirRuta(ruta);
    std::shared_ptr<Nodo> actual = nodoBase;

    for (const std::string& parte : partes) {
        if (parte == ".") {
            continue;
        } else if (parte == "..") {
            if (actual->padre) {
                actual = actual->padre;
            } else {
                return nullptr;
            }
        } else {
            actual = actual->buscarHijo(parte);
            if (!actual) {
                return nullptr;
            }
        }
    }

    return actual;
}

bool SistemaArchivos::esDescendiente(std::shared_ptr<Nodo> posibleDescendiente, std::shared_ptr<Nodo> ancestro) {
    std::shared_ptr<Nodo> actual = posibleDescendiente;

    while (actual) {
        if (actual == ancestro) {
            return true;
        }
        actual = actual->padre;
    }

    return false;
}

std::vector<std::shared_ptr<Nodo>> SistemaArchivos::obtenerTodosNodos() {
    std::vector<std::shared_ptr<Nodo>> resultado;
    std::queue<std::shared_ptr<Nodo>> cola;

    cola.push(raiz);

    while (!cola.empty()) {
        std::shared_ptr<Nodo> actual = cola.front();
        cola.pop();

        if (actual->id != 0) {
            resultado.push_back(actual);
        }

        for (auto& hijo : actual->hijos) {
            cola.push(hijo);
        }
    }

    return resultado;
}

std::vector<std::string> SistemaArchivos::dividirRuta(const std::string& ruta) {
    std::vector<std::string> partes;
    std::string parteActual;

    for (char c : ruta) {
        if (c == '/') {
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

std::string SistemaArchivos::escapeJSON(const std::string& texto) {
    std::string resultado;

    for (char c : texto) {
        switch (c) {
            case '"': resultado += "\\\""; break;
            case '\\': resultado += "\\\\"; break;
            case '\n': resultado += "\\n"; break;
            case '\r': resultado += "\\r"; break;
            case '\t': resultado += "\\t"; break;
            default: resultado += c; break;
        }
    }

    return resultado;
}

void SistemaArchivos::recorridoPreorden(std::shared_ptr<Nodo> nodo, std::vector<std::string>& resultado) {
    if (!nodo) return;

    resultado.push_back(nodo->obtenerRutaCompleta());

    for (auto& hijo : nodo->hijos) {
        recorridoPreorden(hijo, resultado);
    }
}

void SistemaArchivos::actualizarIndices(std::shared_ptr<Nodo> nodo, bool agregar) {
    if (agregar) {
        trieNombres.insertar(nodo->nombre, nodo->id);
        mapaNodos[nodo->id] = nodo;
    } else {
        trieNombres.eliminar(nodo->nombre, nodo->id);
        mapaNodos.erase(nodo->id);
    }
}

// ============ OPERACIONES PRINCIPALES ============

void SistemaArchivos::mkdir(const std::string& nombre, const std::string& ruta) {
    std::shared_ptr<Nodo> destino = obtenerNodoDesdeRuta(ruta);

    if (!destino) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }

    if (destino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }

    if (destino->buscarHijo(nombre)) {
        std::cout << "Ya existe un elemento con ese nombre." << std::endl;
        return;
    }

    std::shared_ptr<Nodo> nuevaCarpeta = std::make_shared<Nodo>(siguienteID++, nombre, "carpeta", destino);
    destino->agregarHijo(nuevaCarpeta);
    actualizarIndices(nuevaCarpeta, true);

    std::cout << "Carpeta '" << nombre << "' creada." << std::endl;
}

void SistemaArchivos::touch(const std::string& nombre, const std::string& ruta) {
    std::shared_ptr<Nodo> destino = obtenerNodoDesdeRuta(ruta);

    if (!destino) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }

    if (destino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }

    if (destino->buscarHijo(nombre)) {
        std::cout << "Ya existe un elemento con ese nombre." << std::endl;
        return;
    }

    std::shared_ptr<Nodo> nuevoArchivo = std::make_shared<Nodo>(siguienteID++, nombre, "archivo", destino);
    destino->agregarHijo(nuevoArchivo);
    actualizarIndices(nuevoArchivo, true);

    std::cout << "Archivo '" << nombre << "' creado." << std::endl;
}

void SistemaArchivos::ls(const std::string& ruta) {
    std::shared_ptr<Nodo> destino = obtenerNodoDesdeRuta(ruta);

    if (!destino) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }

    if (destino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }

    if (destino->hijos.empty()) {
        std::cout << "Directorio vacio." << std::endl;
        return;
    }

    std::cout << "Contenido de " << destino->nombre << ":" << std::endl;
    for (size_t i = 0; i < destino->hijos.size(); i++) {
        std::string tipo = destino->hijos[i]->tipo == "carpeta" ? "[DIR]" : "[FILE]";
        std::cout << "  " << i + 1 << ". " << tipo << " " << destino->hijos[i]->nombre << std::endl;
    }
}

void SistemaArchivos::cd(const std::string& ruta) {
    if (ruta.empty()) {
        directorioActual = raiz;
        std::cout << "Directorio cambiado a raiz." << std::endl;
        return;
    }

    if (ruta == "..") {
        if (directorioActual->padre) {
            directorioActual = directorioActual->padre;
            std::cout << "Directorio cambiado a: " << directorioActual->nombre << std::endl;
        } else {
            std::cout << "Ya estás en la raiz." << std::endl;
        }
        return;
    }

    std::shared_ptr<Nodo> destino = obtenerNodoDesdeRuta(ruta);

    if (!destino) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }

    if (destino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }

    directorioActual = destino;
    std::cout << "Directorio cambiado a: " << directorioActual->nombre << std::endl;
}

void SistemaArchivos::mv(const std::string& origen, const std::string& destino) {
    std::shared_ptr<Nodo> nodoOrigen = obtenerNodoDesdeRuta(origen);
    std::shared_ptr<Nodo> nodoDestino = obtenerNodoDesdeRuta(destino);

    if (!nodoOrigen || !nodoDestino) {
        std::cout << "Ruta(s) no válida(s)." << std::endl;
        return;
    }

    if (nodoDestino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }

    if (esDescendiente(nodoDestino, nodoOrigen)) {
        std::cout << "No se puede mover una carpeta dentro de si misma." << std::endl;
        return;
    }

    if (nodoDestino->buscarHijo(nodoOrigen->nombre)) {
        std::cout << "Ya existe un elemento con ese nombre en el destino." << std::endl;
        return;
    }

    std::shared_ptr<Nodo> padreActual = nodoOrigen->padre;
    int posicion = -1;

    for (size_t i = 0; i < padreActual->hijos.size(); i++) {
        if (padreActual->hijos[i] == nodoOrigen) {
            posicion = i;
            break;
        }
    }

    if (posicion != -1) {
        padreActual->hijos.erase(padreActual->hijos.begin() + posicion);
        nodoDestino->agregarHijo(nodoOrigen);
        nodoOrigen->padre = nodoDestino;

        std::cout << "Movido '" << nodoOrigen->nombre << "' a '" << nodoDestino->nombre << "'" << std::endl;
    }
}

void SistemaArchivos::renombrar(const std::string& ruta, const std::string& nuevoNombre) {
    std::shared_ptr<Nodo> nodo = obtenerNodoDesdeRuta(ruta);

    if (!nodo) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }

    if (nodo->padre) {
        for (auto& hermano : nodo->padre->hijos) {
            if (hermano != nodo && hermano->nombre == nuevoNombre) {
                std::cout << "Ya existe un elemento con ese nombre." << std::endl;
                return;
            }
        }
    }

    trieNombres.eliminar(nodo->nombre, nodo->id);
    trieNombres.insertar(nuevoNombre, nodo->id);

    std::string nombreAntiguo = nodo->nombre;
    nodo->nombre = nuevoNombre;

    std::cout << "Renombrado '" << nombreAntiguo << "' a '" << nuevoNombre << "'" << std::endl;
}

void SistemaArchivos::rm(const std::string& ruta) {
    std::shared_ptr<Nodo> nodo = obtenerNodoDesdeRuta(ruta);

    if (!nodo) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }

    if (nodo == raiz) {
        std::cout << "No se puede eliminar la raiz." << std::endl;
        return;
    }

    std::shared_ptr<Nodo> padre = nodo->padre;
    int posicion = -1;

    for (size_t i = 0; i < padre->hijos.size(); i++) {
        if (padre->hijos[i] == nodo) {
            posicion = i;
            break;
        }
    }

    if (posicion != -1) {
        papelera.agregar(nodo, padre, posicion);
        padre->hijos.erase(padre->hijos.begin() + posicion);
        actualizarIndices(nodo, false);

        std::cout << "Eliminado '" << nodo->nombre << "' (enviado a papelera)" << std::endl;
    }
}

// ============ BÚSQUEDA ============

void SistemaArchivos::buscarPrefijo(const std::string& prefijo) {
    if (prefijo.empty()) {
        std::cout << "Prefijo no puede estar vacio." << std::endl;
        return;
    }

    std::vector<int> ids = trieNombres.buscarPrefijo(prefijo);

    if (ids.empty()) {
        std::cout << "No se encontraron elementos con el prefijo '" << prefijo << "'" << std::endl;
        return;
    }

    std::cout << "Resultados para '" << prefijo << "':" << std::endl;
    for (int id : ids) {
        auto it = mapaNodos.find(id);
        if (it != mapaNodos.end()) {
            std::shared_ptr<Nodo> nodo = it->second;
            std::string tipo = nodo->tipo == "carpeta" ? "[DIR]" : "[FILE]";
            std::cout << "  " << tipo << " " << nodo->obtenerRutaCompleta() << std::endl;
        }
    }
}

// ============ EXPORTACIÓN ============

void SistemaArchivos::exportarPreorden(const std::string& rutaArchivo, const std::string& rutaInicio) {
    std::shared_ptr<Nodo> inicio = rutaInicio.empty() ? raiz : obtenerNodoDesdeRuta(rutaInicio);

    if (!inicio) {
        std::cout << "Ruta de inicio no valida." << std::endl;
        return;
    }

    std::vector<std::string> recorrido;
    recorridoPreorden(inicio, recorrido);

    std::ofstream archivo(rutaArchivo);
    if (!archivo) {
        std::cout << "Error al crear el archivo." << std::endl;
        return;
    }

    for (const std::string& linea : recorrido) {
        archivo << linea << std::endl;
    }

    archivo.close();
    std::cout << "Recorrido en preorden exportado a '" << rutaArchivo << "' ("
             << recorrido.size() << " elementos)" << std::endl;
}

// ============ PERSISTENCIA ============

void SistemaArchivos::guardarJSON(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cout << "Error al crear el archivo JSON." << std::endl;
        return;
    }

    archivo << "{\n";
    archivo << "  \"sistema\": {\n";
    archivo << "    \"siguienteID\": " << siguienteID << ",\n";
    archivo << "    \"directorioActualID\": " << directorioActual->id << "\n";
    archivo << "  },\n";
    archivo << "  \"nodos\": [\n";

    std::vector<std::shared_ptr<Nodo>> todosNodos = obtenerTodosNodos();

    for (size_t i = 0; i < todosNodos.size(); i++) {
        std::shared_ptr<Nodo> nodo = todosNodos[i];

        archivo << "    {\n";
        archivo << "      \"id\": " << nodo->id << ",\n";
        archivo << "      \"nombre\": \"" << escapeJSON(nodo->nombre) << "\",\n";
        archivo << "      \"tipo\": \"" << nodo->tipo << "\",\n";
        archivo << "      \"contenido\": \"" << escapeJSON(nodo->contenido) << "\",\n";
        archivo << "      \"padreID\": " << (nodo->padre ? nodo->padre->id : -1) << "\n";
        archivo << "    }";

        if (i < todosNodos.size() - 1) {
            archivo << ",";
        }
        archivo << "\n";
    }

    archivo << "  ]\n";
    archivo << "}\n";

    archivo.close();
    std::cout << "Sistema guardado en '" << nombreArchivo << "'" << std::endl;
}

void SistemaArchivos::cargarJSON(const std::string& nombreArchivo) {
    std::cout << "Funcion cargarJSON implementada parcialmente en MVP." << std::endl;
    std::cout << "Se cargara una estructura basica por defecto." << std::endl;

    // Reiniciar sistema
    raiz = std::make_shared<Nodo>(0, "raiz", "carpeta");
    directorioActual = raiz;
    mapaNodos.clear();
    mapaNodos[0] = raiz;
    siguienteID = 1;
    trieNombres = Trie();
    papelera = Papelera();

    // Crear estructura básica
    mkdir("Documentos");
    mkdir("Imagenes");
    touch("lectura.txt", "Documentos");

    std::cout << "Estructura básica cargada." << std::endl;
}

// ============ OPERACIONES PAPELERA ============

void SistemaArchivos::mostrarPapelera() {
    papelera.listar();
}

void SistemaArchivos::recuperarPapelera(int indice) {
    papelera.recuperar(indice);
}

void SistemaArchivos::vaciarPapelera() {
    papelera.vaciar();
}

// ============ INFORMACIÓN ============

void SistemaArchivos::pwd() {
    std::cout << "Directorio actual: " << directorioActual->obtenerRutaCompleta() << std::endl;
}

void SistemaArchivos::info() {
    int totalNodos = mapaNodos.size() - 1;
    int carpetas = 0;
    int archivos = 0;

    for (auto& par : mapaNodos) {
        if (par.second->tipo == "carpeta") carpetas++;
        else if (par.second->tipo == "archivo") archivos++;
    }

    std::cout << "=== Informacion del Sistema ===" << std::endl;
    std::cout << "Total nodos: " << totalNodos << std::endl;
    std::cout << "Carpetas: " << carpetas << std::endl;
    std::cout << "Archivos: " << archivos << std::endl;
    std::cout << "Próximo ID: " << siguienteID << std::endl;
}
