	public class numeros {
		public static void main(String[] args) {
			int [] numeros = {1,2,3,4,5};
			numeros[0] =85;
			numeros[1] = 44;
			numeros[2] = 31;
			numeros[3] = 20;
			numeros[4] = 91;
			// escribir todos los numeros en el arreglo
			for(int i = 0; i < numeros.length; i++) {
				System.out.println(numeros[i]);
			}
		}
	}
