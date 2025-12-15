#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

// nodo.hpp

#include <memory>
#include <vector>
#include <string>

class Nodo : public std::enable_shared_from_this<Nodo> {
public:
    int id;
    std::string nombre;
    std::string tipo; // "carpeta" o "archivo"
    std::string contenido;
    std::vector<std::shared_ptr<Nodo>> hijos;
    std::shared_ptr<Nodo> padre;

    Nodo(int id, std::string nombre, std::string tipo, std::shared_ptr<Nodo> padre = nullptr);

    void agregarHijo(std::shared_ptr<Nodo> hijo);
    bool eliminarHijo(std::string nombreHijo);
    std::shared_ptr<Nodo> buscarHijo(std::string nombreHijo);
    std::string obtenerRutaCompleta();

private:
    // Métodos auxiliares privados
};

#endif // NODO_H_INCLUDED
