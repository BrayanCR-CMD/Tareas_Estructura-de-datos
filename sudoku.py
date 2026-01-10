from typing import List, Tuple
import random
import sys
import argparse
# Estilos ANSI (colores)

USE_COLORS = True
HIGH_CONTRAST = False
RESET = "\033[0m"
BOLD = "\033[1m"
DIM = "\033[2m"
FG_CYAN = "\033[36m"
FG_GREEN = "\033[32m"
FG_YELLOW = "\033[33m"
FG_MAGENTA = "\033[35m"
FG_BRIGHT_CYAN = "\033[96m"
FG_BRIGHT_GREEN = "\033[92m"
FG_BRIGHT_YELLOW = "\033[93m"
FG_BRIGHT_WHITE = "\033[97m"


def style_original(text: str) -> str:
    if not USE_COLORS:
        return text
    color = FG_BRIGHT_CYAN if HIGH_CONTRAST else FG_CYAN
    return f"{BOLD}{color}{text}{RESET}"


def style_user(text: str) -> str:
    if not USE_COLORS:
        return text
    color = FG_BRIGHT_YELLOW if HIGH_CONTRAST else FG_GREEN
    return f"{BOLD}{color}{text}{RESET}"


def style_empty(text: str) -> str:
    if not USE_COLORS:
        return text
    # En alto contraste usa blanco brillante tenue
    return f"{FG_BRIGHT_WHITE}{DIM}{text}{RESET}" if HIGH_CONTRAST else f"{DIM}{text}{RESET}"


def style_banner(text: str) -> str:
    return f"{BOLD}{FG_MAGENTA}{text}{RESET}" if USE_COLORS else text



# Tipos

Grid = List[List[int]]



# Generador y solucionador

def _find_empty(grid: Grid) -> Tuple[int, int] | None:
    for r in range(9):
        for c in range(9):
            if grid[r][c] == 0:
                return r, c
    return None


def _is_safe(grid: Grid, row: int, col: int, num: int) -> bool:
    for i in range(9):
        if grid[row][i] == num:
            return False
        if grid[i][col] == num:
            return False
    start_r = (row // 3) * 3
    start_c = (col // 3) * 3
    for r in range(start_r, start_r + 3):
        for c in range(start_c, start_c + 3):
            if grid[r][c] == num:
                return False
    return True


def _solve_backtracking(grid: Grid) -> bool:
    empty = _find_empty(grid)
    if not empty:
        return True
    r, c = empty
    nums = list(range(1, 10))
    for num in nums:
        if _is_safe(grid, r, c, num):
            grid[r][c] = num
            if _solve_backtracking(grid):
                return True
            grid[r][c] = 0
    return False


def count_solutions(grid: Grid) -> int:
    count = 0
    def solve():
        nonlocal count
        empty = _find_empty(grid)
        if not empty:
            count += 1
            return
        r, c = empty
        for num in range(1, 10):
            if _is_safe(grid, r, c, num):
                grid[r][c] = num
                solve()
                grid[r][c] = 0
                if count > 1:
                    return  # early stop
    solve()
    return count


def _fill_complete_grid() -> Grid:
    grid: Grid = [[0 for _ in range(9)] for _ in range(9)]

    def fill() -> bool:
        empty = _find_empty(grid)
        if not empty:
            return True
        r, c = empty
        nums = list(range(1, 10))
        random.shuffle(nums)
        for num in nums:
            if _is_safe(grid, r, c, num):
                grid[r][c] = num
                if fill():
                    return True
                grid[r][c] = 0
        return False

    fill()
    return grid


def _copy_grid(grid: Grid) -> Grid:
    return [row[:] for row in grid]


def generate_puzzle(level: int) -> Tuple[Grid, Grid]:
    """
    Genera un puzzle (con ceros como vacíos) y su solución.
    La dificultad se controla por cantidad de pistas.
    """
    # Dificultad creciente por nivel: menos pistas a mayor nivel.
    # Nivel 1 ≈50 pistas (fácil) -> Nivel 5 ≈24 pistas (difícil)
    base_clues = 50
    step = 8
    clues = max(24, base_clues - (level - 1) * step)

    while True:
        solution = _fill_complete_grid()
        puzzle = _copy_grid(solution)

        total_cells = 81
        to_remove = total_cells - clues
        positions = [(r, c) for r in range(9) for c in range(9)]
        random.shuffle(positions)

        removed = 0
        for r, c in positions:
            if removed >= to_remove:
                break
            if puzzle[r][c] != 0:
                puzzle[r][c] = 0
                removed += 1

        # Verificar que tenga exactamente una solución
        temp_grid = _copy_grid(puzzle)
        if count_solutions(temp_grid) == 1:
            break

    return puzzle, solution


def check_complete(board: Grid) -> bool:
    return all(all(cell != 0 for cell in row) for row in board)


def validate_move(board: Grid, original_mask: List[List[bool]], row: int, col: int, val: int) -> Tuple[bool, str]:
    if not (0 <= row < 9 and 0 <= col < 9):
        return False, "Coordenadas fuera de rango (1-9)."
    if original_mask[row][col]:
        return False, "No puedes cambiar una pista original."
    if not (1 <= val <= 9):
        return False, "Valor fuera de rango (1-9)."
    return True, ""



# Interfaz por consola

def render_board(board: Grid, original_mask: List[List[bool]]) -> str:
    # Cabecera columnas
    lines: List[str] = []
    header_cols = " ".join([str(c + 1) for c in range(9)])
    lines.append(style_banner("   " + header_cols))

    # Líneas superior/medio/inferior (unicode box drawing)
    h_group = "─────────"  # 9 celdas (3*3), cada celda ancho 3
    top = f"   ┌{h_group}┬{h_group}┬{h_group}┐"
    mid = f"   ├{h_group}┼{h_group}┼{h_group}┤"
    bottom = f"   └{h_group}┴{h_group}┴{h_group}┘"
    lines.append(top)


    for r in range(9):
        def cell_str(v: int, is_orig: bool) -> str:
            if v == 0:
                return style_empty(" . ")
            s = f" {v} "
            return style_original(s) if is_orig else style_user(s)

        group1 = "".join([cell_str(board[r][c], original_mask[r][c]) for c in range(0, 3)])
        group2 = "".join([cell_str(board[r][c], original_mask[r][c]) for c in range(3, 6)])
        group3 = "".join([cell_str(board[r][c], original_mask[r][c]) for c in range(6, 9)])
        line = f"{r + 1:>2} │{group1}│{group2}│{group3}│"
        lines.append(line)
        if r in (2, 5):
            lines.append(mid)
    lines.append(bottom)
    return "\n".join(lines)


def prompt_help() -> str:
    legend = (
        f"Leyenda: Original {style_original('número')} | Jugada {style_user('número')} | Vacía {style_empty('.')}\n"
    )
    return (
        legend
        + "Comandos:\n"
        + "- Colocar número: 'fila columna valor' (ej: 3 7 9)\n"
        + "- Borrar número: 'borrar fila columna'\n"
        + "- Ver tablero: 'ver'\n"
        + "- Salir: 'salir'\n"
    )



# Gestor del juego

class GameManager:
    def __init__(self, levels: int = 5, puzzles_per_level: int = 5, lives_per_game: int = 5):
        self.total_levels = levels
        self.puzzles_per_level = puzzles_per_level
        self.lives_per_game = lives_per_game
        self.current_level = 1
        self.puzzles_solved_in_level = 0

    def _make_original_mask(self, puzzle: Grid) -> List[List[bool]]:
        return [[puzzle[r][c] != 0 for c in range(9)] for r in range(9)]

    def _play_single_puzzle(self, puzzle: Grid, solution: Grid) -> bool:
        board: Grid = [row[:] for row in puzzle]
        original_mask = self._make_original_mask(puzzle)
        lives = self.lives_per_game

        # Corregimos banner para que sea una sola línea de 30 caracteres
        banner_top = style_banner("\n" + ("═" * 30))
        print(banner_top)
        print(style_banner(f"Nivel {self.current_level} | Ganadas: {self.puzzles_solved_in_level}/{self.puzzles_per_level} | Vidas: {lives}"))
        print(render_board(board, original_mask))
        print(prompt_help())

        while True:
            if board == solution:
                print("\n¡Tablero completo! Partida ganada.")
                return True

            cmd = input("Ingresa tu jugada o comando: ").strip().lower()

            if cmd == "salir":
                print("Saliendo del juego. ¡Hasta luego!")
                sys.exit(0)
            if cmd == "ver":
                print(render_board(board, original_mask))
                continue
            if cmd.startswith("borrar"):
                parts = cmd.split()
                if len(parts) != 3:
                    print("Uso: borrar fila columna")
                    continue
                try:
                    r = int(parts[1]) - 1
                    c = int(parts[2]) - 1
                except ValueError:
                    print("Fila/columna deben ser números (1-9).")
                    continue
                if not (0 <= r < 9 and 0 <= c < 9):
                    print("Coordenadas fuera de rango (1-9).")
                    continue
                if original_mask[r][c]:
                    print("No puedes borrar una pista original.")
                    continue
                board[r][c] = 0
                print(render_board(board, original_mask))
                continue

            parts = cmd.split()
            if len(parts) == 3:
                try:
                    r = int(parts[0]) - 1
                    c = int(parts[1]) - 1
                    v = int(parts[2])
                except ValueError:
                    print("Entrada inválida. Usa: fila columna valor (ej: 3 7 9)")
                    continue

                ok, msg = validate_move(board, original_mask, r, c, v)
                if not ok:
                    print(msg)
                    continue

                if not _is_safe(board, r, c, v):
                    lives -= 1
                    print(f"Movimiento inválido: viola reglas de Sudoku. Pierdes una vida. Vidas restantes: {lives}")
                    if lives <= 0:
                        print("Has perdido todas las vidas en esta partida.")
                        return False
                    continue

                board[r][c] = v
                print(render_board(board, original_mask))
                continue

            print("Comando no reconocido. Escribe 'ver', 'salir', 'borrar fila columna' o 'fila columna valor'.")

    def play_level(self):
        while self.puzzles_solved_in_level < self.puzzles_per_level:
            puzzle, solution = generate_puzzle(self.current_level)
            solved = self._play_single_puzzle(puzzle, solution)
            if solved:
                self.puzzles_solved_in_level += 1
                print(f"Progreso: {self.puzzles_solved_in_level}/{self.puzzles_per_level} partidas ganadas en nivel {self.current_level}.")
            else:
                print("Cambiando a otro tablero del mismo nivel. ¡Ánimo!")

        print(f"\n¡Nivel {self.current_level} completado! Pasas al siguiente nivel.")
        self.current_level += 1
        self.puzzles_solved_in_level = 0

    def start(self):
        print("Bienvenido/a al Sudoku con niveles, vidas y partidas.")
        print("Debes ganar 5 partidas por nivel para avanzar. ¡Suerte!")

        while self.current_level <= self.total_levels:
            self.play_level()

        print("\n¡Felicidades! Has completado los 5 niveles.")



# Punto de entrada

def main():
    parser = argparse.ArgumentParser(description="Sudoku con niveles, vidas y partidas (consola)")
    parser.add_argument("--no-color", action="store_true", help="Desactivar colores ANSI en la salida")
    parser.add_argument("--high-contrast", action="store_true", help="Usar colores de alto contraste para mejor visibilidad")
    args = parser.parse_args()

    # Aplicar opciones de estilo
    global USE_COLORS, HIGH_CONTRAST
    if args.no_color:
        USE_COLORS = False
    HIGH_CONTRAST = args.high_contrast and USE_COLORS

    game = GameManager(levels=5, puzzles_per_level=5, lives_per_game=5)
    game.start()


if __name__ == "__main__":
    main()