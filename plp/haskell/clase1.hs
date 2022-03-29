doble :: Int -> Int
doble x = x + x

signo :: Int -> Bool
signo n | n >= 0    = True
        | otherwise = False

sumaMas2 x y = mas2 x + y
                where mas2 z = 2 + z