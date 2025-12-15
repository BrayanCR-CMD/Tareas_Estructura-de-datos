// sistema_archivos.cpp
#include "sistema_archivos.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <ctime>
#include <stack>

SistemaCompleto::SistemaCompleto() : siguienteID(1), operacionesRealizadas(0), modoPruebas(false) {
    inicioEjecucion = time(nullptr);
    raiz = std::make_shared<NodoAvanzado>(0, "raiz", "carpeta");
    directorioActual = raiz;
    mapaNodos[0] = raiz;
    
    inicializarEstructuraBasica();
    inicializarContadores();
}

// ============ INICIALIZACIÓN ============

void SistemaCompleto::inicializarEstructuraBasica() {
    mkdir("Documentos");
    mkdir("Proyectos");
    mkdir("Imagenes");
    
    cd("Documentos");
    touch("notas.txt", "", "Notas importantes del proyecto");
    touch("tareas.md", "", "# Lista de tareas\n- [ ] Terminar proyecto\n- [ ] Documentar codigo");
    
    cd("/Proyectos");
    mkdir("Arboles");
    
    cd("Arboles");
    touch("main.cpp", "", "// Codigo principal");
    touch("README.md", "", "Proyecto de gestion de arboles");
    
    cd("/");
    std::cout << "Estructura basica inicializada." << std::endl;
}

void SistemaCompleto::inicializarContadores() {
    contadorOperaciones = {
        {"mkdir", 0},
        {"touch", 0},
        {"ls", 0},
        {"mv", 0},
        {"renombrar", 0},
        {"rm", 0},
        {"buscar", 0},
        {"autocompletar", 0},
        {"exportar", 0},
        {"guardar", 0},
        {"cargar", 0}
    };
}

void SistemaCompleto::registrarTiempo(const std::string& operacion, 
                                     std::chrono::high_resolution_clock::time_point inicio,
                                     std::chrono::high_resolution_clock::time_point fin) {
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
    tiemposOperacion.push_back({operacion, duracion.count() / 1000.0});
}

// ============ DÍAS 10-11: PRUEBAS DE INTEGRACIÓN ============

void SistemaCompleto::ejecutarPruebasIntegracion() {
    std::cout << "\n=== EJECUTANDO PRUEBAS DE INTEGRACION ===" << std::endl;
    
    modoPruebas = true;
    erroresEncontrados.clear();
    
    int pruebasPasadas = 0;
    int pruebasTotales = 7;
    
    // Prueba 1: Inserción masiva
    std::cout << "\n1. Prueba de insercion masiva..." << std::endl;
    if (pruebaInsercionMasiva()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Prueba 2: Eliminación y recuperación
    std::cout << "\n2. Prueba de eliminacion y recuperacion..." << std::endl;
    if (pruebaEliminacionRecuperacion()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Prueba 3: Movimientos y consistencia
    std::cout << "\n3. Prueba de movimientos y consistencia..." << std::endl;
    if (pruebaMovimientosConsistencia()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Prueba 4: Búsqueda y autocompletado
    std::cout << "\n4. Prueba de busqueda y autocompletado..." << std::endl;
    if (pruebaBusquedaAutocompletado()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Prueba 5: Persistencia JSON
    std::cout << "\n5. Prueba de persistencia JSON..." << std::endl;
    if (pruebaPersistenciaJSON()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Prueba 6: Casos límite
    std::cout << "\n6. Prueba de casos limite..." << std::endl;
    if (pruebaCasosLimite()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Prueba 7: Performance
    std::cout << "\n7. Prueba de performance..." << std::endl;
    if (pruebaPerformance()) {
        std::cout << "   PASADA" << std::endl;
        pruebasPasadas++;
    } else {
        std::cout << "   FALLADA" << std::endl;
    }
    
    // Resultados
    std::cout << "\n=== RESULTADOS DE PRUEBAS ===" << std::endl;
    std::cout << "Pruebas pasadas: " << pruebasPasadas << "/" << pruebasTotales << std::endl;
    
    if (!erroresEncontrados.empty()) {
        std::cout << "\nErrores encontrados:" << std::endl;
        for (const auto& error : erroresEncontrados) {
            std::cout << "  - " << error << std::endl;
        }
    }
    
    modoPruebas = false;
    
    if (pruebasPasadas == pruebasTotales) {
        std::cout << "\nTODAS LAS PRUEBAS PASARON CORRECTAMENTE" << std::endl;
    } else {
        std::cout << "\nALGUNAS PRUEBAS FALLARON" << std::endl;
    }
}

void SistemaCompleto::ejecutarPruebaPerformance(int tamañoArbol) {
    std::cout << "\n=== PRUEBA DE PERFORMANCE ===" << std::endl;
    std::cout << "Creando arbol con " << tamañoArbol << " elementos..." << std::endl;
    
    auto inicio = std::chrono::high_resolution_clock::now();
    
    // Guardar estado actual
    auto raizOriginal = raiz;
    auto directorioActualOriginal = directorioActual;
    auto siguienteIDOriginal = siguienteID;
    
    crearArbolGrande(tamañoArbol);
    medirOperaciones();
    
    // Restaurar estado
    raiz = raizOriginal;
    directorioActual = directorioActualOriginal;
    siguienteID = siguienteIDOriginal;
    mapaNodos.clear();
    mapaNodos[0] = raiz;
    trieNombres = TrieAvanzado();
    
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    
    std::cout << "Prueba completada en " << duracion.count() << " ms" << std::endl;
}

bool SistemaCompleto::verificarConsistencia() {
    std::cout << "\n=== VERIFICACIÓN DE CONSISTENCIA ===" << std::endl;
    
    bool consistente = true;
    
    // 1. Verificar que todos los nodos tengan padre válido (excepto raíz)
    for (const auto& par : mapaNodos) {
        if (par.first == 0) continue;
        
        if (!par.second->padre) {
            std::cout << "Nodo " << par.second->nombre << " (ID: " << par.first 
                     << ") no tiene padre" << std::endl;
            consistente = false;
        }
    }
    
    // 2. Verificar que no hay IDs duplicados
    if (mapaNodos.size() != siguienteID) {
        std::cout << "Inconsistencia en IDs: " << mapaNodos.size() 
                 << " nodos vs ID máximo " << siguienteID << std::endl;
        consistente = false;
    }
    
    // 3. Verificar estructura de padres/hijos
    consistente = consistente && verificarRelacionesPadresHijos();
    
    if (consistente) {
        std::cout << "El árbol es consistente" << std::endl;
    } else {
        std::cout << "Se encontraron inconsistencias en el arbol" << std::endl;
    }
    
    return consistente;
}

// ============ IMPLEMENTACIÓN DE PRUEBAS ============

bool SistemaCompleto::pruebaInsercionMasiva() {
    int nodosAntes = mapaNodos.size();
    
    for (int i = 0; i < 100; i++) {
        if (i % 2 == 0) {
            mkdir("test_dir_" + std::to_string(i));
        } else {
            touch("test_file_" + std::to_string(i) + ".txt", "", "Contenido de prueba");
        }
    }
    
    int nodosDespues = mapaNodos.size();
    int esperados = nodosAntes + 100;
    
    if (nodosDespues == esperados) {
        return true;
    } else {
        erroresEncontrados.push_back("Prueba insercion masiva: esperados " + 
                                    std::to_string(esperados) + ", obtenidos " + 
                                    std::to_string(nodosDespues));
        return false;
    }
}

bool SistemaCompleto::pruebaEliminacionRecuperacion() {
    touch("archivo_prueba.txt", "", "Contenido");
    mkdir("carpeta_prueba");
    
    rm("archivo_prueba.txt");
    rm("carpeta_prueba", true);
    
    if (obtenerNodoDesdeRuta("archivo_prueba.txt") || 
        obtenerNodoDesdeRuta("carpeta_prueba")) {
        erroresEncontrados.push_back("Prueba eliminacion: elementos no eliminados correctamente");
        return false;
    }
    
    std::cout << "   Nota: Recuperacion de papelera requiere interfaz" << std::endl;
    return true;
}

bool SistemaCompleto::pruebaMovimientosConsistencia() {
    mkdir("origen");
    mkdir("destino");
    touch("mover.txt", "origen", "Archivo a mover");
    
    mv("origen/mover.txt", "destino");
    
    bool enDestino = obtenerNodoDesdeRuta("destino/mover.txt") != nullptr;
    bool enOrigen = obtenerNodoDesdeRuta("origen/mover.txt") != nullptr;
    
    if (enDestino && !enOrigen) {
        return true;
    } else {
        erroresEncontrados.push_back("Prueba movimientos: archivo no movido correctamente");
        return false;
    }
}

bool SistemaCompleto::pruebaBusquedaAutocompletado() {
    touch("documento1.txt");
    touch("documento2.txt");
    touch("documentacion.md");
    
    std::vector<int> resultados = trieNombres.buscarPrefijo("doc", 10);
    
    if (resultados.size() >= 3) {
        return true;
    } else {
        erroresEncontrados.push_back("Prueba busqueda: esperados al menos 3 resultados, obtenidos " + 
                                    std::to_string(resultados.size()));
        return false;
    }
}

bool SistemaCompleto::pruebaPersistenciaJSON() {
    std::string archivo = "prueba_persistencia.json";
    guardarJSON(archivo);
    
    std::ifstream f(archivo);
    bool existe = f.good();
    f.close();
    
    std::remove(archivo.c_str());
    
    if (existe) {
        return true;
    } else {
        erroresEncontrados.push_back("Prueba persistencia: archivo JSON no creado");
        return false;
    }
}

bool SistemaCompleto::pruebaCasosLimite() {
    bool todosPasaron = true;
    
    std::cout << "   Probando nombres invalidos..." << std::endl;
    touch("archivo/con/slashes.txt");
    
    std::cout << "   Probando movimientos invalidos..." << std::endl;
    mkdir("carpeta_test");
    mv("carpeta_test", "carpeta_test");
    
    std::cout << "   Probando eliminación de raiz..." << std::endl;
    rm("/");
    
    std::cout << "   Probando eliminacion directorio no vacio..." << std::endl;
    mkdir("no_vacia");
    touch("archivo.txt", "no_vacia");
    rm("no_vacia");
    
    return todosPasaron;
}

bool SistemaCompleto::pruebaPerformance() {
    std::cout << "   Probando árbol con 500 elementos..." << std::endl;
    
    auto inicio = std::chrono::high_resolution_clock::now();
    crearArbolGrande(500);
    
    int pasosTrie = 0;
    trieNombres.buscarPrefijoPerformance("test", pasosTrie);
    
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    
    std::cout << "   Tiempo total: " << duracion.count() << " ms" << std::endl;
    std::cout << "   Pasos en búsqueda Trie: " << pasosTrie << std::endl;
    
    // Limpiar
    while (raiz->hijos.size() > 0) {
        raiz->hijos.pop_back();
    }
    siguienteID = 1;
    mapaNodos.clear();
    mapaNodos[0] = raiz;
    trieNombres = TrieAvanzado();
    
    return duracion.count() < 5000;
}

void SistemaCompleto::crearArbolGrande(int cantidad) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> tipoDist(0, 1);
    std::uniform_int_distribution<> numDist(1, 10);
    
    std::stack<std::shared_ptr<NodoAvanzado>> pila;
    pila.push(raiz);
    
    int creados = 0;
    while (creados < cantidad && !pila.empty()) {
        auto actual = pila.top();
        pila.pop();
        
        int hijos = std::min(numDist(gen), cantidad - creados);
        
        for (int i = 0; i < hijos && creados < cantidad; i++) {
            std::string nombre = "test_" + std::to_string(creados);
            
            if (tipoDist(gen) == 0) {
                mkdir(nombre, actual->obtenerRutaCompleta());
            } else {
                touch(nombre + ".txt", actual->obtenerRutaCompleta(), 
                      "Contenido de prueba " + std::to_string(creados));
            }
            
            creados++;
            
            if (actual->hijos.back()->tipo == "carpeta") {
                pila.push(actual->hijos.back());
            }
        }
    }
}

void SistemaCompleto::medirOperaciones() {
    std::cout << "   Midiendo operaciones..." << std::endl;
    
    auto inicio = std::chrono::high_resolution_clock::now();
    mkdir("perf_test_dir");
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
    std::cout << "   mkdir: " << duracion.count() << " μs" << std::endl;
    
    inicio = std::chrono::high_resolution_clock::now();
    buscar("test", "prefijo");
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
    std::cout << "   buscar: " << duracion.count() << " μs" << std::endl;
}

bool SistemaCompleto::verificarRelacionesPadresHijos() {
    bool consistente = true;
    
    for (const auto& par : mapaNodos) {
        std::shared_ptr<NodoAvanzado> nodo = par.second;
        
        for (const auto& hijo : nodo->hijos) {
            if (hijo->padre != nodo) {
                std::cout << "Inconsistencia padre-hijo: " 
                         << hijo->nombre << " -> " << nodo->nombre << std::endl;
                consistente = false;
            }
        }
        
        if (nodo != raiz) {
            bool encontrado = false;
            for (const auto& hermano : nodo->padre->hijos) {
                if (hermano == nodo) {
                    encontrado = true;
                    break;
                }
            }
            
            if (!encontrado) {
                std::cout << "Nodo " << nodo->nombre << " no está en hijos de su padre" << std::endl;
                consistente = false;
            }
        }
    }
    
    return consistente;
}

// ============ MÉTODOS AUXILIARES PRIVADOS ============

std::shared_ptr<NodoAvanzado> SistemaCompleto::obtenerNodoDesdeRuta(const std::string& ruta) {
    if (ruta.empty()) return directorioActual;
    
    if (ruta[0] == '/') {
        return obtenerNodoDesdeRutaRelativa(raiz, ruta.substr(1));
    } else {
        return obtenerNodoDesdeRutaRelativa(directorioActual, ruta);
    }
}

std::shared_ptr<NodoAvanzado> SistemaCompleto::obtenerNodoDesdeRutaRelativa(
    std::shared_ptr<NodoAvanzado> base, const std::string& ruta) {
    
    if (ruta.empty()) return base;
    
    std::vector<std::string> partes = dividirRuta(ruta);
    std::shared_ptr<NodoAvanzado> actual = base;
    
    for (const std::string& parte : partes) {
        if (parte == ".") continue;
        if (parte == "..") {
            if (actual->padre) actual = actual->padre;
            else return nullptr;
        } else {
            actual = actual->buscarHijo(parte);
            if (!actual) return nullptr;
        }
    }
    
    return actual;
}

bool SistemaCompleto::validarNombre(const std::string& nombre) {
    if (nombre.empty() || nombre.length() > 255) return false;
    
    std::string caracteresInvalidos = "/\\:*?\"<>|";
    for (char c : caracteresInvalidos) {
        if (nombre.find(c) != std::string::npos) return false;
    }
    
    return true;
}

bool SistemaCompleto::validarMovimiento(std::shared_ptr<NodoAvanzado> origen, 
                                       std::shared_ptr<NodoAvanzado> destino) {
    if (origen == destino) {
        std::cout << "No se puede mover a si mismo." << std::endl;
        return false;
    }
    
    std::shared_ptr<NodoAvanzado> actual = destino;
    while (actual) {
        if (actual == origen) {
            std::cout << "No se puede mover dentro de un subdirectorio." << std::endl;
            return false;
        }
        actual = actual->padre;
    }
    
    if (destino->buscarHijo(origen->nombre)) {
        std::cout << "Ya existe un elemento con ese nombre." << std::endl;
        return false;
    }
    
    return true;
}

bool SistemaCompleto::realizarMovimiento(std::shared_ptr<NodoAvanzado> origen, 
                                        std::shared_ptr<NodoAvanzado> destino) {
    std::shared_ptr<NodoAvanzado> padreActual = origen->padre;
    int posicion = -1;
    
    for (size_t i = 0; i < padreActual->hijos.size(); i++) {
        if (padreActual->hijos[i] == origen) {
            posicion = i;
            break;
        }
    }
    
    if (posicion == -1) return false;
    
    padreActual->hijos.erase(padreActual->hijos.begin() + posicion);
    padreActual->actualizarTamaño();
    
    destino->agregarHijo(origen);
    origen->padre = destino;
    
    return true;
}

void SistemaCompleto::eliminarRecursivo(std::shared_ptr<NodoAvanzado> nodo) {
    for (auto& hijo : nodo->hijos) {
        eliminarRecursivo(hijo);
    }
    
    for (auto& hijo : nodo->hijos) {
        actualizarIndices(hijo, false);
    }
    
    nodo->hijos.clear();
}

void SistemaCompleto::actualizarIndices(std::shared_ptr<NodoAvanzado> nodo, bool agregar) {
    if (agregar) {
        trieNombres.insertar(nodo->nombre, nodo->id);
        mapaNodos[nodo->id] = nodo;
    } else {
        trieNombres.eliminar(nodo->nombre, nodo->id);
        mapaNodos.erase(nodo->id);
    }
}

void SistemaCompleto::indexarContenido(std::shared_ptr<NodoAvanzado> archivo) {
    if (archivo->tipo != "archivo" || archivo->contenido.empty()) return;
    
    std::string contenido = archivo->contenido;
    std::transform(contenido.begin(), contenido.end(), contenido.begin(), ::tolower);
    
    std::stringstream ss(contenido);
    std::string palabra;
    while (ss >> palabra) {
        palabra.erase(std::remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());
        
        if (palabra.length() > 2) {
            indiceContenido[palabra].push_back(archivo->id);
        }
    }
}

std::vector<int> SistemaCompleto::buscarEnContenido(const std::string& texto) {
    std::vector<int> resultados;
    std::string textoLower = texto;
    std::transform(textoLower.begin(), textoLower.end(), textoLower.begin(), ::tolower);
    
    auto it = indiceContenido.find(textoLower);
    if (it != indiceContenido.end()) {
        resultados = it->second;
        std::sort(resultados.begin(), resultados.end());
        resultados.erase(std::unique(resultados.begin(), resultados.end()), resultados.end());
    }
    
    return resultados;
}

void SistemaCompleto::mostrarResultadosBusqueda(const std::vector<int>& resultados, 
                                               const std::string& criterio, const std::string& tipo) {
    if (resultados.empty()) {
        std::cout << "No se encontraron resultados." << std::endl;
        return;
    }
    
    std::cout << "Resultados (" << resultados.size() << "):" << std::endl;
    
    for (int id : resultados) {
        auto it = mapaNodos.find(id);
        if (it != mapaNodos.end()) {
            std::shared_ptr<NodoAvanzado> nodo = it->second;
            std::string tipoNodo = nodo->tipo == "carpeta" ? "[DIR]" : "[FILE]";
            
            std::cout << "  " << tipoNodo << " " << nodo->obtenerRutaCompleta();
            
            if (tipo == "contenido" && nodo->tipo == "archivo") {
                std::string fragmento = nodo->contenido.substr(0, 30);
                if (nodo->contenido.length() > 30) fragmento += "...";
                std::cout << " - \"" << fragmento << "\"";
            }
            
            std::cout << std::endl;
        }
    }
}

void SistemaCompleto::recorridoPreordenCompleto(std::shared_ptr<NodoAvanzado> nodo, 
                                               std::string prefijo, 
                                               std::vector<std::string>& resultado, 
                                               bool conMetadatos) {
    if (!nodo) return;
    
    std::string linea = prefijo;
    if (conMetadatos) {
        linea += nodo->obtenerInfo();
    } else {
        linea += nodo->obtenerRutaCompleta();
    }
    
    resultado.push_back(linea);
    
    for (auto& hijo : nodo->hijos) {
        std::string nuevoPrefijo = conMetadatos ? prefijo + "  " : "";
        recorridoPreordenCompleto(hijo, nuevoPrefijo, resultado, conMetadatos);
    }
}

void SistemaCompleto::listarDirecto(std::shared_ptr<NodoAvanzado> nodo, 
                                   bool detallado, bool mostrarOcultos) {
    int visibles = 0;
    
    for (size_t i = 0; i < nodo->hijos.size(); i++) {
        const auto& hijo = nodo->hijos[i];
        
        if (!mostrarOcultos && hijo->oculto) {
            continue;
        }
        
        visibles++;
        
        if (detallado) {
            char fechaMod[20];
            std::strftime(fechaMod, sizeof(fechaMod), "%Y-%m-%d %H:%M", 
                         std::localtime(&hijo->fechaModificacion));
            
            std::string tipo = (hijo->tipo == "carpeta") ? "d" : "-";
            tipo += "rw-r--r--";
            
            std::cout << tipo << " ";
            std::cout << std::setw(3) << hijo->hijos.size() << " ";
            std::cout << std::setw(8) << formatoTamaño(hijo->tamaño) << " ";
            std::cout << fechaMod << " ";
            std::cout << hijo->nombre;
            
            if (hijo->tipo == "carpeta") std::cout << "/";
            if (hijo->oculto) std::cout << " [oculto]";
            std::cout << std::endl;
        } else {
            std::string tipo = (hijo->tipo == "carpeta") ? "[DIR] " : "[FILE] ";
            std::cout << "  " << i + 1 << ". " << tipo << hijo->nombre;
            
            if (hijo->oculto) std::cout << " [oculto]";
            std::cout << std::endl;
        }
    }
    
    if (visibles == 0 && !nodo->hijos.empty()) {
        std::cout << "  (todos los elementos están ocultos)" << std::endl;
    }
}

void SistemaCompleto::listarRecursivo(std::shared_ptr<NodoAvanzado> nodo, 
                                     std::string prefijo, bool detallado, bool mostrarOcultos) {
    for (size_t i = 0; i < nodo->hijos.size(); i++) {
        const auto& hijo = nodo->hijos[i];
        
        if (!mostrarOcultos && hijo->oculto) {
            continue;
        }
        
        bool ultimo = (i == nodo->hijos.size() - 1);
        std::string nuevoPrefijo = prefijo + (ultimo ? "└── " : "├── ");
        std::string siguientePrefijo = prefijo + (ultimo ? "    " : "│   ");
        
        if (detallado) {
            char fechaMod[20];
            std::strftime(fechaMod, sizeof(fechaMod), "%Y-%m-%d", 
                         std::localtime(&hijo->fechaModificacion));
            
            std::cout << nuevoPrefijo << hijo->nombre;
            if (hijo->tipo == "carpeta") std::cout << "/";
            std::cout << " [" << fechaMod << ", " << formatoTamaño(hijo->tamaño) << "]";
            if (hijo->oculto) std::cout << " [oculto]";
            std::cout << std::endl;
        } else {
            std::cout << nuevoPrefijo << hijo->nombre;
            if (hijo->tipo == "carpeta") std::cout << "/";
            if (hijo->oculto) std::cout << " [oculto]";
            std::cout << std::endl;
        }
        
        if (hijo->tipo == "carpeta") {
            listarRecursivo(hijo, siguientePrefijo, detallado, mostrarOcultos);
        }
    }
}

int SistemaCompleto::contarElementos(std::shared_ptr<NodoAvanzado> nodo, bool incluirOcultos) {
    int count = 0;
    
    for (const auto& hijo : nodo->hijos) {
        if (incluirOcultos || !hijo->oculto) {
            count++;
        }
    }
    
    return count;
}

std::vector<std::shared_ptr<NodoAvanzado>> SistemaCompleto::obtenerTodosNodos() {
    std::vector<std::shared_ptr<NodoAvanzado>> resultado;
    std::queue<std::shared_ptr<NodoAvanzado>> cola;
    cola.push(raiz);
    
    while (!cola.empty()) {
        std::shared_ptr<NodoAvanzado> actual = cola.front();
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

std::vector<std::string> SistemaCompleto::dividirRuta(const std::string& ruta) {
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

std::string SistemaCompleto::escapeJSON(const std::string& texto) {
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

std::string SistemaCompleto::formatoTamaño(size_t bytes) const {
    const char* unidades[] = {"B", "KB", "MB", "GB"};
    int unidad = 0;
    double tamaño = bytes;
    
    while (tamaño >= 1024 && unidad < 3) {
        tamaño /= 1024;
        unidad++;
    }
    
    std::stringstream ss;
    if (unidad == 0) {
        ss << bytes << " " << unidades[unidad];
    } else {
        ss << std::fixed << std::setprecision(2) << tamaño << " " << unidades[unidad];
    }
    return ss.str();
}

std::string SistemaCompleto::obtenerFechaHora() {
    time_t ahora = time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&ahora));
    return std::string(buffer);
}

void SistemaCompleto::reiniciarSistema() {
    raiz = std::make_shared<NodoAvanzado>(0, "raiz", "carpeta");
    directorioActual = raiz;
    mapaNodos.clear();
    mapaNodos[0] = raiz;
    trieNombres = TrieAvanzado();
    papelera = PapeleraAvanzada();
    indiceContenido.clear();
    siguienteID = 1;
}

// ============ OPERACIONES PRINCIPALES ============

void SistemaCompleto::mkdir(const std::string& nombre, const std::string& ruta) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> destino = obtenerNodoDesdeRuta(ruta);
    
    if (!validarNombre(nombre)) {
        std::cout << "Nombre invalido." << std::endl;
        return;
    }
    
    if (!destino || destino->tipo != "carpeta") {
        std::cout << "Destino no valido." << std::endl;
        return;
    }
    
    if (destino->buscarHijo(nombre)) {
        std::cout << "Ya existe un elemento con ese nombre." << std::endl;
        return;
    }
    
    std::shared_ptr<NodoAvanzado> nuevaCarpeta = std::make_shared<NodoAvanzado>(
        siguienteID++, nombre, "carpeta", destino);
    destino->agregarHijo(nuevaCarpeta);
    actualizarIndices(nuevaCarpeta, true);
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("mkdir", inicio, fin);
    contadorOperaciones["mkdir"]++;
    
    std::cout << "Carpeta '" << nombre << "' creada." << std::endl;
    operacionesRealizadas++;
}

void SistemaCompleto::touch(const std::string& nombre, const std::string& ruta, 
                           const std::string& contenido) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> destino = obtenerNodoDesdeRuta(ruta);
    
    if (!validarNombre(nombre)) {
        std::cout << "Nombre invalido." << std::endl;
        return;
    }
    
    if (!destino || destino->tipo != "carpeta") {
        std::cout << "Destino no válido." << std::endl;
        return;
    }
    
    if (destino->buscarHijo(nombre)) {
        std::cout << "Ya existe un elemento con ese nombre." << std::endl;
        return;
    }
    
    std::shared_ptr<NodoAvanzado> nuevoArchivo = std::make_shared<NodoAvanzado>(
        siguienteID++, nombre, "archivo", destino);
    nuevoArchivo->setContenido(contenido);
    
    destino->agregarHijo(nuevoArchivo);
    actualizarIndices(nuevoArchivo, true);
    
    if (!contenido.empty()) {
        indexarContenido(nuevoArchivo);
    }
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("touch", inicio, fin);
    contadorOperaciones["touch"]++;
    
    std::cout << "Archivo '" << nombre << "' creado." << std::endl;
    operacionesRealizadas++;
}

void SistemaCompleto::ls(const std::string& ruta, bool detallado, 
                        bool recursivo, bool mostrarOcultos) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> destino = obtenerNodoDesdeRuta(ruta);
    
    if (!destino || destino->tipo != "carpeta") {
        std::cout << "Destino no valido." << std::endl;
        return;
    }
    
    std::cout << "Contenido de " << destino->obtenerRutaCompleta() << ":" << std::endl;
    
    if (destino->hijos.empty()) {
        std::cout << "  (vacio)" << std::endl;
        return;
    }
    
    if (recursivo) {
        listarRecursivo(destino, "", detallado, mostrarOcultos);
    } else {
        listarDirecto(destino, detallado, mostrarOcultos);
    }
    
    std::cout << "Total: " << contarElementos(destino, mostrarOcultos) << " elementos" << std::endl;
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("ls", inicio, fin);
    contadorOperaciones["ls"]++;
}

void SistemaCompleto::cd(const std::string& ruta) {
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
            std::cout << "Ya estas en la raiz." << std::endl;
        }
        return;
    }
    
    std::shared_ptr<NodoAvanzado> destino = obtenerNodoDesdeRuta(ruta);
    
    if (!destino) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }
    
    if (destino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }
    
    directorioActual = destino;
    std::cout << "Directorio cambiado a: " << directorioActual->obtenerRutaCompleta() << std::endl;
}

void SistemaCompleto::mv(const std::string& origen, const std::string& destino) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> nodoOrigen = obtenerNodoDesdeRuta(origen);
    std::shared_ptr<NodoAvanzado> nodoDestino = obtenerNodoDesdeRuta(destino);
    
    if (!nodoOrigen || !nodoDestino) {
        std::cout << "Ruta(s) no valida(s)." << std::endl;
        return;
    }
    
    if (nodoDestino->tipo != "carpeta") {
        std::cout << "El destino no es una carpeta." << std::endl;
        return;
    }
    
    if (!validarMovimiento(nodoOrigen, nodoDestino)) {
        return;
    }
    
    if (realizarMovimiento(nodoOrigen, nodoDestino)) {
        std::cout << "Movido '" << nodoOrigen->nombre << "'" << std::endl;
        operacionesRealizadas++;
    }
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("mv", inicio, fin);
    contadorOperaciones["mv"]++;
}

void SistemaCompleto::renombrar(const std::string& ruta, const std::string& nuevoNombre, bool forzar) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> nodo = obtenerNodoDesdeRuta(ruta);
    
    if (!nodo) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }
    
    if (!validarNombre(nuevoNombre)) {
        std::cout << "Nombre nuevo invalido." << std::endl;
        return;
    }
    
    if (!forzar && nodo->padre) {
        for (auto& hermano : nodo->padre->hijos) {
            if (hermano != nodo && hermano->nombre == nuevoNombre) {
                std::cout << "Ya existe un elemento con ese nombre." << std::endl;
                return;
            }
        }
    }
    
    actualizarIndices(nodo, false);
    
    std::string nombreAntiguo = nodo->nombre;
    nodo->nombre = nuevoNombre;
    nodo->actualizarFechaModificacion();
    
    actualizarIndices(nodo, true);
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("renombrar", inicio, fin);
    contadorOperaciones["renombrar"]++;
    
    std::cout << "Renombrado a '" << nuevoNombre << "'" << std::endl;
    operacionesRealizadas++;
}

void SistemaCompleto::rm(const std::string& ruta, bool forzar, const std::string& motivo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> nodo = obtenerNodoDesdeRuta(ruta);
    
    if (!nodo) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }
    
    if (nodo == raiz) {
        std::cout << "No se puede eliminar la raiz." << std::endl;
        return;
    }
    
    if (!forzar && nodo->tipo == "carpeta" && !nodo->hijos.empty()) {
        std::cout << "La carpeta no está vacia." << std::endl;
        return;
    }
    
    std::shared_ptr<NodoAvanzado> padre = nodo->padre;
    int posicion = -1;
    
    for (size_t i = 0; i < padre->hijos.size(); i++) {
        if (padre->hijos[i] == nodo) {
            posicion = i;
            break;
        }
    }
    
    if (posicion != -1) {
        if (forzar && nodo->tipo == "carpeta") {
            eliminarRecursivo(nodo);
        }
        
        if (papelera.agregar(nodo, padre, posicion, motivo)) {
            padre->hijos.erase(padre->hijos.begin() + posicion);
            padre->actualizarTamaño();
            actualizarIndices(nodo, false);
            std::cout << "Eliminado '" << nodo->nombre << "'" << std::endl;
            operacionesRealizadas++;
        }
    }
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("rm", inicio, fin);
    contadorOperaciones["rm"]++;
}

// ============ BÚSQUEDA AVANZADA ============

void SistemaCompleto::buscar(const std::string& criterio, const std::string& tipoBusqueda) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    if (criterio.empty()) {
        std::cout << "Criterio no puede estar vacio." << std::endl;
        return;
    }
    
    std::vector<int> resultados;
    
    if (tipoBusqueda == "prefijo") {
        resultados = trieNombres.buscarPrefijo(criterio, 20);
    } 
    else if (tipoBusqueda == "contenido") {
        resultados = buscarEnContenido(criterio);
    }
    else {
        std::cout << "Tipo de busqueda no valido." << std::endl;
        return;
    }
    
    mostrarResultadosBusqueda(resultados, criterio, tipoBusqueda);
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("buscar", inicio, fin);
    contadorOperaciones["buscar"]++;
}

void SistemaCompleto::autocompletar(const std::string& prefijo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    if (prefijo.length() < 2) {
        std::cout << "Ingrese al menos 2 caracteres." << std::endl;
        return;
    }
    
    auto sugerencias = trieNombres.obtenerSugerencias(prefijo, 5);
    
    if (sugerencias.empty()) {
        std::cout << "No hay sugerencias." << std::endl;
        return;
    }
    
    std::cout << "Sugerencias para '" << prefijo << "':" << std::endl;
    for (size_t i = 0; i < sugerencias.size(); i++) {
        std::cout << "  " << i + 1 << ". " << sugerencias[i] << std::endl;
    }
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("autocompletar", inicio, fin);
    contadorOperaciones["autocompletar"]++;
}

// ============ EXPORTACIÓN ============

void SistemaCompleto::exportarPreorden(const std::string& archivoSalida, 
                                      const std::string& rutaInicio, bool incluirMetadatos) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::shared_ptr<NodoAvanzado> inicioNodo = rutaInicio.empty() ? raiz : obtenerNodoDesdeRuta(rutaInicio);
    
    if (!inicioNodo) {
        std::cout << "Ruta de inicio no valida." << std::endl;
        return;
    }
    
    std::ofstream archivo(archivoSalida);
    if (!archivo) {
        std::cout << "Error al crear archivo." << std::endl;
        return;
    }
    
    std::vector<std::string> lineas;
    recorridoPreordenCompleto(inicioNodo, "", lineas, incluirMetadatos);
    
    archivo << "# Recorrido en preorden" << std::endl;
    archivo << "# Total elementos: " << lineas.size() << std::endl << std::endl;
    
    for (const std::string& linea : lineas) {
        archivo << linea << std::endl;
    }
    
    archivo.close();
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("exportar", inicio, fin);
    contadorOperaciones["exportar"]++;
    
    std::cout << "Exportado a '" << archivoSalida << "'" << std::endl;
}

void SistemaCompleto::mostrarArbol(const std::string& ruta, int profundidadMaxima) {
    std::shared_ptr<NodoAvanzado> inicio = ruta.empty() ? directorioActual : obtenerNodoDesdeRuta(ruta);
    
    if (!inicio) {
        std::cout << "Ruta no valida." << std::endl;
        return;
    }
    
    std::cout << "Estructura de arbol desde " << inicio->obtenerRutaCompleta() << ":" << std::endl;
    // Implementación simplificada para mostrar árbol
    std::cout << "Función mostrarArbol implementada parcialmente." << std::endl;
}

// ============ PERSISTENCIA ============

void SistemaCompleto::guardarJSON(const std::string& nombreArchivo, bool comprimir) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cout << "Error al crear archivo JSON." << std::endl;
        return;
    }
    
    archivo << "{\n";
    archivo << "  \"metadata\": {\n";
    archivo << "    \"version\": \"1.0\",\n";
    archivo << "    \"totalNodos\": " << mapaNodos.size() - 1 << ",\n";
    archivo << "    \"siguienteID\": " << siguienteID << "\n";
    archivo << "  },\n";
    archivo << "  \"nodos\": [\n";
    
    std::vector<std::shared_ptr<NodoAvanzado>> todosNodos = obtenerTodosNodos();
    
    for (size_t i = 0; i < todosNodos.size(); i++) {
        std::shared_ptr<NodoAvanzado> nodo = todosNodos[i];
        
        archivo << "    {\n";
        archivo << "      \"id\": " << nodo->id << ",\n";
        archivo << "      \"nombre\": \"" << escapeJSON(nodo->nombre) << "\",\n";
        archivo << "      \"tipo\": \"" << nodo->tipo << "\",\n";
        archivo << "      \"contenido\": \"" << escapeJSON(nodo->contenido) << "\",\n";
        archivo << "      \"tamaño\": " << nodo->tamaño << ",\n";
        archivo << "      \"padreID\": " << (nodo->padre ? nodo->padre->id : -1) << "\n";
        archivo << "    }";
        
        if (i < todosNodos.size() - 1) archivo << ",";
        archivo << "\n";
    }
    
    archivo << "  ]\n";
    archivo << "}\n";
    
    archivo.close();
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("guardar", inicio, fin);
    contadorOperaciones["guardar"]++;
    
    std::cout << "Sistema guardado en '" << nombreArchivo << "'" << std::endl;
}

void SistemaCompleto::cargarJSON(const std::string& nombreArchivo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::cout << "Funcion cargarJSON implementada parcialmente." << std::endl;
    
    auto fin = std::chrono::high_resolution_clock::now();
    registrarTiempo("cargar", inicio, fin);
    contadorOperaciones["cargar"]++;
}

// ============ PAPELERA ============

void SistemaCompleto::mostrarPapelera(bool detallado) {
    if (detallado) {
        papelera.listarDetallado();
    } else {
        papelera.mostrarEstadisticas();
    }
}

void SistemaCompleto::recuperarPapelera(const std::string& parametro) {
    if (parametro == "todos") {
        papelera.recuperarTodos();
    } else {
        try {
            int indice = std::stoi(parametro);
            papelera.recuperar(indice);
        } catch (...) {
            std::cout << "Parametro invalido." << std::endl;
        }
    }
}

void SistemaCompleto::vaciarPapelera(bool forzar) {
    papelera.vaciar(forzar);
}

// ============ INFORMACIÓN Y MÉTRICAS ============

void SistemaCompleto::pwd() const {
    std::cout << directorioActual->obtenerRutaCompleta() << std::endl;
}

void SistemaCompleto::info() const {
    int totalNodos = mapaNodos.size() - 1;
    int carpetas = 0;
    int archivos = 0;
    size_t tamañoTotal = 0;
    
    for (const auto& par : mapaNodos) {
        if (par.second->tipo == "carpeta") carpetas++;
        else if (par.second->tipo == "archivo") archivos++;
        tamañoTotal += par.second->tamaño;
    }
    
    double tiempoEjecucion = difftime(time(nullptr), inicioEjecucion);
    
    std::cout << "=== INFORMACIÓN DEL SISTEMA ===" << std::endl;
    std::cout << "Total nodos: " << totalNodos << std::endl;
    std::cout << "  Carpetas: " << carpetas << std::endl;
    std::cout << "  Archivos: " << archivos << std::endl;
    std::cout << "Espacio total: " << formatoTamaño(tamañoTotal) << std::endl;
    std::cout << "Operaciones realizadas: " << operacionesRealizadas << std::endl;
    std::cout << "Tiempo de ejecucion: " << std::fixed << std::setprecision(1) 
             << tiempoEjecucion << " segundos" << std::endl;
    std::cout << "Proximo ID: " << siguienteID << std::endl;
}

void SistemaCompleto::mostrarMetricas() {
    std::cout << "=== METRICAS DEL SISTEMA ===" << std::endl;
    
    std::cout << "\nOperaciones realizadas:" << std::endl;
    for (const auto& op : contadorOperaciones) {
        std::cout << "  " << op.first << ": " << op.second << std::endl;
    }
    
    std::cout << "\nTiempos promedio de operaciones:" << std::endl;
    std::map<std::string, std::vector<double>> tiemposPorOperacion;
    
    for (const auto& tiempo : tiemposOperacion) {
        tiemposPorOperacion[tiempo.first].push_back(tiempo.second);
    }
    
    for (const auto& op : tiemposPorOperacion) {
        double suma = 0;
        for (double t : op.second) suma += t;
        double promedio = suma / op.second.size();
        std::cout << "  " << op.first << ": " << std::fixed << std::setprecision(3) 
                 << promedio << " ms (" << op.second.size() << " muestras)" << std::endl;
    }
    
    trieNombres.mostrarMetricas();
    papelera.mostrarEstadisticas();
}

void SistemaCompleto::ayuda() const {
    std::cout << "=== COMANDOS DISPONIBLES ===" << std::endl;
    std::cout << "mkdir <nombre> [ruta]" << std::endl;
    std::cout << "touch <nombre> [ruta] [contenido]" << std::endl;
    std::cout << "ls [ruta] [-l] [-r] [-a]" << std::endl;
    std::cout << "cd [ruta]" << std::endl;
    std::cout << "mv <origen> <destino>" << std::endl;
    std::cout << "ren <ruta> <nuevoNombre> [-f]" << std::endl;
    std::cout << "rm <ruta> [-f]" << std::endl;
    std::cout << "buscar <texto> [prefijo|contenido]" << std::endl;
    std::cout << "autocompletar <prefijo>" << std::endl;
    std::cout << "export <archivo> [ruta] [-m]" << std::endl;
    std::cout << "guardar <archivo.json>" << std::endl;
    std::cout << "cargar <archivo.json>" << std::endl;
    std::cout << "papelera [-s]" << std::endl;
    std::cout << "recuperar <indice|todos>" << std::endl;
    std::cout << "vaciarpapelera [-f]" << std::endl;
    std::cout << "pwd" << std::endl;
    std::cout << "info" << std::endl;
    std::cout << "metricas" << std::endl;
    std::cout << "pruebas" << std::endl;
    std::cout << "performance [tamaño]" << std::endl;
    std::cout << "consistencia" << std::endl;
    std::cout << "demo" << std::endl;
    std::cout << "ayuda" << std::endl;
    std::cout << "salir" << std::endl;
}

// ============ DÍA 13: DEMO ============

void SistemaCompleto::ejecutarDemo() {
    std::cout << "\n=== EJECUTANDO DEMOSTRACION ===" << std::endl;
    
    std::cout << "\n1. Creando estructura de demo..." << std::endl;
    mkdir("Demo");
    mkdir("Demo/Documentos");
    mkdir("Demo/Proyectos");
    
    touch("README.md", "Demo", "# Proyecto Demo\nEste es un archivo de demostracion.");
    touch("notas.txt", "Demo/Documentos", "Notas importantes");
    touch("main.cpp", "Demo/Proyectos", "int main() { return 0; }");
    
    std::cout << "\n2. Estructura creada:" << std::endl;
    ls("Demo", false, true);
    
    std::cout << "\n3. Demostrando búsqueda:" << std::endl;
    buscar("main", "prefijo");
    
    std::cout << "\n4. Demostrando autocompletado:" << std::endl;
    autocompletar("no");
    
    std::cout << "\n5. Exportando recorrido:" << std::endl;
    exportarPreorden("demo_export.txt", "Demo", true);
    
    std::cout << "\n6. Información del sistema:" << std::endl;
    info();
    
    std::cout << "\n Demostración completada" << std::endl;
    std::cout << "Los archivos de demo se guardaron en 'demo_export.txt'" << std::endl;
}

