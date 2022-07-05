// Ejercicio 1
let c1r = {
    r: 1,
    i: 1
};

c1r.sumar = function(otroComplejo){
    this.r = this.r + otroComplejo.r;
    this.i = this.i + otroComplejo.i;
}

c1r.staticSumar = function(otroComplejo){
    let complejoADevolver = {
        r: this.r + otroComplejo.r,
        i: this.i + otroComplejo.i
    };
    Object.setPrototypeOf(complejoADevolver, this);
    return complejoADevolver;
}

let c = c1r.staticSumar(c1r);

c.staticRestar = function(otroComplejo){
    let complejoADevolver = {
        r: this.r - otroComplejo.r,
        i: this.i - otroComplejo.i
    };
    Object.setPrototypeOf(complejoADevolver, this);
    return complejoADevolver;
}

c1r.mostrar = function(){
    return this.r.toString() + " + " + this.i.toString() + "i";
}

// Ejercicio 2
let t = {
    ite: function(a, b){
        return a;
    }
}

let f = {
    ite: function(a, b){
        return b;
    }
}

t.mostrar = function(){
    return "Verdadero";
}

f.mostrar = function(){
    return "Falso";
}

t.not = function(){
    return f;
}

f.not = function(){
    return t;
}

t.and = function(anotherBoolean){
    return anotherBoolean;
}

f.and = function(anotherBoolean){
    return f;
}

// Ejercicio 3
let cero = {

    esCero: () => {return true},
    succ: function() {
        return {
            esCero: () => {return false},
            pred: () => {return this},
            succ: this.succ
        }
    }
}

// cero.toNumber = 0;
// cero.succ = function(){
//     return {
//         esCero: false,
//         toNumber: this.toNumber + 1,
//         pred: this,
//         succ: this.succ
//     }
// }

// cero.for = function(o){
//     return;
// }
// cero.succ = function(){
//     let parent = this;
//     return {
//         esCero: false,
//         toNumber: parent.toNumber + 1,
//         pred: parent,
//         succ: parent.succ,
//         for: function(o){
//             parent.for(o);
//             o.eval(parent.toNumber + 1);
//         }
//     }
// }

let evaluator = {
    eval: function(i){
        console.log(i)
    }
}

// Ejercicio 4
let Punto = {
    mostrar: function(){
        return `Punto(${this.x},${this.y})`;
    },
    new: function(x, y){
        let res = Object.create(this);
        res.x = x;
        res.y = y;
        return res;
    }
}

let PuntoColoreado = Object.create(Punto);
PuntoColoreado.color = "rojo";

PuntoColoreado.newWithColor = function(x, y, c){
    let res = this.new(x, y);
    res.color = c;
    return res;
}


// Ejercicio 5

function ClasePunto(x, y){
    if(x !== undefined) this.x = x;
    if(y !== undefined) this.y = y;
}
ClasePunto.prototype.mostrar = function(){
    return `Punto(${this.x},${this.y})`;
}

function PuntoColoreado(x, y, color = 'rojo') {
    Punto.call(this, x, y)
    this.color = color
}

Object.setPrototypeOf(PuntoColoreado.prototype, Punto.prototype);

// Ejercicio 7
function C1(){};
C1.prototype.g = "hola";
function C2(){};
C2.prototype.g = "mundo";
let A = new C2();
let B = new C1();
let C = Object.create(A);
A = B; /* primera opcion */
// C2.prototype.g = C1.prototype.g; /* segunda opcion */
// Object.setPrototypeOf(A, B); /* tercera opcion */
// console.log(A.g);
// console.log(B.g);
// console.log(C.g);

// Ejercicio 8