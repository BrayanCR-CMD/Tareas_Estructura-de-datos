# metodo de ordenamiento tree sort
class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.val = key
def insert(root, key):
    if root is None:
        return Node(key)
    else:
        if root.val < key:
            root.right = insert(root.right, key)
        else:
            root.left = insert(root.left, key)
    return root
def inorder_traversal(root, res):
    if root:
        inorder_traversal(root.left, res)
        res.append(root.val)
        inorder_traversal(root.right, res)
    return res

# Ejemplo de uso
numeros = [5, 3, 8, 1, 4]
r = Node(numeros[0])
for num in numeros[1:]:
    insert(r, num)
sorted_numeros = inorder_traversal(r, [])
print("Arreglo original:", numeros)
print("Arreglo ordenado:", sorted_numeros)