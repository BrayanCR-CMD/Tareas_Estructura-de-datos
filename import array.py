import array
# Captura la cantidad de números
n = int(input("¿Cuántos números deseas ingresar? "))
numeros = []

# Captura los números
for i in range(n):
    num = int(input(f"Ingrese el número {i+1}: "))
    numeros.append(num)

# Muestra los números usando for
print("Los números ingresados son:")
for numero in numeros:
    print(numero)