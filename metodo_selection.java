public class metodo_selection {
    public static void selectionSort(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;

            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }

            if (minIndex != i) {
                int temp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = temp;
            }
        }
    }

    public static void main(String[] args) {
        int[] array = {64, 25, 12, 22, 11};
        System.out.println("arreglo desordenado:");
        for (int num : array) {
            System.out.print(num + " ");
        }
        
        selectionSort(array);
        System.out.println("arreglo ordenado:");
        for (int num : array) {
            System.out.print(num + " ");
        }
    }
}