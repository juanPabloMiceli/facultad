import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM


prepararPizza tVarPizzas = do
    modifyTVar tVarPizzas(+1)

pedirPizza tVarPizzasGrandes tVarPizzasChicas = do
    case (readTVar tVarPizzasGrandes) of
        0 -> (do
            cantidadPizzasChicas <- readTVar tVarPizzasChicas;
            check cantidadPizzasChicas >= 2;
            modifyTVar cantidadPizzasChicas (-2);
        )
        cantidadPizzasGrandes -> (modifyTVar tVarPizzasGrandes (-1))

main = do
    pizzasGrandes <- atomically (newTVar 0);
    pizzasChicas <- atomically (newTVar 0);

    forkIO (atomically (prepararPizza pizzasGrandes));
    forkIO (atomically (prepararPizza pizzasChicas));
    forkIO (atomically (prepararPizza pizzasChicas));
    forkIO (atomically (pedirPizza pizzasGrandes pizzasChicas));
    forkIO (atomically (pedirPizza pizzasGrandes pizzasChicas));
