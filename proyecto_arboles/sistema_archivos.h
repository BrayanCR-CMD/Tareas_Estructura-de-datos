#ifndef SISTEMA_ARCHIVOS_H_INCLUDED
#define SISTEMA_ARCHIVOS_H_INCLUDED

// sistema_archivos.h

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <chrono>
#include "nodo.h"
#include "trie.h"
#include "papelera.h"

class SistemaCompleto {
private:
    std::shared_ptr<NodoAvanzado> raiz;
    std::shared_ptr<NodoAvanzado> directorioActual;
    TrieAvanzado trieNombres;
    PapeleraAvanzada papelera;
    int siguienteID;
    std::unordered_map<int, std::shared_ptr<NodoAvanzado>> mapaNodos;
    std::unordered_map<std::string, std::vector<int>> indiceContenido;
    
    // Métricas
    int operacionesRealizadas;
    time_t inicioEjecucion;
    std::map<std::string, int> contadorOperaciones;
    std::vector<std::pair<std::string, double>> tiemposOperacion;
    
    // Para pruebas
    bool modoPruebas;
    std::vector<std::string> erroresEncontrados;
    
    // Métodos auxiliares privados
    void inicializarEstructuraBasica();
    void inicializarContadores();
    void registrarTiempo(const std::string& operacion, 
                        std::chrono::high_resolution_clock::time_point inicio,
                        std::chrono::high_resolution_clock::time_point fin);
    
    std::shared_ptr<NodoAvanzado> obtenerNodoDesdeRuta(const std::string& ruta);
    std::shared_ptr<NodoAvanzado> obtenerNodoDesdeRutaRelativa(std::shared_ptr<NodoAvanzado> base, 
                                                              const std::string& ruta);
    bool validarNombre(const std::string& nombre);
    bool validarMovimiento(std::shared_ptr<NodoAvanzado> origen, 
                          std::shared_ptr<NodoAvanzado> destino);
    bool realizarMovimiento(std::shared_ptr<NodoAvanzado> origen, 
                           std::shared_ptr<NodoAvanzado> destino);
    void eliminarRecursivo(std::shared_ptr<NodoAvanzado> nodo);
    void actualizarIndices(std::shared_ptr<NodoAvanzado> nodo, bool agregar);
    void indexarContenido(std::shared_ptr<NodoAvanzado> archivo);
    std::vector<int> buscarEnContenido(const std::string& texto);
    void mostrarResultadosBusqueda(const std::vector<int>& resultados, 
                                  const std::string& criterio, const std::string& tipo);
    void recorridoPreordenCompleto(std::shared_ptr<NodoAvanzado> nodo, std::string prefijo, 
                                  std::vector<std::string>& resultado, bool conMetadatos);
    void listarDirecto(std::shared_ptr<NodoAvanzado> nodo, bool detallado, bool mostrarOcultos);
    void listarRecursivo(std::shared_ptr<NodoAvanzado> nodo, std::string prefijo, 
                        bool detallado, bool mostrarOcultos);
    int contarElementos(std::shared_ptr<NodoAvanzado> nodo, bool incluirOcultos);
    std::vector<std::shared_ptr<NodoAvanzado>> obtenerTodosNodos();
    std::vector<std::string> dividirRuta(const std::string& ruta);
    std::string escapeJSON(const std::string& texto);
    std::string formatoTamaño(size_t bytes) const;
    std::string obtenerFechaHora();
    void reiniciarSistema();
    
    // Métodos de pruebas
    bool pruebaInsercionMasiva();
    bool pruebaEliminacionRecuperacion();
    bool pruebaMovimientosConsistencia();
    bool pruebaBusquedaAutocompletado();
    bool pruebaPersistenciaJSON();
    bool pruebaCasosLimite();
    bool pruebaPerformance();
    void crearArbolGrande(int cantidad);
    void medirOperaciones();
    bool verificarRelacionesPadresHijos();
    
public:
    SistemaCompleto();
    
    // ============ DÍAS 10-11: PRUEBAS ============
    void ejecutarPruebasIntegracion();
    void ejecutarPruebaPerformance(int tamañoArbol = 1000);
    bool verificarConsistencia();
    
    // ============ OPERACIONES PRINCIPALES ============
    void mkdir(const std::string& nombre, const std::string& ruta = "");
    void touch(const std::string& nombre, const std::string& ruta = "", 
              const std::string& contenido = "");
    void ls(const std::string& ruta = "", bool detallado = false, 
           bool recursivo = false, bool mostrarOcultos = false);
    void cd(const std::string& ruta);
    void mv(const std::string& origen, const std::string& destino);
    void renombrar(const std::string& ruta, const std::string& nuevoNombre, bool forzar = false);
    void rm(const std::string& ruta, bool forzar = false, const std::string& motivo = "");
    
    // ============ BÚSQUEDA AVANZADA ============
    void buscar(const std::string& criterio, const std::string& tipoBusqueda = "prefijo");
    void autocompletar(const std::string& prefijo);
    
    // ============ EXPORTACIÓN ============
    void exportarPreorden(const std::string& archivoSalida, const std::string& rutaInicio = "", 
                         bool incluirMetadatos = false);
    void mostrarArbol(const std::string& ruta = "", int profundidadMaxima = 3);
    
    // ============ PERSISTENCIA ============
    void guardarJSON(const std::string& nombreArchivo, bool comprimir = false);
    void cargarJSON(const std::string& nombreArchivo);
    
    // ============ PAPELERA ============
    void mostrarPapelera(bool detallado = true);
    void recuperarPapelera(const std::string& parametro);
    void vaciarPapelera(bool forzar = false);
    
    // ============ INFORMACIÓN Y MÉTRICAS ============
    void pwd() const;
    void info() const;
    void mostrarMetricas();
    void ayuda() const;
    
    // ============ DÍA 13: DEMO ============
    void ejecutarDemo();
};

#endif // SISTEMA_ARCHIVOS_H_INCLUDED

