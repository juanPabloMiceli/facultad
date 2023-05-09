import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


-- Leo del buffer
get :: TVar (Maybe t) -> STM (Maybe t)
get buffer = do
    maybeValor <- readTVar buffer;
    case maybeValor of
        Nothing -> return Nothing;
        Just valor -> do 
            writeTVar buffer Nothing;
            return maybeValor;

-- Escribo en el buffer
put :: TVar (Maybe t) -> t -> STM Bool
put buffer valor = do 
    case buffer of
        Nothing -> do 
            writeTVar buffer valor;
            return True;
        Just valor_anterior -> return False;

-- newBuffer :: TVar (Maybe a)
newBuffer = do 
    b <- newTVar Nothing;
    return b;

main = do
    buffer <- atomically (newBuffer)
    atomically (put buffer 'a');
    maybeValor <- atomically (get buffer)
    case maybeValor of
        Nothing -> print "Nothing";
        Just valor -> putStrLn $ "Valor:" ++ (show valor);
