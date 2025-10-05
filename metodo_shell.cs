using System;
class metodo_shell
{
    // metodo de ordenamiento shell sort
    public static void Shell(int[] arreglo)
    {
        int salto, aux, i;
        bool cambios;
        for (salto = arreglo.Length / 2; salto != 0; salto /= 2)
        {
            cambios = true;
            while (cambios)
            {
                cambios = false;
                for (i = salto; i < arreglo.Length; i++)
                {
                    if (arreglo[i - salto] > arreglo[i])
                    {
                        aux = arreglo[i];
                        arreglo[i] = arreglo[i - salto];
                        arreglo[i - salto] = aux;
                        cambios = true;
                    }
                }
            }
        }
    }

    static void Main()
    {
        int[] arreglo = { 23, 12, 1, 8, 34, 54, 2, 3 };
        Console.WriteLine("Arreglo original:");
        Console.WriteLine(string.Join(", ", arreglo));
        Shell(arreglo);
        Console.WriteLine("Arreglo ordenado:");
        Console.WriteLine(string.Join(", ", arreglo));
    }
}