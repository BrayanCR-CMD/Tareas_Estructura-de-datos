using System;

class Program
{
    const int TAM = 10;
    static char[,] tablero1 = new char[TAM, TAM];
    static char[,] tablero2 = new char[TAM, TAM];
    static char[,] vista1 = new char[TAM, TAM]; // lo que el jugador 1 ve del jugador 2
    static char[,] vista2 = new char[TAM, TAM]; // lo que el jugador 2 ve del jugador 1

    // Barcos: portaaviones(5), acorazado(4), crucero(3), submarino(3), destructor(2)
    static int[] barcos = { 5, 4, 3, 3, 2 };

    static void Main()
    {
        Inicializar(tablero1);
        Inicializar(tablero2);
        Inicializar(vista1);
        Inicializar(vista2);

        Console.WriteLine("=== BATALLA NAVAL ===");
        Console.WriteLine("Tablero 10x10 (A-J, 1-10)");
        Console.WriteLine();

        Console.WriteLine("Jugador 1 coloca sus barcos:");
        ColocarFlota(tablero1);
        Console.Clear();

        Console.WriteLine("Jugador 2 coloca sus barcos:");
        ColocarFlota(tablero2);
        Console.Clear();

        int turno = 1;
        while (true)
        {
            if (turno == 1)
            {
                Console.WriteLine("Turno del Jugador 1");
                MostrarTablero(vista1);
                Disparar(tablero2, vista1);
                if (TodosHundidos(tablero2))
                {
                    Console.WriteLine("¡Jugador 1 ha ganado!");
                    break;
                }
                turno = 2;
            }
            else
            {
                Console.WriteLine("Turno del Jugador 2");
                MostrarTablero(vista2);
                Disparar(tablero1, vista2);
                if (TodosHundidos(tablero1))
                {
                    Console.WriteLine("¡Jugador 2 ha ganado!");
                    break;
                }
                turno = 1;
            }
            Console.Clear();
        }
    }

    static void Inicializar(char[,] t)
    {
        for (int i = 0; i < TAM; i++)
            for (int j = 0; j < TAM; j++)
                t[i, j] = '.';
    }

    static void MostrarTablero(char[,] t)
    {
        Console.Write("   ");
        for (int j = 0; j < TAM; j++) Console.Write((j + 1).ToString().PadLeft(3));
        Console.WriteLine();

        for (int i = 0; i < TAM; i++)
        {
            Console.Write((char)('A' + i) + "  ");
            for (int j = 0; j < TAM; j++)
                Console.Write("  " + t[i, j]);
            Console.WriteLine();
        }
    }

    static void ColocarFlota(char[,] t)
    {
        foreach (int tam in barcos)
        {
            bool colocado = false;
            while (!colocado)
            {
                MostrarTablero(t);
                Console.WriteLine($"Coloca un barco de tamaño {tam}");
                Console.Write("Coordenada inicial (ejemplo A5): ");
                string entrada = Console.ReadLine().ToUpper();

                if (!ConvertirCoordenada(entrada, out int fila, out int col))
                {
                    Console.WriteLine("Coordenada inválida.");
                    continue;
                }

                Console.Write("Orientación (H o V): ");
                string orient = Console.ReadLine().ToUpper();
                bool horiz = orient == "H";

                if (PuedeColocar(t, fila, col, tam, horiz))
                {
                    for (int i = 0; i < tam; i++)
                    {
                        if (horiz) t[fila, col + i] = 'S';
                        else t[fila + i, col] = 'S';
                    }
                    colocado = true;
                }
                else
                {
                    Console.WriteLine("No se puede colocar ahí, intenta de nuevo.");
                }
                Console.Clear();
            }
        }
    }

    static bool PuedeColocar(char[,] t, int f, int c, int tam, bool horiz)
    {
        if (horiz)
        {
            if (c + tam > TAM) return false;
            for (int i = 0; i < tam; i++)
                if (t[f, c + i] != '.') return false;
        }
        else
        {
            if (f + tam > TAM) return false;
            for (int i = 0; i < tam; i++)
                if (t[f + i, c] != '.') return false;
        }
        return true;
    }

    static void Disparar(char[,] tablero, char[,] vista)
    {
        bool valido = false;
        while (!valido)
        {
            Console.Write("Disparo (ejemplo B7): ");
            string entrada = Console.ReadLine().ToUpper();
            if (!ConvertirCoordenada(entrada, out int f, out int c))
            {
                Console.WriteLine("Coordenada inválida.");
                continue;
            }

            if (vista[f, c] != '.')
            {
                Console.WriteLine("Ya disparaste ahí.");
                continue;
            }

            if (tablero[f, c] == 'S')
            {
                Console.WriteLine("¡Impacto!");
                tablero[f, c] = 'X';
                vista[f, c] = 'X';
            }
            else
            {
                Console.WriteLine("Agua...");
                tablero[f, c] = 'o';
                vista[f, c] = 'o';
            }
            valido = true;
        }
        Console.WriteLine("Presiona una tecla para continuar...");
        Console.ReadKey();
    }

    static bool ConvertirCoordenada(string entrada, out int fila, out int col)
    {
        fila = col = -1;
        if (string.IsNullOrEmpty(entrada)) return false;
        char letra = entrada[0];
        if (letra < 'A' || letra > 'J') return false;
        fila = letra - 'A';

        if (!int.TryParse(entrada.Substring(1), out int num)) return false;
        if (num < 1 || num > TAM) return false;
        col = num - 1;
        return true;
    }

    static bool TodosHundidos(char[,] t)
    {
        for (int i = 0; i < TAM; i++)
            for (int j = 0; j < TAM; j++)
                if (t[i, j] == 'S') return false;
        return true;
    }
}