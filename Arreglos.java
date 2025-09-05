import java.util.Scanner;
public class Arreglos {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int[] numeros = new int[6];
		
		//capturar los numeros denntro del arreglo
		for (int i = 0; i < numeros.length; i++) {
			System.out.println("ingrese un numero");
			numeros[i] = sc.nextInt();
		}
		//mostrar los numeros dentro del arreglo
		for (int i = 0; i < numeros.length; i++){
			System.out.println("el numero en la posicion " + i + " es: " + numeros[i]);
		}
		
	}
}