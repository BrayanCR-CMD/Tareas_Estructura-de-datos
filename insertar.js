// funcion de insertar elemento en un array en una posicion dada
function insertarElemento(array, elemento, posicion) {
    if (posicion < 0 || posicion > array.length) {
        throw new Error("Posición fuera de los límites del array");
    }
    array.splice(posicion, 0, elemento);
    return array;
}

let array = [1, 2, 3, 4, 5];
let elemento = 10;
let posicion = 2;
let nuevoArray = insertarElemento(array, elemento, posicion);
console.log(nuevoArray); // Output: [1, 2, 10, 3, 4, 5]
return 0;
