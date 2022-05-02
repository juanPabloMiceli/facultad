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