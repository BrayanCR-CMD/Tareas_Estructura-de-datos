#metodo de ordenamiento por seleccion
def ordenar_seleccion(arr):
    n = len(arr)
    for i in range(n):
        small = i
        for j in range(i + 1, n):
            if arr[j] < arr[small]:
                small = j
        arr[i], arr[small] = arr[small], arr[i]
    return arr

# ejemplo de uso
numeros = [64, 25, 12, 22, 11]
print("Arreglo original:", numeros)
ordenado = ordenar_seleccion(numeros)
print("Arreglo ordenado:", ordenado)