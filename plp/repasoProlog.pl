a(1,2) :- !.
a(1,3).
b(3).
p(X,Y) :- a(X,Y), b(Y).
