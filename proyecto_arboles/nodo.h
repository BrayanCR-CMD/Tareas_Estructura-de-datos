#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

// nodo

#include <memory>
#include <vector>
#include <string>
#include <ctime>

class NodoAvanzado : public std::enable_shared_from_this<NodoAvanzado> {
public:
    int id;
    std::string nombre;
    std::string tipo; // "carpeta" o "archivo"
    std::string contenido;
    std::vector<std::shared_ptr<NodoAvanzado>> hijos;
    std::shared_ptr<NodoAvanzado> padre;
    time_t fechaCreacion;
    time_t fechaModificacion;
    size_t tamaño;
    bool oculto;
    
    NodoAvanzado(int id, std::string nombre, std::string tipo, 
                std::shared_ptr<NodoAvanzado> padre = nullptr);
    
    // Métodos públicos
    void agregarHijo(std::shared_ptr<NodoAvanzado> hijo);
    bool eliminarHijo(std::string nombreHijo);
    std::shared_ptr<NodoAvanzado> buscarHijo(std::string nombreHijo, bool incluirOcultos = false);
    std::string obtenerRutaCompleta() const;
    std::string obtenerInfo() const;
    
    // Métodos de gestión
    void actualizarFechaModificacion();
    void actualizarFechaAcceso();
    void actualizarTamaño();
    bool setContenido(const std::string& nuevoContenido);
    void marcarOculto(bool esOculto);
    
private:
    std::string formatoTamaño(size_t bytes) const;
};

#endif // NODO_H_INCLUDED

