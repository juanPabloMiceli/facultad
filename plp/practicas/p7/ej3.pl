natural(0).
natural(suc(X)) :- natural(X).

menorOIgual(X,X) :- natural(X).
menorOIgual(X,suc(Y)) :- menorOIgual(X,Y).