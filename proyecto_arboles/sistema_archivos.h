#ifndef SISTEMA_ARCHIVOS_H_INCLUDED
#define SISTEMA_ARCHIVOS_H_INCLUDED

// sistema_archivos.hpp

#include <memory>
#include <string>
#include <map>
#include "nodo.h"
#include "trie.h"
#include "papelera.h"

class SistemaArchivos {
private:
    std::shared_ptr<Nodo> raiz;
    std::shared_ptr<Nodo> directorioActual;
    Trie trieNombres;
    Papelera papelera;
    int siguienteID;
    std::map<int, std::shared_ptr<Nodo>> mapaNodos;

    // Métodos auxiliares privados
    std::shared_ptr<Nodo> obtenerNodoDesdeRuta(const std::string& ruta);
    std::shared_ptr<Nodo> obtenerNodoDesdeRutaRelativa(std::shared_ptr<Nodo> nodoBase, const std::string& ruta);
    bool esDescendiente(std::shared_ptr<Nodo> posibleDescendiente, std::shared_ptr<Nodo> ancestro);
    std::vector<std::shared_ptr<Nodo>> obtenerTodosNodos();
    std::vector<std::string> dividirRuta(const std::string& ruta);
    std::string escapeJSON(const std::string& texto);
    void recorridoPreorden(std::shared_ptr<Nodo> nodo, std::vector<std::string>& resultado);
    void actualizarIndices(std::shared_ptr<Nodo> nodo, bool agregar);

public:
    SistemaArchivos();

    // Operaciones principales
    void mkdir(const std::string& nombre, const std::string& ruta = "");
    void touch(const std::string& nombre, const std::string& ruta = "");
    void ls(const std::string& ruta = "");
    void cd(const std::string& ruta);
    void mv(const std::string& origen, const std::string& destino);
    void renombrar(const std::string& ruta, const std::string& nuevoNombre);
    void rm(const std::string& ruta);

    // Búsqueda
    void buscarPrefijo(const std::string& prefijo);

    // Exportación
    void exportarPreorden(const std::string& rutaArchivo, const std::string& rutaInicio = "");

    // Persistencia
    void guardarJSON(const std::string& nombreArchivo);
    void cargarJSON(const std::string& nombreArchivo);

    // Papelera
    void mostrarPapelera();
    void recuperarPapelera(int indice);
    void vaciarPapelera();

    // Información
    void pwd();
    void info();
};

#endif // SISTEMA_ARCHIVOS_H_INCLUDED
