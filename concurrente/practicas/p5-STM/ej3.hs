import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


newtype Cola a = Tvar [a]


tomar colaTvar = do
    cola <- readTVar colaTvar
    case cola of
        (x:xs) -> (do writeTVar colaTvar xs; return x)
        [] -> retry;

liberar colaTVar elemento = do
    cola <- readTVar colaTVar
    writeTVar colaTVar (cola ++ [elemento])


main = do
    myCola <- atomically (newTVar ['a', 'b', 'c'])
    atomically (do recurso1 <- tomar myCola; recurso2 <- tomar myCola; liberar myCola recurso2)

