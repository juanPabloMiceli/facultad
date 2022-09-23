% aplanar(+Xs, -Ys)
aplanar([], []).
aplanar([X|Xs], L) :- is_list(X), aplanar(X, Xaplando), append(Xaplando, Xs, ListaAplanada), aplanar(ListaAplanada, L).
aplanar([X|Xs], [X|L]) :- not(is_list(X)), aplanar(Xs, L).