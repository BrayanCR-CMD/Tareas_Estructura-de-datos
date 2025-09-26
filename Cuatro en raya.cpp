#include <iostream>
#include <vector>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;

void mostrarTablero(vector<vector<char>>& tablero) {
    system("cls"); 
    cout << "\n    JUEGO: 4 EN RAYA\n\n";
    for (int c = 0; c < COLUMNAS; c++)
        cout << "  " << c+1; 
    cout << endl;

    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            cout << "| " << tablero[f][c];
        }
        cout << "|\n";
    }
    for (int c = 0; c < COLUMNAS; c++)
        cout << "---";
    cout << "-" << endl;
}

bool colocarFicha(vector<vector<char>>& tablero, int columna, char ficha) {
    if (columna < 0 || columna >= COLUMNAS) return false;
    for (int f = FILAS - 1; f >= 0; f--) {
        if (tablero[f][columna] == '.') {
            tablero[f][columna] = ficha;
            return true;
        }
    }
    return false; 
}

bool verificarGanador(vector<vector<char>>& tablero, char ficha) {
    // Horizontal
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c <= COLUMNAS - 4; c++) {
            if (tablero[f][c] == ficha && tablero[f][c+1] == ficha &&
                tablero[f][c+2] == ficha && tablero[f][c+3] == ficha)
                return true;
        }
    }
    // Vertical
    for (int f = 0; f <= FILAS - 4; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            if (tablero[f][c] == ficha && tablero[f+1][c] == ficha &&
                tablero[f+2][c] == ficha && tablero[f+3][c] == ficha)
                return true;
        }
    }
    // Diagonal ↘
    for (int f = 0; f <= FILAS - 4; f++) {
        for (int c = 0; c <= COLUMNAS - 4; c++) {
            if (tablero[f][c] == ficha && tablero[f+1][c+1] == ficha &&
                tablero[f+2][c+2] == ficha && tablero[f+3][c+3] == ficha)
                return true;
        }
    }
    // Diagonal ↙
    for (int f = 0; f <= FILAS - 4; f++) {
        for (int c = 3; c < COLUMNAS; c++) {
            if (tablero[f][c] == ficha && tablero[f+1][c-1] == ficha &&
                tablero[f+2][c-2] == ficha && tablero[f+3][c-3] == ficha)
                return true;
        }
    }
    return false;
}

bool tableroLleno(vector<vector<char>>& tablero) {
    for (int c = 0; c < COLUMNAS; c++) {
        if (tablero[0][c] == '.') return false;
    }
    return true;
}

int main() {
    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, '.'));
    char jugador1 = 'X';
    char jugador2 = 'O';
    char turno = jugador1;

    while (true) {
        mostrarTablero(tablero);
        cout << "Turno del jugador " << (turno == jugador1 ? "1 (X)" : "2 (O)") << endl;
        cout << "Elige una columna (1-7): ";
        int columna;
        cin >> columna;
        columna--; // ajustar índice

        if (!colocarFicha(tablero, columna, turno)) {
            cout << "Columna inválida o llena. Intenta otra.\n";
            system("pause");
            continue;
        }

        if (verificarGanador(tablero, turno)) {
            mostrarTablero(tablero);
            cout << "¡Jugador " << (turno == jugador1 ? "1 (X)" : "2 (O)") << " gana!\n";
            break;
        }

        if (tableroLleno(tablero)) {
            mostrarTablero(tablero);
            cout << "¡Empate!\n";
            break;
        }

        turno = (turno == jugador1) ? jugador2 : jugador1; // cambiar turno
    }

    return 0;
}
