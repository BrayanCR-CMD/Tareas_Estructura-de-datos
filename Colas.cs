using System;

class Cola
{
    const int MAXSIZE = 5;
    static int[] queue = new int[MAXSIZE];
    static int front = -1, rear = -1;

    static void Insertar()
    {
        Console.Write("Ingrese el elemento a insertar: ");
        int elemento = int.Parse(Console.ReadLine());

        if (rear == MAXSIZE - 1)
        {
            Console.WriteLine("Desbordamiento de cola");
            return;
        }

        if (front == -1 && rear == -1)
        {
            front = rear = 0;
        }
        else
        {
            rear++;
        }

        queue[rear] = elemento;
        Console.WriteLine("Elemento insertado: " + elemento);
    }

    static void Eliminar()
    {
        if (front == -1 || front > rear)
        {
            Console.WriteLine("Subdesbordamiento de cola");
            return;
        }

        int elemento = queue[front];

        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front++;
        }

        Console.WriteLine("Elemento eliminado: " + elemento);
    }

    static void Mostrar()
    {
        if (rear == -1 || front == -1 || front > rear)
        {
            Console.WriteLine("La cola está vacía");
        }
        else
        {
            Console.Write("Elementos en la cola: ");
            for (int i = front; i <= rear; i++)
            {
                Console.Write(queue[i] + " ");
            }
            Console.WriteLine();
        }
    }

    static void Main(string[] args)
    {
        int opcion;

        do
        {
            Console.WriteLine("\nMenú de operaciones de cola");
            Console.WriteLine("1. Insertar");
            Console.WriteLine("2. Eliminar");
            Console.WriteLine("3. Mostrar");
            Console.WriteLine("4. Salir");
            Console.Write("Ingrese su opción: ");
            opcion = int.Parse(Console.ReadLine());

            switch (opcion)
            {
                case 1:
                    Insertar();
                    break;

                case 2:
                    Eliminar();
                    break;

                case 3:
                    Mostrar();
                    break;

                case 4:
                    Console.WriteLine("Saliendo del programa");
                    break;

                default:
                    Console.WriteLine("Opción inválida");
                    break;
            }

        } while (opcion != 4);
    }
}
