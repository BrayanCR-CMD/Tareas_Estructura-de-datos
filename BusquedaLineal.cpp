#include <iostream>
#include <string>
using namespace std;
int buscar_persona(persona datos_persona[], int n, string nombre_buscar) {
    for (int i = 0; i < n; i++) {
        if (datos_persona[i].nombre == nombre_buscar) {
            return i; // Retorna el índice si se encuentra la persona
        }
    }
    return -1; // Retorna -1 si no se encuentra la persona
}

class persona{
    public:
        string nombre;
        int edad;
        long numero_telefono;
};

int main()
{
    persona datos_persona [3];
    int n = datos_persona.length();
    string nombre_buscar;
    int opcion;
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
    do while (opcion = 1){
        cout << "ingresa el nombre de la persona que deseas buscar" << endl;
        cin >> nombre_buscar;
        int indice = buscar_persona(datos_persona, n, nombre_buscar);
        if (indice != -1) {
            cout << "Persona encontrada en el índice: " << indice << endl;
            cout << "Nombre: " << datos_persona[indice].nombre << endl;
            cout << "Edad: " << datos_persona[indice].edad << endl;
            cout << "Número de Teléfono: " << datos_persona[indice].numero_telefono << endl;
        } else {
            cout << "Persona no encontrada." << endl;
        }
        cout << "deseas buscar otra persona? 1. si 2. no" << endl;
        cin >> opcion;

    }

    return 0;
}