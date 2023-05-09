import System.IO
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.STM

producir productosTVar buffer = do
    productos <- readTVar productosTVar;
    (p1:p2:_) <- productos;
    put buffer p1;
    put buffer p2;

consumir miProducto bufferProductosEnLaMesa = do
    listaProductos <- peek2 bufferProductosEnLaMesa;
    (p1:p2:[]) <- listaProductos;
    producto <- readTVar miProducto;
    check producto != p1;
    check producto != p2;
    consumir2 bufferProductosEnLaMesa;
    return;


consumirFosforo buffer = do
    while(true):
        consumir "fosforo" buffer;
    
    
consumirTabaco buffer = do
    while(true):
        consumir "tabaco" buffer;

consumirPapel buffer = do
    while(true):
        consumir "papel" buffer;


main = do
    buffer <- atomically (newTVar []);
    productos <- atomically (newTVar ["fosforo", "papel", "tabaco"]);
    forkIO ( atomically consumirFosforo);
    forkIO ( atomically consumirTabaco);
    forkIO ( atomically consumirPapel);

    while(true):
        atomically (do
            producir productos buffer;
        )
