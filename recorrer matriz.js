//recorrer matriz por columnas
let matriz = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];
for (let j = 0; j < matriz[0].length; j++) {
    for (let i = 0; i < matriz.length; i++) {
        console.log(matriz[i][j]);
    }
}
//salida: 1,4,7,2,5,8,3,6,9
