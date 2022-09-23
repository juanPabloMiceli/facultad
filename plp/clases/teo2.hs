-- Esquema de recursion estructural
-- g :: [a] -> b
-- g [] = z
-- g (x:xs) = f x (g xs) 

-- foldr sirve para aplicar un esquema de recursion estructural de forma cortita
-- foldr :: (a -> b -> b) -> b -> [a] -> b
-- foldr _ z [] = z
-- foldr f z (x:xs) = f x (foldr f z xs)

sumaLista :: Num a => [a] -> a
sumaLista x = foldr (+) 0 x

concatenar :: [[a]] -> [a]
concatenar x = foldr (++) [] x

reverso :: [a] -> [a]
reverso x = foldr (\y z -> z ++ [y]) [] x

customMap f x = foldr (\y z -> f y : z) [] x

customFilter f x = foldr (\y z -> if f y then y : z else z) [] x

-- Recursion primitiva
-- g :: [a] -> b
-- g [] = z
-- g (x:xs) = f x xs (g xs) 

-- Arboles binarios
data Arbol a = Hoja a | Nodo a (Arbol a) (Arbol a)

mapArbol :: (a -> b) -> Arbol a -> Arbol b
mapArbol f (Hoja x) = Hoja (f x)
mapArbol f (Nodo r i d) = Nodo (f r) (mapArbol f i) (mapArbol f d)

sumaArbol :: Num a => Arbol a -> a
sumaArbol (Hoja x) = x
sumaArbol (Nodo r i d) = r + (sumaArbol i) + (sumaArbol d)

lengthArbol :: Arbol a -> Int
lengthArbol (Hoja x) = 1
lengthArbol (Nodo r i d) = 1 + lengthArbol i + lengthArbol d

-- foldArbol :: (a -> b) -> (a -> b -> b -> b) -> Arbol a -> b
-- foldArbol f g (Hoja x) = f x
-- foldArbol f g (Nodo x i d) = g x (foldArbol f g i) (foldArbol f g d)

-- maxArbol :: Arbol Int -> Int
-- maxArbol arbol = foldArbol ((\x -> x) (\y maxI maxD -> maximum [y maxI maxD]) arbol)
