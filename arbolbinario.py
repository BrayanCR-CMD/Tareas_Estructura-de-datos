import sys
class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

# arbol Binario de Búsqueda 
class BST:
    def __init__(self):
        self.root = None

    # --- INSERCIÓN ---
    def insert(self, key):
        self.root = self._insert_rec(self.root, key)

    def _insert_rec(self, node, key):
        # Si el nodo está vacío, crea uno nuevo
        if node is None:
            return Node(key)
        # Menores a la izquierda, Mayores a la derecha 
        if key < node.key:
            node.left = self._insert_rec(node.left, key)
        elif key > node.key:
            node.right = self._insert_rec(node.right, key)
        return node

    # --- Busqueda ---
    def search(self, key):
        return self._search_rec(self.root, key)

    def _search_rec(self, node, key):
        if node is None or node.key == key:
            return node
        if key < node.key:
            return self._search_rec(node.left, key)
        return self._search_rec(node.right, key)

    # --- Eliminación ---
    def delete(self, key):
        self.root = self._delete_rec(self.root, key)

    def _delete_rec(self, node, key):
        if node is None: return node

        # Buscar el nodo a eliminar
        if key < node.key:
            node.left = self._delete_rec(node.left, key)
        elif key > node.key:
            node.right = self._delete_rec(node.right, key)
        else:
            # Caso 1 y 2: Sin hijos o con un solo hijo
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left

            # Caso 3: Dos hijos 
            # Busca el sucesor (el más pequeño del subárbol derecho)
            temp = self._min_value_node(node.right)
            node.key = temp.key # Copiamos el valor
            # Elimina el sucesor duplicado
            node.right = self._delete_rec(node.right, temp.key)

        return node

    def _min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current

    # --- RECORRIDOS  ---
    def inorder(self):
        result = []
        self._inorder_rec(self.root, result)
        print("Inorder:", result)
        return result

    def _inorder_rec(self, node, result):
        if node:
            self._inorder_rec(node.left, result)
            result.append(node.key)
            self._inorder_rec(node.right, result)

    def preorder(self):
        result = []
        self._preorder_rec(self.root, result)
        print("Preorder:", result)

    def _preorder_rec(self, node, result):
        if node:
            result.append(node.key)
            self._preorder_rec(node.left, result)
            self._preorder_rec(node.right, result)

    def postorder(self):
        result = []
        self._postorder_rec(self.root, result)
        print("Postorder:", result)

    def _postorder_rec(self, node, result):
        if node:
            self._postorder_rec(node.left, result)
            self._postorder_rec(node.right, result)
            result.append(node.key)

    # (Altura y Tamaño)
    def height(self):
        print(f"Altura: {self._height_rec(self.root)}")

    def _height_rec(self, node):
        if node is None: return 0 # Base: altura 0 si no hay nodo
        # La altura es 1 + la mayor altura entre sus hijos 
        return 1 + max(self._height_rec(node.left), self._height_rec(node.right))

    def size(self):
        print(f"Tamaño (nodos): {self._size_rec(self.root)}")

    def _size_rec(self, node):
        if node is None: return 0
        return 1 + self._size_rec(node.left) + self._size_rec(node.right)

    def export_inorder(self, filename="tree_export.txt"):
        result = []
        self._inorder_rec(self.root, result)
        try:
            with open(filename, "w") as f:
                f.write(str(result))
            print(f"Exportado exitosamente a {filename}")
        except IOError as e:
            print(f"Error al escribir archivo: {e}")

# 3. INTERFAZ
def main():
    tree = BST()
    print("--- Gestor de Números ---")
    print("Escribe 'help' para ver los comandos.")

    while True:
        try:
            command_input = input("\n> ").strip().split()
            if not command_input: continue

            cmd = command_input[0].lower()
            args = command_input[1:]

            if cmd == "insert":
                if args: tree.insert(int(args[0]))
                else: print("Uso: insert <numero>")
            elif cmd == "search":
                if args:
                    found = tree.search(int(args[0]))
                    print(f"Encontrado: {found.key}" if found else "No encontrado")
                else: print("Uso: search <numero>")
            elif cmd == "delete":
                if args: tree.delete(int(args[0]))
                else: print("Uso: delete <numero>")
            elif cmd == "inorder": tree.inorder()
            elif cmd == "preorder": tree.preorder()
            elif cmd == "postorder": tree.postorder()
            elif cmd == "height": tree.height()
            elif cmd == "size": tree.size()
            elif cmd == "export": tree.export_inorder()
            elif cmd == "help":
                print("Comandos: insert, search, delete, inorder, preorder, postorder, height, size, export, exit")
            elif cmd == "exit":
                print("Saliendo...")
                break
            else:
                print("Comando desconocido.")
        except ValueError:
            print("Por favor ingresa un número válido.")
        except Exception as e:
            print(f"Ocurrió un error: {e}")

if __name__ == "__main__":
    main()
