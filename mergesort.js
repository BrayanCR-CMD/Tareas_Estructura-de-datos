// metodo de ordenamiento merge sort
function mergeSort(arr) {
    if (arr.length <= 1) {
        return arr;
    } else {
        const mid = Math.floor(arr.length / 2);
        const left = arr.slice(0, mid);
        const right = arr.slice(mid);
        return merge(mergeSort(left), mergeSort(right));
    }
}
function merge(left, right) {
    const result = [];
    let i = 0;
    let j = 0;
    while (i < left.length && j < right.length) {
        if (left[i] < right[j]) {
            result.push(left[i]);
            i++;
        }
        else {
            result.push(right[j]);
            j++;
        }
    }
    return result.concat(left.slice(i)).concat(right.slice(j));
}

// ejemplo de uso
const arr = [38, 27, 43, 3, 9, 82, 10];
const sortedArr = mergeSort(arr);
console.log(sortedArr); // [3, 9, 10, 27, 38, 43, 82]
return 0;
