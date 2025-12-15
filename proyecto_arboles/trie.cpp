// trie.cpp
#include "trie.h"
#include <algorithm>
#include <cctype>

NodoTrie::NodoTrie() : esFinDePalabra(false) {}

Trie::Trie() : raiz(std::make_shared<NodoTrie>()) {}

void Trie::insertar(const std::string& palabra, int idNodo) {
    std::shared_ptr<NodoTrie> actual = raiz;

    for (char c : palabra) {
        char cLower = std::tolower(c);
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            actual->hijos[cLower] = std::make_shared<NodoTrie>();
        }
        actual = actual->hijos[cLower];
    }

    actual->esFinDePalabra = true;
    actual->idsNodos.push_back(idNodo);
}

void Trie::eliminar(const std::string& palabra, int idNodo) {
    std::shared_ptr<NodoTrie> actual = raiz;

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
        }

        if (actual->idsNodos.empty()) {
            actual->esFinDePalabra = false;
        }
    }
}

std::vector<int> Trie::buscarPrefijo(const std::string& prefijo) {
    std::vector<int> resultados;
    std::shared_ptr<NodoTrie> actual = raiz;

    for (char c : prefijo) {
        char cLower = std::tolower(c);
        if (actual->hijos.find(cLower) == actual->hijos.end()) {
            return resultados;
        }
        actual = actual->hijos[cLower];
    }

    recogerIDs(actual, resultados);
    return resultados;
}

void Trie::recogerIDs(std::shared_ptr<NodoTrie> nodo, std::vector<int>& resultados) {
    if (nodo->esFinDePalabra) {
        resultados.insert(resultados.end(), nodo->idsNodos.begin(), nodo->idsNodos.end());
    }

    for (auto& par : nodo->hijos) {
        recogerIDs(par.second, resultados);
    }
}
