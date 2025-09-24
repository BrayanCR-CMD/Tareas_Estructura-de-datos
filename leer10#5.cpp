#include <iostream>
using namespace std;
int orden_inv(int n, int numeros[]){
    int j = 0;
    for(int i = (n-1); i>4; i--){
        int temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
        j = j + 1;

    }
}
int main(){
    int n = 10;
    int numeros[10];

    for (int i = 0; i < n; i++){
        system("cls");

        cout << "ingrese un numero" << endl;
        cin >> numeros[i];
    }

    for(int i = 0; i < n; i++){
        cout << "el numero en la posicion " << i << " es: " << numeros[i] << endl;
    }
    cout << "\n";

    cout << "ahora invertimos el orden \n" << endl;
    orden_inv(n, numeros);
    for(int i = 0; i < n; i++){
        cout << "el numero en la posicion " << i << " es: " << numeros[i] << endl;
    }

}
