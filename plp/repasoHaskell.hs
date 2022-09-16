-- sumaL :: Num a => [a] -> a
-- sumaL [] = 0
-- sumaL (x:xs) = x + sumaL xs

-- foldrL :: b -> (a -> b -> b) -> [a] -> b
-- foldrL z _ [] = z
-- foldrL z f (x:xs) = f x (foldrL z f xs)

-- sumaFold :: Num a => [a] -> a
-- sumaFold = foldrL 0 (+)

-- recrL :: b -> (a -> [a] -> b -> b) -> [a] -> b
-- recrL z _ [] = z
-- recrL z f (x:xs) = f x xs (recrL z f xs)

-- dropWhileL :: (a -> Bool) -> [a] -> [a]
-- dropWhileL p l = recrL [] (\x xs rec -> if p x then rec else xs) l




myMap :: (a -> b) -> [a] -> [b] 
myMap _ [] = []
myMap f (x:xs) = f x : myMap f xs 

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ [] = []
myFilter p (x:xs) = if p x then x : myFilter p xs else myFilter p xs


myFoldR :: (a -> b -> b) -> b -> [a] -> b
myFoldR _ z [] = z
myFoldR f z (x:xs) = f x (myFoldR f z xs) 

myRecR :: (a -> b -> [a] -> b) -> b -> [a] -> b
myRecR f z = myFoldR (\e (recRes, recLista) -> f e ()) (z, [])

foldSum :: Num a => [a] -> a
foldSum = myFoldR (+) 0

foldElem :: Eq a => a -> [a] -> Bool
foldElem e arr = myFoldR (\x rec -> x == e || rec) False arr

foldConcat :: [a] -> [a] -> [a]
foldConcat l1 l2 = myFoldR (\e rec -> e : rec) l2 l1

foldFilter :: (a -> Bool) -> [a] -> [a]
foldFilter p = myFoldR (\e rec -> if p e then e : rec else rec) []

foldMap :: (a -> b) -> [a] -> [b]
foldMap f = myFoldR (\e rec -> f e : rec) []

data ArbolBinario a = Hoja a | Nodo (ArbolBinario a) a (ArbolBinario a)

foldArbolBinario :: (a -> b) -> (b -> a -> b -> b) -> ArbolBinario a -> b
foldArbolBinario fHoja _ (Hoja hoja) = fHoja hoja 
foldArbolBinario fHoja fNodo (Nodo arbolI raiz arbolD) = fNodo (foldArbolBinario fHoja fNodo arbolI) raiz (foldArbolBinario fHoja fNodo arbolD) 

recArbolBinario :: (a -> b) -> (b -> a -> b -> ArbolBinario a -> ArbolBinario a -> b) -> ArbolBinario a -> b
recArbolBinario fHoja fNodo arbol = case arbol of
                                Hoja a -> fHoja a
                                Nodo left root right -> fNodo (recArbolBinario fHoja fNodo left) root (recArbolBinario fHoja fNodo right) left right


sumaArbolBinario :: Num a => ArbolBinario a -> a
sumaArbolBinario = foldArbolBinario id (\left root right -> left + root + right)

truncar10 :: ArbolBinario Int -> ArbolBinario Int
truncar10 arbol = foldArbolBinario (\e -> Hoja e) 
    (\arbolI root arbolD -> if ((sumaArbolBinario arbolI) + root + (sumaArbolBinario arbolD)) < 10 
                                then (Hoja ((sumaArbolBinario arbolI) + root + (sumaArbolBinario arbolD))) 
                                else (Nodo arbolI root arbolD)) arbol

printArbolBinario :: ArbolBinario Int -> [Int]
printArbolBinario arbol = foldArbolBinario (\e -> [-1,e]) (\i r d -> i ++ [-2,r] ++ d) arbol

data D a = C (D a) | N (D a) a

foldA :: (b -> b) -> (b -> a -> b) -> D a -> b
foldA fc fn d = case d of
                    C d -> fc (foldA fc fn d)
                    N d a -> fn (foldA fc fn d) a

recA :: (b -> D a -> b) -> (b -> D a -> a -> b) -> D a -> b
recA fc fn d = case d of 
                    C d -> fc (recA fc fn d) d
                    N d a -> fn (recA fc fn d) d a


-- foldConcat [1,2] [3,4] = 
-- myFoldR (\e rec -> e : rec) [3,4] [1,2] =
-- 1 : myFoldR (\e rec -> e : rec) [3,4] [2] =
-- 1 : 2 : myFoldR (\e rec -> e : rec) [3,4] [] =
-- 1 : 2 : [3,4] =



-- myFoldR (+) 0 [1,2,3] = 
-- (+) 1 (myFoldR (+) 0 [2,3]) = 
-- (+) 1 ((+) 2 (myFoldR (+) 0 [3])) = 
-- (+) 1 ((+) 2 ((+) 3 (myFoldR (+) 0 []))) = 
-- (+) 1 ((+) 2 ((+) 3 0)) = 
-- (+) 1 ((+) 2 3) = 
-- (+) 1 5 = 
-- 6
























