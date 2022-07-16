%Autómatas de ejemplo. Si agregan otros,  mejor.

ejemplo(1, a(s1, [sf], [(s1, a, sf)])).
ejemplo(2, a(si, [si], [(si, a, si)])).
ejemplo(3, a(si, [si], [])).
ejemplo(4, a(s1, [s2, s3], [(s1, a, s1), (s1, a, s2), (s1, b, s3)])).
ejemplo(5, a(s1, [s2, s3], [(s1, a, s1), (s1, b, s2), (s1, c, s3), (s2, c, s3)])).
ejemplo(6, a(s1, [s3], [(s1, b, s2), (s3, n, s2), (s2, a, s3)])).
ejemplo(7, a(s1, [s2], [(s1, a, s3), (s3, a, s3), (s3, b, s2), (s2, b, s2)])).
ejemplo(8, a(s1, [sf], [(s1, a, s2), (s2, a, s3), (s2, b, s3), (s3, a, s1), (s3, b, s2), (s3, b, s4), (s4, f, sf)])). % No deterministico :)
ejemplo(9, a(s1, [s1], [(s1, a, s2), (s2, b, s1)])).
ejemplo(10, a(s1, [s10, s11], 
        [(s2, a, s3), (s4, a, s5), (s9, a, s10), (s5, d, s6), (s7, g, s8), (s15, g, s11), (s6, i, s7), 
        (s13, l, s14), (s8, m, s9), (s12, o, s13), (s14, o, s15), (s1, p, s2), (s3, r, s4), (s2, r, s12), (s10, s, s11)])).
ejemplo(11, a(s0, [s2], [(s0, a, s1), (s0, b, s3), (s1, b, s2), (s3, a, s3)])). % Tiene un ciclo desde el que no se puede alcanzar un estado final.
ejemplo(12, a(s0, [s4], [(s0, a, s1), (s1, b, s2), (s2, a, s3), (s3, b, s1), (s1, a, s4)])). % Tiene un ciclo desde el que se puede alcanzar un estado final.
ejemplo(13, a(s0, [s5], [(s0, a, s1), (s1, b, s2), (s2, a, s1), (s1, c, s3), (s3, d, s4), (s4, e, s3), (s3, f, s5)])). % Tiene dos ciclos desde los que se puede alcanzar un estado final.
ejemplo(14, a(s0, [s3], [(s0, b, s1), (s1, a, s2), (s2, b, s1), (s1, a, s3), (s0, a, s4), (s4, c, s5), (s5, d, s4)])). % Tiene un ciclo desde el que se puede alcanzar un estado final y uno desde el que no.
ejemplo(15, a(s1, [s2], [(s1, a, s2), (s1, b, s3), (s3, b, s3)])). % Tiene un ciclo desde el que no se puede alcanzar un estado final.

ejemploMalo(1, a(s1, [s2], [(s1, a, s1), (s1, b, s2), (s2, b, s2), (s2, a, s3)])). %s3 es un estado sin salida.
ejemploMalo(2, a(s1, [sf], [(s1, a, s1), (sf, b, sf)])). %sf no es alcanzable.
ejemploMalo(3, a(s1, [s2, s3], [(s1, a, s3), (s1, b, s3)])). %s2 no es alcanzable.
ejemploMalo(4, a(s1, [s3], [(s1, a, s3), (s2, b, s3)])). %s2 no es alcanzable.
ejemploMalo(5, a(s1, [s3, s2, s3], [(s1, a, s2), (s2, b, s3)])). %Tiene un estado final repetido.
ejemploMalo(6, a(s1, [s3], [(s1, a, s2), (s2, b, s3), (s1, a, s2)])). %Tiene una transición repetida.
ejemploMalo(7, a(s1, [], [(s1, a, s2), (s2, b, s3)])). %No tiene estados finales.

%%Proyectores
inicialDe(a(I, _, _), I).

finalesDe(a(_, F, _), F).

transicionesDe(a(_, _, T), T).

%Auxiliar dada en clase
%desde(+X, -Y).
desde(X, X).
desde(X, Y):-desde(X, Z),  Y is Z + 1.


%%Predicados pedidos.

% 1) esDeterministico(+Automata)
esDeterministico(a(_, _, [])).
esDeterministico(a(_, _, [(Estado, Etiqueta, _)|Transiciones])) :- not(member((Estado, Etiqueta, _), Transiciones)), esDeterministico(a(_, _, Transiciones)).

% 2) estados(+Automata, ?Estados)
% estados(a(I, F, []), L) :- ground(L).
estados(A, L) :- ground(L), dameEstados(A, EstadosDeA), subset(EstadosDeA, L), subset(L, EstadosDeA).
estados(a(I, F, Transiciones), L) :- var(L),
                                     dameEstados(a(I, F, Transiciones), EstadosRepetidos),
                                     list_to_set(EstadosRepetidos, EstadosSinRepetir),
                                     sort(EstadosSinRepetir, L).

% dameEstados(+Automata, -Estados)
dameEstados(a(I, F, []), [I|F]).
dameEstados(a(I, F, [(Estado1, _, Estado2)|Transiciones]), L) :- dameEstados(a(I, F, Transiciones), RecL), append([Estado1, Estado2], RecL, L).

% 3)esCamino(+Automata, ?EstadoInicial, ?EstadoFinal, +Camino)
esCamino(A, S1, S1, [S1]) :- estados(A, EstadosDeA), member(S1, EstadosDeA).
esCamino(a(I, F, Transiciones), S1, S2, [S1|[Siguiente|Resto]]) :- member((S1, _, Siguiente), Transiciones),
                                                                   esCamino(a(I, F, Transiciones), Siguiente, S2, [Siguiente|Resto]).

% 4) ¿el predicado anterior es o no reversible con respecto a Camino y por qué?
% No es reversible porque si el autómata tiene ciclos, puede generar infinitamente mas caminos metiendo ciclos cuando tiene que instanciar Siguiente y nunca va a llegar a una resolución.

% 5) caminoDeLongitud(+Automata, +N, -Camino, -Etiquetas, ?S1, ?S2)
caminoDeLongitud(A, 1, [S1], [], S1, S1) :- estados(A, EstadosDeA), member(S1, EstadosDeA).
caminoDeLongitud(a(I, F, Ts), N, [S1|[Sig|Resto]], [E|Es], S1, S2) :- N > 1, M is N-1,
                                                                      member((S1, E, Sig), Ts),
                                                                      caminoDeLongitud(a(I, F, Ts), M, [Sig|Resto], Es, Sig, S2).

% 6) alcanzable(+Automata, +Estado) - hecho con generate and test
alcanzable(a(I, F, T), S) :- cantidadDeEstados(a(I,F,T), M), N is M+1,
                             between(2, N, Longitud), caminoDeLongitud(a(I, F, T), Longitud, _, _, I, S), !. % porque puede haber muchos caminos

% 7) automataValido(+Automata)
automataValido(a(I, F, T)) :- estados(a(I, F, T), EstadosDeA), subtract(EstadosDeA, F, EstadosNoFinales), subtract(EstadosDeA, [I], EstadosNoIniciales),
                              forall(member(S, EstadosNoFinales), tieneTransicionesSalientes(a(I, F, T), S)),
                              forall(member(S, EstadosNoIniciales), alcanzable(a(I, F, T), S)),
                              F \= [],
                              length(F, LongitudF), list_to_set(F, FSinRepetidos), length(FSinRepetidos, LongitudF),
                              length(T, LongitudT), list_to_set(T, TSinRepetidos), length(TSinRepetidos, LongitudT).

% tieneTransicionesSalientes(+Automata, +Estado)
tieneTransicionesSalientes(a(_, _, T), S) :- member((S, _, _), T).

%--- NOTA: De acá en adelante se asume que los autómatas son válidos.

% 8) hayCiclo(+Automata) - hecho con generate and test
hayCiclo(a(I, F, T)) :- estados(a(I, F, T), EstadosDeA), member(S, EstadosDeA), alcanzable(a(S, F, T), S), !.

% 9) reconoce(+Automata, ?Palabra) - hecho con generate and test
% reconoce(A, P) :- ground(P), length(P, M), N is M+1, inicialDe(A, I), unFinal(A, SF), caminoDeLongitud(A, N, _, P, I, SF).
% reconoce(A, P) :- not(ground(P)), not(hayCiclo(A)), reconoceSinCiclos(A, P).
% reconoce(A, P) :- not(ground(P)), hayCiclo(A), reconoceConCiclos(A, P).
reconoce(A, P) :- ground(P), length(P, M), N is M+1, inicialDe(A, I), unFinal(A, SF), caminoDeLongitud(A, N, _, P, I, SF).
reconoce(A, P) :- not(ground(P)), not(tienePalabraConCiclos(A)), reconoceSinCiclos(A, P).
reconoce(A, P) :- not(ground(P)), tienePalabraConCiclos(A), reconoceConCiclos(A, P).

% reconoceSinCiclos(+Automata, ?Palabra)
reconoceSinCiclos(A, P) :- cantidadDeEstados(A, M), between(0, M, N), inicialDe(A, I), unFinal(A, SF), caminoDeLongitud(A, N, _, P, I, SF).

% reconoceConCiclos(+Automata, ?Palabra)
reconoceConCiclos(A, P) :- desde(0, N), inicialDe(A, I), unFinal(A, SF), caminoDeLongitud(A, N, _, P, I, SF).

% tienePalabraConCiclos(+Automata)
tienePalabraConCiclos(A) :- cantidadDeEstados(A, M), N is 2*M, between(M, N, Long), inicialDe(A, I), unFinal(A, SF), caminoDeLongitud(A, Long, _, _, I, SF).

% 10) PalabraMásCorta(+Automata, ?Palabra)
% palabraMasCorta(A, Palabras) :- largoPalabraMasCorta(A, L), etiquetas(A, E), todasLasOpciones(L, E, Palabras), reconoce(A, Palabras).
palabraMasCorta(A, Palabra) :- largoPalabraMasCorta(A, L), reconoceSinCiclos(A, Palabra), length(Palabra, L).

% largoPalabraMasCorta(+Automata, -Largo)
largoPalabraMasCorta(A, L) :- reconoce(A,P), !, length(P, L).

%% Predicados auxiliares

% unFinal(+A, -SF)
unFinal(A, SF) :- finalesDe(A, F), member(SF, F).

% cantidadDeEstados(+A, -N)
cantidadDeEstados(A, N) :- estados(A, E), length(E, N).

%-----------------
%----- Tests -----
%-----------------

% Algunos tests de ejemplo. Deben agregar los suyos.

test(1) :- ejemplo(5, Det), esDeterministico(Det).
test(2) :- ejemplo(4, NoDet), not(esDeterministico(NoDet)).
test(3) :- ejemplo(5, A), estados(A, [s2,s1,s2,s3]).
test(4) :- ejemplo(5, A), not(estados(A, [s2,s1])).
test(5) :- ejemplo(5, A), esCamino(A, s1, s2, [s1,s2]).
test(6) :- ejemplo(5, A), esCamino(A, s1, s1, [s1]).
test(7) :- ejemplo(5, A), esCamino(A, s1, s1, [s1,s1,s1,s1,s1,s1]).
test(8) :- ejemplo(5, A), caminoDeLongitud(A, 3, [s1, s1, s1], [a, a], s1, s1).
test(9) :- ejemplo(5, A), caminoDeLongitud(A, 3, [s1, s1, s2], [a, b], s1, s2).
test(10) :- ejemplo(5, A), caminoDeLongitud(A, 3, [s1, s1, s3], [a, c], s1, s3).
test(11) :- ejemplo(5, A), caminoDeLongitud(A, 3, [s1, s2, s3], [b, c], s1, s3).
test(12) :- ejemplo(5, A), alcanzable(A, s3).
test(13) :- ejemploMalo(2, A), not(alcanzable(A, sf)).
test(14) :- forall(ejemplo(_, A),  automataValido(A)).
test(15) :- not((ejemploMalo(_, A),  automataValido(A))).
test(16) :- ejemplo(5, A), hayCiclo(A).
test(17) :- ejemplo(9, A), reconoce(A, [a,  b,  a,  b,  a,  b,  a,  b]).
test(18) :- ejemplo(7, A), reconoce(A, [a,  a,  a,  b,  b]).
test(19) :- ejemplo(7, A), not(reconoce(A, [b])).
test(20) :- not((ejemplo(5, A), reconoce(A, [a, b, b, c]))).
test(21) :- ejemplo(10, A), reconoce(A, [p, X, r, X, d, i, _, _, a, _]).
test(22) :- ejemplo(15, A), reconoce(A, [a]).
test(23) :- ejemplo(11, A), reconoce(A, [a,b]).
test(24) :- ejemplo(2, A),  findall(P, palabraMasCorta(A, P), [[]]).
test(25) :- ejemplo(5, A),  findall(P, palabraMasCorta(A, P), Lista), length(Lista, 2), sort(Lista, [[b], [c]]).
test(26) :- ejemplo(4, A),  findall(P, palabraMasCorta(A, P), Lista), length(Lista, 2), sort(Lista, [[a], [b]]).
test(27) :- ejemplo(6, A),  findall(P, palabraMasCorta(A, P), [[b, a]]).
test(28) :- ejemplo(7, A),  findall(P, palabraMasCorta(A, P), [[a, b]]).
test(29) :- ejemplo(8, A),  findall(P, palabraMasCorta(A, P), Lista), length(Lista, 2), sort(Lista, [[a,  a,  b,  f], [a,  b,  b,  f]]).
test(30) :- ejemplo(10, A),  findall(P, palabraMasCorta(A, P), [[p, r, o, l, o, g]]).
test(31) :- forall(member(X, [2, 4, 5, 6, 7, 8, 9]), (ejemplo(X, A), hayCiclo(A))).
test(32) :- not((member(X, [1, 3, 10]), ejemplo(X, A), hayCiclo(A))).
test(33) :- ejemplo(10, A), findall(P, reconoce(A, P), Lista), length(Lista, 3), sort(Lista, [[p, a, r, a, d, i, g, m, a],[p, a, r, a, d, i, g, m, a, s], [p, r, o, l, o, g]]).

tests :- forall(between(1, 33, N), test(N)). %IMPORTANTE: Actualizar la cantidad total de tests para contemplar los que agreguen ustedes.
