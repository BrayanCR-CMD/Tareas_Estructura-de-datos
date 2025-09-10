#include <iostream>
#include <string>
using namespace std;

//definir la clase persona y sus elementos
class persona{
    public:
        string nombre;
        int edad;
        long numero_telefono;
};

//funcion para realizar la busqueda dentro del arreglo
int buscar_persona(persona datos_persona[], int n, string nombre_buscar) {
    for (int i = 0; i < n; i++) {
        if (datos_persona[i].nombre == nombre_buscar) {
            return i; // Retorna el índice si se encuentra la persona
        }
    }
    return -1; // Retorna -1 si no se encuentra la persona
}

int main()
{
    persona datos_persona [3];
    int n = 3;
    string nombre_buscar;
    int opcion = 0;
    persona insertar;
    int posicion;

    //arreglo para capturar los datos de la persona
    for(int i =0; i<3; i++)
    {
        cout << "ingresa el nombre" << endl;
        cin >> datos_persona[i].nombre;
        cout << "ingresa la edad" << endl;
        cin >> datos_persona[i].edad;
        cout << "ingresa el numero de telefono" << endl;
        cin >> datos_persona[i].numero_telefono;
    }

    //arreglo para mostrar los datos de la persona
    for(int i =0; i<3; i++)
    {
        cout << "nombre: " << datos_persona[i].nombre << endl;
        cout << "edad: " << datos_persona[i].edad << endl;
        cout << "numero de telefono: " << datos_persona[i].numero_telefono << endl;
    }

    switch (opcion) {
        case 1:

        break;

        case 2:
            
        break;
    }

    //ciclo para buscar personas en el arreglo usando sus nombres
    do {
        cout << "que accion desea realizar?" << '\n' << "1: buscar" << '\n' << "2: insertar" << '\n' << "3: apagar" << endl;
        cin >> opcion;
        // hacer un switch para realizar algun tipo de accion
        switch(opcion){
            case 1:
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
                break;
            case 2:
                cout << "ingrese la posicion en la que quiere ingresar los nuevos datos (0 a 2)" << endl;
                cin >> posicion;
                
                if(posicion < 0 || posicion >=n){
                    cout << "posicion invalida." << endl;
                    break;
                }

                //arreglo para recorrer los elementos del arreglo a la derecha (el ultimo elemento a la derecha se elimina)
                for (int i = n-1; i>posicion; i--){
                    datos_persona[i].nombre =  datos_persona[i - 1].nombre;
                    datos_persona[i].edad =  datos_persona[i - 1].edad;
                    datos_persona[i].numero_telefono =  datos_persona[i - 1].numero_telefono;
                }
                //leemos los datos que remplazaran los antiguos
                cout << "ingrese el nuevo nombre" << endl;
                cin >> insertar.nombre;
                cout << "ingrese la edad" << endl;
                cin >> insertar.edad;
                cout << "ingrese el numero" << endl;
                cin >> insertar.numero_telefono;

                //remplazamos los datos (insertamos)
                datos_persona[posicion].nombre = insertar.nombre;
                datos_persona[posicion].edad = insertar.edad;
                datos_persona[posicion].numero_telefono = insertar.numero_telefono;
                break;
            case 3:
                cout << "apagando..." << endl;
                break;
            default:
                cout << "opcion invalida" << endl;
                break;
        }
    } while ((opcion != 3));

    return 0;
}