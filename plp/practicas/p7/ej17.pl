frutal(frutilla).
frutal(banana).
frutal(manzana).

cremoso(banana).
cremoso(americana).
cremoso(frutilla).
cremoso(ddl).

leGusta(X) :- frutal(X), cremoso(X), !.
cucurucho(X, Y) :- leGusta(X), leGusta(Y).