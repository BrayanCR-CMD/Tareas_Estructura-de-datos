#ifndef PAPELERA_H_INCLUDED
#define PAPELERA_H_INCLUDED

// papelera

#include <memory>
#include <vector>
#include <string>
#include <ctime>

// Declaración anticipada
class NodoAvanzado;

class PapeleraAvanzada {
private:
    struct ElementoPapelera {
        std::shared_ptr<NodoAvanzado> nodo;
        std::shared_ptr<NodoAvanzado> padreOriginal;
        int posicionOriginal;
        time_t fechaEliminacion;
        time_t fechaExpiracion;
        std::string motivo;
        int tamaño;
        
        ElementoPapelera(std::shared_ptr<NodoAvanzado> n, std::shared_ptr<NodoAvanzado> p, 
                        int pos, const std::string& mot);
        
        bool estaExpirado() const;
        double tiempoRestanteHoras() const;
    };
    
    std::vector<ElementoPapelera> elementos;
    size_t capacidadMaximaBytes;
    size_t espacioUtilizado;
    int maxElementos;
    
    // Métodos privados
    bool liberarEspacio(size_t espacioNecesario);
    void aplicarLimites();
    void limpiarExpirados();
    std::string formatoTamaño(size_t bytes);
    std::string formatearFecha(time_t tiempo);
    
public:
    PapeleraAvanzada();
    
    // Configuración
    void configurarLimites(size_t maxBytes, int maxElem);
    
    // Operaciones
    bool agregar(std::shared_ptr<NodoAvanzado> nodo, std::shared_ptr<NodoAvanzado> padre, 
                int posicion, const std::string& motivo = "");
    void listarDetallado(bool mostrarExpirados = false);
    bool recuperar(int indice);
    int recuperarTodos();
    bool vaciar(bool forzar = false);
    
    // Información
    void mostrarEstadisticas();
    
    // Pruebas
    void llenarConDatosAleatorios(int cantidad);
};

#endif // PAPELERA_H_INCLUDED

