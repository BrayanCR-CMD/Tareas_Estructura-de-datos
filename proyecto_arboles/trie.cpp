// trie.cpp

#include "trie.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <map>
#include <ctime>

NodoTrieAvanzado::NodoTrieAvanzado() : esFinDePalabra(false), frecuencia(0), ultimoAcceso(0) {}

TrieAvanzado::TrieAvanzado() : raiz(std::make_shared<NodoTrieAvanzado>()), 
                              totalPalabras(0), totalConsultas(0), aciertosCache(0) {}

void TrieAvanzado::insertar(const std::string& palabra, int idNodo) {
    std::shared_ptr<NodoTrieAvanzado> actual = raiz;
    
    for (char c : palabra) {
        char cLower = std::tolower(c);
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            actual->hijos[cLower] = std::make_shared<NodoTrieAvanzado>();
        }
        actual = actual->hijos[cLower];
    }
    
    if (!actual->esFinDePalabra) {
        totalPalabras++;
    }
    
    actual->esFinDePalabra = true;
    actual->idsNodos.push_back(idNodo);
    actual->frecuencia++;
    actual->ultimoAcceso = time(nullptr);
}

void TrieAvanzado::eliminar(const std::string& palabra, int idNodo) {
    std::shared_ptr<NodoTrieAvanzado> actual = raiz;
    
    for (char c : palabra) {
        char cLower = std::tolower(c);
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            return;
        }
        actual = actual->hijos[cLower];
    }
    
    if (actual->esFinDePalabra) {
        auto it = std::find(actual->idsNodos.begin(), actual->idsNodos.end(), idNodo);
        if (it != actual->idsNodos.end()) {
            actual->idsNodos.erase(it);
            actual->frecuencia = std::max(0, actual->frecuencia - 1);
        }
        
        if (actual->idsNodos.empty()) {
            actual->esFinDePalabra = false;
            totalPalabras--;
        }
    }
}

std::vector<int> TrieAvanzado::buscarPrefijo(const std::string& prefijo, int limite) {
    totalConsultas++;
    
    // Cache simple
    static std::map<std::string, std::pair<std::vector<int>, time_t>> cache;
    static const int CACHE_SIZE = 100;
    static const int CACHE_TTL = 60;
    
    auto ahora = time(nullptr);
    auto itCache = cache.find(prefijo);
    if (itCache != cache.end()) {
        if (difftime(ahora, itCache->second.second) < CACHE_TTL) {
            aciertosCache++;
            return itCache->second.first;
        } else {
            cache.erase(itCache);
        }
    }
    
    std::vector<int> resultados;
    std::shared_ptr<NodoTrieAvanzado> actual = raiz;
    
    for (char c : prefijo) {
        char cLower = std::tolower(c);
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            if (cache.size() >= CACHE_SIZE) {
                cache.erase(cache.begin());
            }
            cache[prefijo] = {resultados, ahora};
            return resultados;
        }
        actual = actual->hijos[cLower];
    }
    
    std::vector<std::pair<int, std::pair<int, time_t>>> resultadosConPrioridad;
    recogerIDsConPrioridad(actual, resultadosConPrioridad);
    
    std::sort(resultadosConPrioridad.begin(), resultadosConPrioridad.end(),
        [](const std::pair<int, std::pair<int, time_t>>& a, 
           const std::pair<int, std::pair<int, time_t>>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second.second > b.second.second;
        });
    
    for (int i = 0; i < std::min((int)resultadosConPrioridad.size(), limite); i++) {
        resultados.push_back(resultadosConPrioridad[i].second.first);
    }
    
    if (cache.size() >= CACHE_SIZE) {
        cache.erase(cache.begin());
    }
    cache[prefijo] = {resultados, ahora};
    
    return resultados;
}

std::vector<int> TrieAvanzado::buscarAproximado(const std::string& palabra, int distanciaMaxima) {
    std::vector<int> resultados;
    
    for (size_t i = 1; i <= palabra.length(); i++) {
        std::string prefijo = palabra.substr(0, i);
        auto parcial = buscarPrefijo(prefijo, 5);
        resultados.insert(resultados.end(), parcial.begin(), parcial.end());
    }
    
    std::sort(resultados.begin(), resultados.end());
    resultados.erase(std::unique(resultados.begin(), resultados.end()), resultados.end());
    
    return resultados;
}

std::vector<std::string> TrieAvanzado::obtenerSugerencias(const std::string& prefijo, int maxSugerencias) {
    std::vector<std::string> sugerencias;
    std::shared_ptr<NodoTrieAvanzado> actual = raiz;
    
    for (char c : prefijo) {
        char cLower = std::tolower(c);
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            return sugerencias;
        }
        actual = actual->hijos[cLower];
    }
    
    recogerPalabras(actual, prefijo, sugerencias, maxSugerencias);
    return sugerencias;
}

void TrieAvanzado::mostrarMetricas() const {
    std::cout << "=== MÉTRICAS TRIE ===" << std::endl;
    std::cout << "Total palabras indexadas: " << totalPalabras << std::endl;
    std::cout << "Total consultas: " << totalConsultas << std::endl;
    std::cout << "Aciertos en cache: " << aciertosCache << " (" 
             << (totalConsultas > 0 ? (aciertosCache * 100 / totalConsultas) : 0) << "%)" << std::endl;
    std::cout << "Tamaño estimado en memoria: " << estimarMemoria() << " nodos Trie" << std::endl;
}

std::vector<int> TrieAvanzado::buscarPrefijoPerformance(const std::string& prefijo, int& pasos) {
    pasos = 0;
    std::vector<int> resultados;
    std::shared_ptr<NodoTrieAvanzado> actual = raiz;
    
    for (char c : prefijo) {
        char cLower = std::tolower(c);
        pasos++;
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            return resultados;
        }
        actual = actual->hijos[cLower];
    }
    
    recogerIDsContando(actual, resultados, pasos);
    return resultados;
}

// Métodos privados
void TrieAvanzado::recogerIDsConPrioridad(std::shared_ptr<NodoTrieAvanzado> nodo, 
                                         std::vector<std::pair<int, std::pair<int, time_t>>>& resultados) {
    if (nodo->esFinDePalabra) {
        for (int id : nodo->idsNodos) {
            resultados.push_back({nodo->frecuencia, {id, nodo->ultimoAcceso}});
        }
    }
    
    for (auto& par : nodo->hijos) {
        recogerIDsConPrioridad(par.second, resultados);
    }
}

void TrieAvanzado::recogerIDsContando(std::shared_ptr<NodoTrieAvanzado> nodo, 
                                     std::vector<int>& resultados, int& pasos) {
    pasos++;
    if (nodo->esFinDePalabra) {
        resultados.insert(resultados.end(), nodo->idsNodos.begin(), nodo->idsNodos.end());
    }
    
    for (auto& par : nodo->hijos) {
        recogerIDsContando(par.second, resultados, pasos);
    }
}

void TrieAvanzado::recogerPalabras(std::shared_ptr<NodoTrieAvanzado> nodo, 
                                  std::string palabraActual, 
                                  std::vector<std::string>& palabras, int limite) {
    if (palabras.size() >= limite) return;
    
    if (nodo->esFinDePalabra) {
        palabras.push_back(palabraActual);
    }
    
    for (auto& par : nodo->hijos) {
        recogerPalabras(par.second, palabraActual + par.first, palabras, limite);
    }
}

int TrieAvanzado::estimarMemoria() const {
    return estimarMemoriaRecursivo(raiz);
}

int TrieAvanzado::estimarMemoriaRecursivo(std::shared_ptr<NodoTrieAvanzado> nodo) const {
    int total = 1;
    
    for (auto& par : nodo->hijos) {
        total += estimarMemoriaRecursivo(par.second);
    }
    
    return total;
}

