// metodo de ordenamiento Bucket Sort
function bucketSort(arr, bucketSize = 5) {
    if (arr.length === 0) {
        return arr;
    }
    // Encontrar el valor mínimo y máximo en el arreglo
    let minValue = arr[0];
    let maxValue = arr[0];
    for (let i = 1; i < arr.length; i++) {
        if (arr[i] < minValue) {
            minValue = arr[i];
        } else if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }

    // Crear los buckets
    const bucketCount = Math.floor((maxValue - minValue) / bucketSize) + 1;
    const buckets = new Array(bucketCount);
    for (let i = 0; i < buckets.length; i++) {
        buckets[i] = [];
    }

    // Distribuir los elementos en los buckets
    for (let i = 0; i < arr.length; i++) {
        const bucketIndex = Math.floor((arr[i] - minValue) / bucketSize);
        buckets[bucketIndex].push(arr[i]);
    }
    // Ordenar cada bucket y concatenarlos
    const sortedArray = [];
    for (let i = 0; i < buckets.length; i++) {
        if (buckets[i].length > 0) {
            insertionSort(buckets[i]);
            sortedArray.push(...buckets[i]);
        }
    }
    return sortedArray;
}
// Metodo de ordenamiento Insertion Sort para ordenar los buckets
function insertionSort(arr) {
    for (let i = 1; i < arr.length; i++) {
        const key = arr[i];
        let j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr;
}

//ejemplo de uso
const array = [29, 25, 3, 49, 9, 37, 21, 43];
const sortedArray = bucketSort(array, 10);
console.log(sortedArray); // Salida: [3, 9, 21, 25, 29, 37, 43, 49]
return 0;
