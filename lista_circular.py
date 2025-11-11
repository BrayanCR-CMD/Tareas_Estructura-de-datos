#lista circular
class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None

class ListaCircular:
    def __init__(self):
        self.cabeza = None

    def esta_vacia(self):
        return self.cabeza is None

    def agregar(self, dato):
        nuevo_nodo = Nodo(dato)
        if self.esta_vacia():
            self.cabeza = nuevo_nodo
            nuevo_nodo.siguiente = nuevo_nodo
        else:
            actual = self.cabeza
            while actual.siguiente != self.cabeza:
                actual = actual.siguiente
            actual.siguiente = nuevo_nodo
            nuevo_nodo.siguiente = self.cabeza

    def eliminar(self, dato):
        if self.esta_vacia():
            return

        actual = self.cabeza
        previo = None

        while True:
            if actual.dato == dato:
                if previo is not None:
                    previo.siguiente = actual.siguiente
                else:
                    # Si es el único nodo en la lista
                    if actual.siguiente == self.cabeza:
                        self.cabeza = None
                    else:
                        # Encontrar el último nodo para actualizar su siguiente
                        ultimo = self.cabeza
                        while ultimo.siguiente != self.cabeza:
                            ultimo = ultimo.siguiente
                        ultimo.siguiente = actual.siguiente
                        self.cabeza = actual.siguiente
                return
            previo = actual
            actual = actual.siguiente
            if actual == self.cabeza:
                break

    def mostrar(self):
        elementos = []
        if not self.esta_vacia():
            actual = self.cabeza
            while True:
                elementos.append(actual.dato)
                actual = actual.siguiente
                if actual == self.cabeza:
                    break
        return elementos
    
# Ejemplo de uso
if __name__ == "__main__":
    lista = ListaCircular()
    lista.agregar(1)
    lista.agregar(2)
    lista.agregar(3)
    print("Lista después de agregar elementos:", lista.mostrar())

    lista.eliminar(2)
    print("Lista después de eliminar el elemento 2:", lista.mostrar())

    lista.eliminar(1)
    print("Lista después de eliminar el elemento 1:", lista.mostrar())

    lista.eliminar(3)
    print("Lista después de eliminar el elemento 3:", lista.mostrar())