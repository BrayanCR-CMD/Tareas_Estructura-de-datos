#include <iostream>
using namespace std;
//proceso para invertir el orden del arreglo
int orden_inv(int n, int numeros[]){
    int j = 0;
    for(int i = (n-1); i>4; i--){
        int temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
        j = j + 1;

    }
}
//proceso para mostrar el arreglo
void escribir_nums(int n, int numeros[]){
    for(int i = 0; i < n; i++){
        cout << "el numero en la posicion " << i << " es: " << numeros[i] << endl;
    }
    cout << "\n";
}
//proceso para capturar los numeros
int capturar_nums(int n, int numeros[]){
    for (int i = 0; i < n; i++){
        system("cls");

        cout << "ingrese un numero" << endl;
        cin >> numeros[i];
    }
}
//bloque de codigo principal
int main(){
    // variables
    int n = 10;
    int numeros[10];

    capturar_nums(n,numeros);
    escribir_nums(n,numeros);
    cout << "ahora invertimos el orden \n" << endl;
    orden_inv(n, numeros);
    escribir_nums(n,numeros);
}
