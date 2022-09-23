padre(juan, carlos).
padre(juan, luis).
padre(carlos, daniel).
padre(carlos, diego).
padre(luis, pablo).
padre(luis, manuel).
padre(luis, ramiro).
abuelo(X,Y) :- padre(X,Z), padre(Z,Y).

% 1
% abuelo(X,manuel) => X = juan

% 2
hijo(X, Y) :- padre(Y,X).
hermano(X,Y) :- padre(Z, X), padre(Z,Y), X \= Y.
descendiente(X,Y) :- padre(Y,X).
descendiente(X,Y) :- abuelo(Y,X).

% 3
% abuelo(juan, X)

% 4
% hermano(pablo, X).

% ancestro(X,X).
% ancestro(X,Y) :- ancestro(Z,Y), padre(X,Z).

% 5
ancestro(X,Y) :- descendiente(Y,X).