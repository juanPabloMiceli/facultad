% interseccion(+L1, +L2, -L3)

interseccion([], _, []).
interseccion([Head|Tail], L2, [Head|L3]) :- member(Head, L2), interseccion(Tail, L2, L3).
interseccion([Head|Tail], L2, L3) :- not(member(Head, L2)), interseccion(Tail, L2, L3).

% partir(?N, ?L, ?L1, ?L2)
partir(N, L, L1, L2) :- append(L1, L2, L), length(L1, N).

% borrar(+OldL, +Elem, -newL)
borrar([],_,[]).
borrar([Head|Tail], Elem, [Head|L]) :- Elem \= Head, borrar(Tail, Elem, L).
borrar([Elem|Tail], Elem, L) :- borrar(Tail, Elem, L).

% sacarDuplicados(+L1, -L2)
sacarDuplicados([], []).
sacarDuplicados([Head|Tail], L) :- member(Head, Tail), !, sacarDuplicados(Tail, L).
sacarDuplicados([Head|Tail], [Head|L]) :- not(member(Head, Tail)), sacarDuplicados(Tail, L).

% permutacion(+L1, ?L2)
permutacion([],[]).
permutacion([Head1|Tail1], [Head2|Tail2]) :- ground([Head2|Tail2]), member(Head1, [Head2|Tail2]), append(Left, [Head1|Right], [Head2|Tail2]), append(Left, Right, ListaSinHead2), permutacion(Tail1, ListaSinHead2).
permutacion([Head|Tail], ListaPermutada) :- not(ground(ListaPermutada)), permutacion(Tail, ListaPermutadaSinHead), append(LeftListaPermutada, RightListaPermutada, ListaPermutadaSinHead), append(LeftListaPermutada,[Head|RightListaPermutada], ListaPermutada).

% reparto(+L, +N, -LListas)
reparto(L, 1, [L]).
reparto(L, N, [P|Ls]) :- N > 1, append(P,S,L), M is N-1, reparto(S, M, Ls).

% repartoSinVacias(+L, -LListas)
repartoSinVacias([], []).
repartoSinVacias([X| XS], [P | Slistas]) :- append(P, S, [X|XS]), length(P,N), N > 0 ,  repartoSinVacias(S, Slistas).
