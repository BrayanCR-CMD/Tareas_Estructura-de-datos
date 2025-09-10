#include <iostream>
#include <string>
using namespace std;

class persona{
    public:
        string nombre;
        int edad;
        long numero_telefono;
};

int main()
{
    persona datos_persona [3];

    //arreglo para capturar los datos de la persona
    for(int i =0; i<3; i++)
    {
        cout << "ingresa el nombre" << endl;
        cin >> datos_persona[i].nombre;
        cout << "ingresa la edad" << endl;
        cin >> datos_persona[i].edad;
        cout << "ingresa el nombre de telefono" << endl;
        cin >> datos_persona[i].numero_telefono;
    }

    //arreglo para mostrar los datos de la persona
    for(int i =0; i<3; i++)
    {
        cout << "nombre: " << datos_persona[i].nombre << endl;
        cout << "edad: " << datos_persona[i].edad << endl;
        cout << "numero de telefono: " << datos_persona[i].numero_telefono << endl;
    }
    return 0;
}
