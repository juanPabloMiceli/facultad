Para obtener un csv con la predicciones de "testing data" luego de haber fitteado con "training data" ejecutar desde una consola el siguiente comando:


$./tp2 -m 0 -i {path training data} -q {path testing data} -o {path out predicciones}


El programa anterior se ejecuta por default con la version de KNN de 3 vecinos.
Este comportamiento se puede cambiar agregando el flag -k {numero de vecinos}.
Adicionalmente, tambien se puede modificar cuantas imagenes se usan para entrenar con el flag -n {cantidad de imagenes}

Un modificacion al comando anterior para usar KNN con 10 vecinos para 500 imagenes de entrenamiento se veria asi:


$./tp2 -m 0 -i {path training data} -q {path testing data} -o {path out predicciones} -k 10 -n 500




Para obtener el csv de las predicciones, esta vez usando una combinacion de PCA+KNN se puede usar el siguiente comando.


$./tp2 -m 1 -i {path training data} -q {path testing data} -o {path out predicciones}


Este programa se ejecuta con los parametros Alfa=19 y k=3. 
Se puede modificar el valor de k de la misma manera que se hizo anteriormente, el valor de Alfa se modifica con el flag -A. 
Como entrenar el modelo en este caso es muy costoso existe la opcion de guardar en un archivo binario la matriz con los autovectores conseguidos. Esto se hace agregando al final del comando un segundo -o {path binario de salida}. Es importante pasar este flag luego de pasar "-o path out predicciones".
Un ejemplo de esto con Alfa = 5 se veria asi:


$./tp2 -m 1 -i {path training data} -q {path testing data} -o {path out predicciones} -A 5 -o {path out binario}  


Para ahorrarnos el training, ahora usamos el flag -P (notar que es mayuscula) junto con el path del binario generado 


$./tp2 -m 1 -i {path training data} -q {path testing data} -o {path out predicciones} -P {path out binario}  



Para la experimentacion utilizamos 2 modos mas, uno para calcular las predicciones de un rango de ks y otro para un rango de alfas. Estos no toman un csv de testing, ya que particionan el csv de training en 2. Por default esta particion es de 80% de la data para training y el 20% para testing. Esto se puede cambiar con el flag -p {porcentaje para training} (notar que es minuscula). Este parametro se pone en 0 para que toda la data se use para testing y en 1 para que toda la data se use para training. Al igual que en todos los modos se puede seleccionar cuantos datos usar para training con el flag -n.

Para seleccionar el rango de predicciones que se desea obtener para k se utilizan los flags --min_k {k minimo} y --max_k {k maximo}. Lo mismo se hace para alfa con los flags --min_alfa {alfa minimo} y --max_alfa {alfa maximo}.

Para conseguir el csv con predicciones de k en el rango [2,8] con 500 imagenes de training y 500 de testing correr el siguiente comando:


$./tp2 -m 2 -i {path training data} -o {path out predicciones} -n 1000 --min_k 2 --max_k 8 -p 0.5


El funcionamiento para el rango de alfas es analogo. Con el añadido de que, al igual que en PCA+KNN se puede guardar y levantar un binario con la matriz de autovectores. El unico requisito es que al momento de levantar un binario, la matriz se debe haber calculado con un alfa >= max_alfa. De no cumplirse el programa no terminará.

Por ejemplo para conseguir la prediccion para los alfas en el rango [1,4] con 800 imagenes de training y 200 de testing guardando la matriz de autovectores se debe correr el siguiente comando:


$./tp2 -m 3 -i {path training data} -o {path out predicciones} -n 1000 --min_alfa 1 --max_alfa 4 -o {path out binario}

Y para levantar ese binario y conseguir las mismas predicciones alcanza con cambiar el flag -o por el flag -P.


$./tp2 -m 3 -i {path training data} -o {path out predicciones} -n 1000 --min_alfa 1 --max_alfa 4 -P {path out binario}