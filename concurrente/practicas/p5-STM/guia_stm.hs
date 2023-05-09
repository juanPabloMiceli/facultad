import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM

-- limitedWithdraw acc n = do
--     bal <- readTVar acc;
--     check (n <= bal);
--     writeTVar acc (bal - n)


-- delayDeposit acc amount = do
--     threadDelay 6000000
--     putStrLn "Depositando!"
--     hFlush stdout
--     atomically (do 
--         bal <- readTVar acc
--         writeTVar acc (bal + amount))

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
    writeTVar buffer (Just valor);
    return (True);

-- newBuffer :: TVar (Maybe a)
newBuffer = do 
    b <- newTVar Nothing;
    return b;

main = do
    buffer <- atomically (newBuffer)
    valor <- atomically (get buffer)
    case valor of
        Nothing -> print "Nothing";
        Just valor -> print "Tuki";

-- main = do

--      r <- atomically (newTVar 0)
--      forkIO (atomically (incT2 r))
--      atomically (incT2 r)
--      threadDelay 1000000 -- delay for 1 second
--      v <- atomically (readTVar r)
--      print v
  -- -- Create a new TVar with an initial value of 0
  -- tvar <- newTVarIO 0

  -- -- Perform some STM transactions
  -- atomically $ do
  --   -- Read the value of the TVar
  --   value <- readTVar tvar
  --   -- Write a new value to the TVar
  --   writeTVar tvar (value + 1)

  -- -- Read the final value of the TVar
  -- finalValue <- readTVarIO tvar

  -- -- Print the final value
  -- putStrLn $ "Final value: " ++ show finalValue
--     r <- atomically (newTVar 0)
--     forkIO (atomically (incT r))
--     atomically (incT r);
--     val <- atomically (readTVar r)
--     print val
