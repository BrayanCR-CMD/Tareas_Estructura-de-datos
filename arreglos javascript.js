// Pedir cuántos números quiere capturar
let n = parseInt(prompt("¿Cuántos números quieres capturar?"));

// Crear un arreglo vacío
let numeros = [];

// Capturar números con un ciclo for
for (let i = 0; i < n; i++) {
    let num = parseInt(prompt(`Ingresa el número ${i + 1}:`));
    numeros.push(num);
}

// Mostrar los números con otro ciclo for
console.log("Los números capturados son:");
for (let i = 0; i < numeros.length; i++) {
    console.log(numeros[i]);
}