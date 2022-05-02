
--pares quiere la lista infinita de todos los pares (sin repetidos)
paresMal :: [(Int, Int)]
paresMal = [(x,y) | x <-[0..], y <-[0..]] -- Solo genera (0,i) para todo i en los naturales

paresLento :: [(Int, Int)]
paresLento = [(x,y) | z <- [0..], x <-[0..z], y <-[0..z], z == x+y] -- Genera muchos numeros que al final tira

paresRapido :: [(Int, Int)]
paresRapido = [(x,z-x) | z <- [0..], x <-[0..z]]

listasQueSuman :: Int -> [[Int]]
listasQueSuman 0 = [[]]
listasQueSuman x | x > 0 = [ n : l | n <- [1..x], l <- listasQueSuman(x-n)]

listasPositivas :: [[Int]]
listasPositivas = concat [listasQueSuman x | x<-[0..]] 

-- Datazo de color
listasPositivasV2 :: [[Int]]
listasPositivasV2 = concatMap listasQueSuman [0..]

ultimo :: [a] -> a -- 😎
ultimo l = foldr1 (\x y -> y) l

maximo :: Ord a => [a] -> a
maximo l = foldr1 max l

reverso :: [a] -> [a]
reverso l = foldl (flip (:)) [] l

contiene :: Eq a => a -> [a] -> Bool
contiene x l = foldr (\e elemXs -> e == x || elemXs) False l

sumaAlt :: Num a => [a] -> a
sumaAlt l = foldr (-) 0 l
-- sumaAlt [5,4,3]  ~~> 5 - (sumaAlt [4,3])
--                  ~~> 5 - (4 - (sumaAlt[3])) 
--                  ~~> 5 - (4 - (3 - (sumaAlt [])))
--                  ~~> 5 - (4 - (3 - (0)))
--                  ~~> 5 - (4 - 3) ~~> 5 - 4 + 3 

recr :: b -> (a -> [a] -> b -> b) -> [a] -> b
recr z _ [] = z
recr z f (x:xs)= f x xs (recr z f xs)

-- sacarPrimera :: Eq a => a -> [a] -> [a]
-- sacarPrimera e l = recr (\x sacarPrimeraXs xs -> if x == e then xs else e : sacarPrimeraXs) [] l

cierre :: [a] -> [b] -> [(a, b)]
cierre [] _ = []
cierre (x:xs) (y:ys) = if null ys then [] else (x, y) : (cierre xs ys)

cierreV2 :: [a] -> [b] -> [(a, b)]
cierreV2 = foldr (\x cierreV2Xs -> (\ys -> if null ys then [] else (x, head ys) : cierreV2Xs (tail ys))) (const [])

data Polinomio a = X
                    | Cte a
                    | Suma (Polinomio a) (Polinomio a)
                    | Prod (Polinomio a) (Polinomio a)

foldPoli :: b -> (a -> b) -> (b -> b -> b) -> (b -> b -> b) -> (Polinomio a) -> b
foldPoli casoX casoCte casoSuma casoProd pol = case pol of
                                                        X -> casoX
                                                        Cte n -> casoCte n
                                                        Suma p q -> casoSuma (foldPoli casoX casoCte casoSuma casoProd p) (foldPoli casoX casoCte casoSuma casoProd q)
                                                        Prod p q -> casoProd (foldPoli casoX casoCte casoSuma casoProd p) (foldPoli casoX casoCte casoSuma casoProd q)
                                                            -- where rec = foldPoli casoX casoCte casoSuma casoProd
evaluar :: Num a => a -> Polinomio a -> a
evaluar k = foldPoli k id (+) (*)

data RoseTree a = Rose a [RoseTree a]

foldRose :: (a -> [b] -> b) -> (RoseTree a) -> b
foldRose f (Rose x hs) = f x (map (foldRose f) hs)

altura :: RoseTree a -> Int
altura = foldRose (\_ as -> if null as then 1 else 1 + maximum as)

type Conj a = (a->Bool)

vacio :: Conj a
vacio = const False

agregar :: Eq a => a -> Conj a -> Conj a
agregar x c = (\y -> y == x || c y)

interseccion :: Eq a => Conj a -> Conj a -> Conj a
interseccion c1 c2 = (\y -> c1 y && c2 y)

union :: Eq a => Conj a -> Conj a -> Conj a
union c1 c2 = (\y -> c1 y || c2 y)

infinitasFunciones :: Conj (Int -> Int)
infinitasFunciones = (\f -> f 0 == 0)