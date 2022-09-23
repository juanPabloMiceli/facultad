% palindromo(+L, ?L1)
palindromo(L, L1) :- reversa(L, LR), append(L, LR, L1).

% reversa(+L, -LR)
reversa([], []).
reversa(L, [Head2|Tail2]) :- append(TodoMenosUltimo, [Head2], L), reversa(TodoMenosUltimo, Tail2).

% iesimo(?I, +L, -X)
iesimo(I, L, Elem) :- append(Left, [Elem|_], L), length(Left, K), I is K + 1.