%Ejercicio 4
concatenar([],Y,Y).
concatenar([X|XS], Y, [X|ZS]) :- concatenar(XS, Y, ZS).

%Ejercicio 5
%a
last(L, U) :- append(_, [U], L).
%b
reverse([], []).
reverse([L|LS], R) :- reverse(LS,R1), append(R1, [L], R).
%c
prefijo(P, L) :- append(P, _, L).
%d
sufijo(S,L) :- append(_ ,S, L).
%e Puede dar repetidos
sublista(S, L) :- prefijo(P, L), sufijo(S,P).
%f
pertenece(X, L) :- prefijo(P, L), append(P, [X], P1), append(P1, _, L). 

%Ejercicio 6
aplanar([], []).
aplanar([[]|XS], YS) :- aplanar(XS, YS).
aplanar([[X|XS]|YS], ZS) :- aplanar([X|XS], IZQ), aplanar(YS, DER), append(IZQ, DER, ZS).
aplanar([X| XS], YS) :- X \= [], X \= [_ | _] , aplanar(XS, DER), append([X], DER, YS). 

%Ejercicio 7
palindromo(L, L1) :- reverse(L, LR), append(L, LR, L1).
%For fun
iesimo2(0, [X | _], X).
iesimo2(N, [_ | XS], Y) :- iesimo2(M, XS, Y), N is M + 1.
%verdadero
iesimo(N, XS, Z) :- append(IZQ, [Z | _], XS), length(IZQ,N).

%Ejercicio 8 PENDIENTE EL A
noEsta(_, []).
noEsta(X, [Y | XS]) :- noEsta(X, XS),  X \= Y.
%a
partir(N, L, L1, L2) :- append(L1, L2, L), length(L1, N).
%b Devuelvo muchas veces el mismo resultado
borrar(L, X, L) :- noEsta(X, L).
borrar(L, X, LsinX) :- member(X, L), append(L2, L3, L), append(L1, [X], L2) , append(L1, L3,LsinUnaX), borrar(LsinUnaX, X, LsinX).
%c 
sacarDuplicados([], []).
sacarDuplicados([X | XS], [X|L2]) :-sacarDuplicados(XS, L2), noEsta(X, L2).
sacarDuplicados([X | XS], L2) :-sacarDuplicados(XS, L2), member(X, L2).
%d
insertar(X, L, LconX) :- append(P, S, L), append(P, [X|S], LconX).
permutacion([], []).
permutacion([X | L], P) :- permutacion(L, P1), insertar(X, P1, P).
%e
reparto(L, 1, [L]).
reparto(L, N, [P | LS]):- N > 1, append(P, S, L), M is N-1 ,reparto(S, M, LS). 
%f Esto es medio trampa
repartoSinVacias([], []).
repartoSinVacias([X| XS], [P | Slistas]) :- append(P, S, [X|XS]), length(P,N), N > 0 ,  repartoSinVacias(S, Slistas).

%Ejercicio 9 
esLista([]).
esLista([_ | _]).
elementosTomadosEnOrden(L, 0, []) :- esLista(L).
elementosTomadosEnOrden(L, N, Elementos) :- N > 0, repartoSinVacias(L, LS), length(LS, N), ultimosEnOrden(LS, Elementos).
%Menos el ultimo
ultimosEnOrden([XS], [X]) :- member(X,XS).
ultimosEnOrden([XS|[YS|ZS]], [X| L]) :- last(XS,X), ultimosEnOrden([YS|ZS], L).
%Ejercicio 10 sale sin var?
desde(X,X).
desde(X,Y) :- N is X+1, desde(N,Y).
%Ejercicio 11
intercalar([], [], []).
intercalar([], [Y | YS], [Y | YS]).
intercalar([X | XS], [], [X | XS]).
intercalar([X | XS], [Y | YS], [X|[Y|ZS]]) :- intercalar(XS, YS, ZS).

%Ejercicio 12
vacio(nil).

raiz(bin(_, X, _), X).

altura(nil, 0).
altura(bin(IZQ,_,DER), H) :- altura(IZQ, HIZQ), altura(DER, HDER), H is max(HIZQ,HDER) + 1.

cantidadDeNodos(nil,0).
cantidadDeNodos(bin(IZQ,_,DER), C) :- cantidadDeNodos(IZQ, CIZQ), cantidadDeNodos(DER, CDER), C is 1+CIZQ+CDER.

%Ejercicio 13
%bin(bin(nil,4,bin(nil,1,nil)),3, bin(nil,8,nil))
%bin(nil, 4, bin(bin(nil,5,nil), 6,nil))
%bin(bin(nil,1,nil),2,bin(nil,3,nil))
%
%a
inorder(nil, []).
inorder(bin(IZQ, X, DER), L) :- inorder(IZQ, LIZQ), inorder(DER, LDER), append(LIZQ, [X|LDER], L).
%b
arbolConInorder([], nil).
arbolConInorder(XS, bin(IZQ, V, DER)) :- append(P, [V|S], XS), arbolConInorder(P, IZQ), arbolConInorder(S, DER).
%c Uso max_list :D podria chequear que todos esten en orden en inorer  pero bue
aBB(nil).
aBB(bin(nil,X,DER)) :- inorder(DER, LDER), min_list(LDER, MDER), X < MDER.
aBB(bin(IZQ,X,nil)) :- inorder(IZQ, LIZQ), max_list(LIZQ, MIZQ), MIZQ < X.
aBB(bin(IZQ,X,DER)) :- inorder(IZQ, LIZQ), inorder(DER, LDER), max_list(LIZQ, MIZQ), min_list(LDER, MDER), MIZQ < X, X < MDER.
%d
aBBInsertar(X,nil,bin(nil,X,nil)).
aBBInsertar(X, bin(IZQ1, Y, DER), bin(IZQ2, Y, DER)) :- X =< Y, aBBInsertar(X, IZQ1, IZQ2).
aBBInsertar(X, bin(IZQ, Y, DER1), bin(IZQ, Y, DER2)) :- X > Y, aBBInsertar(X, DER1, DER2).
%Ejercicio 14

coprimos(X, Y) :- pares(X,Y), gcd(X,Y) =:= 1.
pares(X,Y) :- desde(0,Z), between(0, Z, X), Y is Z-X.  

%Ejercicio 15
%a
listaQueSuma(1, X, [X]).
listaQueSuma(N, S, [X|XS]) :- N > 1, between(0, S, X), S1 is S - X, N1 is N - 1, listaQueSuma(N1, S1, XS).

rectanguloLatinoConSuma(1, C, S, [L]) :- listaQueSuma(C, S, L).
rectanguloLatinoConSuma(F, C, S, [L | LS]) :- F > 1, listaQueSuma(C, S, L), F1 is F-1 ,rectanguloLatinoConSuma(F1, C, S, LS). 

cuadradosLatinos(N, XS) :- desde(0, S), rectanguloLatinoConSuma(N, N, S, XS).

%b Solucion fea

cuadradoMagico(N, XS) :- N>1, cuadradosLatinos(N, XS), columnasSumanIgual(XS).

columnasSumanIgual(XS) :- sumaPorColumna(XS, SUMC), todosIguales(SUMC).

sumaPorColumna([L],L).
sumaPorColumna([L | LS], SUMC) :- sumaPorColumna(LS, SUMC1), sumaDeLista(SUMC1,L, SUMC).

sumaDeLista([X], [Y], [Z]) :- Z is X+Y.
sumaDeLista([X | XS], [Y | YS], [Z | ZS]) :- Z is X+Y, sumaDeLista(XS,YS,ZS).

todosIguales([_]).
todosIguales([X,Y|XS]):- X is Y, todosIguales([Y|XS]).
%Ejercicio 16 lo dimos en clase.

%Ejercicio 17 me olvide de guardar
%Ejercicio 18 same
%Ejercicio 19
corteMasParejo(L, L1, L2) :- append(L1, L2, L), dif(L1, L2, DIF), not(existeMenor(L, DIF)).

dif(L1, L2, DIF) :- sum_list(L1, S1), sum_list(L2, S2), DIF is abs(S1 - S2).

existeMenor(L, DifMenor) :- append(L1, L2, L), dif(L1, L2, DIF), DIF < DifMenor.

p(X) :- X mod 2 =:= 0, X*7 mod 3 =:= 1.
%Podes usar el not per se traba al pedirle mas soluciones, o por  lo menos lo que se me ocurrio
menorNat(X) :- desde(0, X), p(X), !.



