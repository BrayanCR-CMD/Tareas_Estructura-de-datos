import java.util.Scanner;

public class RecorrerMatriz {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int columnas = 3;
        int filas = 3;
        int[][] matriz = new int [filas][columnas];

        //capturar los numeros dentro del arreglo
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                System.out.println("ingrese un numero");
                matriz[i][j] = sc.nextInt();
            }
        }

        //mostrar los numeros dentro del arreglo
        for (int i = 0; i < filas; i++) {  
            for (int j = 0; j < columnas; j++) {
                System.out.println("el numero en la posicion [" + i + "][" + j + "] es: " + matriz[i][j]);
            }
        }
    }
}
