import random
import time
import os

# Configuración del juego
WIDTH, HEIGHT = 20, 20
SNAKE_CHAR = "■"
FOOD_CHAR = "●"
TRAP_CHAR = "X"
EMPTY_CHAR = " "

def gotoxy(x, y):
    """Posiciona el cursor en las coordenadas x,y de la terminal"""
    print(f"\033[{y};{x}H", end='')

def limpiar_pantalla():
    os.system('cls' if os.name == 'nt' else 'clear')

def inicializar_pantalla():
    """Dibuja el marco inicial y la información estática"""
    limpiar_pantalla()
    
    # Dibujar marco superior
    print("+" + "-" * WIDTH + "+")
    
    # Dibujar área de juego vacía
    for _ in range(HEIGHT):
        print("|" + " " * WIDTH + "|")
    
    # Dibujar marco inferior
    print("+" + "-" * WIDTH + "+")
    
    # Dibujar información estática
    gotoxy(1, HEIGHT + 3)
    print("Controles: w=arriba, s=abajo, a=izquierda, d=derecha, q=salir")
    print("Nivel: 1 | Tamaño: 5 | Items: 0")

def actualizar_ui(nivel, tamaño, items_count):
    """Actualiza solo la información de la UI"""
    gotoxy(1, HEIGHT + 4)
    print(f"Nivel: {nivel} | Tamaño: {tamaño} | Items: {items_count}")

def dibujar_elemento(x, y, char):
    """Dibuja un elemento en la posición específica"""
    gotoxy(x + 2, y + 2)  # +2 para compensar los márgenes
    print(char, end='')

def limpiar_elemento(x, y):
    """Limpia un elemento en la posición específica"""
    gotoxy(x + 2, y + 2)  # +2 para compensar los márgenes
    print(EMPTY_CHAR, end='')

def generar_items(items, snake):
    """Genera nuevos items si es necesario"""
    while len(items) < 3:  # Mantener 3 items en pantalla
        x = random.randint(0, WIDTH - 1)
        y = random.randint(0, HEIGHT - 1)
        pos = [x, y]
        
        if pos not in snake and pos not in [item[0] for item in items]:
            if random.random() < 0.7:
                items.append([pos, "comida", FOOD_CHAR, time.time()])
                # Dibujar nuevo item inmediatamente
                dibujar_elemento(x, y, FOOD_CHAR)
            else:
                items.append([pos, "trampa", TRAP_CHAR, time.time()])
                # Dibujar nuevo item inmediatamente
                dibujar_elemento(x, y, TRAP_CHAR)
            break

def actualizar_items(items, snake):
    """Elimina items expirados y los quita de la pantalla"""
    tiempo_actual = time.time()
    items_actualizados = []
    
    for item in items:
        pos, tipo, char, tiempo_creacion = item
        tiempo_vida = 12 if tipo == "comida" else 7  # Comida 12s, Trampas 7s
        
        if tiempo_actual - tiempo_creacion < tiempo_vida:
            items_actualizados.append(item)
        else:
            # Item expirado - limpiar de la pantalla
            limpiar_elemento(pos[0], pos[1])
    
    return items_actualizados

def mover_serpiente(snake, nueva_cabeza, items):
    """Mueve la serpiente y maneja colisiones con items"""
    cola_anterior = snake[-1] if len(snake) > 1 else None
    
    # Verificar colisión consigo misma
    if nueva_cabeza in snake:
        return False, None
    
    # Insertar nueva cabeza
    snake.insert(0, nueva_cabeza)
    
    # Dibujar nueva cabeza
    dibujar_elemento(nueva_cabeza[0], nueva_cabeza[1], SNAKE_CHAR)
    
    # Verificar colisión con items
    item_comido = False
    for i, item in enumerate(items):
        if nueva_cabeza == item[0]:
            if item[1] == "comida":
                # Comida: mantener la nueva cabeza (crecer)
                item_comido = True
            else:
                # Trampa: eliminar cola
                if len(snake) > 1:
                    cola_eliminada = snake.pop()
                    limpiar_elemento(cola_eliminada[0], cola_eliminada[1])
            # Eliminar el item de la pantalla y la lista
            limpiar_elemento(item[0][0], item[0][1])
            items.pop(i)
            item_comido = True
            break
    
    # Si no comió, eliminar cola
    if not item_comido and len(snake) > 5:
        cola_eliminada = snake.pop()
        limpiar_elemento(cola_eliminada[0], cola_eliminada[1])
    
    return True, cola_anterior

def juego_snake():
    # Inicializar pantalla
    inicializar_pantalla()
    
    # Inicializar serpiente
    snake = []
    for i in range(5):
        snake.append([WIDTH//2 - i, HEIGHT//2])
    
    # Dibujar serpiente inicial
    for segmento in snake:
        dibujar_elemento(segmento[0], segmento[1], SNAKE_CHAR)
    
    direccion = [1, 0]
    items = []
    nivel = 1
    velocidad = 0.3
    ultimo_movimiento = time.time()
    ultima_reduccion = time.time()
    intervalo_reduccion = 10
    
    # Generar items iniciales
    for _ in range(3):
        generar_items(items, snake)
    
    # Posicionar cursor fuera del área de juego inicialmente
    gotoxy(1, HEIGHT + 6)
    
    while True:
        # Leer input
        try:
            import select
            import sys
            if select.select([sys.stdin], [], [], 0.1)[0]:
                key = sys.stdin.read(1).lower()
                if key == 'q':
                    break
                elif key == 'w' and direccion != [0, 1]:
                    direccion = [0, -1]
                elif key == 's' and direccion != [0, -1]:
                    direccion = [0, 1]
                elif key == 'a' and direccion != [1, 0]:
                    direccion = [-1, 0]
                elif key == 'd' and direccion != [-1, 0]:
                    direccion = [1, 0]
        except:
            # Para Windows o si falla el método anterior
            try:
                import msvcrt
                if msvcrt.kbhit():
                    key = msvcrt.getch().decode('utf-8').lower()
                    if key == 'q':
                        break
                    elif key == 'w' and direccion != [0, 1]:
                        direccion = [0, -1]
                    elif key == 's' and direccion != [0, -1]:
                        direccion = [0, 1]
                    elif key == 'a' and direccion != [1, 0]:
                        direccion = [-1, 0]
                    elif key == 'd' and direccion != [-1, 0]:
                        direccion = [1, 0]
            except:
                pass
        
        # Movimiento
        tiempo_actual = time.time()
        if tiempo_actual - ultimo_movimiento > velocidad:
            # Nueva cabeza
            cabeza = snake[0].copy()
            cabeza[0] = (cabeza[0] + direccion[0]) % WIDTH
            cabeza[1] = (cabeza[1] + direccion[1]) % HEIGHT
            
            # Mover serpiente
            movimiento_valido, cola_anterior = mover_serpiente(snake, cabeza, items)
            if not movimiento_valido:
                gotoxy(1, HEIGHT + 7)
                print("¡Perdiste! Chocaste contigo misma.")
                break
            
            ultimo_movimiento = tiempo_actual
            
            # Actualizar items (eliminar los expirados)
            items = actualizar_items(items, snake)
            
            # Generar nuevos items si es necesario
            if len(items) < 3:
                generar_items(items, snake)
            
            # Actualizar UI
            actualizar_ui(nivel, len(snake), len(items))
            
            # Cambiar nivel
            if len(snake) >= 15:
                nivel += 1
                if nivel % 3 == 0:
                    velocidad = max(0.1, velocidad * 0.8)
                    intervalo_reduccion = max(5, intervalo_reduccion - 1)
                
                # Limpiar serpiente anterior
                for segmento in snake:
                    limpiar_elemento(segmento[0], segmento[1])
                
                # Reiniciar serpiente
                cabeza_actual = snake[0]
                snake = []
                for i in range(5):
                    snake.append([cabeza_actual[0] - i, cabeza_actual[1]])
                
                # Dibujar nueva serpiente
                for segmento in snake:
                    dibujar_elemento(segmento[0], segmento[1], SNAKE_CHAR)
                
                # Limpiar items
                for item in items:
                    limpiar_elemento(item[0][0], item[0][1])
                items = []
                for _ in range(3):
                    generar_items(items, snake)
                
                actualizar_ui(nivel, len(snake), len(items))
                gotoxy(1, HEIGHT + 7)
                print(f"¡Nivel {nivel} completado!          ")
        
        # Reducción automática
        if tiempo_actual - ultima_reduccion > intervalo_reduccion:
            if len(snake) > 1:
                cola_eliminada = snake.pop()
                limpiar_elemento(cola_eliminada[0], cola_eliminada[1])
                ultima_reduccion = tiempo_actual
                actualizar_ui(nivel, len(snake), len(items))
            if len(snake) == 0:
                gotoxy(1, HEIGHT + 7)
                print("¡Perdiste! La serpiente desapareció.")
                break
        
        # Actualizar items periódicamente (por si no hay movimiento)
        items_anteriores = len(items)
        items = actualizar_items(items, snake)
        if len(items) != items_anteriores:
            actualizar_ui(nivel, len(snake), len(items))
        
        # Generar items si hay muy pocos
        if len(items) < 2:
            generar_items(items, snake)
            actualizar_ui(nivel, len(snake), len(items))
        
        # Pequeña pausa para evitar uso excesivo de CPU
        time.sleep(0.01)

if __name__ == "__main__":
    try:
        juego_snake()
    finally:
        # Asegurarse de que el cursor vuelva al final
        gotoxy(1, HEIGHT + 10)
        print("Juego terminado.")
