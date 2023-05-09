import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


newtype Cola a = Tvar [a]

generarBolita cantidadBolitas cantidadGeneradores = do
    check (readTVar cantidadBolitas) < (readTVar cantidadGeneradores);
    modifyTVar cantidadBolitas (+1)

tomarBolitas cantidadBolitas = do
    check (readTVar cantidadBolitas) >= 2;
    modifyTVar cantidadBolitas (-2)

registrarGenerador cantidadGeneradores = do
    modifyTVar cantidadGeneradores (+1)

main = do
    cantidadBolitas <- (newTVar 0);
    cantidadGeneradores <- (newTVar 0);
    atomically (registrarGenerador cantidadGeneradores);
    atomically (generarBolita cantidadBolitas);
    atomically (tomarBolitas cantidadBolitas);
