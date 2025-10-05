#funcion de busqueda lineal
def busqueda_lineal(arr, buscar):
    for i in range(len(arr)):
        if arr[i] == buscar:
            return i
    return -1

# Ejemplo de uso
arr = [3, 6, 8, 10, 1, 2, 1]
print("Arreglo:", arr)
buscar = 10
indice = busqueda_lineal(arr, buscar)
if indice != -1:
    print(f"Elemento {buscar} encontrado en el índice: {indice + 1}.")
else:
    print(f"Elemento {buscar} no encontrado en el arreglo.")