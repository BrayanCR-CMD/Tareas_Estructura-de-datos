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
    // metodo de ordenamiento insert
    for (int i = 0; i < n; i++){
        temp = edad[i];
        int j = i - 1;
        while(j>=0 && temp < edad[j]){
            edad[j + 1] = edad[j];
            j = j - 1;
        }
        edad[j + 1] = temp;
    }

    //mostrar los datos del arreglo ordenado
    for (int i = 0; i < n; i++){
        cout << edad[i] << '\n';
    }

    return 0;
}
