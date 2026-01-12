MAXSIZE = 5
queue = [0] * MAXSIZE
front = -1
rear = -1

def insertar():
    global front, rear
    elemento = int(input("Ingrese el elemento a insertar: "))

    if rear == MAXSIZE - 1:
        print("Desbordamiento de cola")
        return

    if front == -1 and rear == -1:
        front = rear = 0
    else:
        rear += 1

    queue[rear] = elemento
    print(f"Elemento insertado: {elemento}")

def eliminar():
    global front, rear

    if front == -1 or front > rear:
        print("Subdesbordamiento de cola")
        return

    elemento = queue[front]

    if front == rear:
        front = rear = -1
    else:
        front += 1

    print(f"Elemento eliminado: {elemento}")

def mostrar():
    if rear == -1 or front == -1 or front > rear:
        print("La cola está vacía")
    else:
        print("Elementos en la cola:", end=" ")
        for i in range(front, rear + 1):
            print(queue[i], end=" ")
        print()

def menu():
    while True:
        print("\nMenú de operaciones de cola")
        print("1. Insertar")
        print("2. Eliminar")
        print("3. Mostrar")
        print("4. Salir")

        opcion = input("Ingrese su opción: ")

        match opcion:
            case "1":
                insertar()
            case "2":
                eliminar()
            case "3":
                mostrar()
            case "4":
                print("Saliendo del programa")
                break
            case _:
                print("Opción inválida")

menu()
