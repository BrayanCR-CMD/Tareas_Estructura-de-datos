#include <iostream>
using namespace std;

int main(){
    int n = 5;
    int edad [5];
    int temp;
    bool ordenado;
    //llenar el arreglo
    for(int i = 0; i < n; i++){
        cout << "ingresa la edad: ";
        cin >> edad[i];
    }

    //metodo de la burbuja para ordenar datos
    while(!ordenado){
        ordenado = true;
        for (int i = 0; i < n-1; i++){
          if (edad[i] > edad[i + 1]){
              temp = edad[i];
             edad[i] = edad[i + 1];
             edad[i + 1] = temp;
             ordenado = false;
            }
        }
    }

    //mostrar los datos del arreglo ordenado
    for (int i = 0; i < n; i++){
        cout << edad[i] << '\n';
    }

    return 0;
}