#metodo de ordenamiento shell sort
def shell_sort(arr):
    n = len(arr)
    gap = n // 2  # Inicializa el gap

    # Reduce el gap hasta que sea 0
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            # Mueve los elementos del arreglo que son mayores que temp
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2  # Reduce el gap

    return arr

# Ejemplo de uso
numeros = [12, 34, 54, 2, 3]
print("Arreglo original:", numeros)
sorted_numeros = shell_sort(numeros)
print("Arreglo ordenado:", sorted_numeros)