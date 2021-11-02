<style type="text/css">
    ol ol {list-style-type: lower-alpha;}
</style>
<font size="4">



## Complejidad de problemas
1. Certificados positivos  

    1. Debemos recibir el factor k. El verificador chequea:
        * $1 < k < n \ \ O(1)$
        * $m \equiv 0 (k) \ \ O(1)$

    2. Debemos recibir el min(A). El verificador chequea:
        * $min(A) \leq k \ \ O(1)$

    3. Debemos recibir una lista de tuplas que tengan, la arista y el flujo que pasa por esa arista $<E, F>$. El verificador chequea:
        * $((\forall \ tupla: \ t) \ \pi_{1}(t) > C(\pi_{0}(t))\ \ O(m)$
        * La sumatoria de $\pi_{1}(t)$ para toda tupla cuya arista salga de $s$ es igual a la sumatoria de $\pi_{1}(t)$ para toda tupla cuya arista llegue de $t$. $O(m)$ 
        * La sumatoria de $\pi_{1}(t)$ para toda tupla cuya arista salga de $s$ $\geq f$. $O(m)$
        * $((\forall \ tupla: \ t) \ (\pi_{0}(t) = e) \Rightarrow e \in E(N)) \ \ O(m)$
        * Flujo positivo

    4. Debemos recibir una lista $l$ ordenada de aristas dirigidas que indicaran el camino a seguir para salir de $s$ y llegar a $t$. El verificador chequea:
        * $l[0][0] = s$
        * $l[|l|-1][1] = t$
        * $((\forall \ arista: \ e) (e \in l) \Rightarrow e \in E(G)) \ \ O(n)$
        * $\sum\limits_{e \in l} C(e) \leq k \ \ O(n)$
        * $((\forall \ (\mathbb{N},\mathbb{N}): \ (i,j)) (0 \leq i < j < |l|) \Rightarrow l[i] \neq l[j]) \ \ O(n^2)$

    5. Idem pero sin el ultimo chequeo.

    6. Debemos recibir una lista $l$ ordenada de aristas dirigidas que indicaran el camino a seguir para salir de $s$ y llegar a $t$. El verificador chequea:
        * $l[0][0] = s \ \ O(1)$
        * $l[|l|-1][1] = t \ \ O(1)$
        * $((\forall \ arista: \ e) (e \in l) \Rightarrow e \in E(G)) \ \ O(n)$
        * $((\forall \ (\mathbb{N},\mathbb{N}): \ (i,j)) (0 \leq i < j < |l|) \Rightarrow l[i] \neq l[j]) \ \ O(n)$
        * $|l| = |V| \ \ O(1)$

    7. Idem anterior pero el verificador ademas chequea que el peso del camino sea $\leq k$.

    8. Debemos recibir una lista $l$ de vertices. El verificador chequea:
        * $|l| \geq k \ \ O(1)$
        * $((\forall \ vertice: \ v)(v \in l) \Rightarrow(v \in V)) \ \ O(n)$
        * $((\forall \ (vertice, vertice): \ (v_{1}, v_{2}))(v_{1} \neq v_{2} \land (v_{1}, v_{2}) \in l)\Rightarrow ((v_{1}\rightarrow v_{2} \lor v_{2} \rightarrow v_{1}) \in E)) \ \ O(n^2)$
  
    9. Chequeado. El algoritmo no es polinomial en la entrada. El verificador si.


    10. Preguntar a vicky
    
    11. Debemos recibir una funcion $f: V(H) \rightarrow V(G)$ que contenga la tranformacion de los vertices para de $H$ a $G$. El verificador chequea:
        * $((\forall \ (vertice,vertice)): \ (v_{1},v_{2}))((v_{1}\rightarrow v_{2}))\Leftrightarrow(f(v_{1})\rightarrow f(v_{2})))$
        * $|V(G)| = |V(H)|$

    12. Idem anterior pero sin el ultimo chequeo. Deberia chequear que sea menor la cantidad de vertices.

    13. Debemos recibir el valor de verdad para cada parametro $X=(x_1, x_2, ..., x_n)$. El verificador chequea que:
        * $\phi(X) = False$

2. Certificados negativos
    
    1. Debemos recibir un natural $k$ tal que $n$ sea divisible por $k$. El verificador chequea:
        * $n \equiv 0(k)$
    
    2. Debemos recibir 2 indices $i, j$ tal que $i < j \land A[i] > A[j]$. El verificador chequea:
        * $((i < j)\land(A[i] > A[j]))\lor((i > j)\land(A[i] < A[j]))$
    
    3. Debemos recibir una secuencia ordenada $l$ de nodos que contengan el camino a seguir para formar el ciclo. El verificador chequea:
        * $|l| > k$
        * $((\forall \ \mathbb{N}: \ i)(0 \leq i \leq |l|-1)\Rightarrow(l[i]\rightarrow l[i+1] \in E(G)))$
        * $l[0] = l[|l|-1]$
        * $((\forall \ (\mathbb{N},\mathbb{N}): \ (i,j)) (0 \leq i < j < |l|-1) \Rightarrow l[i] \neq l[j]) \ \ O(n)$
    
    4. Debemos recibir un ciclo de longitud impar. El verificador chequea:
        * Que sea un ciclo de longitud impar :)

    5. Preguntar a vicky

    6. Debemos recibir una formula proposicional $X=(x_1, x_2, ..., x_n)$. El verificador chequea que:
        * $\phi(X) = False$

    7. Opcional

    8. Opcional

3. Opcional

4. Preguntar a vicky

5. Opcional

6. Reduccion polinomial

    
    1. $\Longrightarrow$)
    
        Sabemos que $\langle G,s,t,k\rangle$ es una instancia positiva de *EVEN-PATH*. QvQ: $\langle G',(s,p),(t,p),k\rangle$ es una instancia positiva de *PATH*.
    
        Sabemos que s y t están conectados por un recorrido par mas chico que k pues *EVEN-PATH*. Además, por como está armado $G'$ sabemos que para cuales quiera $v_i$ y $v_j$ nodos de $G$ a distancia par en, existe camino en $G'$ entre $(v_i, p)$ y $(v_j, p)$. 

        $\Longleftarrow$)

        Sabemos que $\langle G',(s,p),(t,p),k\rangle$ es una instancia positiva de *PATH*. QvQ: $\langle G,s,t,k\rangle$ es una instancia positiva de *EVEN-PATH*.

        Sabemos que s y t estan conectados por un recorrido mas chico que k pues *PATH*. Ademas por como esta armado $G'$ sabemos que s y t estan a distancia par. Entonces *EVEN-PATH* se cumple :)

    2. Para la reduccion del punto anterior alcanza con crear todos los nodos repetidos en $\mathcal{O}(2*n)$. Y hacer todas las conexiones en $\mathcal{O}(n+m)$.

7. Reducciones
    1. $\Longrightarrow$)

        Sabemos que X es una instancia positiva de *2-PARTITION*. Veamos que $\langle r, R\rangle$ es una instancia positiva de *RECTANGLE PACKING*. 

        Lo primero quiere decir que existe un $S \subseteq X$ tal que la sumatoria de los numeros en $S$ es igual a la sumatoria de los numeros en $X \setminus S$. Entonces, la suma de ambos de estos conjuntos es la sumatoria de los elementos de $X$ sobre 2.  Como $r$ tiene base esa sumatoria y altura 2 y $R$ tiene base $x$ y altura 1, entonces podemos llenar el primer piso de $R$ con los rectangulos de $S$ y el segundo piso con los de $X \setminus S$.

        $\Longleftarrow$)

        Sabemos que $\langle r, R\rangle$ es una instancia positiva de *RECTANGLE PACKING*. Veamos que X es una instancia positiva de *2-PARTITION*.

        Sabemos que el rectangulo $r$ esta lleno, como $min(X) > 2$ entonces no pueden haber rectangulos parados. Eso quiere decir que todos los rectangulos ocupan 1 fila. Podemos separar los rectangulos en los que ocupan la fila 1 y los que ocupan la fila 2. Los de la 1 van a estar en $S$, los demas van a estar en $X \setminus S$.

    2. $\Longrightarrow$)

        Sabemos que $X$ es una instancia positiva de *3-PARTITION*. Veamos que $\langle r,R \rangle$ es una instancia positiva de *RECTANGLE PACKING*

        Agarramos ese set de triplas, cada tripla ocupa una columna y ya que la tripla suma $t$, la columna va a sumar $t+3n$. Ya que tenemos n triplas podemos llenar n columnas y nos queda $r$ lleno.

        $\Longleftarrow$)

        Sabemos que $\langle r,R \rangle$ es una instancia positiva de *RECTANGLE PACKING*. Veamos que $X$ es una instancia positiva de *3-PARTITION*.

        Como los rectangulos tienen altura $n+x, x>0$ entonces tienen que estar si o si parados. Ademas sabemos que tenemos $3*n$ rectangulos que suman $n*t$ ya que si no la instancia estaria mal definida. Como el $x < \lfloor t/2 \rfloor$ entonces siempre tienen que haber mas de 2 rectangulos. Lo que fuerza a que siempre hayan 3 rectangulos. Entonces cada columna es una tripla.

8. Si G y H tienen la misma cantidad de vertices, aristas y las secuencias ordenadas de sus grados son iguales (lo podemos chequear polinomialmente) entonces aplicamos *ISOMORFISMO (restringido)* sobre la instancia original. Caso contrario aplicamos transformamos a 2 grafos no isomorfos.

9. Opcional

10. No entendi un pingo

11. Opcional

12. 

13.

14.

15.

16.

17. 

18.

19.

20.

21.

22.

23. Opcional

24. Sea $X = (x_1, x_2, ..., x_n), x_i \in \{True, \ False\}$ el conjunto de variables que toma SAT. El conjunto de soluciones candidatas esta formado por todas las posibles combinaciones del conjunto anterior. Una solucion parcial se forma fijando valores para las primeras $i$ variables de $X$ con $i<n$. Dada una solucion parcial $S_i$, la formula para extender la misma es fijar un valor a $x_{i+1}$. Mostrar el arbolito, le hacemos DFS. Cada vez que nos extendemos chequeamos si alguna disyuncion tiene todas las variables fijadas y el termino evalua Falso. Ahi esa solucion no va a llegar a una solucion valida asi que cortamos ese puente para evitar caminos innecesarios.

25. Preguntar a vicky

26. Isomorfismo
    * Fijamos un orden $w_1, w_2, ..., w_n$ en los nodos de H.
    * Las soluciones candidatas son las permutaciones de $V(G) = (v_1, v_2, ..., v_n)$
    * Las soluciones parciales son los ordenes $v_1, ..., v_i$ tales que $$

27.
</font>



