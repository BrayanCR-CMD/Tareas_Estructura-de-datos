//metodo radix sort para C#
using System;
class RadixSort
{
    // Función para obtener el dígito en la posición exp
    static int GetDigit(int number, int exp)
    {
        return (number / exp) % 10;
    }

    // Función para realizar el conteo de sorteo basado en el dígito actual
    static void CountingSort(int[] array, int exp)
    {
        int n = array.Length;
        int[] output = new int[n];
        int[] count = new int[10];

        // Inicializar el conteo
        for (int i = 0; i < 10; i++)
            count[i] = 0;

        // Contar las ocurrencias de cada dígito
        for (int i = 0; i < n; i++)
            count[GetDigit(array[i], exp)]++;

        // Cambiar count[i] para que contenga la posición real del dígito en output[]
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Construir el array de salida
        for (int i = n - 1; i >= 0; i--)
        {
            output[count[GetDigit(array[i], exp)] - 1] = array[i];
            count[GetDigit(array[i], exp)]--;
        }

        // Copiar el array de salida al array original
        for (int i = 0; i < n; i++)
            array[i] = output[i];
    }

    // Función principal para realizar Radix Sort
    public static void RadixSortFunction(int[] array)
    {
        // Encontrar el número máximo para saber el número de dígitos
        int max = array[0];
        for (int i = 1; i < array.Length; i++)
            if (array[i] > max)
                max = array[i];

        // Aplicar Counting Sort para cada dígito
        for (int exp = 1; max / exp > 0; exp *= 10)
            CountingSort(array, exp);
    }

    // Función para imprimir el array
    static void PrintArray(int[] array)
    {
        foreach (var item in array)
            Console.Write(item + " ");
        Console.WriteLine();
    }

    // Método Main para probar el Radix Sort

    static void Main()
    {
        int[] array = { 170, 45, 75, 90, 802, 24, 2, 66 };
        Console.WriteLine("Array original:");
        PrintArray(array);

        RadixSortFunction(array);

        Console.WriteLine("Array ordenado:");
        PrintArray(array);
    }

}