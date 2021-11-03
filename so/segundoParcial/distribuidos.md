Tenemos una red con 6 nodos, cada uno de ellos tiene la siguiente información:

1. ID: Identifica al nodo.
2. privilegio: A mayor privilegio, más chances se tiene de ser el lider.
3. Líderes: Lista que contiene a todos los líderes por ID. Inicia con un único elemento, el ID propio.
4. SoyLider: Booleano que indica si soy o no el lider. Inicia en true.

Para empezar se corre *Bully* desde el nodo de ID = 0. O sea, que el nodo 0 anuncia que quiere ser lider y manda su privilegio en un mensaje. Como en *Bully* normal se declarará el lider si nadie le contesta. En caso en que alguien le conteste quiere decir que no es el lider por lo que debe apagar su flag *soyLider*.

Si somos el nodo $i$ y nos llega un mensaje del nodo 0 pueden pasar 3 cosas, tenemos privilegio menor, igual o mayor al privilegio recibido.

Si nuestro privilegio es menor quiere decir que somos simples ciervos y que en el corto plazo no podremos ser líderes de nada, por lo cual con mucho dolor seteamos *SoyLider* a false y limpiamos *líderes*

Si nuestro privilegio es igual quiere decir que nos contacto un hermano que quiere compartir el trono con nosotros, es por esto que debemos broadcastear nuestro privilegio a todos los nodos de *ID* mayor al nuestro, para dar aviso que nosotros también reinaremos. En este caso no devolvemos el mensaje a nuestro hermano el nodo 0 ya que queremos que el mismo pueda ser lider junto con nosotros.

Si nuestro privilegio es mayor, debemos broadcastearle nuestro mensaje a quien nos lo envió para avisarle que no hay lugar para él en el trono y enviamos nuestro deseo de reinar a los nodos de *ID* mayor al nuestro.

Cuando no hayan más mensajes en la red quiere decir que todos los líderes han sido elegidos. En ese momento los nodos afortunados que hayan sido elegidos deben broadcastear su condición de reyes a todos los demás nodos, sin excepción.

Por cada uno de estos broadcast recibidos debemos agregar al monarca a nuestra lista *líderes*.

Al finalizar los broadcasts, todos los nodos tendrán la misma lista de líderes.