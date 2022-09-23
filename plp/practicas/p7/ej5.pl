% last(?L, ?U)
last(L,U) :- append(_,[U],L).

% reverse(+L, -L1)
reverse([], []).
reverse(L,[Head2|Tail2]) :- last(L, Head2), append(ListaSinUltimo, [Head2], L), reverse(ListaSinUltimo, Tail2). 

% prefijo(?P, +L)
prefijo(P,L) :- append(P,_,L).

% sufijo(?S, +L)
sufijo(S,L) :- append(_,S,L).

% sublista(?S, +L)
sublista(S,L) :- prefijo(P,L), sufijo(S,P).

% pertenece(?X, +L)
pertenece(X,L) :- sublista([X], L).