import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


signal sem = do
    val <- readTVar sem
    writeTVar sem (val+1)

wait sem = do
    val <- readTVar sem
    check (val > 0)
    writeTVar sem (val-1)

permisos sem = do
    return readTVar sem;

main = do
    sem <- atomically (newTVar 5)
    atomically ( do wait sem; wait sem;)
    
