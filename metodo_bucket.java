//metodo de ordenamiento bucket sort
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
public class metodo_bucket {
    public static void bucketSort(int[] array, int numBuckets) {
        if (array.length == 0) {
            return;
        }

        // Encontrar el valor máximo y mínimo en el array
        int minValue = array[0];
        int maxValue = array[0];
        for (int value : array) {
            if (value < minValue) {
                minValue = value;
            } else if (value > maxValue) {
                maxValue = value;
            }
        }

        // Crear los buckets
        List<List<Integer>> buckets = new ArrayList<>(numBuckets);
        for (int i = 0; i < numBuckets; i++) {
            buckets.add(new ArrayList<>());
        }

        // Distribuir los elementos en los buckets
        for (int value : array) {
            int bucketIndex = (int) ((value - minValue) * numBuckets / (maxValue - minValue + 1));
            buckets.get(bucketIndex).add(value);
        }

        // Ordenar cada bucket y concatenar los resultados
        int index = 0;
        for (List<Integer> bucket : buckets) {
            Collections.sort(bucket);
            for (int value : bucket) {
                array[index++] = value;
            }
        }
    }
    // Ejemplo de uso
    public static void main(String[] args) {
        int[] array = {34, 2, 10, 6, 7, 5, 3, 1, 9, 8, 4};
        int numBuckets = 5;

        System.out.println("Array original:");
        for (int value : array) {
            System.out.print(value + " ");
        }
        System.out.println();

        bucketSort(array, numBuckets);

        System.out.println("Array ordenado:");
        for (int value : array) {
            System.out.print(value + " ");
        }
    }
    
}

