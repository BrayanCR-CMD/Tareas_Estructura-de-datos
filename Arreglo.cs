using System;

class ArregloNumeros
{
    static void Main()
    {
        int[] numeros = new int[5];

        // Capturar los números en el arreglo
        for (int i = 0; i < numeros.Length; i++)
        {
            Console.Write("Ingrese el número en la posición " + i + ": ");
            numeros[i] = int.Parse(Console.ReadLine());
        }

        // Mostrar los números ingresados
        Console.WriteLine("Los números ingresados son:");
        for (int i = 0; i < numeros.Length; i++)
        {
            Console.WriteLine("Posición " + i + ": " + numeros[i]);
        }
    }
}