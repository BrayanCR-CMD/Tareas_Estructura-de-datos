// metodo de ordenamiento shellsort
function shellSort(arr) {
    let n = arr.length;
    let gap = Math.floor(n / 2);

    while (gap > 0) {
        for (let i = gap; i < n; i++) {
            let temp = arr[i];
            let j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }   
        gap = Math.floor(gap / 2);
    }
    return arr;
}

// ejemplo de uso
let array = [12, 34, 54, 2, 3];
console.log("Array original: " + array);
let sortedArray = shellSort(array);
console.log("Array ordenado: " + sortedArray);
return 0;
