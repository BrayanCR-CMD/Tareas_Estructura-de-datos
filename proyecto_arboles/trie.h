#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

// trie.hpp

#include <memory>
#include <map>
#include <vector>
#include <string>

class NodoTrie {
public:
    std::map<char, std::shared_ptr<NodoTrie>> hijos;
    bool esFinDePalabra;
    std::vector<int> idsNodos;

    NodoTrie();
};

class Trie {
private:
    std::shared_ptr<NodoTrie> raiz;

    void recogerIDs(std::shared_ptr<NodoTrie> nodo, std::vector<int>& resultados);

public:
    Trie();
    void insertar(const std::string& palabra, int idNodo);
    void eliminar(const std::string& palabra, int idNodo);
    std::vector<int> buscarPrefijo(const std::string& prefijo);
};

#endif // TRIE_H_INCLUDED
