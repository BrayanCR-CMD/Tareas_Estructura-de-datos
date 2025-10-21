import java.util.Random;
import java.util.Scanner;

public class Laberinto {

    static final int TAM = 25;
    static char[][] laberinto = new char[TAM][TAM];
    static boolean[][] descubierto = new boolean[TAM][TAM]; // células que el jugador ha visto/interactuado
    static int jugadorX, jugadorY;
    static int vidas;
    static final int VIDAS_INICIALES = 3;
    static int nivel = 1;
    static int llaves = 0;
    static int puntos = 0;
    static Random rand = new Random();
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        vidas = VIDAS_INICIALES;
        generarLaberinto(nivel);
        while (true) {
            jugarNivel();
        }
    }

    // genera un laberinto aleatorio en función del nivel (mayor nivel -> más paredes)
    static void generarLaberinto(int nivelActual) {
        int wallProb = Math.min(50, 10 + nivelActual * 4); // probabilidad muro %
        int keyProb = Math.max(1, 3 - nivelActual/5);      // probabilidad llave %
        int doorProb = Math.max(2, 4 - nivelActual/6);     // probabilidad puerta %
        int trapProb = Math.min(10, 3 + nivelActual * 2);  // probabilidad trampa %
        int coinProb = Math.min(12, 5 + nivelActual * 2);  // probabilidad moneda %

        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                int r = rand.nextInt(100);
                if (i == 0 || j == 0 || i == TAM - 1 || j == TAM - 1) {
                    laberinto[i][j] = '1'; // borde
                } else if (r < wallProb) {
                    laberinto[i][j] = '1'; // pared
                } else if (r < wallProb + keyProb) {
                    laberinto[i][j] = 'L'; // llave
                } else if (r < wallProb + keyProb + doorProb) {
                    laberinto[i][j] = 'C'; // puerta (cerrada)
                } else if (r < wallProb + keyProb + doorProb + trapProb) {
                    laberinto[i][j] = 'T'; // trampa
                } else if (r < wallProb + keyProb + doorProb + trapProb + coinProb) {
                    laberinto[i][j] = 'M'; // moneda
                } else {
                    laberinto[i][j] = ' '; // espacio libre
                }
                descubierto[i][j] = false;
            }
        }

        // colocar jugador en (1,1) o primera celda libre cercana
        jugadorX = 1;
        jugadorY = 1;
        if (laberinto[jugadorX][jugadorY] == '1') laberinto[jugadorX][jugadorY] = ' ';
        laberinto[jugadorX][jugadorY] = 'P';
        descubierto[jugadorX][jugadorY] = true;

        // colocar salida S en esquina opuesta (asegurar que sea espacio)
        int exitX = TAM - 2, exitY = TAM - 2;
        if (laberinto[exitX][exitY] == '1') laberinto[exitX][exitY] = ' ';
        laberinto[exitX][exitY] = 'S';
        descubierto[exitX][exitY] = false; // solo se muestra si el jugador interactúa o llega
    }

    static void jugarNivel() {
        while (true) {
            mostrarLaberinto();
            mostrarEstado();

            System.out.print("Movimiento (W/A/S/D), Q=salir: ");
            String token = sc.next();
            if (token.isEmpty()) continue;
            char mov = Character.toUpperCase(token.charAt(0));

            if (mov == 'Q') {
                System.out.println("Saliendo...");
                System.exit(0);
            }

            int nx = jugadorX, ny = jugadorY;
            switch (mov) {
                case 'W': nx--; break;
                case 'S': nx++; break;
                case 'A': ny--; break;
                case 'D': ny++; break;
                default:
                    System.out.println("Tecla invalida.");
                    continue;
            }

            if (nx < 0 || ny < 0 || nx >= TAM || ny >= TAM) {
                System.out.println("Fuera de límites.");
                continue;
            }

            char destino = laberinto[nx][ny];

            // MARCAR que el jugador ha interactuado/intentado ver esa celda
            descubierto[nx][ny] = true;

            if (destino == '1') {
                // pared: se revela pero no se mueve
                System.out.println("¡Hay una pared!");
                continue;
            } else if (destino == 'C') {
                // puerta: si tiene llave la abre (desaparece), se revela y se mueve
                System.out.println("Te topaste con una puerta.");
                if (llaves > 0) {
                    llaves--;
                    laberinto[nx][ny] = ' '; // abrir puerta
                    System.out.println("Usaste una llave. Puerta abierta.");
                    // mover
                } else {
                    System.out.println("Necesitas una llave para abrirla.");
                    continue;
                }
            } else if (destino == 'L') {
                // llave: recogerla, incrementar llaves y puntos, se mueve y celda queda libre
                llaves++;
                puntos += 5;
                System.out.println("Has recogido una llave. Llaves: " + llaves + " | +5 puntos");
                laberinto[nx][ny] = ' ';
            } else if (destino == 'M') {
                // moneda: sumar puntos y eliminar moneda
                puntos += 10;
                System.out.println("Has recogido una moneda. +10 puntos (Total: " + puntos + ")");
                laberinto[nx][ny] = ' ';
            } else if (destino == 'T') {
                // trampa: perder vida, se revela (puede permanecer)
                vidas--;
                System.out.println("¡Has caido en una trampa! Vidas restantes: " + vidas);
                if (vidas <= 0) {
                    System.out.println("Has perdido todas tus vidas. Volviendo al nivel 1.");
                    nivel = 1;
                    vidas = VIDAS_INICIALES;
                    llaves = 0;
                    puntos = 0;
                    generarLaberinto(nivel);
                    return; // reinicia nivel
                }
                // dejar trampa en el mapa (ya se reveló)
            } else if (destino == 'S') {
                // salida: subir de nivel y generar nuevo laberinto aleatorio
                System.out.println("¡Has llegado a la salida! Avanzas al siguiente nivel.");
                nivel++;
                // al subir de nivel, mantener vidas, llaves y puntos (opcional)
                generarLaberinto(nivel);
                return;
            }

            // si llegó aquí, se puede mover: actualizar mapa
            laberinto[jugadorX][jugadorY] = ' '; // borrar posición anterior
            jugadorX = nx;
            jugadorY = ny;
            laberinto[jugadorX][jugadorY] = 'P';
            descubierto[jugadorX][jugadorY] = true;
        }
    }

    // muestra solo la posición del jugador y las celdas con las que ha interactuado
    static void mostrarLaberinto() {
        System.out.println();
        for (int i = 0; i < TAM; i++) {
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < TAM; j++) {
                if (i == jugadorX && j == jugadorY) {
                    sb.append('P');
                } else if (descubierto[i][j]) {
                    sb.append(laberinto[i][j]);
                } else {
                    sb.append('?'); // area no descubierta
                }
            }
            System.out.println(sb.toString());
        }
    }

    static void mostrarEstado() {
        System.out.println();
        System.out.println("Nivel: " + nivel + " | Vidas: " + vidas + " | Llaves: " + llaves + " | Puntos: " + puntos);
        System.out.println("Se muestran en pantalla: tu posicion (P) y las celdas con las que has interactuado.");
    }
}