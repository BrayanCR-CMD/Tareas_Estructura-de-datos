// metodo de ordenamiento de arbol binario
class Node {
    constructor(data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

class BinarySearchTree {
    constructor() {
        this.root = null;
    }
    insert(data) {
        let newNode = new Node(data);
        if (this.root === null) {
            this.root = newNode;
        }
        else {
            this.insertNode(this.root, newNode);
        }
    }
    insertNode(node, newNode) {
        if (newNode.data < node.data) {
            if (node.left === null) {
                node.left = newNode;
            }
            else {
                this.insertNode(node.left, newNode);
            }
        }
        else {
            if (node.right === null) {
                node.right = newNode;
            }
            else {
                this.insertNode(node.right, newNode);
            }
        }
    }
    inorder(node, result) {
        if (node !== null) {
            this.inorder(node.left, result);
            result.push(node.data);
            this.inorder(node.right, result);
        }
    }
    getSortedArray() {
        let result = [];
        this.inorder(this.root, result);
        return result;
    }
}

function treeSort(arr) {
    let bst = new BinarySearchTree();
    for (let i = 0; i < arr.length; i++) {
        bst.insert(arr[i]);
    }
    return bst.getSortedArray();
}
// ejemplo de uso
let array = [12, 34, 54, 2, 3];
console.log("Array original: " + array);
let sortedArray = treeSort(array);
console.log("Array ordenado: " + sortedArray);
return 0;
