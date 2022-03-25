## ¿Qué es y para qué sirve una System Call? Explicar los pasos involucrados por hardware y software. Ejemplificar.

Una syscall es la forma que tiene el usuario de interactuar con el SO, por ejemplo para crear otro proceso o para que haga operaciones de E/S. Esto es necesario porque el usuario no tiene permisos para hacer estas acciones, todo lo que sea crítico para el buen funcionamiento del sistema lo va a hacer el kernel mediante syscalls para evitar que nos mandemos alguna cagada nosotros.

Los pasos ejecutados por el hardware y el software son los siguientes:

1. El hardware de interrupción mete el `PC` y algunos registros del proceso actual a la pila.

2. El hardware carga el nuevo `PC` del vector de interrupciones.

3. Un procedimiento de ASM guarda los registros del proceso actual en su entrada de la `PCB`.

4. Un procedimiento de ASM establece una nueva pila temporal para el manejador de procesos.

5. Se ejecuta el procedimiento de interrupciones (por lo general hecho en C).

6. El procedimiento en C llama al scheduler para que decida a quien darle CPU.

7. El scheduler decide y le da el control al código ASM.

8. Este código inicia el nuevo proceso actual (reestablece registros, pila, etc...).

En un sistema x86-32 los pasos son los siguientes:

1. El procedimiento en espacio de usuario llama a un wrapper en C de la syscall.

2. Este wrapper recibe los parámetros de la syscall a través de la pila, pero la syscall los espera guardados directamente en unos registros específicos, así que este wrapper se encarga de hacer el pasaje de parámetros.

3. El wrapper además guarda en un registro específico el número asociado a la syscall que se quiere llamar.

4. El wrapper ejecuta la instrucción `int 0x80` que genera un *trap* y hace que el proceso pase de modo usuario a modo kernel y ejecute el código apuntado por la dirección 0x80 del `system's trap vector`.

5. Este código hecho en ASM guarda los registros en el stack del kernel, chequea que el nro de syscall sea válido y después llama a la syscall en cuestión, la cual es encontrada usando el nro de syscall como indice en la tabla de syscalls del kernel. Después se ejecuta la syscall propiamente dicha (generalmente en C) y devuelve el resultado a este código en ASM. Este código restaura los registros que estaban en la pila del kernel y pone en la pila (stack o usuario?) el resultado de la syscall. Por último, se vuelve al wrapper en C y ya estamos de nuevo en espacio de usuario.

6. Si el valor retornado indica un error, el wrapper guarda el valor en la variable global `errno`. El procedimiento termina con el wrapper retornando el resultado al procedimiento del usuario que llamó a la syscall.



## Una PCB clásica para el manejo de procesos contiene todos los recursos para que el proceso pueda ejecutar, por ejemplo Registros, Archivos abiertos, etc. ¿Cómo debe modificarse para soportar threads?

## Proponga un escenario en donde un proceso requiera la modificación de algún valor de la PCB. Escriba el pseudocódigo de las rutinas para realizar ese cambio y quién (SO o proceso) es responsable de cada una.

## En Unix/Linux los procesos no pueden acceder a puertos de entrada/salida directamente, salvo que explícitamente se le de permiso. ¿Cómo podría implementarse?

## ¿Qué son las funciones reentrantes y cuál es su relación con los threads?

## Dar dos ejemplos de transición de running a ready.

## Se puede ir directo de waiting a running? Explicar las razones.

## Cuál es la diferencia entre mode switch y context switch?

## Dibujar el mapa de memoria de un proceso.

## Qué pasa con la memoria cuando se crea un proceso hijo? Explicar los casos de fork() y vfork().

## Qué es Copy on Write? Cómo funciona en sistemas con Paginación?

## Cuántas veces imprime "Hello, world!" el siguiente programa? Explicar. ¿Qué pasa si se usa vfork() en lugar de fork()? 

```
foo () {
 int i;
 for(i = 0; i<3; i++) fork();
 printf("Hello, world!\n");
}
```

## Se poseen dos procesadores y se pueden ver los cambios de estado de los procesos. ¿Qué tendría que ver para que se aumente el rendimiento agregando un procesador?
¿Qué tendría que ver para que se aumente el rendimiento agregando más memoria?
