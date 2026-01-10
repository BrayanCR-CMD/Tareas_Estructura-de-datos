// arreglos con clases
class Persona {
    constructor(nombre, edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
}

class agregarPersona {
    constructor() {
        this.personas = [];
    }
}

agregarPersona.prototype.agregar = function(nombre, edad) {
    const nuevaPersona = new Persona(nombre, edad);
    this.personas.push(nuevaPersona);
}

agregarPersona.prototype.mostrarPersonas = function() {
    this.personas.forEach(persona => {
        console.log(`Nombre: ${persona.nombre}, Edad: ${persona.edad}`);
    });
}
// Ejemplo de uso
const listaPersonas = new agregarPersona();
listaPersonas.agregar('Ana', 28);
listaPersonas.agregar('Luis', 34);
listaPersonas.mostrarPersonas();
 return 0;
