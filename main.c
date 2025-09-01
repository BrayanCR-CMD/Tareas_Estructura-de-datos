#include <stdio.h>
#include <string.h>

int main() {
    char nombres[5][50];

    // Capturar los nombres por teclado
    for (int i = 0; i < 5; i++) {
        printf("Ingrese el nombre #%d: ", i + 1);
        fgets(nombres[i], sizeof(nombres[i]), stdin);
        // Eliminar el salto de línea al final
        nombres[i][strcspn(nombres[i], "\n")] = 0;
    }

    // Mostrar los nombres almacenados
    for (int i = 0; i < 5; i++) {
        printf("Nombre en la posición %d: %s\n", i, nombres[i]);
    }

    return 0;
}