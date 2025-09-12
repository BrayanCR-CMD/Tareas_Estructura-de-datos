# El tablero se representa con una lista de 9 strings
tablero = ["-", "-", "-", "-", "-", "-", "-", "-", "-"]
juego_en_curso = True
ganador = None
jugador_actual = "X"

def mostrar_tablero():
    """Muestra el estado actual del tablero"""
    print("\n")
    print(tablero[0] + " | " + tablero[1] + " | " + tablero[2] + "     1 | 2 | 3")
    print(tablero[3] + " | " + tablero[4] + " | " + tablero[5] + "     4 | 5 | 6")
    print(tablero[6] + " | " + tablero[7] + " | " + tablero[8] + "     7 | 8 | 9")
    print("\n")

def manejar_turno(jugador):
    """Maneja el turno de un jugador"""
    print("Turno de " + jugador)
    posicion = input("Elige una posición del 1 al 9: ")

    valido = False
    while not valido:
        while posicion not in ["1", "2", "3", "4", "5", "6", "7", "8", "9"]:
            posicion = input("Entrada inválida. Elige una posición del 1 al 9: ")

        posicion = int(posicion) - 1

        if tablero[posicion] == "-":
            valido = True
        else:
            print("¡Esta posición ya está ocupada!")

    tablero[posicion] = jugador
    mostrar_tablero()

def verificar_ganador():
    """Verifica si hay un ganador"""
    global ganador

    # Verificar filas
    if tablero[0] == tablero[1] == tablero[2] and tablero[0] != "-":
        ganador = tablero[0]
        return True
    elif tablero[3] == tablero[4] == tablero[5] and tablero[3] != "-":
        ganador = tablero[3]
        return True
    elif tablero[6] == tablero[7] == tablero[8] and tablero[6] != "-":
        ganador = tablero[6]
        return True

    # Verificar columnas
    elif tablero[0] == tablero[3] == tablero[6] and tablero[0] != "-":
        ganador = tablero[0]
        return True
    elif tablero[1] == tablero[4] == tablero[7] and tablero[1] != "-":
        ganador = tablero[1]
        return True
    elif tablero[2] == tablero[5] == tablero[8] and tablero[2] != "-":
        ganador = tablero[2]
        return True

    # Verificar diagonales
    elif tablero[0] == tablero[4] == tablero[8] and tablero[0] != "-":
        ganador = tablero[0]
        return True
    elif tablero[2] == tablero[4] == tablero[6] and tablero[2] != "-":
        ganador = tablero[2]
        return True
    
    return False

def verificar_empate():
    """Verifica si el juego terminó en empate"""
    global juego_en_curso
    if "-" not in tablero:
        juego_en_curso = False
        return True
    return False

def cambiar_jugador():
    """Cambia el turno entre los jugadores 'X' y 'O'"""
    global jugador_actual
    if jugador_actual == "X":
        jugador_actual = "O"
    else:
        jugador_actual = "X"

def jugar_gato():
    """Función principal para ejecutar el juego"""
    global juego_en_curso, ganador

    while juego_en_curso:
        mostrar_tablero()
        manejar_turno(jugador_actual)

        if verificar_ganador():
            print("¡El ganador es " + ganador + "! 🎉")
            juego_en_curso = False
        elif verificar_empate():
            print("¡Empate! 🤝")
            juego_en_curso = False
        else:
            cambiar_jugador()

# Iniciar el juego
jugar_gato()