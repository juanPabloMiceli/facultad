import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


newtype Pila a = Tvar [a]

push pilaTVar elemento = do
    pila <- readTVar pilaTVar;
    writeTVar pilaTVar (elemento : pila)

pop pilaTVar = do
    pila <- readTVar pilaTVar;
    case pila of
        [] -> retry;
        (x:xs) -> (do 
            writeTVar pilaTVar xs;
            return x;
        )

main = do
    pila <- atomically (newTVar []);
    atomically ( do
        push pila 'a';
        push pila 'b';
        pop pila;
    )
