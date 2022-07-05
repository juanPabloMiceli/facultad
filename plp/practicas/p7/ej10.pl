% desde(+X, -Y)

% desde2(+X, ?Y)
desde2(X, X).
desde2(X,Y) :- nonvar(Y), X =< Y.
desde2(X,Y) :- M is X+1, var(Y), desde2(M, Y).