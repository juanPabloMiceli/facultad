% concatenar(?Lista1, ?Lista2, ?Lista3)
concatenar([], L, L).
concatenar([Head|Tail], L, [Head|Rest]) :- concatenar(Tail, L, Rest).