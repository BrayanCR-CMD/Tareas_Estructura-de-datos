import java.util.Scanner;

public class Cola {

    static final int MAXSIZE = 5;
    static int[] queue = new int[MAXSIZE];
    static int front = -1, rear = -1;
    static Scanner sc = new Scanner(System.in);

    static void insertar() {
        System.out.print("Ingrese el elemento a insertar: ");
        int elemento = sc.nextInt();

        if (rear == MAXSIZE - 1) {
            System.out.println("Desbordamiento de cola");
            return;
        }

        if (front == -1 && rear == -1) {
            front = rear = 0;
        } else {
            rear++;
        }

        queue[rear] = elemento;
        System.out.println("Elemento insertado: " + elemento);
    }

    static void eliminar() {
        if (front == -1 || front > rear) {
            System.out.println("Subdesbordamiento de cola");
            return;
        }

        int elemento = queue[front];

        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }

        System.out.println("Elemento eliminado: " + elemento);
    }

    static void mostrar() {
        if (rear == -1 || front == -1 || front > rear) {
            System.out.println("La cola está vacía");
        } else {
            System.out.print("Elementos en la cola: ");
            for (int i = front; i <= rear; i++) {
                System.out.print(queue[i] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int opcion;

        do {
            System.out.println("\nMenú de operaciones de cola");
            System.out.println("1. Insertar");
            System.out.println("2. Eliminar");
            System.out.println("3. Mostrar");
            System.out.println("4. Salir");
            System.out.print("Ingrese su opción: ");
            opcion = sc.nextInt();

            switch (opcion) {
                case 1:
                    insertar();
                    break;

                case 2:
                    eliminar();
                    break;

                case 3:
                    mostrar();
                    break;

                case 4:
                    System.out.println("Saliendo del programa");
                    break;

                default:
                    System.out.println("Opción inválida");
                    break;
            }

        } while (opcion != 4);
    }
}
