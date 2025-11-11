#lista enlazada
class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None

class ListaEnlazada:
    def __init__(self):
        self.cabeza = None

    def agregar_al_final(self, dato):
        nuevo_nodo = Nodo(dato)
        if not self.cabeza:
            self.cabeza = nuevo_nodo
            return
        ultimo = self.cabeza
        while ultimo.siguiente:
            ultimo = ultimo.siguiente
        ultimo.siguiente = nuevo_nodo

    def eliminar_por_valor(self, dato):
        actual = self.cabeza
        previo = None
        while actual and actual.dato != dato:
            previo = actual
            actual = actual.siguiente
        if not actual:
            return  # El dato no se encontró
        if previo:
            previo.siguiente = actual.siguiente
        else:
            self.cabeza = actual.siguiente

    def buscar(self, dato):
        actual = self.cabeza
        while actual:
            if actual.dato == dato:
                return True
            actual = actual.siguiente
        return False

    def mostrar(self):
        elementos = []
        actual = self.cabeza
        while actual:
            elementos.append(actual.dato)
            actual = actual.siguiente
        return elementos
    
# Ejemplo de uso
if __name__ == "__main__":
    lista = ListaEnlazada()
    lista.agregar_al_final(1)
    lista.agregar_al_final(2)
    lista.agregar_al_final(3)
    print("Lista después de agregar elementos:", lista.mostrar())
    
    lista.eliminar_por_valor(2)
    print("Lista después de eliminar el elemento 2:", lista.mostrar())
    
    encontrado = lista.buscar(3)
    print("¿El elemento 3 está en la lista?", encontrado)
    
    encontrado = lista.buscar(2)
    print("¿El elemento 2 está en la lista?", encontrado)