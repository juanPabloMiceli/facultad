import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


comer tenedorIzquierdo tenedorDerecho = do
    ti <- get tenedorIzquierdo;
    td <- get tenedorDerecho;

    check ti != Nothing;
    check td != Nothing;

    -- Comer
    
    put tenedorIzquierdo 1;
    put tenedorDerecho 1;

main = do
    -- Consideramos 3 filosofos
    tenedor1 <- atomically (newBuffer [1])
    tenedor2 <- atomically (newBuffer [1])
    tenedor3 <- atomically (newBuffer [1])

    forkIO (atomically (comer tenedor1 tenedor2));
    forkIO (atomically (comer tenedor2 tenedor3));
    forkIO (atomically (comer tenedor3 tenedor1));
    
    threadDelay 10000000 -- Esperamos a que terminen de comer


