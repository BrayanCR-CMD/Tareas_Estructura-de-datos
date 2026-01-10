const MAXSIZE = 5;
let queue = [];
let front = -1, rear = -1;

function insertar() {
    let elemento = parseInt(prompt("Ingrese el elemento a insertar: "));
    if (rear === MAXSIZE - 1) {
        console.log("desbordamiento de cola\n");
        return;
    }
    if (front === -1 && rear === -1) {
        front = rear = 0;
    } else {
        rear++;
    }
    queue[rear] = elemento;
    console.log("Elemento insertado: " + elemento + "\n");
}

function eliminar() {
    if (front === -1 || front > rear) {
        console.log("subdesbordamiento de cola\n");
        return;
    }
    let elemento = queue[front];
    if (front === rear) {
        front = rear = -1;
    } else {
        front++;
    }
    console.log("Elemento eliminado: " + elemento + "\n");
}

function mostrar() {
    if (rear === -1 || front === -1 || front > rear) {
        console.log("La cola esta vacia\n");
    } else {
        console.log("Elementos en la cola: ");
        for (let i = front; i <= rear; i++) {
            console.log(queue[i] + " ");
        }
        console.log("\n");
    }
}

function main() {
    let opcion;
    do {
        console.log("Menu de operaciones de cola\n");
        console.log("1. Insertar\n");
        console.log("2. Eliminar\n");
        console.log("3. Mostrar\n");
        console.log("4. Salir\n");
        opcion = parseInt(prompt("Ingrese su opcion: "));
        switch (opcion) {
            case 1:
                insertar();
                break;
            case 2:
                eliminar();
                break;
            case 3:
                mostrar();
                break;
            case 4:
                console.log("Saliendo del programa\n");
                break;
            default:
                console.log("Opcion invalida\n");
        }
    } while (opcion !== 4);
}

main();
