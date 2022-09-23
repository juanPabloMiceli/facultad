desde(X,X).
desde(X,Y) :- M is X + 1, desde(M,Y). 

% coprimos(-X, -Y)
coprimos(X, Y) :- desde(1, Z), between(1, Z, Y), X is Z - Y, gcd(X,Y) =:= 1. 