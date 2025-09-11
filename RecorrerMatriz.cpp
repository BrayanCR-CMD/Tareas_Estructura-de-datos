#include <iostream>
#include <string>
using namespace std;

int main() {
    int numeros[3][3];

    for (int i = 0; i <3; i++) {
        for (int j = 0; j <3; j++) {
            cout << "Ingrese un numero: ";
            cin >> numeros[i][j];
        }
    }
    cout << endl;
    
    for (int i = 0; i<3; i++ ) {
        for (int j = 0; j<3; j++) {
            cout << "el numero en la posicion [" << i << "] [" << j << "] es: " << numeros[i][j] <<endl;
        }
        cout << endl;
    }
}