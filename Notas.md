
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


# Mapa

(0, 0)-- -------(200, 0)  
|                   |
|                   |
(0, 200)-- ----(200, 200)



# Ejecutar

    -Para guardar Ctrl-s
    -Para Compilar (necesario para hacer debugging y para Runnear el codigo) Ctrl+Shift+B
    -Para ejecutar introducir ./a.out 5 2 1 200 (por ejemplo)




# Paginas Hack C++

    -Hack para C++ en general : http://c.conclase.net/curso/?cap=000
    -Programacion punteros HACK: https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Punteros
    -Errores típico con punteros: https://www.fing.edu.uy/inco/cursos/prog3/utils/Punteros.pdf
    -Posible Hack para entrada y salida: https://es.wikipedia.org/wiki/C%2B%2B#Biblioteca_de_entrada_y_salida
    -https://www.aprenderaprogramar.pro/2017/10/arrays-bidimensionales.html
    -Matrices y punteros C++: https://ronnyml.wordpress.com/2009/07/04/vectores-matrices-y-punteros-en-c/
    -Problema con encontrar length: https://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    -Set precision: http://www.cplusplus.com/reference/iomanip/setprecision/

# POSIBLES MEJORAS
- Llamar "Asteroide" al objeto "Asteroides" dado que el plural puede dar lugar a confusión - Tener una clase que se llame Cuerpo que tenga campos(tipo, ejeX, ejeY, masa) 



# Codigo De Por si acaso 



 if ((((vel1x > 0) && (vel2x < 0)) || ((vel1y < 0) && (vel2y > 0)) || ((vel1x < 0) && (vel2x > 0)) || ((vel1y > 0) && (vel2y < 0)))){





 /* Referente a los calculos de velocidad y aceleracion
    for (int i = 0; i < tamano; i++)
    {
        sumatorio_Fx = 0.0;
        sumatorio_Fy = 0.0;
        for (int j = 0; j < tamano; j++)
        {
            sumatorio_Fx += matrizFuerzasX[i][j];
            sumatorio_Fy += matrizFuerzasY[i][j];
        }
        accel_x = sumatorio_Fx / arrayAsteroides[i].masa; //calculamos la aceleración
        accel_y = sumatorio_Fy / arrayAsteroides[i].masa;
        velocidad_x = arrayAsteroides[i].vel_x + accel_x * Intervalotiempo; //* tiempo;  <------- hay que multiplicar por tiempo. De donde saco la varianle tiempo? //calculamos la velocidad
        velocidad_y = arrayAsteroides[i].vel_y + accel_y * Intervalotiempo; //* tiempo;  <------- hay que multiplicar por tiempo. De donde saco la varianle tiempo?
        posicion_x = arrayAsteroides[i].pos_x + velocidad_x * Intervalotiempo; //*tiempo //calculamos la nueva posicion
        posicion_y = arrayAsteroides[i].pos_y + velocidad_y * Intervalotiempo; //*tiempo //calculamos la nueva posicion

        arrayAsteroides[i].vel_x = velocidad_x; //refrescamos los datos de los objetos
        arrayAsteroides[i].vel_y = velocidad_y;
        arrayAsteroides[i].pos_x = posicion_x;
        arrayAsteroides[i].pos_y = posicion_y;
    }
    */



    void imprimirMatrices(int num_asteroides, int num_planetas, double **matrizFuerzasX, double **matrizFuerzasY, asteroides *arrayAsteroides, double **matrizFuerzas)
{
    cout << "---asteroids vs planets---" << endl;
    cout << "Fuerzas Matriz  : " << endl;
    for (int i = 0; i < num_asteroides + num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzas[i][j] << " ";
        }
        cout << "" << endl;
    }

    cout << "Fuerzas Matriz X  : " << endl;
    for (int i = 0; i < num_asteroides + num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzasX[i][j] << " ";
        }
        cout << "" << endl;
    }

    cout << "Fuerzas Matriz Y : " << endl;
    for (int i = 0; i < num_asteroides + num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzasY[i][j] << " ";
        }
        cout << "" << endl;
    }
    cout << "Asteroides con sus posiciones inicial: " << endl;
    for (int i = 0; i < num_asteroides; i++)
    {
        cout << "  Asteroide " << i << ":";
        cout << "  Posicion X: " << arrayAsteroides[i].pos_x;
        cout << "  Posicion Y: " << arrayAsteroides[i].pos_y;
        cout << "  Posicion Masa: " << arrayAsteroides[i].masa;
        cout << "  Velocidad X: " << arrayAsteroides[i].vel_x;
        cout << "  Velocidad Y " << arrayAsteroides[i].vel_y << endl;
    }
}

cout << "  Asteroides con sus posiciones Finales" << endl;
for (int i = 0; i < num_asteroides; i++)
{

    cout << "      Asteroide " << i << ":";
    cout << "      Posicion X: " << arrayAsteroides[i].pos_x;
    cout << "      Posicion Y: " << arrayAsteroides[i].pos_y;
    cout << "      Posicion Masa: " << arrayAsteroides[i].masa;
    cout << "      Velocidad X: " << arrayAsteroides[i].vel_x;
    cout << "      Velocidad Y: " << arrayAsteroides[i].vel_y << endl;
    }