# Clase 1

## Qué es un algoritmo?
Secuencia finita de pasos que termina en un tiempo finito.
Deben estar formulados en terminos de pasos sencillos que sean:
Precisos, bien definidos y finitos.

## Análisis de algoritmos
En algo3 la medida de eficiencia de un algoritmo será su tiempo de ejecución.

### Análisis empírico:
Hay que implementar el algoritmo y luego ejecutarlo sobre un conjunto de instancias representativas y comparar los tiempos de ejecución.

Desventajas:

* Perdida de tiempo y esfuerzo del programador
* Perdida de tiempo de computo
* Conjunto de instancias acotadas

### Análisis teórico:
Se determina matemáticamente la cantidad de tiempo que llevará un algoritmo en función del tamaño de la entrada. Esto nos aisla de las diferentes implementaciones, el lenguaje donde está escrito, o la maquina donde corre el algoritmo.

Para esto necesitamos:

* Un modelo de cómputo
* Un lenguaje sobre este modelo
* Tamaño de la instancia
* Instancias relevantes 

### Modelo de cómputo: Máquina RAM 
La máquina contiene las siguientes partes:

* Unidad de entrada: Cinta con los datos de entrada, se leen secuencialmente, no se puede leer algo ya leido.
* Unidad de salida: Cinta donde se escriben los datos de salida. No se pueden reescribir datos
* Memoria: Memoria de acceso rápido, podemos escribir y leer donde querramos las veces que querramos.
* Registro acumulador: Registro donde se realizan los calculos aritméticos.
* Programa: Cinta finita de instrucciones, se comienza desde la primera instrucción y se sigue el flujo de control del mismo.

## Complejidad computacional

* Definición informal: Función que representa tiempo de ejecución en función del tamaño de la entrada del algoritmo

* Definición "formal": Una operación es **elemental** si su tiempo de ejecución puede ser acotado por una constante que:

    * Depende solo de la implementación particular utilizada.
    * No depende de la medida de los parámetros de la instancia considerada.

Nos interesa saber como crece el tiempo de ejecución en función de la entrada. No queremos un tiempo exacto.

### Operaciones básicas en la práctica:
Existen 2 modelos para calcular el costo de estas operaciones:

* Modelo uniforme: Cada operación básica tiene un tiempo constante.
    * Es un método sencillo, pero puede ser erroneo para instancias con valores arbitrariamente grandes.

    * Sirve cuando los operandos entran en una palabra.

* Modelo logarítmico: El tiempo de ejecución de cada operación depende de la cantidad de bits de los operandos.
    * Sirve cuando los operandos pueden crecer arbitrariamente.


# Clase 2

## Fuerza bruta

Analizamos todas las posibilidades. Son re fáciles de inventar e implementar porque básicamente hay que encontrar una forma de generar todas las instancias.

Si existe solución la vamos a encontrar, asi que funciona siempre. Son meeeeega ineficientes.

## Golosos

Construimos una solución eligiendo en cada paso la mejor alternativa posible localmente. Es decir, no tengo visión a futuro, hago lo que más me convenga en el momento. Nunca volvemos para atras a revisar elecciones hechas ni a evaluar otras alternativas. 

Son faciles de implementar y suelen ser eficientes. La desventaja de estos algoritmos es que no siempre dan la mejor solución. Lo mas importante de un algoritmo goloso es la funcion de seleccion.

## Recursivos

La correctitud de la POST de estos algoritmos se demuestra por induccion. Necesitamos que el mismo termine, y que cumpla la POST.

La complejidad se calcula mediante la funcion de recurrencia, si la misma es facil la podes pasar a una sumatoria.

## Divide and Conquer

Si la instancia es lo suficientemente chica, uso en algoritmo trivial para resolverla. Si no, divido la instancia de entrada en K instancias mas pequeñas en pos de llegar a esa solucion trivial. Por ultimo, combino las soluciones pequeñas obtenidas para llegar a una solución de la instancia original.

Para que un algoritmo de divide and conquer sea eficiente, el K debe ser chico e independiente de la instancia particular. Ademas, no debemos resolver el mismo subproblema varias veces y la medida de los subproblemas debe ser similar. 

La complejidad de estos algoritmos sigue la misma logica que en los algoritmos recursivos. En este caso tenemos el teorema maestro.

## Backtracking

Recorremos de forma ordenada todas las posibles soluciones. A priori es como fuerza bruta, pero esta tecnica aprovecha informacion del problema para evitar recorrer todas las soluciones. Aseguramos encontrar la mejor solucion siempre y cuando no pode soluciones que me interesan.

Creamos un arbol de soluciones parciales donde la raiz es la solucion vacia, los hojas las soluciones completas posibles y una nodo x es padre de un nodo y, si puedo extender la solucion x a la solucion y en un paso. 

Podas sobre ese arbol:

* Factibilidad: Ninguna extension de la solucion parcial deriva en una solucion valida del problema.
* Optimalidad: Ninguna extension de la solucion parcial deriva en una solucion del problema optima.

Backtracking tiene exito sii las podas son buenas, si no es tan mala como fuerza bruta.

## Programación dinámica

Es muy parecida a divide and conquer, ya que divide el problema en subproblemas de menor tamaño mas simples de resolver. Una vez resueltos los subproblemas combina todo y devuelve la solución al problema original. Es muy adecuada cuando divide and conquer tiene que resolver muchas veces los mismos subproblemas. Almacena resultados intermedios para evitar calculos innecesarios.

La complejidad de estos algoritmos es la cantidad de subproblemas posibles por el costo de resolver cada suproblema.

# Clase 3

Los grafos modelan relaciones entre vertices.

Un grafo G = (V,X) es un par de conjuntos donde V es un conjunto de vertices y X un subconjunto del conjunto de pares no ordenados de elementos distintos de V.

Los elementos de X son las aristas.

Tenemos multigrafos que son grafos donde pueden haber varias aristas entre un par de nodos.

Un pseudografo es un grafo en el que puede haber varias aristas entre un par de vertices y ademas puede haber una arista en un vertice consigo mismo.

Grado de un vertice: Cuantas aristan inciden sobre un vertice.

$\Delta (G):$ Grado maximo del grafo

$\delta (G):$ Grado minimo del grafo

* Complemento de G: Una arista esta en G complemento sii no esta en G.

* Recorrido en G: Secuencia de vertices.

* Camino en G: Recorrido que no repite vertices.

* Seccion de un camino en G: Subseccion de vertices perteneciente al camino

* Circuito en G: Recorrido que empieza y termina en el mismo vertice.

* Ciclo en G: Circuito que no repite vertices.

* Longitud de un camino: Cantidad de aristas en un camino.

* Distancia entre 2 vertices: Longitud del camino minimo.

* Distancia de un vertice a si mismo = 0

* Distancia entre 2 vertices no conectados = $\infty$.

Subgrafos:

* Subgrafo: Un subgrafo de G es un grafo H tal que los nodos de H estan contenidos en los de G, idem aristas con la salvedad de que no pueden haber aristas sin nodos.

* Subgrafo propio: Idem anterior pero G $\neq$ H.

* Subgrafo generador: H tiene todos los nodos de G.

* Subgrafo inducido: Para todo par de vertices u,v en H, los mismos estan conectados si esa conexion existe en G.

Conexo: Un grafo es conexo si hay camino entre todo par de vertices.

Componente conexa: Subgrafo conexo de G.

Grafos bipartitos: Podemos separar el grafo en 2 subconjuntos tal que no existe ninguna arista que conecte 2 nodos dentro del mismo subgrafo.

Un grafo es bipartito si todas sus componentes conexas son bipartitas.

Un grafo es bipartito si no tiene ningun ciclo de longitud impar.

Isomorfismo: Dados 2 grafos G y H, estos son isomorfos si existe una funcion: $V\rightarrow V$. tal que u, v estan conectados en G $\Longleftrightarrow$ f(u) y f(v) estan conectados en H. 

Digrafo: Es un grafo orientado, o sea que puede ser que v sea adyacente a w sin que w sea adyacente a v.

Ahora el grado de un vertice se separa en grado de entrada y grado de salida.

Un grafo subyacente de un digrafo G es borrar las orientaciones del digrafo G.

Un digrafo es fuertemente conexo si para todo par de vertices u, v existe un camino orientado de u a v.

# Clase 4

* Arbol: Grafo conexo sin circuitos

* Puente: Arista que si la saco aumento el numero de componentes conexas.

Definiciones equivalentes de arbol:

1. Grafo G sin circuitos simples tal que si agregamos una arista, G tiene exactamente un circuito simple.

2. Existe exactamente un camino simple entre todo par de vertices.

3. Toda arista de G es puente.


Lemas:

La union de 2 caminos simples distintos entre 2 vertices contiene un circuito simple.

Lema 2: Sea G un grafo conexo y e una arista de G. 

G$\setminus${e} es conexo $\Longleftrightarrow$ e pertenece a un circuito simple de G.

Definicion 3:

Una hoja es un vertice de grado 1.

Lema 3: Todo arbol de mas de 1 vertice tiene al menos 2 hojas.

Lema 4: En un arbol, m = n-1.

Definicion 4: Un bosque es un grafo sin circuitos simples. Osea, un conjunto de arboles.

Corolario 1: Sea G un bosque, con C componentes conexas. Entonces m = n-C.

Corolario 2: Sea G = (V,X) con C componentes conexas. Entonces m >= n-C. 


Mas definiciones equivalentes de arbol:

1. G no tiene ciruitos simples y $m = n - 1$.

2. G es conexo y $m = n - 1$.


Arboles enraizados:

Definiciones:

* Estos son arboles que tienen un vertice distinguido al que llamamos raiz. Queda definido un arbol dirigido considerando caminos orientados desde la raiz al resto de los vertices.

* Vertice interno = No soy raiz ni hoja.

* Nivel de un vertice v = dist(v, raiz)

* Altura de h = max(dist(v, raiz)) for v in V.

* Un arbol m-ario de altura h tiene a lo sumo $m^h$ hojas.


Arboles generadores:

Definicion: 

Un arbol generador de un grafo G es un subgrafo generador de G que es arbol. Osea, tiene la minima cantidad de aristas para conectar los nodos de G.

Teorema:

Todo grafo conexo tiene al menos un arbol generador. Si el grafo es un arbol entonces existe un unico AG y es el mismo grafo.

Para encontrar estos arboles generadores podemos usar 2 algoritmos. BFS y DFS, el primero recorre el grafo a lo ancho y el segundo lo hace en profundidad.
 
La complejidad de estos algoritmos es O(m).

Arbol generador minimo:

Esto surge cuando los aristas tienen peso. Y ahora queremos que la suma de las aristas del arbol generador sea la minima posible. Para eso no nos sirven bfs/dfs porque no distinguen pesos.

Para eso tenemos 2 algoritmos:

Prim:
Este construye 2 conjuntos, uno de vertices que empieza inicializado con un vertice cualquiera y otro de aristas que empieza vacio. En cada iteracion se agrega un elemento a cada uno de estos conjuntos. Cuando el conjunto de vertices ya tiene a todos los vertices del grafo original el algoritmo termina y el conjunto de aristas definen un AGM de G.

Para elegir el proximo nodo y la proxima arista se busca la arista de menor costo entre las que tienen un extremo en Vt y otro en V\Vt.

Kruskal:
Ordena las aristas de menor a mayor, y despues va eligiendo la arista de menor peso que no forme un ciclo con las ya elegidas. Se hace esto N-1 veces y listo. Empezas con un bosque de N componentes conexas y cada vez vas uniendo 2 componentes conexas hasta que te queda una sola.


La complejidad de estos algoritmos es O(min{n^2, mlog(n)})

# Clase 5

Definicion:

Un camino minimo entre v y u es un camino entre v y u tal que este sea el de minima longitud entre todos los caminos posible P(v,u).

Tres variantes de caminos minimos:

* Unico origen - unico destino:

Se quiere saber el camino minimo entre 2 vertices especificos.

No hay un algoritmo especificamente para esto. Cuando se quiere algo asi se usan algoritmos de unico origen a multiples destinos.

* Unico origen - multiples destinos:

Se quiere determinar un camino minimo de un vertice especifico al resto de los vertices de G.

* Multiples origenes - multiples destinos:

Se quiere saber un camino minimo entre todo par de vertices de G.

Proposicion copada:

Todo subcamino de un camino minimo es camino minimo.

Unico origen - Multiples destinos:

Si el digrafo es no pesado usamos BFS y punto, ya que BFS nos va a dar la distancia minima hacia el vertice elegido para todos los otros vertices. Esta complejidad queda en O(m).

Si el digrafo es pesado tenemos varias opciones:

La primera es el algoritmo de Dijkstra. Algo mucho muy importante es que este algoritmo sirve si y solo si las aristas son todas POSITIVAS.

Este algoritmo construye un arbol de caminos minimos, o sea, un arbol enraizado en v conteniendo un camino minimo desde v hacia todo otro vertice de V. Empezamos solamente con v y en cada iteracion agregamos el vertice mas cercano a v de entre todos los que todavia no estan en el arbol.

La complejidad de dijkstra O(min{n^2, mlog(n)}).

Otra opcion es BellMan-Ford:

Esta opcion sirve cuando tambien hay aristas negativas. Pero pero pero no pueden haber ciclos de longitud negativa, ya que ahi el problema esta mal definido.

Al terminar la k-esima iteracion, el algoritmo encuentra todos los caminos mınimos desde v con, a lo sumo, k arcos. Por como funciona deberia terminar en N-1 iteraciones. Igualmente, si en alguna iteracion no se nota ninguna mejora el algoritmo tambien se puede dar por terminado. Este algoritmo es copado para encontrar ciclos de longitud negativa, ya que si el algoritmo no termina en N iteraciones quiere decir que hay un ciclo negativo. El costo de este algoritmo es O(nm). Osea, si podes usar dijkstra usa dijkstra.

Multiples origenes - Multiples destinos:

Para estos algoritmos definimos la matriz de distancias. La misma tiene en la posicion ij la longitud del camino minimo desde i hasta j. En caso que no haya camino posible se coloca inf.

Algoritmo de Floyd:

Es una idea parecida a la def BellMan-Ford. Iniciamos la matriz seteando todo a infinito, y para toda arista v->w seteamos la posicion correspondiente en la matriz al largo de dicha arista.

Al finalizar la iteracion k del algoritmo de Floyd, d\[i\]\[j\] es la longitud de los caminos mınimos desde vi a vj cuyos vertices intermedios son elementos de {v1, . . . , vk}.

La complejidad temporal del algoritmo es O(n^3).

# Clase 6

Grafos eulerianos y hamiltonianos:

* Circuiro Euleriano: Circuito que pasa por todas las aristas exactamente una vez.

* Grafo Euleriano: Grafo que tiene un circuito euleriano


Definicion de grafo euleriano:

1. Todos los vertices de G tienen grado par.

2. Las aristas de G se pueden particionar en circuitos simples


* Camino Euleriano: Camino que pasa por todas las aristas exactamente una vez, pero no empieza y termina en el mismo vertice.

Definicion de camino euleriano:

1. G es conexo y tiene unicamente 2 vertices de grado impar.

* Propiedad:

Un digrafo conexo es euleriano sii todos los nodos tienen $d_{in} = d_{out}$

* Circuito Hamiltoniano: Circuito que pasa por todos los nodos exactamente una vez.

* Grafo Hamiltoniano: Grafo que tiene un circuito hamiltoniano


Condicion necesaria para circuitos Hamiltonianos:

* Sea G un grafo conexo. Si existe W $\subset$ V tal que G $\setminus$ W tiene c componentes conexas con c > |W| entonces G no es hamiltoniano. **LA RECIPROCA NO VALE**.

Condicion suficiente para circuitos Hamiltonianos:

* Sea G un grafo con n $\geq$ 3 y tal que para todo v $\in$ V se verifica que d(v) $\geq$ $\frac{n}{2}$ entonces G es hamiltoniano. **LA RECIPROCA NO VALE**.

* Sea G un grafo con n $\geq$ 3 y tal que para todo par v, w $\in$ (V,V) no adyacentes se verifica que $d_v + d_w \geq n$ entonces es hamiltoniano.

# Clase 7: Heuristicas y Metaheuristicas

Se usan en problemas de optimizacion. Buscamos la mejor solución, el problema es que el cardinal de soluciones posibles es finito pero excesivamente grande. No podemos permitirnos visitarlas todas.

Las soluciones que minimizan/maximizan el objetivo son llamadas "soluciones optimas" o "soluciones globales".

Podemos encontrar una solucion exacta mediante backtracking/PD/FB, pero a veces eso tardaria años o siglos. Por eso buscamos una solución que se aproxime a la solución optima, esto ahorrandonos mucho cómputo.

Las heuristicas clasicas por lo general construyen una solucion inicial con algun metodo constructivo. Teniendo esa solucion aplican alguna busqueda local para mejorar esta primer solucion.

Estas heuristicas pueden ser usadas en problemas de decision. Por ejemplo:

* Si tengo una heuristica para el problema de decidir si un grafo es hamiltoniano. La respuesta positiva asegura que el grafo es hamiltoniano. La respuesta negativa no da ninguna garantia de que el mismo no sea hamiltoniano, lo unico que indica es que el algoritmo no lo encontró.

Algunas heuristicas nos permiten encontrar una cota para la solución encontrada. Por ejemplo, podemos decir que la solución es a lo sumo 2 veces la óptima.

Decimos que A es un algoritmo $\epsilon$-aproximado, con $\epsilon > 0$ si para toda instancia se cumple que la diferencia entre la solucion optima y la solucion hallada es $\leq$ $\epsilon$ por la solución optima.

## Heuristicas constructivas

Las heuristicas constructivas son metodos que construyen una solucion factible de alguna manera. Se puede hacer de forma aleatoria pero el resultado esperado es bastante malo. 

Una buena manera de construir la solucion es mediante algoritmos golosos, ya que el costo computacional suele ser bajo, los algoritmos que hacen esto no son complicados y suelen tener una calidad aceptable.

## Algoritmos de busqueda local

Se usan para mejorar las soluciones obtenidas por las heuristicas constructivas. Estos algoritmos agarran esa solucion constructiva y generan un conjunto finito y por lo general pequeño de instancias que pertenecen a un conjunto definido como "Vecindad de una solucion". Luego verifican todas esas soluciones y se quedan con la mejor. Esto se itera hasta que la solucion no pueda ser mejorada.
Esta solucion obtenida es una solucion optima local, podria ademas ser una solucion optima global, pero no suele serlo. Lo que podemos esperar es que sea un buen optimo local.

En la practica se suele hacer un trade off entre el tamaño de la vecindad y la calidad de la solución obtenida. Ya que el tiempo de ejecución crece de la mano del tamaño de la vecindad. Tambien se puede elegir tomar un subconjunto de la vecindad de cardinal mucho menor al tamaño de la misma.

## Metaheuristicas

Guian la exploracion en el espacio de busqueda. El objetivo es ampliar el espacio de busqueda para no quedar estancado en un optimo local. Suelen ser algoritmos no deterministicos con el objetivo de poder visitar mas minimos locales.

Usan informacion del problema y aprendizaje adquirido para lograr mejores soluciones (memoria).

Permiten movernos a una solucion pese a que no sea mejor a la actual, la memoria a corto plazo se utiliza para intentar no volver hacia soluciones ya visitadas.

Existe el concepto de memoria a largo plazo, esta define un criterio, por ejemplo para penalizar a las soluciones que usan una componente en especifico, o que incentivan el visitar muchas areas del universo de soluciones.

La **eficiencia** de estos algoritmos se define en funcion de:

* La calidad de las soluciones encontradas.
* El tiempo de computo.

Casi siempre se debera elegir una de estas 2 a priorizar. Esto dependerá del contexto en donde se aplique este problema.

# Clase 8: Planaridad y coloreo

## Planaridad

Un grafo es planar si se puede dibujar en un papel de forma tal que no se crucen las aristas.


* Region de un grafo planar: el conjunto de todos los puntos alcanzables desde un punto sin atravesar vertices ni aristas.

* Frontera de una region: Circuito que rodea a la region. Puede tener aristas repetidas

* Grado de una region: Numero de aristas que tiene su frontera.

Existen algoritmos polinomiales para saber si un grafo es planar.

Propiedades:

* Todo subgrafo de un grafo planar es planar.

* Si un grafo contiene un subgrafo no planar entonces es no planar.

Teorema:

* Si G es un grafo conexo planar entonces cualquier representacion planar de G determina $r = m - n + 2$ regiones en el plano.

Corolario:

* Si G es conexo y planar con $n \geq 3$, entonces $m \leq 3n - 6$. 

* Si G es bipartito, conexo y planar con $n \geq 3$, entonces $m \leq 2n - 4$. 

## Coloreo

Un coroleo de vertices es una funcion de vertices a colores tal que si 2 vertices son adyacentes entonces no pueden compartir el mismo color.

* K-coloreo de G: es un coloreo de G que usa exactamente K colores.

* Un grafo G es K-coloreable si existe un K-coloreo de G.

* Numero cromatico de G: Minima cantidad de colores necesaria para colorear G.

* G es K-cromatico si su numero cromatica es K.


### Clique

Una clique en un grafo es un subgrafo completo maximal.

El numero clique de un grafo es el tamaño de la clique maxima de G.

El numero cromatico de un grafo es mayor o igual al numero clique del mismo.

El numero cromatico es menor o igual al grado maximo de G + 1.

Teorema:

    Sea G un grafo conexo que no es un circuito impar ni un grafo completo. Entonces: El numero cromatico es menor o igual al grado maximo de G.

**Teorema de los 4 colores:**

    El numero cromatico de G planar es menor o igual a 4. O sea que todo grafo planar es 4-coloreable.

Encontrar el numero cromatico y el numero clique son problemas dificiles.


## Algoritmo secuencial

La primer idea intuitiva para colorear un grafo es el elegir un orden cualquiera e ir poniendo el primer color libre que tengo. El resultado obtenido puede ser acotado por la siguiente proposicion:

Proposicion:

$$u_S(G,v_1,v_2,...,v_n) = max \ min\{i,d(v_i)+1\}$$

Si $\chi_S(G)$ es el numero de colores usado por el algoritmo secuencial para colorear G cuando los vertices se consideran en el orden $v_1,...,v_n$, entonces

$$chi(G)\leq \chi^S(G) \leq u_S(G,v_1,v_2,...,v_n)$$
 
## Algoritmo secuencial (Largest First):

Viendo la proposicion nos damos cuenta que lo mejor es sacarnos rapido de encima los nodos con un grado grande. Entonces en este algoritmo vamos a ir coloreando igual que antes, pero elegimos los nodos en orden decreciente con respecto a su grado. Con este cambio, el resultado obtenido es acotado por la siguiente proposicion:

Proposicion:

Si $u_{LF}(G,v_1,v_2,...,v_n) = u_{G}(G,u_1,u_2,...,u_n)$ donde $u_1, u_2,...,u_n$ estan ordenados segun su grado. Entonces

$$u_{LF}(G) \leq min \ u_{s}(G,v_1,v_2,...,v_n)$$ 

Para cualquier permutacion de $v_1,v_2,...,v_n$. O sea que siguiendo el orden secuencial es el mejor orden posible.

## Algoritmo secuencial (Smallest Last):

En este caso elijo como $v_n$ al vertice de menor grado. El nodo $v_{n-1}$ sera el vertice de menor grado en el grafo inducido por G con todos los nodos menos $v_n$. Asi seguimos hasta asignar todo el orden. Se puede demostrar que la cota de este algoritmo es mejor que la cota de Largest First.

Proposicion:

* Smallest First asegura colorear cualquier grafo planar usando 6 colores o menos.

## Algoritmo secuencial con intercambio:

Otra mejora para el algoritmo secuencial. En este caso, cada vez que necesite usar un color nuevo, se trata de recolorear los vertices ya coloreados para no necesitar ese color nuevo.

Supongamos que estoy coloreando el vertice v y necesitamos un color nuevo $k+1$. Entonces v tiene vecinos coloreados con todos los colores $1,...,k$. El algoritmo intenta cambiar el color de algun vecino de $v_i$ para liberar un color de los $1,...,k$ y no necesitar un color nuevo.

Este intercambio se da si existen p y q 2 colores usados en el coloreo parcial, tal que en todas las componentes conexas de $H_{pq}$, el subgrafo inducido por los vertices de colores p y q, los vertices adyacentes a v tienen el mismo color, podemos intercambiar los colores p y q en las componentes de $H_{pq}$ con vertices adyacentes a v con color p. 

* Requiere un mayor esfuerzo computacional.

* No siempre es mejor SI que S.

Se puede demostrar que:

* SI colorea un grafo bipartito con 2 colores.

* SI con el ordenamiento SL colorea un grafo planar con 5 colores maximo.

## Algoritmo secuencial con backtracking (exacto):

En cada paso se extiende la solucion parcial coloreando un vertice aun no coloreado.

Las soluciones tienen el formato $a_1,...,a_n$ con $a_i$ indicando el color asignado al vertice $v_i$.

La funcion de extension solo extiende a soluciones validas.

Se usan podas para evitar generar soluciones no optimas y soluciones simetricas.

## Coloreo de aristas:

* Coloreo valido de aristas de G: Asignacion de colores a las mismas tal que 2 aristas que inciden sobre el mismo vertice no tengan el mismo color.

* Indice cromatico de G ($\chi'(G)$): Menor numero de colores con que se pueden colorear las aristas de G.

Teorema de Vizing:

    Para todo G se verifica que
    
$$\Delta(G) \leq \chi'(G) \leq \Delta(G) + 1$$

Este tambien es un problema dificil.

# Clase 9: Flujo maximo en redes

Una red $N = (V,X)$ es un grafo orientado conexo que tiene 2 vertices distinguidos, una fuente $s$ con grado de salida positivo, y un sumidero $t$ con grado de entrada positivo.

Una funcion de capacidades en la red es una funcion $c: X \rightarrow \mathbb{R}_{\geq 0}$. O sea, toma una arista y da una capacidad positiva.

## Problema de flujo maximo

    Dada una red con capacidades de flujo en los arcos, ¿Como podemos enviar la maxima cantidad de flujo posible desde un origen a un sumidero determinados respetando las capacidades maximas de los arcos?

## Problema de costo minimo

    Si ademas de la capacidad maxima de flujo que puede atravesar un arco, cada arco tiene asociado un costo por unidad de flujo enviado a traves de el, ¿Como podemos enviar una determinada cantidad de flujo desde un origen a un sumidero determinados respetando las capacidades maximas de los arcos a menor costo?

Un flujo factible en una red $N = (V,X)$ con funcion de capacidad c, es una funcion $f: X \rightarrow \mathbb{R}_{\geq 0}$ que verifica:

1. $0 \leq f(e) \leq c(e)$ para todo arco $e \in X$.

2. Ley de conservacion de flujo

    $\sum_{e \in In(v)} f(e) = \sum_{e \in Out(v)} f(e)$ 

    Para todo vertice $v \in V \setminus \{s,t\}$, donde
    
    $In(v) = \{e \in X, e = (w \rightarrow v), w \in V\}$

    $Out(v) = \{e \in X, e = (v \rightarrow w), w \in V\}$

El valor de flujo de F es igual al flujo que entra a $t$ menos el flujo que sale de $t$.

Lema:

    El valor de flujo de F es igual al flujo que sale a $d$ menos el flujo que entra en $s$.

## Problema de corte minimo

Un corte en la red $N = (V,X)$ es un subconjunto $S \subseteq V \setminus \{t\}$ tal que $s \in S$. O sea, subconjunto de vertices que incluye a $s$ pero no a $t$.

Notacion:

* Dados $S, T \subseteq V$, llamaremos

    $ST = \{(u\rightarrow v) \in X: u \in S \ y \ v \in T\}$

Proposicion:

* Sea f un flujo definido en una red $N$ y sea $S$ un corte, entonces F es igual al flujo que sale de S menos el flujo que entra a S.

Dada una red $N = (V,X)$ con funcion de capacidad c, la capacidad de un corte $S$ se define como la suma de las capacidades que salen de S.

El problema de corte minimo consiste en encontrar el corte de una red que tenga la minima capacidad entre todos los cortes posibles.

Lema:

    Dadas una red, una funcion de flujo y un corte, se cumple que el valor de la funcion de flujo es menor o igual a la capacidad del corte.

Corolario:

    Si F es el valor de un flujo f y S un corte en una red N tal que $F = c(s)$ entonces: F es un flujo maximo y S es un corte de capacidad minima.

## Camino de aumento

* Red residual: $R(N,f) = (V,X_R)$ donde para toda arista de N, si su flujo es menor a la capacidad, la misma se encuentra en $X_R$ (puedo agregar mas flujo). Ademas, si su flujo es mayor a cero tambien se encuentra la arista invertida (puedo sacar flujo).

* Camino de aumento: Camino orientado de s a t en $R(N,f)$.

Proposicion:

* Dada una red N, un flujo f y su residual $R(N,f) = (V, X_R)$, el algoritmo de camino de aumento determina un camino de aumento en R, P, si existe y, en caso contrario, determina un corte S de N.

Habiendo obtenido el camino de aumento, para cada arco definimos un $\Delta$ que sera la diferencia en el flujo entre 2 iteraciones del algoritmo. El mismo es el maximo flujo que le puedo sumar (capacidad menos flujo) o el maximo flujo que le puedo restar (flujo actual). El $\Delta$ del camino es el minimo entre todos los deltas de ese camino.

Si en el camino de aumento se encontraba la arista en el mismo sentido que en la red original, el nuevo flujo sera el anterior mas el $\Delta$. Si se encontraba en el sentido inverso el nuevo flujo sera el anterior menos el $\Delta$.

Proposicion:

    El flujo luego de iterar con el camino de aumento siempre aumenta en $\Delta$.

Teorema:

    f es un flujo maximo si y solo si no existe un camino de aumento en R.

## Algoritmo de Ford y Flukerson F&F

Basicamente hace lo que cualquiera pensaria. Empieza con una red con flujo 0. Construye la red residual, busca el camino de aumento y modifica los valores de flujo de manera acorde al $\Delta$ conseguido. Repite esto hasta que no haya un camino de aumento.

Proposicion:

    Si las capacidades de los arcos son enteras entonces el problema de flujo maximo tiene un flujo maximo entero.

Proposicion:

    Viendo la proposicion anterior nos podemos dar cuenta que si las capacidades son enteras F&F a lo sumo vamos a hacer F iteraciones, donde F es el maximo valor de flujo.

Proposicion:

    Si los valores del flujo inicial y las capacidades de los arcos de la red son enteros, F&F es O(n*m*U), donde U es una cota superior para el valor de las capacidades. El flujo maximo es a lo sumo tan alto como la capacidad maxima por la cantidad de nodos.

Esta complejidad no es polinomial en el tamaño de la entrada, ya que U no depende de la misma.

F&F podria no depender en el tamaño de la entrada si no se especifica un orden para elegir los arcos y los vertices. Incluso podria no terminar si las capacidades o el flujo inicial son irracionales.

## Implementacion de Edmonds y Karp E&K

* Esta implementacion usa BFS para marcar los vertices en el camino de aumento.

* E&K realiza a lo sumo n*m iteraciones.

* La complejidad resultante es $\mathcal{O}(m^2n)$.

* Existen algoritmos mas eficientes pero son mas complicados.

Asi logramos que la complejidad sea polinomial en el tamaño de la entrada.

Teorema:

    Dada una red N con n vertices y m arcos, el algoritmo de E&K realiza a lo sumo n*m iteraciones.

# Clase 10: Complejidad computacional


Tipos de problemas:

* Version de optimizacion: Encontrar una solucion optima de el problema $\Pi$ para la instancia I.

* Version de evaluacion: Determinar el valor de una solucion optima de $\Pi$ para I.

* Version de localizacion: Dado un numero k, determinar una solucion factible de $\Pi$ para I tal que $f(S) \leq k$. 

* Version de decision: Dado un numero k, determinar si existe una solucion factible de $\Pi$ para I tal que $f(S) \leq k$.

La version de optimizacion suele ser la version mas dificil. Mientras que la version de decision suele ser la mas facil.

Si la version de decision es facil, y el valor de la solucion optima es un entero cuyo logartimo esta acotado por un polinomio en orden de la entrada, podemos resolver el problema de optimizacion de manera polinomial haciendo busqueda binaria sobre las soluciones posibles.

Si la version de decision es facil, podemos encontrar la solucion de la version de localizacion resolviendo una cantidad polinomial de problemas de decision para instancias reducidas de la instancia original.

    Por lo general, si existe un algoritmo eficiente para alguna de estas 4 versiones, entonces existe para todas ellas.

La clasificacion y el estudio se realiza sobre problemas de decision. De esta forma podemos uniformar el estudio, ya que hay problemas que no tienen version de optimizacion.

Instancia de un problema: Especificacion de sus parametros.

Un problema de decision $\Pi$ tiene asociado un conjunto de instancias factibles. Un subconjunto del mismo esta formado por instancias cuya respuesta es SI.

## Problemas intratables:

SOn problemas que no pueden ser resueltos por ningun algoritmo eficiente. Esto se puede dar por varios motivos:

* La respuesta en si es exponencial en el tamaño de la entrada.

* El problema es indecidible. O sea que ni siquiera existe un algoritmo que lo resuelva.

* El problema es decidible pero no se conocen algoritmos polinomiales que lo resuelvan.

## SAT (version de decision)

Dado un conjunto de clausulas $C_1, ..., C_m$ formadas por literales basados en las variables booleanas $X = \{x_1,...,x_n\}$, existe alguna valuacion de $X$ tal que la conjuncion de todas las C sea verdadera?

## Maquina de turing deterministica:

Es modelo de computo. Consta de:

* Una cabeza lecto escritora

* Una cinta infinita que actuara como memoria.

La cabeza lectora se puede mover de izquierda a derecha por la cinta.

Las posiciones de la cinta tienen los valores 1 y -1, existe una celda de valor 0 que es definida como la celda inicial.

Una maquina M resuelve el problema de decision $\Pi$ si para toda instancia alcanza un estado final y responde de forma correcta.

La complejidad de la maquina de turing es la cantidad de movimientos que hace la cabeza hasta llegar al estado final. Se toma el maximo entre todas las instancias.

## Clase P

Un problema de decision $\Pi$ pertenece a la clase P si existe una MTD de complejidad polinomial que lo resuelve.

En otras palabras:
    
    Existe un algoritmo polinomial que lo resuelve.

## Maquinas de turing no deterministicas:

* Generalizacion de MTD.

* Ahora para cada estado del programa podria tomar varias decisiones.

* Evalua distintas alternativas en paralelo, si en algun estado la ejecucion puede tomar varios caminos, se podria pensar que la maquina abre tantas copias como caminos sean necesarios.

* Si se llega a un estado SI en alguna copia, todas paran y se responde SI.

* So se llega a NO, solo para esa copia y las demas siguen normalmente.

Una MTND resuelve el problema de decision $\Pi$ si existe una secuencia de alternativas que lleva a un estado SI, si y solo si, la respuesta es SI. 

La complejidad de estas maquinas se calcula como el maximo numero de pasos que toma la minima rama en llegar a SI.

## Clase NP

Un problema de decision $\Pi$ pertenece a la clase NP si existe una MTND de complejidad polinomial que lo resuelve.

En otras palabras:
    
    Dada una instancia del problema con respuesta SI se puede dar un certificado de longitud polinomial que garantiza que la respuesta es SI, y esta garantia se puede verificar en tiempo polinomial.

* $P \in NP$

Lema:

* Si $\Pi$ es un problema de decision que pertenece a NP, entonces $\Pi$ puede ser resuelto por un algoritmo deterministico en tiempo exponencial respecto al tamaño de la entrada.

## Clases P y NP

* $P \subseteq NP$

* ¿P = NP? No se sabe. Todavia no se pudo demostrar que existe un problema en NP que no pertenezca a P.

## Transformaciones polinomiales

Una transformacion o reduccion polinomial de un problema $\Pi'$ a un problema $\Pi$ es una funcion polinomial de una instancia de $\Pi'$ a una instancia de $\Pi$ tal que $I'$ responde SI en $\Pi'$ si y solo si $f(I')$ responde SI en $\Pi$.

Si esta existe, se dice que $\Pi'$ se reduce polinomialmente a $\Pi$. Se nota como $\Pi' \leq_{p} \Pi$.

## Clase NP-completo

* Es el centro de la teoria de la complejidad computacional.

* Intuitivamente, agrupa a los problemas de decision que son los mas dificiles de la clase NP.

Cuentan con 2 propiedades muy importantes:

* No se conocen algoritmos polinomiales para resolverlos.

* Si existe un algoritmo polinomial para uno de ellos, existen algoritmos polinomiales para todos ellos.

Un problema de decision $\Pi$ es **NP-completo** si:

1. $\Pi \in NP$
2. $\forall \ \Pi' \in NP, \ \Pi' \leq_{p} \Pi$

Si un problema verifica la condicion 2, $\Pi$ es **NP-dificil**.

Para demostrar que un problema $\Pi$ es **NP-completo** tenemos que hacer esos 2 chequeos.

Primero vemos que sea NP encontrando un certificado polinomial que se pueda verificar en tiempo polinomial.

Segundo, vemos que un problema $\Pi' \in NP-completo$ se reduce polinomialmente a $\Pi$, ya que si esto pasa, por transitividad todos los problema en NP, se reducen a $\Pi$. 

## P y NP

Lemas:

* Si existe un problema en NP-completo que ademas este en P, entonces P = NP.

* Si existe un problema en NP que no esta en P, entonces P $\neq$ NP.

## Co-NP

El problema complemento de un problema de decision $\Pi$, $\Pi^c$, es el problema de decision cuyo conjunto de instancias es igual al de $\Pi$ y responde SI para todas las instancias que $\Pi$ responde NO y viceversa. 

Proposicion:

    Si un problema pertenece a P, entonces su complemento tambien pertenece a P.

Esto no sirve para NP. O sea que si $\Pi$ esta en NP, no se sabe si $\Pi^c$ esta en NP.

Un problema de decision pertenece a Co-NP si dada una instancia de NO y evidencia polinomial de la misma, se puede verificar en tiempo polinomial.

Proposicion:

Si un problema $\Pi$ pertenece a NP, entonces $\Pi^c$ pertenece a Co-NP.

## Extension de un problema

Un problema es una restriccion de otro si el dominio del primero esta incluido en el del segundo.

El caso inverso se llama extension o generalizacion.

* Algunas veces, restricciones de un problema NP-completo resultan en P.

Si $\Pi$ es una restriccion de $\Pi'$, podemos deducir que:

* Si $\Pi' \in P$, entonces $\Pi \in P$.

* Si $\Pi' \in NP$, entonces $\Pi \in NP$.

* Si $\Pi \in NP-completo$, entonces $\Pi' \in NP-dificil$.


## Algoritmos pseudopolinomiales

Un algoritmo es pseudopolinomial si la complejidad es polinomial en funcion del valor de la entrada. 

# Clase 11: Matching, conjunto independiente y recubrimientos

## Problemas a estudiar

* Matching: Conjunto de aristas M de G tal que para todo vertice v de G, v es incidente a lo sumo a una arista de M.  

* Conjunto independiente: Conjunto de vertices I de G tal que para toda arista e del grafo, e es incidente a lo sumo a un vertice de I.

* Recubrimiento de aristas: Conjunto de vertices R de G tal que para toda arista e de G, e es incidente al menos a un vertice de R.

* Recubrimiento de vertices: Conjunto de aristas R de G tal que para todo vertice v de G, v es incidente al menos a una arista de R.

## Problemas de optimizacion asociados
 
* Matching maximo: Encontrar el matching de maximo cardinal entre todos los posibles. **Problema FACIL**

* Conjunto independiente maximo: Encontrar el conjunto independiente de maximo cardinal entre todos los posibles. **Problema DIFICIL**

* Recubrimiento de aristas minimo: Encontrar el recubrimiento de aristas de minimo cardinal entre todos los posibles. **Problema DIFICIL**

* Recubrimiento de vertices minimo: Encontrar el recubrimiento de vertices de minimo cardinal entre todos los posibles. **Problema FACIL**

Lema:

* $S \subseteq V$. S es un conjunto independiente $\Longleftrightarrow$ $V \setminus S$ es un recubrimiento de aristas.

## Relacion entre coloreo y conjunto independiente

Es facil notar que todos los vertices pintados del mismo color forman un conjunto independiente. Entonces, el problema de coloreo se puede definir como encontrar una particion de los vertices de G en conjuntos independientes. 

El problema de optimizacion seria minimizar la cantidad de conjuntos.

* No es cierto que en un coloreo optimo, el conjunto independiente de cardinal maximo tenga el mismo color.

Igualmente podemos definir un algoritmo goloso para colorear un grafo, pintando el mismo buscando conjuntos independientes de mayor a menor tamaño. El maximo tratamos de encontrarlo con alguna heuristica ya que este tambien es un problema dificil.

## Matching maximo

* Vertice saturado: Vertice incidente a una arista del matching M.

* Camino alternado: Dado un matching M en G, un camino alternado en G es un camino simple donde se alternan aristas que estan en M con aristas que no estan en M.

* Camino de aumento: Dado un matching M en G, un camino de aumento en G es un camino alternado entre vertices no saturados por M.

Teorema: 

    M es un matching maximo de G si y solo si, no existe un camino de aumento en G con respecto a M.

Algoritmo:

1. Empiezo con una arista cualquiera (es matching).

2. Mientras exista camino de aumento, hago la diferencia simetrica entre el matching que tenia y el camino de aumento. Esto asegura un matching de cardinal aumentado en 1.

3. Cuando no haya camino de aumento retorno el matching actual, este es maximo.

## Matching, conjunto independiente, recubrimientos

Teorema:

    Dado un grafo G sin vertices aislados, si M es un matching maximo de G y R un recubrimiento minimo de los vertices de G, entonces |M|+|R| = n.

Teorema:

    Dado un grafo G, si I es un conjunto independiente maximo de G y R un recubrimiento minimo de las aristas de G, entonces |I|+|R| = n.


# Errores:
## Clase 1:
* diapo 20. Solo va sin tilde
* diapo 21: Interesa esta mal escrito