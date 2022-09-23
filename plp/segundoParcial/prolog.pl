% masRepetidos(+L,-X)
masRepetidos(L,X) :- append(Left, [X|_], L), not(member(X,Left)), 
                     cantidad(X, L, N), not((member(Y, L), cantidad(Y, L, M), M > N)).

% cantidad(+E, +L, -N)
cantidad(_, [], 0).
cantidad(E, [E|Tail], N) :- cantidad(E, Tail, M), N is M + 1.
cantidad(E, [H|Tail], N) :- E \= H, cantidad(E, Tail, N).

% partesQueSuman(+L, +S, -P)
partesQueSuman(L,S,UnaParte) :- partes(L, ListaDePartes), member(UnaParteReverse, ListaDePartes), suma(UnaParteReverse, S), reverseList(UnaParteReverse, UnaParte).

% partes(+L, -P)
partes([], []).
partes([Head|Tail], Partes) :- partes(Tail, PT), addToAll(PT, Head, P2), append(PT, P2, Partes).

% reverseList(+L, -Lout)
reverseList([], []).
reverseList([Head|Tail], L) :- reverseList(Tail, Left), append(Left, [Head], L).

% suma(+L, -S)
suma([], 0).
suma([Head|Tail], S2) :- suma(Tail, S1), S2 is S1 + Head.

% addToAll(+LL, +E, -LLOut)
addToAll([], E, [[E]]).
addToAll([Head|Tail], E, [Head2|Tail2]) :- append(Head, [E], Head2), addToAll(Tail, E, Tail2).