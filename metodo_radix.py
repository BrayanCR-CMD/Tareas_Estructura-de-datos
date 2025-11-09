#metodo de ordenamiento radix sort
def counting_sort_for_radix(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10

    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1

    for i in range(n):
        arr[i] = output[i]

def radix_sort(arr):
    max1 = max(arr)

    exp = 1
    while max1 // exp > 0:
        counting_sort_for_radix(arr, exp)
        exp *= 10

# Ejemplo de uso
numeros = [170, 45, 75, 90, 802, 24, 2, 66]
print("Arreglo original:", numeros)
radix_sort(numeros)
print("Arreglo ordenado:", numeros)