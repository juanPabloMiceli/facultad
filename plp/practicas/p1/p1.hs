-- Ej 1 Incompleto
max2 :: (Float, Float) -> Float
max2 (x, y) | x >= y = x
            | otherwise = y

normaVectorial :: (Float, Float) -> Float
normaVectorial (x, y) = sqrt (x^2 + y^2)

-- flip (-) x ~~> x (-)
sustraer :: Float -> (Float -> Float)
sustraer = flip (-) 

predecesor :: Float -> Float
predecesor = subtract 1

evaluarEnCero :: (Float -> Float) -> Float
evaluarEnCero = \f -> f 0

dosVeces :: (Float -> Float) -> (Float -> Float)
dosVeces = \f -> f.f

flipAll :: [a -> b -> c] -> [b -> a -> c]
flipAll = map flip

-- flip flip
flipRaro :: b -> (a -> b -> c) -> a -> c
flipRaro = flip flip

-- Ej 2

customCurry :: ((Float, Float) -> Float) -> (Float -> (Float -> Float))
customCurry f = (\x y -> f(x,y))

customUncurry :: (Float -> (Float -> Float)) -> ((Float, Float) -> Float)
customUncurry f = (\(x,y) -> f x y)

-- curryN: Imposible manito


-- Ej 3
-- [x | x <- [1..3], y <- [x..3], (x + y) `mod` 3 == 0]
-- ~~> x = 1, y = 1 ~~> x+y = 2 ~~> False
-- ~~> x = 1, y = 2 ~~> x+y = 3 ~~> True ~~> keep x ~~> keep 1
-- ~~> x = 1, y = 3 ~~> x+y = 4 ~~> False
-- ~~> x = 2, y = 2 ~~> x+y = 4 ~~> False
-- ~~> x = 2, y = 3 ~~> x+y = 5 ~~> False
-- ~~> x = 3, y = 3 ~~> x+y = 6 ~~> True ~~> keep x ~~> keep 3

-- [1, 3]

-- Ej 4
pitagoricas :: [(Integer, Integer, Integer)]
pitagoricas = [(x,y,z) | w <- [1..], x <- [1..w], y <- [1..w], z <- [1..w], x^2 + y^2 == z^2, w == x+y+z, x >= y]

-- Ej 5
-- milPrimos :: [Int]
-- milPrimos = milPrimosAux []

-- milPrimosAux :: [Int] -> [Int]
-- milPrimos x = 

-- Ej 10

sumFoldR :: Num a => [a] -> a
sumFoldR = foldr (\rightMostElem resultadoHastaElMomento -> rightMostElem + resultadoHastaElMomento) 0

elemFoldR :: Eq a => a -> [a] -> Bool
elemFoldR e = foldr (\rightMostElem resultadoHastaElMomento -> rightMostElem == e || resultadoHastaElMomento) False 

addFoldR :: [a] -> [a] -> [a]
addFoldR lista2 = flip (foldr (\rightMostElem resultadoHastaElMomento -> rightMostElem : resultadoHastaElMomento)) lista2

filterFoldR :: (a -> Bool) -> [a] -> [a]
filterFoldR predicado = foldr (\rightMostElem resultadoHastaElMomento -> if (predicado rightMostElem) then rightMostElem : resultadoHastaElMomento else resultadoHastaElMomento) []

mapFoldR :: (a -> b) -> [a] -> [b]
mapFoldR f = foldr (\rightMostElem resultadoHastaElMomento -> f rightMostElem : resultadoHastaElMomento) []


mejorSegun :: (a -> a -> Bool) -> [a] -> a
mejorSegun comparador = foldr1 (\rightMostElem secondRightMostElem -> if (comparador rightMostElem secondRightMostElem) then rightMostElem else secondRightMostElem) 

sumasParciales :: Num a => [a] -> [a]
sumasParciales = foldl (\resultadoHastaElMomento leftMostElem  -> if (length resultadoHastaElMomento) == 0 then [leftMostElem] else resultadoHastaElMomento ++ [(leftMostElem + (last resultadoHastaElMomento))]) []

sumaAlt :: Num a => [a] -> a
sumaAlt = foldr (-) 0


-- Ej 13

recr :: (a -> [a] -> b -> b) -> b -> [a] -> b
recr _ z [] = z
recr f z (x:xs) = f x xs (recr f z xs)

sacarUna :: Eq a => a -> [a] -> [a]
sacarUna elem = recr (\x xs resultadoRecursivo -> if (x == elem) then xs else x : resultadoRecursivo) []

insertarOrdenado :: Ord a => a -> [a] -> [a]
insertarOrdenado elem = recr (\x xs resultadoRecursivo -> if (x >= elem) then elem : (x : xs) else x : resultadoRecursivo) []

-- Ej 18
foldNat :: Num a => (a -> a) -> a -> Integer -> a
foldNat _ casoBase 0 = casoBase
foldNat f casoBase n = f (foldNat f casoBase (n-1))

potencia :: Integer -> Integer -> Integer
potencia base = foldNat (\resultadoRecursivo -> resultadoRecursivo * base) 1

-- Ej 19
data Polinomio a =  X
                 |  Cte a
                 |  Suma (Polinomio a) (Polinomio a)
                 |  Prod (Polinomio a) (Polinomio a) 

foldPolinomio :: b -> (a -> b) -> (b -> b -> b) -> (b -> b -> b) -> (Polinomio a) -> b
foldPolinomio casoX casoCte casoSuma casoProd pol = case pol of
                                                        X -> casoX
                                                        Cte k -> casoCte k
                                                        Suma p1 p2 -> casoSuma (foldPolinomio casoX casoCte casoSuma casoProd p1) (foldPolinomio casoX casoCte casoSuma casoProd p2)
                                                        Prod p1 p2 -> casoProd (foldPolinomio casoX casoCte casoSuma casoProd p1) (foldPolinomio casoX casoCte casoSuma casoProd p2)

evaluar :: Num a => a -> (Polinomio a) -> a
evaluar k = foldPolinomio k id (+) (*)

-- Ej 20
type Conj a = (a -> Bool)

vacio :: Conj a
vacio = const False

agregar :: Eq a => a -> Conj a -> Conj a
agregar elem c = (\x -> (elem == x) || c x)

interseccion :: Eq a => Conj a -> Conj a -> Conj a
interseccion c1 c2 = (\x -> c1 x && c2 x)

union :: Eq a => Conj a -> Conj a -> Conj a
union c1 c2 = (\x -> c1 x || c2 x)

singleton :: Eq a => a -> Conj a
singleton x = agregar x vacio

-- Ej 22
data AHD tInterno tHoja = Hoja tHoja
                        | Rama tInterno (AHD tInterno tHoja)
                        | Bin (AHD tInterno tHoja) tInterno (AHD tInterno tHoja)

foldAHD :: (tHoja -> tRes) -> (tInterno -> tRes -> tRes) -> (tRes -> tInterno -> tRes -> tRes) -> AHD tInterno tHoja -> tRes
foldAHD casoHoja casoRama casoBin ahd = case ahd of 
                                            Hoja hoja -> casoHoja hoja
                                            Rama rama subAhd -> casoRama rama (foldAHD casoHoja casoRama casoBin subAhd)
                                            Bin i rama d -> casoBin (foldAHD casoHoja casoRama casoBin i) rama (foldAHD casoHoja casoRama casoBin d)

mapAHD :: (tInterno -> tInternoRes) -> (tHoja -> tHojaRes) -> AHD tInterno tHoja -> AHD tInternoRes tHojaRes
mapAHD fInterna fHoja = foldAHD (\hoja -> Hoja (fHoja hoja)) (\rama subAhd -> Rama (fInterna rama) subAhd) (\i rama d -> Bin i (fInterna rama) d)

hojasAHD :: AHD tInterno tHoja -> [tHoja]
hojasAHD = foldAHD (\hoja -> [hoja]) (\rama res -> res) (\i rama d -> i ++ d)

internosAHD :: AHD tInterno tHoja -> [tInterno]
internosAHD = foldAHD (\hoja -> []) (\rama res -> rama : res) (\i rama d -> i ++ (rama : d))

-- Ej 24
data RoseTree a = Rose a [RoseTree a]

foldRoseTree :: (a -> [b] -> b) -> RoseTree a -> b
foldRoseTree casoRose (Rose elem hijos) = casoRose elem (map (foldRoseTree casoRose) hijos)

hojasRoseTree :: RoseTree a -> [a]
hojasRoseTree = foldRoseTree (\elem hijosResueltos -> if null hijosResueltos then [elem] else aplanar hijosResueltos)

aplanar :: [[a]] -> [a]
aplanar [x] = x
aplanar (x:xs) = x ++ (aplanar xs)

distanciasRoseTree :: RoseTree a -> [Integer]
distanciasRoseTree = foldRoseTree (\elem hijosResueltos -> if (null hijosResueltos) then [0] else map (\x -> x+1) (aplanar hijosResueltos))

alturaRoseTree :: RoseTree a -> Integer
alturaRoseTree r = (maximum (distanciasRoseTree r)) + 1 


-- Repaso primer parcial

data AB a =     Nil
            |   Arbol (AB a) a (AB a)

foldAB :: b -> (b -> a -> b -> b) -> AB a -> b
foldAB casoNil casoArbol ab = case ab of 
                            Nil -> casoNil
                            Arbol i r d -> casoArbol (foldAB casoNil casoArbol i) r (foldAB casoNil casoArbol d)

recAB :: b -> (b -> a -> b -> AB a -> AB a -> b) -> AB a -> b
recAB casoNil casoArbol ab = case ab of
                            Nil -> casoNil
                            Arbol i r d -> casoArbol (recAB casoNil casoArbol i) r (recAB casoNil casoArbol d) i d

esNil :: AB a -> Bool
esNil ab = case ab of
            Nil -> True
            Arbol i r d -> False

esHoja :: AB a -> Bool
esHoja ab = case ab of
            Nil -> False
            Arbol i r d -> (esNil i) && (esNil d)

mejorSegunAB :: (a -> a -> Bool) -> AB a -> a
mejorSegunAB comp ab = mejorSegunABAux (getBest comp) ab

getBest :: (a -> a -> Bool) -> (a -> a -> a)
getBest comp = (\e1 e2 -> if (comp e1 e2) then e1 else e2)


mejorSegunABAux :: (a -> a -> a) -> AB a -> a
mejorSegunABAux best = recAB 
                                    (error "Empty tree!") 
                                    (\recI r recD i d -> if (esNil i && esNil d) 
                                                            then r 
                                                            else 
                                                                if esNil i
                                                                    then best r recD
                                                                    else
                                                                        if esNil d
                                                                            then best r recI
                                                                            else
                                                                                best r (best recI recD)
                                    ) 

esABB :: Ord a => AB a -> Bool
esABB = recAB True (\recI r recD i d -> recI && recD && (esNil i || (r > (mejorSegunAB (>) i))) && (esNil d || (r < (mejorSegunAB (<) d))))

data Prop = Var String | Not Prop | And Prop Prop | Or Prop Prop

recProp :: (String -> b) -> (Prop -> b -> b) -> (Prop -> Prop -> b -> b -> b) -> (Prop -> Prop -> b -> b -> b) -> Prop -> b
recProp casoVar casoNot casoAnd casoOr prop = case prop of
                                                Var x -> casoVar x
                                                Not p -> casoNot p (recc p)
                                                And p q -> casoAnd p q (recc p) (recc q)
                                                Or p q -> casoOr p q (recc p) (recc q)
                                                where recc = recProp casoVar casoNot casoAnd casoOr

foldProp :: (String -> b) -> (b -> b) -> (b -> b -> b) -> (b -> b -> b) -> Prop -> b
foldProp casoVar casoNot casoAnd casoOr = recProp casoVar (\p -> casoNot) (\p q -> casoAnd) (\p q -> casoOr)

valuacion :: (String -> Bool)
valuacion "x" = True
valuacion "y" = False

evaluarProp :: (String -> Bool) -> Prop -> Bool
evaluarProp v = foldProp v not (&&) (||)

printProp :: Prop -> String
printProp = foldProp id (\p -> " not " ++ p) (\p q -> p ++ " and " ++ q) (\p q -> p ++ " or " ++ q)


negProp :: Prop -> Prop
negProp = recProp 
                    (\x -> Not (Var x)) 
                    (\pOrig pRec -> case pOrig of 
                        Var x -> Not (Var x)
                        otherwise -> pRec)
                    (\pOrig qOrig pRec qRec -> Or pRec qRec)
                    (\pOrig qOrig pRec qRec -> And pRec qRec)

