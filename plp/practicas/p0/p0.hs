-- Ej 2

valorAbsoluto :: Float -> Float
valorAbsoluto x | x < 0 = (-x)
                | otherwise = x

bisiesto :: Int -> Bool
bisiesto anio   | mod anio 400 == 0 = True
                | mod anio 100 == 0 = False
                | mod anio 4 == 0 = True
                | otherwise = False

factorial :: Int -> Int
factorial 0 = 1
factorial x = factorial (x-1) * x

esPrimo :: Int -> Bool
esPrimo 1 = False
esPrimo x = esPrimoAux x (x-1)

esPrimoAux :: Int -> Int -> Bool
esPrimoAux x y  | y == 1 = True
                | mod x y == 0 = False
                | otherwise = esPrimoAux x (y-1)

cantDivisoresPrimos :: Int -> Int
cantDivisoresPrimos x = length (filter esPrimo [1..x])

-- Ej 3

inverso :: Float -> Maybe Float
inverso x   | x == 0 = Nothing
            | otherwise = Just (1 / x)

aEntero :: Either Bool Int -> Int
aEntero (Left True) = 1
aEntero (Left False) = 0
aEntero (Right x) = x

-- Ej 4

limpiar :: String -> String -> String
limpiar [] y = y
limpiar (x:xs) y    | contiene x y = limpiar xs (borrarTodas x y)
                    | otherwise = limpiar xs y


contiene :: Char -> String -> Bool
contiene letra [] = False
contiene letra (x:xs)   | letra == x = True
                        | otherwise = contiene letra xs

borrarTodas :: Char -> String -> String
borrarTodas letra palabra = filter (\x -> x /= letra) palabra

difPromedio :: [Float] -> [Float]
difPromedio x = map (\elem -> elem - p) x
                where p = promedio x

promedio :: [Float] -> Float
promedio x = (suma x) / fromInteger ((toInteger (length x))) 

suma :: [Float] -> Float
suma [] = 0
suma (x:xs) = x + suma xs 

todosIguales :: [Int] -> Bool
todosIguales [] = True
todosIguales [x] = True
todosIguales (x:xs) | x /= (head xs) = False
                    | otherwise = todosIguales xs

-- Ej 5
data Ab a = Nil | Bin a (Ab a) (Ab a)

vacioAB :: Ab a -> Bool
vacioAB Nil = True
vacioAB _ = False

negacionAB :: Ab Bool -> Ab Bool
negacionAB Nil = Nil
negacionAB (Bin r izq der) = (Bin (not r) (negacionAB izq) (negacionAB der))

toArr :: Ab a -> [a]
toArr Nil = []
toArr (Bin r izq der) = (toArr izq) ++ [r] ++ (toArr der)

productoAB :: Num a => Ab a -> a
productoAB Nil = 1
productoAB (Bin r izq der) = r * (productoAB izq) * (productoAB der)

testAb = (Bin 4 (Bin 2 (Bin 1 Nil Nil) (Bin 3 Nil Nil)) (Bin 6 (Bin 5 Nil Nil) (Bin 7 Nil Nil)))

testAbBool = (Bin True (Bin True (Bin False Nil Nil) (Bin False Nil Nil)) (Bin True (Bin False Nil Nil) (Bin False Nil Nil)))

