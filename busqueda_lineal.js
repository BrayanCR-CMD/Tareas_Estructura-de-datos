//busqueda lineal
function busquedaLineal(arr, objetivo) {
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === objetivo) {
            return i; // Retorna el índice si se encuentra el objetivo
        }
    }
    return -1; // Retorna -1 si no se encuentra el objetivo
}

// Ejemplo de uso:
const arreglo = [4, 2, 7, 1, 3];
const objetivo = 7;
const resultado = busquedaLineal(arreglo, objetivo);
if (resultado !== -1) {
    console.log(`Elemento encontrado en el índice: ${resultado + 1}`);
} else {
    console.log('Elemento no encontrado en el arreglo.');
}

return 0;
