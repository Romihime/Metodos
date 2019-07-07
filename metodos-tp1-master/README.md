NOTA IMPORTANTE:
Las entradas que tienen un salto de linea al final dejando un renglon vacio pueden generar error.

Para correr el programa:

Cada carpeta tiene un makefile, con la opcion make tp1 se genera el archivo ejecutable.
Finalmente para correrlo se debe hacer ./tp1 test_a_correr probabilidad_del_tests. 
En el caso del ejecutable de la carpeta TP1 este va imprimir por pantalla el tiempo que tardó en correr el programa,
esto se debe a que se hizo experimentos de tiempo sobre este(basta con comentar un cout para que no imprima nada).
Todas las soluciones son escritas en el archivo "archivo.out" siguiendo las expecificaciones de la catedra.

Para correr los experimentos:

Si no modificamos el p, se utiliza p = 0.5 (excepto para los test de la cátedra)
Si no modificamos el EPS, se utiliza EPS = 10e-4
Como el EPS es un define, cuando variamos el EPS hacemos corridas distintas a mano.

Para los experimentos cualitativos:

Corremos la solucion con el arhivo de nombre, por ejemplo, para grafo_estrella corremos ./tp1 ExpGrafoEstrella p, con los p que variamos.

Para correr experimento de tiempo en la carpeta TP1:

Usamos un script de bash que corre 50 veces y escribe el resultado en otro archivo. Despues este
corre el archivo de python "promedio_tiempos.py" y asi conseguimos la media de tiempos, que escribe en el
archivo promedio_tiempos15segundos o el que corresponda, y borra los archivos intermedios.
Para correr el script de bash se necesita hacer chmod +x exp_tiempos.sh para darle permiso
de ejecucion y despues ./exp_tiempos.sh para correrlo, fijarse de que la entrada tiene que estar en la misma carpeta.
Notar que los parametros de entrada de estos scripts estan escrito dentro del codigo.

