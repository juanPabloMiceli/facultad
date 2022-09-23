% vacio(+AB)
vacio(nil).

% raiz(+AB, ?Raiz)
raiz(nil, nil).
raiz(bin(_, R, _), R).

% altura(+AB, ?Altura)
altura(nil, 0).
altura(bin(Left, _, Right), Altura) :- altura(Left, AlturaLeft), altura(Right, AlturaRight), max(AlturaLeft, AlturaRight, MaxAlturaSubArbol), Altura is MaxAlturaSubArbol + 1. 

% max(+E1, +E2, ?Max)
max(E1, E2, E1) :- E1 >= E2. 
max(E1, E2, E2) :- E2 > E1. 

% min(+E1, +E2, ?Min)
min(E1, E2, E2) :- E1 >= E2. 
min(E1, E2, E1) :- E2 > E1. 

% cantidadDeNodos(+AB, ?Cantidad)
cantidadDeNodos(nil, 0).
cantidadDeNodos(bin(Left, _, Right), Cantidad) :- cantidadDeNodos(Left, CantidadLeft), cantidadDeNodos(Right, CantidadRight), Cantidad is CantidadLeft + CantidadRight + 1.