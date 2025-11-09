import random
import time
import pandas as pd
import matplotlib.pyplot as plt

# 1. IMPLEMENTACIÓN DE LOS MÉTODOS DE ORDENAMIENTO

# --- Bubble Sort ---
def bubble_sort(arr):
    """Ordenamiento burbuja: compara pares adyacentes e intercambia si están desordenados."""
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

# --- Insertion Sort ---
def insertion_sort(arr):
    """Inserta cada elemento en la posición correcta dentro de la parte ya ordenada."""
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# --- Selection Sort ---
def selection_sort(arr):
    """Busca el mínimo en el arreglo restante y lo coloca en su posición."""
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

# --- Quick Sort ---
def quick_sort(arr):
    """Ordenamiento rápido (Quick Sort) recursivo."""
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

# --- Merge Sort ---
def merge_sort(arr):
    """Divide el arreglo en mitades, las ordena y las combina."""
    if len(arr) > 1:
        mid = len(arr)//2
        L = arr[:mid]
        R = arr[mid:]
        merge_sort(L)
        merge_sort(R)
        i = j = k = 0
        # Combina las mitades ordenadas
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        # Agrega los elementos restantes
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# --- Heap Sort ---
def heapify(arr, n, i):
    """Reorganiza un subárbol para mantener la propiedad del heap."""
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    """Convierte el arreglo en un heap y luego lo ordena."""
    n = len(arr)
    # Construcción del heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    # Extrae elementos del heap uno por uno
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

# --- Bucket Sort ---
def bucket_sort(arr):
    """Distribuye los elementos en cubetas (buckets), los ordena y combina."""
    if len(arr) == 0:
        return arr
    bucket = [[] for _ in range(10)]
    max_value = max(arr)
    for num in arr:
        index = int(num / (max_value + 1) * 10)
        bucket[index].append(num)
    for i in range(10):
        bucket[i].sort()
    return [num for sublist in bucket for num in sublist]

# --- Radix Sort ---
def radix_sort(arr):
    """Ordena números dígito a dígito (base 10)."""
    RADIX = 10
    maxLength = False
    tmp, placement = -1, 1
    while not maxLength:
        maxLength = True
        buckets = [list() for _ in range(RADIX)]
        for i in arr:
            tmp = i // placement
            buckets[tmp % RADIX].append(i)
            if maxLength and tmp > 0:
                maxLength = False
        a = 0
        for b in range(RADIX):
            buck = buckets[b]
            for i in buck:
                arr[a] = i
                a += 1
        placement *= RADIX
    return arr

# --- Hash Sort (versión simple) ---
def hash_sort(arr):
    """Simula un ordenamiento usando una tabla hash (dict) + sort final."""
    table = {}
    for num in arr:
        table[num] = num
    return sorted(table.keys())

# 2. DEFINICIÓN DE ESCENARIOS DE PRUEBA

# Tamaños de los arreglos
sizes = [100, 1000, 10000, 100000]

# Tipos de orden inicial
types = ["Ordenado", "Medio", "Inverso"]

# Diccionario de algoritmos con sus funciones
algorithms = {
    "Bubble Sort": bubble_sort,
    "Insertion Sort": insertion_sort,
    "Selection Sort": selection_sort,
    "Quick Sort": lambda a: quick_sort(a.copy()),
    "Merge Sort": merge_sort,
    "Heap Sort": heap_sort,
    "Hash Sort": lambda a: hash_sort(a.copy()),
    "Bucket Sort": lambda a: bucket_sort(a.copy()),
    "Radix Sort": lambda a: radix_sort(a.copy())
}

# Lista para almacenar los resultados
results = []

# 3. EJECUCIÓN DE LAS PRUEBAS

# Se recorren los tamaños y tipos para formar los 12 escenarios
for size in sizes:
    base = list(range(size))
    for t in types:
        # Generación del arreglo según el tipo de orden
        if t == "Ordenado":
            arr = base.copy()
        elif t == "Medio":
            arr = base.copy()
            random.shuffle(arr)
        else:  # Inverso
            arr = base[::-1]

        # Ejecución de todos los algoritmos sobre el mismo escenario
        for name, func in algorithms.items():
            data = arr.copy()  # copia del arreglo original
            start = time.perf_counter()  # inicio de medición
            func(data)
            end = time.perf_counter()    # fin de medición
            results.append({
                "Método": name,
                "Tamaño": size,
                "Tipo": t,
                "Tiempo (s)": end - start
            })
            print(f"{name:<15} | {size:>6} | {t:<10} | {end - start:.5f}s")

# 4. VISUALIZACIÓN DE TODAS LAS GRÁFICAS POR TAMAÑO

import seaborn as sns
sns.set(style="whitegrid")

# Asegúrate de crear el DataFrame antes de usarlo
df = pd.DataFrame(results)

# Convertimos tiempos a milisegundos
df["Tiempo (ms)"] = df["Tiempo (s)"] * 1000

# Generar una gráfica por cada tamaño
for n in [100, 1000, 10000, 100000]:
    df_n = df[df["Tamaño"] == n]

    plt.figure(figsize=(10, 6))
    sns.barplot(
        data=df_n,
        x="Método",
        y="Tiempo (ms)",
        hue="Tipo",
        palette="deep"
    )

    plt.title(f"Tiempos de algoritmos de ordenamiento (n={n})", fontsize=13)
    plt.xlabel("Algoritmo", fontsize=11)
    plt.ylabel("Tiempo (ms)", fontsize=11)
    plt.legend(title="Tipo de arreglo")
    plt.xticks(rotation=30)
    plt.tight_layout()
    plt.show()