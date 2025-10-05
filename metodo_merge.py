# metodo de ordenamiento merge sort
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2  # Encuentra el punto medio del arreglo
        L = arr[:mid]        # Divide el arreglo en dos mitades
        R = arr[mid:]

        merge_sort(L)  # Ordena la primera mitad
        merge_sort(R)  # Ordena la segunda mitad

        i = j = k = 0

        # Copia los datos a los arreglos temporales L[] y R[]
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        # Verifica si quedaron elementos
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1
    return arr

# Ejemplo de uso

numeros = [38, 27, 43, 3, 9, 82, 10]
print("Arreglo original:", numeros)
sorted_numeros = merge_sort(numeros)
print("Arreglo ordenado:", sorted_numeros)