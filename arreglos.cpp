#include <iostream>
using namespace std;

int main(){
    string nombres [5];
    //llenar el arreglo
    for(int i = 0; i < 5; i++){
        cout << "ingresa un nombre:";
        cin >> nombres[i];
    }
    //mostrar los datos del arreglo
    for (int i = 0; i < 5; i++){
        cout << nombres[i];
    }
    return 0;

}
