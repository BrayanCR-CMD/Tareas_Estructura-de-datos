# metodo de ordenamiento bucket sort
def bucket_sort(arr):
    if len(arr) == 0:
        return arr

    # Crear los buckets
    min_value = min(arr)
    max_value = max(arr)
    bucket_count = len(arr)
    bucket_size = (max_value - min_value) / bucket_count
    buckets = [[] for _ in range(bucket_count)]

    # Distribuir los elementos en los buckets
    for num in arr:
        index = int((num - min_value) / bucket_size)
        if index == bucket_count:  # Manejar el caso del valor máximo
            index -= 1
        buckets[index].append(num)

    # Ordenar cada bucket y concatenar los resultados
    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(sorted(bucket))

    return sorted_arr

# Ejemplo de uso
if __name__ == "__main__":
    data = [0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.55, 0.43, 0.88]
    sorted_data = bucket_sort(data)
    print("Array original:", data)
    print("Array ordenado:", sorted_data)