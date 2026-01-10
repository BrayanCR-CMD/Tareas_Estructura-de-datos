const max_size = 100;

let stack = [];
let top = -1;

function push(value) {
    if (top >= max_size - 1) {
        console.log("Stack Overflow");
        return;
    }
    stack[++top] = value;
}

function pop() {
    if (top < 0) {
        console.log("Stack Underflow");
        return -1; // Indica si la pila esta vacia
    }
    return stack[top--];
}

function peek() {
    if (top < 0) {
        console.log("Stack vacio");
        return -1; // Indica si la pila esta vacia
    }
    return stack[top];
}

function isEmpty() {
    return top === -1;
}

function isFull() {
    return top >= max_size - 1;
}

// ejemplo de uso
push(10);
push(20);
push(30);

console.log("Top element is: " + peek());

console.log("Popped element is: " + pop());

console.log("Is stack empty? " + (isEmpty() ? "Yes" : "No"));
