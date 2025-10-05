#include<iostream>
using namespace std;
// metododo de ordenamiento quicksort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high]; // Elegir el pivote
        int i = (low - 1); // Índice del elemento más pequeño

        for (int j = low; j < high; j++) {
            // Si el elemento actual es menor o igual al pivote
            if (arr[j] <= pivot) {
                i++; // Incrementar el índice del elemento más pequeño
                swap(arr[i], arr[j]); // Intercambiar
            }
        }
        swap(arr[i + 1], arr[high]); // Intercambiar el pivote con el elemento en i+1
        int pi = i + 1; // Índice del pivote después de la partición

        // Llamadas recursivas para ordenar los subarreglos
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main() {
    int n = 5;
    int edad[5];
    // Llenar el arreglo
    for (int i = 0; i < n; i++) {
        cout << "Ingresa la edad: ";
        cin >> edad[i];
    }

    // Llamar a la función quicksort
    quicksort(edad, 0, n - 1);

    // Mostrar los datos del arreglo ordenado
    cout << "Edades ordenadas:\n";
    for (int i = 0; i < n; i++) {
        cout << edad[i] << '\n';
    }

    return 0;
}