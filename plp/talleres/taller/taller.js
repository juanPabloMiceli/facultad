//Escriban acá su código.


function calcularResultado(){
//Editen esta función para que devuelva lo que quieran ver. Pueden escribir acá sus tests, y descomentar las líneas que siguen para correr los tests predefinidos.
  let res = "";
  
  let anilloUno = {dato: 1};
  anilloUno.siguiente = anilloUno;

  // Ejercicio 1
  let anilloCero = {dato: 0};
  anilloCero.siguiente = anilloCero;
  anilloCero.agregar = function(d) {
    let siguienteViejo = this.siguiente;
    this.siguiente = Object.create(this); // hereda los metodos del prototipo, pero queremos sobrecargar los campos
    this.siguiente.dato = d;
    this.siguiente.siguiente = siguienteViejo;
    return this;
  }

  // Ejercicio 2
  anilloCero.toString = function() {
    let res = this.dato.toString();
    let nodoActual = this.siguiente;

    while (nodoActual != this) {
      res += "↝";
      res += nodoActual.dato.toString();
      nodoActual = nodoActual.siguiente;
    }

    return res;
  }

  // Ejercicio 3
  function Anillo(d) {
    this.dato = d;
    this.siguiente = this;
  }

  Anillo.prototype.agregar = anilloCero.agregar;
  Anillo.prototype.toString = anilloCero.toString;

  //Ejercicio 4
  Anillo.prototype.map = function(f) {
    this.dato = f(this.dato);
    let nodoActual = this.siguiente;

    while (nodoActual != this) {
      nodoActual.dato = f(nodoActual.dato);
      nodoActual = nodoActual.siguiente;
    }

    return this;
  }

  Anillo.prototype.copiar = function() {
    let res = new Anillo(this.dato);
    let nodoActual = this.siguiente;
    let nodoActualCopia = res;

    while (nodoActual != this) {
      nodoActualCopia.siguiente = new Anillo(nodoActual.dato);
      nodoActual = nodoActual.siguiente;
      nodoActualCopia = nodoActualCopia.siguiente;
    }

    nodoActualCopia.siguiente = res;
    return res;
  }

  Anillo.prototype.cantidad = function() {
    let res = 1;
    let nodoActual = this.siguiente;

    while (nodoActual != this) {
      res++;
      nodoActual = nodoActual.siguiente; 
    }

    return res;
  }

  // Ejercicio 5
  Anillo.prototype.ponerAnteriores = function(){
    let nodoActual = this;
    let nodoSiguiente = nodoActual.siguiente;

    let newAgregar = function(d) {
      let siguienteViejo = this.siguiente;
      this.siguiente = Object.create(this); // hereda los metodos del prototipo, pero queremos sobrecargar los campos
      this.siguiente.dato = d;
      this.siguiente.siguiente = siguienteViejo;
      this.siguiente.anterior = this
      return this;
    }

    while (nodoSiguiente != this) {
      nodoSiguiente.anterior = nodoActual;
      nodoSiguiente.agregar = newAgregar
      nodoActual = nodoActual.siguiente; 
      nodoSiguiente = nodoSiguiente.siguiente; 
    }
    nodoSiguiente.anterior = nodoActual;
    nodoSiguiente.agregar = newAgregar
    return this;
  }

  // Tests
  Object.setPrototypeOf(anilloUno, anilloCero);

  res += anilloUno.agregar(3).agregar(2)+"<br />"+anilloUno.siguiente; //1 ↝ 2 ↝ 3<br />2 ↝ 3 ↝ 1
  res += "<br />"+(new Anillo(0)).agregar(2).agregar(1)+"<br />"+anilloCero.siguiente; //0 ↝ 1 ↝ 2<br />0
  res += "<br />"+(new Anillo(0)).agregar(2).agregar(1).map(e => e+1);//1 ↝ 2 ↝ 3
  res += "<br />"+(new Anillo(0)).agregar(1).map(e => e+4);//4 ↝ 5
  res += "<br />"+(new Anillo(1)).map(e => e*2);//2
  let anilloDos = new Anillo(2).agregar(2);
  let anilloCopia = anilloDos.copiar();
  anilloDos.agregar(2);
  anilloCopia.agregar(1);
  res +="<br />"+anilloDos;//2 ↝ 2 ↝ 2
  res +="<br />"+anilloCopia;//2 ↝ 1 ↝ 2
  res +="<br />"+anilloCopia;//2 ↝ 1 ↝ 2
  res +="<br />"+anilloDos.cantidad();//3
  res +="<br />"+new Anillo(0).agregar(3).agregar(2).ponerAnteriores().agregar(1).siguiente.anterior;//0 ↝ 1 ↝ 2 ↝ 3
  let anilloLetras = (new Anillo("a")).agregar("d").agregar("c");
  anilloLetras.siguiente.ponerAnteriores();
  anilloLetras.agregar("b");
  res +="<br />"+anilloLetras.siguiente.anterior.dato;//a 
  anilloLetras.anterior.agregar("e");
  res +="<br />"+anilloLetras;//a ↝ b ↝ c ↝ d ↝ e
  res +="<br />"+anilloDos.agregar(2).siguiente.anterior;//undefined
  res +="<br />"+(new Anillo(1)).agregar(2).siguiente.anterior;//undefined 
  return res;
}