import java.util.Arrays;

public class metodo_radix {

    // Función principal para realizar el Radix Sort
    public static void radixSort(int[] arr) {
        // Encontrar el número máximo para saber el número de dígitos
        int max = getMax(arr);

        // Hacer Counting Sort para cada dígito (unidad, decena, centena, etc.)
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }

    // Obtiene el valor máximo del arreglo
    private static int getMax(int[] arr) {
        int max = arr[0];
        for (int num : arr) {
            if (num > max)
                max = num;
        }
        return max;
    }

    // Counting Sort modificado para ordenar según el dígito actual
    private static void countingSortByDigit(int[] arr, int exp) {
        int n = arr.length;
        int[] output = new int[n];  // arreglo temporal
        int[] count = new int[10];  // hay 10 posibles dígitos (0-9)

        // Contar ocurrencias de cada dígito
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }

        // Cambiar count[i] para que contenga la posición real de ese dígito en output[]
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Construir el arreglo de salida (de derecha a izquierda para estabilidad)
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // Copiar los elementos ordenados al arreglo original
        System.arraycopy(output, 0, arr, 0, n);
    }

    // Ejemplo de uso
    public static void main(String[] args) {
        int[] datos = {170, 45, 75, 90, 802, 24, 2, 66};

        System.out.println("Arreglo original: " + Arrays.toString(datos));
        radixSort(datos);
        System.out.println("Arreglo ordenado: " + Arrays.toString(datos));
    }
}
