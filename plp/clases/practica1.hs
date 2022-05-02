triple_v1 = (*) 3

triple_v2 x = (*3) x

-- (<=) a b ~~> a < b
esMayorDeEdad_v1 = (<=) 18

esMayorDeEdad_v2 = (>=18)

esMayorDeEdad_v3 = (18<=)

-- g: M -> N, f: N -> R
-- componer toma 2 funciones f y g y devuelve (f o g) 
-- componer (N -> R) -> (M -> N) -> (M -> R)
componer :: (a -> b) -> (c -> a) -> (c -> b) 
componer f g = \x -> f (g x)

-- customFlip(f(x, y)) ~~> f(y, x)
customFlip :: (a -> b -> c) -> b -> a -> c
customFlip f = \x y -> f y x

foo b x = if b then x else (-x)

-- aplicar(f(x)) ~~> f(x)
aplicar :: (a -> b) -> a -> b
aplicar f = \x -> f x

-- fafa f = flip aplicar 0 f ~~> aplicar f 0 ~~> f 0

-- fefe x = (==0) . (flip mod 2) x ~~> (==0) . 

maximo :: Ord a => [a] -> a
maximo [x] = x
maximo (x:xs) = if x >= currentMax then x else currentMax  
                where currentMax = maximo xs

minimo :: Ord a => [a] -> a
minimo [x] = x
minimo (x:xs) = if x <= currentMin then x else currentMin  
                where currentMin = minimo xs

listaMasCorta :: [[a]] -> [a]
listaMasCorta [x] = x
listaMasCorta (x:xs) = if length x < length currentMin then x else currentMin
                        where currentMin = listaMasCorta xs


mejorSegun :: (a -> a -> Bool) -> [a] -> a
mejorSegun _ [x] = x
mejorSegun f (x:xs) = let n = mejorSegun f xs
                        in if f x n then x else n

minimo_v2 :: Ord a => [a] -> a
minimo_v2 x = mejorSegun (<) x

listaMasCorta_v2 :: [[a]] -> [a]
listaMasCorta_v2 x = mejorSegun (\y z -> length y < length z) x

infinitosUnos = 1 : infinitosUnos

nUnos n = take n infinitosUnos

-- nUnos 2 ~~> take 2 inf1 ~~> take 2 (1:inf1) ~~> 1 : take (2-1) inf 1 ~~> 1 : take 1 inf1 ~~> 1 : take 1 (1:inf1) ~~> 1 : 1 : take 0 inf1 ~~> 1 : 1 : [] 

deLongitudN :: Int -> [[a]] -> [[a]]
deLongitudN n x = filter (\y -> length y == n) x

soloPuntosFijosEnN :: Int -> [Int->Int] -> [Int->Int] 
soloPuntosFijosEnN n x = filter (\y -> y n == n) x 

-- shuffle([1, 3, 0], ['a', 'b', 'c', 'd']) ~~> ['b', 'd', 'a']
shuffle :: [Int] -> [a] -> [a]
shuffle indices lista = map (\x -> lista!!x) indices

-- reverseAnidado([["quedate", "en", "casa"]]) ~~> ["asac", "ne", "etadeuq"]
reverseAnidado :: [[Char]] -> [[Char]]
reverseAnidado x = reverse (map (\y -> reverse y) x)

-- paresCuadrados([1,2,3,4]) ~~> [4, 16]
paresCuadrados :: [Int] -> [Int]
paresCuadrados x = map (\y -> y*y ) (filter even x)

paresCuadrados_v2 :: [Int] -> [Int]
paresCuadrados_v2 = map (^2).(filter even)
