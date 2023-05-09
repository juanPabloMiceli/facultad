public class MyThread implements Runnable {
    private int threadNumber;

    public MyThread(int threadNumber) {
        this.threadNumber = threadNumber;
    }

    public void run() {
        System.out.println("Thread " + threadNumber + " started");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Thread " + threadNumber + " finished");
    }

    public static void main(String[] args) {
        Thread t1 = new Thread(new MyThread(1));
        Thread t2 = new Thread(new MyThread(2));
        Thread t3 = new Thread(new MyThread(3));
        t1.start();
        t2.start();
        t3.start();
    }
}

class Figura{
    int x = 0;
    int y = 0;
    int alto = 0;
    int ancho = 0;
    Lock lockPosision;
    Lock lockTamano;

    public void ajustarPosicion(int newX, int newY){
        lockPosision.lock();
        this.x = newX;
        this.y = newY;
        lockPosision.release();
    }
    public void ajustarTamano(int newAlto, int newAncho){
        lockTamano.lock();
        this.alto = newAlto;
        this.ancho = newAncho;
        lockTamano.release();
    }
}

public class Recursos {
    Object[] recursos;
    int capacidad;
    Lock[] lock;

    public Recursos(int n){
        capacidad = n;
        recursos = new Object[capacidad];
    }
    public void assign(int pos, Object o){
        if (pos < capacidad)
            lock[pos].lock();
        recursos[pos] = o;
        Thread.sleep(5000);
        lock[pos].release();
    }
    public void swap(int i,int j){
        int menor = min(i, j);
        int mayor = max(i, j);
        i = menor;
        j = mayor;
        if (i < capacidad && j < capacidad){
            lock[i].lock();
            lock[j].lock();
            Object aux = recursos[i];
            recursos[i] = recursos[j];
            recursos[j] = aux;
        }
        lock[i].release();
        lock[j].release();
    }
}

// Como conseguir inanicion? Asumimos que el lock funciona como una cola.
// Tenemos 3 threads que quieren actualizar la misma entrada.
// Primero entra el thread juampi y se pone a hacer el CC.
// Despues entra el thread Vicky, agarra el lock y pierde en la validacion.
// Antes de hacer el continue, le sacan el scheduler a Vicky.
// Juampi termina de ejecutar y pide el lock (todavia lo tiene Vicky). Cola del lock: Juampi
// Llegar el thread Carlitos, pide el lock. Cola del lock: Juampi, Carlos
// Vicky vuelve a ejecutar, releasea el lock y lo vuelve a pedir arriba de todo. Cola del lock: Juampi, Carlos, Vicky
// Juampi adquiere el lock, termina de actualizar y se va para nunca volver. Cola del lock: Carlos, Vicky
// Carlos arranca CC, y vicky quedo igual que al comienzo. Se puede definir como: "Vicky se va a cagar de hambre"
public class Tabla {
    HashMap<Integer,Object> tabla = new HashMap<Integer,Object>();
    private final Lock lock = new ReentrantLock();
    private HashSet<Integer> computandoActualmente = new HashSet<Object>();

    private void actualizarEntrada (int i){
        while(true){
            lock.lock();
            try{
                if(computandoActualmente.contains(i){
                    // Perdi la validacion
                    continue; 
                }
                // Gane la validacion
                computandoActualmente.insert(i);
                lock.release();
                Object v2 = ComputacionalmenteCostoso(v1);
                lock.lock();
                tabla.remove(i);
                tabla.put(i,v2);
                computandoActualmente.remove(i);
                return;
            }
            finally{
                lock.release();
            }
        }
    }
}


// Encolamos 1 y 2. => in: 1|2; out: ||
// t1 quiere desencolar (expected out: 1)
// t1 paso "2" a out, y le sacan el scheduler. in: |1|; out: |2|
// LLego t2, encola 3 y se va para nunca volver. in: |1|3|; out: |2|
// t1 sigue el while y queda todo inconsistente. in: ||; out: |1|3|2|
// t1 devuelve 1 (hasta ahi todo bien), pero queda 3 primero (ta feo).
class Stack {
    synchronized boolean isEmpty() { ... }
    synchronized Object pop() { ... }
    synchronized void push(Object o) { ... }
}

class Queue {
    Stack in = new Stack();
    Stack out = new Stack();
    Lock lock = new ReentrantLock();

    void enq(Object o){ 
        lock.lock();
        int gentePusheando++;
        lock.release();
        in.push(o); 
    }
    Object deq() {
        if(out.isEmpty()) {
            lock.lock();
            while(!in.isEmpty()) {
                out.push(in.pop());
            }
            lock.release();
        }
        return out.pop();
    }
}


Class OriginalBoundedQueue {
    final int capacity;
    private atomic unsigned int size;
    Lock enqueueLock;
    Lock dequeueLock;

    void enqueue() {
        if(size >= capacity){ // Muito lento
            return;
        }
        enqueueLock.lock();
        //
        size++; // Muito lento
                //
        enqueueLock.lock();
    }

    void dequeue() {
        if(size == 0){ // Muito lento
            return;
        }
        dequeueLock.lock();
        //
        size--; // Muito lento
                //
        dequeueLock.lock();

    }

    int getSize(){
        return size;
    }
}


Class ModifiedBoundedQueue {
    final int capacity;
    private atomic unsigned int size;
    Lock enqueueLock;
    Lock dequeueLock;
    int contadorEnqueue = 0;
    int contadorDequeue = 0;

    void enqueue() {
        if(getSize() >= capacity){ // Muito lento
            return;
        }
        enqueueLock.lock();
        //
        contadorEnqueue++;
        //
        enqueueLock.release();
    }

    void dequeue() {
        if(getSize() == 0){ // Muito lento
            return;
        }
        dequeueLock.lock();
        //
        contadorDequeue++;
        //
        dequeueLock.release();

    }

    int getSize(){
        enqueueLock.lock();
        dequeueLock.lock();
        int delta = contadorEnqueue - contadorDequeue;
        size += delta
            contadorEnqueue = 0;
        contadorDequeue = 0;
        enqueueLock.release();
        dequeueLock.release();
        return size;
    }
}


Class BoundedStack {

    final int capacity;
    int size = 0;
    Node head = Node(INT_MIN);

    void push(Object o){
        head.lock();
        try{
            if(capacity >= size) {
                throw new FullException();
            }
            Node next = head.next();
            Node newNode = new Node(o);
            head.next() = newNode;
            newNode.next() = next;
            size++;
        } finally {
            head.release();
        }
    }

    // Alcanza con solo lockear head porque es exactamente lo mismo que un monitor (para arrancar si o si tenes que
    // tener acceso a head)
    Object pop(){
        head.lock();
        try {
            if(head.next() == null){
                throw new EmptyException();
            }
            Node current = head.next();
            Object res = current.item;
            head.next() = current.next();
            size--;
        } finally {
            head.release();
        }
        return res;
    }
}


class Contador {

    AtomicInteger contador = new AtomicInteger(0);

    void inc(){
        contador.addAndGet(1);
    }

    int get(){
        return contador.get();
    }

    void reset(){
        contador.getAndSet(0);
    }

}

class Figura{
    int y = 0;
    int x = 0;
    int alto = 0;
    int ancho = 0;
    AtomicBoolean actualizandoPosicion = new AtomicBoolean(false);
    AtomicBoolean actualizandoTamano = new AtomicBoolean(false);

    public void ajustarPosicion(int newX, int newY){
        while(!actualizandoPosicion.compareandset(false, true)){}
        x = newX;
        y = newY;
        assert actualizandoPosicion.compareandset(true, false);
    }
    
    public void ajustarTamano(int newAlto, int newAncho){
        while(!actualizandoTamano.compareandset(false, true)){}
        alto = newAlto;
        ancho = newAncho;
        assert actualizandoTamano.compareandset(true, false);
    }
}

Class ABAStack {

    private AtomicReference top = new AtomicReference(null);

    boolean tryPush(Node node) {
        Node oldTop = top.get();
        node.next = oldTop;
        return top.compareAndSet(oldTop, node);
    }

    void push(Object o){
        Node node = Memory.new(o);
        while(true) {
            if(tryPush(node)) {
                return;
            } else {
                continue;
            }
        }
    }

    Node tryPop() {
        Node oldTop = top.get();
        Node newTop = oldTop.next;
        if(top.compareAndSet(oldTop, newTop)){
            return oldTop;
        }
        return null;
    }

    Object pop() {
        while(true){
            Node result = tryPop();
            if(result != null){
                return result.item;
            }
        }
    }

}

Class ABAFreeStack {

    private AtomicStampedReference head = new AtomicStampedReference(null, 0);
    int[] stamp = new int[0];

    boolean tryPush(Node node) {
        Node oldHead = head.get(stamp);
        node.next = oldHead;
        return head.compareAndSet(oldHead, node, stamp[0], stamp[0] + 1);
    }

    void push(Object o){
        Node node = Memory.new(o);
        while(true) {
            if(tryPush(node)) {
                return;
            } else {
                continue;
            }
        }
    }

    Node tryPop() {
        Node oldHead = head.get(stamp);
        Node newHead = oldHead.next;
        if(head.compareAndSet(oldHead, newHead, stamp[0], stamp[0]+1)){
            return oldHead;
        }
        return null;
    }

    Object pop() {
        while(true){
            Node result = tryPop();
            if(result != null){
                Object res = result.item;
                Memory.free(result);
                return res;
            }
        }
    }

}
