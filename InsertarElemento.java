import java.util.Scanner;
public class InsertarElemento {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] numeros = new int[6];
        
        //capturar los numeros denntro del arreglo
        for (int i = 0; i < numeros.length; i++) {
            System.out.println("ingrese un numero");
            numeros[i] = sc.nextInt();
        }

        //solicitar el numero y la posicion para insertar un elemento
        System.out.println("Ingrese el numero que desea insertar: ");
        int numeroInsertar = sc.nextInt();
        System.out.println("Ingrese la posicion donde desea insertar el numero (0-5): ");
        int posicion = sc.nextInt();
        
        // Validar que la posicion sea valida
        if (posicion < 0 || posicion >= numeros.length) {
            System.out.println("Posicion invalida.");
        } else {

            // Desplazar elementos a la derecha
            for (int i = numeros.length - 1; i > posicion; i--) {
                numeros[i] = numeros[i - 1];
            }
            
            // Insertar el nuevo numero
            numeros[posicion] = numeroInsertar;
            
            //mostrar los numeros dentro del arreglo
            for (int i = 0; i < numeros.length; i++){
                System.out.println("el numero en la posicion " + i + " es: " + numeros[i]);
            }
        }
        
    }
}