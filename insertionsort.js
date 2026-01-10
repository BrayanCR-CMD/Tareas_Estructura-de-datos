// metodo de ordenamiento insert sort
function insertSort(arr) {
    for (let i = 1; i < arr.length; i++) {
        let key = arr[i];
        let j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return arr;
}

// ejemplo de uso
const array = [12, 11, 13, 5, 6];
console.log("Array original:", array);
const sortedArray = insertSort(array);
console.log("Array ordenado:", sortedArray);

return 0;
