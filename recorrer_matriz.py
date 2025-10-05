#recorrer matriz por columnas
def recorrer_matriz_columnas(matriz):
    filas = len(matriz)
    columnas = len(matriz[0])
    for j in range(columnas):
        for i in range(filas):
            print(matriz[i][j], end=' ')
        print()

#ejemplo de uso
matriz = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print("Recorrer matriz por columnas:")
recorrer_matriz_columnas(matriz)