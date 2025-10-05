public class metodo_tree {
    public static void main(String[] args) {
        // Crear el árbol binario de búsqueda (ABB)
        Nodo raiz = null;
        int[] valores = {8, 9, 10, 4, 5};
        for (int valor : valores) {
            raiz = insertar(raiz, valor);
        }

        // Llamar al método para imprimir el árbol
        System.out.println("Impresion del arbol en preorden:");
        imprimirPreorden(raiz);
        System.out.println("\nImpresion del arbol en inorden:");
        imprimirInorden(raiz);
    }

    // Método para insertar un valor en el ABB
    public static Nodo insertar(Nodo nodo, int valor) {
        if (nodo == null) {
            return new Nodo(valor);
        }
        if (valor < nodo.valor) {
            nodo.izquierda = insertar(nodo.izquierda, valor);
        } else {
            nodo.derecha = insertar(nodo.derecha, valor);
        }
        return nodo;
    }

    // Método para imprimir el árbol en preorden
    public static void imprimirPreorden(Nodo nodo) {
        if (nodo == null) {
            return;
        }
        System.out.print(nodo.valor + " ");
        imprimirPreorden(nodo.izquierda);
        imprimirPreorden(nodo.derecha);
    }

    // Método para imprimir el árbol en inorden
    public static void imprimirInorden(Nodo nodo) {
        if (nodo == null) {
            return;
        }
        imprimirInorden(nodo.izquierda);
        System.out.print(nodo.valor + " ");
        imprimirInorden(nodo.derecha);
    }
}

// Definición de la clase Nodo
class Nodo {
    int valor;
    Nodo izquierda, derecha;

    public Nodo(int item) {
        valor = item;
        izquierda = derecha = null;
    }
}