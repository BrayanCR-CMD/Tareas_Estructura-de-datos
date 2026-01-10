#include <iostream>
using namespace std;

#define MAXSIZE 5
int queue[MAXSIZE];
int front = -1, rear = -1;
void insertar(){
    int elemento;
    cout << "/nIngrese el elemento a insertar: ";
    cin >> elemento;
    if (rear == MAXSIZE - 1){
        cout << "desbordamiento de cola/n";
        return;
    }
    if (front == -1 && rear == -1){
        front = rear = 0;
    } else {
        rear++;
    }
    queue[rear] = elemento;
    cout << "Elemento insertado: " << elemento << "/n";
}
void eliminar(){
    if (front == -1 || front > rear){
        cout << "subdesbordamiento de cola/n";
        return;
    }
    int elemento = queue[front];
    if (front == rear){
        front = rear = -1;
    } else {
        front++;
    }
    cout << "Elemento eliminado: " << elemento << "/n";
}
void mostrar(){
    if (rear == -1 || front == -1 || front > rear){
        cout << "La cola esta vacia/n";
    } else {
        cout << "Elementos en la cola: ";
        for (int i = front; i <= rear; i++){
            cout << queue[i] << " ";
        }
        cout << "/n";
    }
}

int main(){
    int opcion;
    do {
        cout << "Menu de operaciones de cola/n";
        cout << "1. Insertar/n";
        cout << "2. Eliminar/n";
        cout << "3. Mostrar/n";
        cout << "4. Salir/n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        switch (opcion){
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
                cout << "Saliendo del programa/n";
                break;
            default:
                cout << "Opcion invalida/n";
        }
    } while (opcion != 4);
    return 0;
}