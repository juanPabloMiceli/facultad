//Escriban acá su código.

let pilaVacia = {
  isEmpty: () => {return true},
  pop: function(){return this},
  push: function(e){
    return {
      isEmpty: () => {return false},
      top: () => {return e},
      pop: () => {return this},
      push: this.push 
    }
  }
}