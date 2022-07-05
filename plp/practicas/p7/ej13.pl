[ej12].

% inorder(+AB, -Lista)
inorder(nil, []).
inorder(bin(Left, R, Right), L) :- inorder(Left, LeftList), inorder(Right, RightList), append(LeftList, [R|RightList], L).

% arbolConInorder(+Lista, -AB).
arbolConInorder([], nil).
arbolConInorder(L, bin(Left, R, Right)) :- append(LeftList, [R|RightList], L), arbolConInorder(LeftList, Left), arbolConInorder(RightList, Right). 

% abb(+AB)
abb(nil).
abb(bin(nil, _, nil)).
abb(bin(nil, R, Right)) :-  Right \= nil, minInTree(Right, MinRight), R < MinRight,
                            abb(Right).
abb(bin(Left, R, nil)) :-   Left \= nil, maxInTree(Left, MaxLeft), R > MaxLeft,
                            abb(Left).
abb(bin(Left, R, Right)) :- Left \= nil, Right \= nil,
                            maxInTree(Left, MaxLeft), R > MaxLeft, 
                            minInTree(Right, MinRight), R < MinRight,
                            abb(Left), abb(Right).

% maxInTree(+AB, ?Max)
maxInTree(bin(nil, R, nil), R).
maxInTree(bin(nil, R, Right), Max) :- Right \= nil, maxInTree(Right, MaxRight), max(R, MaxRight, Max). 
maxInTree(bin(Left, R, nil), Max) :- Left \= nil, maxInTree(bin(nil, R, Left), Max).
maxInTree(bin(Left, R, Right), Max) :-  Left \= nil, Right \= nil,
                                        maxInTree(bin(Left, R, nil), MaxLeft), 
                                        maxInTree(bin(nil, R, Right), MaxRight),
                                        max(MaxLeft, MaxRight, Max).

% minInTree(+AB, ?Min)
minInTree(bin(nil, R, nil), R).
minInTree(bin(nil, R, Right), Min) :- Right \= nil, minInTree(Right, MinRight), min(R, MinRight, Min). 
minInTree(bin(Left, R, nil), Min) :- Left \= nil, minInTree(bin(nil, R, Left), Min).
minInTree(bin(Left, R, Right), Min) :-  Left \= nil, Right \= nil,
                                        minInTree(bin(Left, R, nil), MinLeft), 
                                        minInTree(bin(nil, R, Right), MinRight),
                                        min(MinLeft, MinRight, Min).

% abbInsertar(+Elem, +ABIn, -ABOut)
% No anda
abbInsertar(Elem, nil, bin(nil, Elem, nil)).

abbInsertar(Elem, bin(nil, Raiz, nil), bin(bin(nil, Elem, nil), Raiz, nil)) :- Elem < Raiz. 
abbInsertar(Elem, bin(nil, Raiz, nil), bin(nil, Elem, bin(nil, Raiz, nil))) :- Elem < Raiz.
abbInsertar(Elem, bin(nil, Raiz, nil), ABOut) :- Elem > Raiz, abbInsertar(Raiz, bin(nil, Elem, nil), ABOut). 

abbInsertar(Elem , bin(nil, Raiz, Right), bin(bin(nil, Raiz, nil), Elem, Right)) :- Right \= nil, Elem > Raiz. 
abbInsertar(Elem , bin(nil, Raiz, Right), bin(nil, Raiz, NewRight)) :- Right \= nil, Elem > Raiz, abbInsertar(Elem, Right, NewRight).
abbInsertar(Elem, bin(nil, Raiz, Right), bin(nil, Elem, bin(nil, Raiz, Right))) :- Right \= nil, Elem < Raiz. 
abbInsertar(Elem, bin(nil, Raiz, Right), bin(Elem, Raiz, Right)) :- Right \= nil, Elem < Raiz. 

abbInsertar(Elem, bin(Left, Raiz, Right), bin(bin(Left, Raiz, nil), Elem, Right)) :- Left \= nil, Right \= nil, Elem > Raiz.
abbInsertar(Elem, bin(Left, Raiz, Right), bin(Left, Raiz, NewRight)) :- Left \= nil, Right \= nil, Elem > Raiz,
                                                                        abbInsertar(Elem, Right, NewRight).
abbInsertar(Elem, bin(Left, Raiz, Right), bin(bin(Left, Raiz, nil), Elem, Right)) :- Left \= nil, Right \= nil, Elem < Raiz.
abbInsertar(Elem, bin(Left, Raiz, Right), bin(Left, Raiz, NewRight)) :- Left \= nil, Right \= nil, Elem > Raiz,
                                                                        abbInsertar(Elem, Right, NewRight).

