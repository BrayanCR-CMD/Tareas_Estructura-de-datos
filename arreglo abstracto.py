#arreglo abstracto
import os
class persona:
    nombre = str
    edad = int
    estatura = float

estudiante = [persona() for i in range (3)]
for i in range (3):
    estudiante[i].nombre = input("ingrese el nombre: ")
    estudiante[i].edad = int(input("ingrese la edad: "))
    estudiante[i].estatura = float(input("ingrese la estatura: "))
os.system('cls')
for i in range (3):
    print("nombre: ", estudiante[i].nombre)
    print("edad: ", estudiante[i].edad)
    print("estatura: ", estudiante[i].estatura)