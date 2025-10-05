# metodo de ordenamiento por insercion
def ordenar_insercion(arr):
    for i in range(1, len(arr)):
        temp = arr[i]
        j = i - 1
        while j >= 0 and temp < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = temp
    return arr

# ejemplo de uso
numeros = [12, 11, 13, 5, 6]
print("Arreglo original:", numeros)
ordenado = ordenar_insercion(numeros)
print("Arreglo ordenado:", ordenado)