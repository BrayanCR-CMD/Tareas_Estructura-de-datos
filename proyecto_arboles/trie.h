#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

// trie

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>

class NodoTrieAvanzado {
public:
    std::unordered_map<char, std::shared_ptr<NodoTrieAvanzado>> hijos;
    bool esFinDePalabra;
    std::vector<int> idsNodos;
    int frecuencia;
    time_t ultimoAcceso;
    
    NodoTrieAvanzado();
};

class TrieAvanzado {
private:
    std::shared_ptr<NodoTrieAvanzado> raiz;
    int totalPalabras;
    int totalConsultas;
    int aciertosCache;
    
    void recogerIDsConPrioridad(std::shared_ptr<NodoTrieAvanzado> nodo, 
                               std::vector<std::pair<int, std::pair<int, time_t>>>& resultados);
    void recogerIDsContando(std::shared_ptr<NodoTrieAvanzado> nodo, 
                           std::vector<int>& resultados, int& pasos);
    void recogerPalabras(std::shared_ptr<NodoTrieAvanzado> nodo, 
                        std::string palabraActual, std::vector<std::string>& palabras, int limite);
    int estimarMemoriaRecursivo(std::shared_ptr<NodoTrieAvanzado> nodo) const;
    
public:
    TrieAvanzado();
    
    // Operaciones básicas
    void insertar(const std::string& palabra, int idNodo);
    void eliminar(const std::string& palabra, int idNodo);
    
    // Búsquedas
    std::vector<int> buscarPrefijo(const std::string& prefijo, int limite = 10);
    std::vector<int> buscarAproximado(const std::string& palabra, int distanciaMaxima = 2);
    std::vector<std::string> obtenerSugerencias(const std::string& prefijo, int maxSugerencias = 5);
    
    // Métricas y pruebas
    void mostrarMetricas() const;
    std::vector<int> buscarPrefijoPerformance(const std::string& prefijo, int& pasos);
    
private:
    int estimarMemoria() const;
};

#endif // TRIE_H_INCLUDED

