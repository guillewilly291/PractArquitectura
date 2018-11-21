
# Versiones 
Para el versionado se seguira el siguiente orden: 
    -1 Generacion Asteroides y planetas
    -2 Calculo de la fuerza
    -3 Movimiento 
    -4 Rebote bordes
    -5 Rebote Asteroides


# To-Do-List:
-poner todas las constantes de la seccion 2.2.5 como constantes en codigo por si se necesitan cambiar cuando sea
const float ....

-Control de errores  en argumentos?¿? 

XXXX-Intentar pasar los parametros del programa mediante la consola y no mediante cin, cout. ---> Listo 

-Hay que poner el calculateMovNormal solo cuando la distancioa sea de 2 o mayor
-en el movimiento normal, si la distancia es mayor a 2 no se debe calcular(?¿?fin de la ejecucion? devuelve 0?¿?¿)


# Ejecutar

    -Para guardar Ctrl-s
    -Para Compilar (necesario para hacer debugging y para Runnear el codigo) Ctrl+Shift+B
    -Para ejecutar introducir ./a.out 5 2 1 200 (por ejemplo)



# Paginas-C++

    -Hack para C++ en general : http://c.conclase.net/curso/?cap=000
    -Programacion punteros HACK: https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Punteros
    -Errores típico con punteros: https://www.fing.edu.uy/inco/cursos/prog3/utils/Punteros.pdf
    -Posible Hack para entrada y salida: https://es.wikipedia.org/wiki/C%2B%2B#Biblioteca_de_entrada_y_salida
    -https://www.aprenderaprogramar.pro/2017/10/arrays-bidimensionales.html
    -Matrices y punteros C++: https://ronnyml.wordpress.com/2009/07/04/vectores-matrices-y-punteros-en-c/
    -Problema con encontrar length: https://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array


# POSIBLES MEJORAS
- Llamar "Asteroide" al objeto "Asteroides" dado que el plural puede dar lugar a confusión - Tener una clase que se llame Cuerpo que tenga campos(tipo, ejeX, ejeY, masa) 