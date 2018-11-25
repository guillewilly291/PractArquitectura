
#include <fstream>  //escribir en un archivo
#include <iostream> //basica
#include <random>   //numeros aleatorios
#include <math.h>
#include <iomanip> //setPrecis
#include <omp.h>   //Libreria OpenMP

using namespace std; // para evitar tener que poner std::cout cada vez que se quiera imprimir

class asteroides
{
  public:
    double pos_x;
    double pos_y;
    double masa;
    double vel_x = 0.0;
    double vel_y = 0.0;
};
class planetas
{
  public:
    double pos_x;
    double pos_y;
    double masa;
};
int contador = 0;
const double gravity = 6.674 * pow(10, -5);
const double Intervalotiempo = 0.1;
const double width = 200.0;
const double height = 200.0;
const double media = 1000;
const double desviacion = 50;
const string StepByStep = "step_by_step.txt";

double calculateDistanceAlCuadrado(asteroides, asteroides);
double calculateDistanceAlCuadrado(asteroides, planetas);
double calculateDistanceAlCuadrado(planetas, asteroides);
double calculateDistanceAlCuadrado(planetas, planetas);

double calculateMovNormal(planetas cuerpo1, planetas cuerpo2);
double calculateMovNormal(planetas cuerpo1, asteroides cuerpo2);
double calculateMovNormal(asteroides cuerpo1, planetas cuerpo2);
double calculateMovNormal(asteroides cuerpo1, asteroides cuerpo2);

double **tablaDeFuerzasX(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides, double **matrizFuerzas);
double **tablaDeFuerzasY(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides, double **matrizFuerzas);
double **tablaDeFuerzas(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides);

void calculateVelocidad(int num_asteroides, int num_planetas, double **matrizFuerzasX, double **matrizFuerzasY, asteroides *arrayAsteroides);
void calcularRebote(asteroides cuerpo);
void imprimirMatrices(int num_asteroides, int num_planetas, asteroides *arrayAsteroides, double **matrizFuerzas, planetas *, int i);

void calculateRebotesParedes(asteroides *, int);
void calcularRebotesAsteroides(asteroides *, int);

int calcParameters(int seed);
uniform_real_distribution<double> xdist{0.0, std::nextafter(width, std ::numeric_limits<double>::max())};
uniform_real_distribution<double> ydist{0.0, std::nextafter(height, std ::numeric_limits<double>::max())};
normal_distribution<double> mdist{media, desviacion};

int main(int argc, char const *argv[])
{

    int num_asteroides, num_iteraciones, num_planetas, seed;

    /* Para ejecutar el programa como es debido se añade esto y se elimina lo de abajo, si seguimos para poder probar y tal usamos de momento lo dee abajo */
    /*  num_asteroides = atoi(argv[1]);//atoi es para pasar de string a numero
    num_iteraciones =atoi(argv[2]);
    num_planetas  = atoi(argv[3]);
    seed  = atoi(argv[4]);
*/
    num_asteroides = 500; //atoi es para pasar de string a numero
    num_iteraciones = 200;
    num_planetas = 500;
    seed = 3;
    argc = 5;
    default_random_engine re{seed}; // inicializamos el generador

    if (num_asteroides < 0 || num_planetas < 0 || num_iteraciones < 0 || seed < 0 || argc < 5)
    {

        cout << "nasteroids-seq: Wrong arguments.\n"
             << "Correct use :\n"
             << "nasteroids - seq num_asteroides num_iteraciones num_planetas semilla " << endl;

        return -1;
    }

    asteroides *arrayAsteroides = (asteroides *)malloc(num_asteroides * sizeof(asteroides)); //reservamos la memoria necesaria para cada array( que será igual a lo que ocuppa un
    planetas *arrayPlanetas = (planetas *)malloc(num_planetas * sizeof(planetas));           //aster/planeta * losque haya)

    //INICIALIZAMOS LOS ASTEROIDES
    for (int i = 0; i < num_asteroides; i++)
    {
        arrayAsteroides[i].pos_x = xdist(re);
        arrayAsteroides[i].pos_y = ydist(re);
        arrayAsteroides[i].masa = mdist(re);
        arrayAsteroides[i].vel_x = 0.0;
        arrayAsteroides[i].vel_y = 0.0;
    }
    //INICIALIZAMOS LOS PLANETAS
    for (int i = 0; i < num_planetas; i++)
    {
        if (i % 4 == 0) //Eje Izqui
        {
            arrayPlanetas[i].pos_x = 0;
            arrayPlanetas[i].pos_y = ydist(re);
        }
        if (i % 4 == 1) //Eje Arriba
        {
            arrayPlanetas[i].pos_x = xdist(re);
            arrayPlanetas[i].pos_y = 0;
        }
        if (i % 4 == 2) //Eje Derecha
        {
            arrayPlanetas[i].pos_x = width;
            arrayPlanetas[i].pos_y = ydist(re);
        }
        if (i % 4 == 3) //Eje Abajo
        {
            arrayPlanetas[i].pos_x = xdist(re);
            arrayPlanetas[i].pos_y = height;
        }
        arrayPlanetas[i].masa = mdist(re) * 10;
    }

    ofstream myfile("init_conf.txt"); //Creamos el archivo al que deseamos enviar las configuraciones de planetas y asteroides

    /*
     for (int i = 1; i < argc; i++)
    {
        myfile << argv[i] << " ";
    }
   */

    myfile << endl;

    for (int i = 0; i < num_asteroides; i++)
    {
        myfile << fixed << std::setprecision(3) << arrayAsteroides[i].pos_x << " " << arrayAsteroides[i].pos_y << " " << arrayAsteroides[i].masa << endl;
    }

    for (int i = 0; i < num_planetas; i++)
    {
        myfile << fixed << std::setprecision(3) << arrayPlanetas[i].pos_x << " " << arrayPlanetas[i].pos_y << " " << arrayPlanetas[i].masa << endl;
    }

    double **matrizFuerzas;

    double **matrizFuerzasX;

    double **matrizFuerzasY;

    matrizFuerzas = tablaDeFuerzas(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides);

    matrizFuerzasX = tablaDeFuerzasX(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides, matrizFuerzas);

    matrizFuerzasY = tablaDeFuerzasY(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides, matrizFuerzas);

    for (int i = 1; i < num_iteraciones; i++)
    { //Bucle que realiza las X iteraciones cambiando las fuerzas y las posiciones de los asteroides.
        calculateVelocidad(num_asteroides, num_planetas, matrizFuerzasX, matrizFuerzasY, arrayAsteroides);
        matrizFuerzas = tablaDeFuerzas(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides);
        matrizFuerzasX = tablaDeFuerzasX(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides, matrizFuerzas);
        matrizFuerzasY = tablaDeFuerzasY(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides, matrizFuerzas);

        imprimirMatrices(num_asteroides, num_planetas, arrayAsteroides, matrizFuerzas, arrayPlanetas, i);
    }

    ofstream outFile("out.txt");

    for (int i = 0; i < num_asteroides; i++)
    {

        outFile << fixed << std::setprecision(3) << arrayAsteroides[i].pos_x << " " << arrayAsteroides[i].pos_y << " " << arrayAsteroides[i].vel_x << " " << arrayAsteroides[i].vel_y << " " << arrayAsteroides[i].masa << endl;
    }
    outFile << endl;
    myfile.close();
    outFile.close();

    return 0;
}

double **tablaDeFuerzas(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides)
{

    int cuerposTotales = num_asteroides + num_planetas;
    double **tablaFx;
    double distancia, distanciaCuadrado;
    tablaFx = new double *[cuerposTotales];
    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaFx[i] = new double[cuerposTotales];
    }

    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaFx[i][i] = 0; //diagonal
        for (int j = i + 1; j < cuerposTotales; j++)
        {

            if (i < num_asteroides && j < num_asteroides)
            {
                distanciaCuadrado = calculateDistanceAlCuadrado(arrayAsteroides[i], arrayAsteroides[j]);
                distancia = sqrt(distanciaCuadrado);
                if (distancia <= 2)
                {
                    tablaFx[i][j] = 0;
                }
                else
                {
                    tablaFx[i][j] = (gravity * arrayAsteroides[i].masa * arrayAsteroides[j].masa) / distanciaCuadrado;
                }
            }
            else if (i < num_asteroides && j >= num_asteroides)
            {
                distanciaCuadrado = calculateDistanceAlCuadrado(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]);
                distancia = sqrt(distanciaCuadrado);
                if (distancia <= 2)
                { //si la distancia es menor que 2, hay rebote por lo que la fuerza de atraccion es 0
                    tablaFx[i][j] = 0;
                }
                else
                {
                    tablaFx[i][j] = (gravity * arrayAsteroides[i].masa * arrayPlanetas[j - num_asteroides].masa) / distanciaCuadrado;
                }
            }
            else if (i >= num_asteroides && j < num_asteroides)
            {
                distanciaCuadrado = calculateDistanceAlCuadrado(arrayPlanetas[i - num_asteroides], arrayAsteroides[j]);
                distancia = sqrt(distanciaCuadrado);
                if (distancia <= 2)
                {
                    tablaFx[i][j] = 0;
                }
                else
                {
                    tablaFx[i][j] = (gravity * arrayPlanetas[i - num_asteroides].masa * arrayAsteroides[j].masa) / distanciaCuadrado;
                }
            }
            else
            {
                distanciaCuadrado = calculateDistanceAlCuadrado(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]);
                distancia = sqrt(distanciaCuadrado);
                if (distancia <= 2)
                {
                    tablaFx[i][j] = 0;
                }
                else
                {
                    tablaFx[i][j] = (gravity * arrayPlanetas[i - num_asteroides].masa * arrayPlanetas[j - num_asteroides].masa) / distanciaCuadrado;
                }
            }

            if (tablaFx[i][j] > 200)
            {
                tablaFx[i][j] = 200;
            }
            tablaFx[j][i] = -tablaFx[i][j]; //la fuerza que hace j sobre i es la inversa que la que ejerce i sobre j
        }
    }
    return tablaFx;
}

double **tablaDeFuerzasX(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides, double **matrizFuerzas)
{

    int cuerposTotales = num_asteroides + num_planetas;
    double **tablaFx;
    //double tablaF[cuerposTotales][cuerposTotales];
    tablaFx = new double *[cuerposTotales];
    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaFx[i] = new double[cuerposTotales];
    }

    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaFx[i][i] = 0; //diagonal
        for (int j = i + 1; j < cuerposTotales; j++)
        {

            if (i < num_asteroides && j < num_asteroides)
            {
                double a = cos(calculateMovNormal(arrayAsteroides[i], arrayAsteroides[j]));
                tablaFx[i][j] = matrizFuerzas[i][j] * a;
            }
            else if (i < num_asteroides && j >= num_asteroides)
            {
                double a = cos(calculateMovNormal(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]));
                tablaFx[i][j] = matrizFuerzas[i][j] * a;
            }
            else if (i >= num_asteroides && j < num_asteroides)
            {
                double a = cos(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayAsteroides[j]));
                tablaFx[i][j] = matrizFuerzas[i][j] * a;
            }
            else
            {
                double a = cos(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]));
                tablaFx[i][j] = matrizFuerzas[i][j] * a;
            }

            if (tablaFx[i][j] > 200)
            {
                tablaFx[i][j] = 200;
            }
            tablaFx[j][i] = -tablaFx[i][j]; //la fuerza que hace j sobre i es la inversa que la que ejerce i sobre j
        }
    }
    return tablaFx;
}

double **tablaDeFuerzasY(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides, double **matrizFuerzas)
{

    int cuerposTotales = num_asteroides + num_planetas;
    double **tablaFy;
    //double tablaF[cuerposTotales][cuerposTotales];
    tablaFy = new double *[cuerposTotales];
    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaFy[i] = new double[cuerposTotales];
    }

    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaFy[i][i] = 0; //diagonal
        for (int j = i + 1; j < cuerposTotales; j++)
        {
            if (i < num_asteroides && j < num_asteroides)
            {
                double a = sin(calculateMovNormal(arrayAsteroides[i], arrayAsteroides[j]));
                tablaFy[i][j] = matrizFuerzas[i][j] * a;
            }
            else if (i < num_asteroides && j >= num_asteroides)
            {
                double a = sin(calculateMovNormal(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]));
                tablaFy[i][j] = matrizFuerzas[i][j] * a;
            }
            else if (i >= num_asteroides && j < num_asteroides)
            {
                double a = sin(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayAsteroides[j]));
                tablaFy[i][j] = matrizFuerzas[i][j] * a;
            }
            else
            {
                double a = sin(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]));
                tablaFy[i][j] = matrizFuerzas[i][j] * a;
            }
            if (tablaFy[i][j] > 200)
            {
                tablaFy[i][j] = 200;
            }
            tablaFy[j][i] = -tablaFy[i][j]; //la fuerza que hace j sobre i es la inversa que la que ejerce i sobre j
        }
    }
    return tablaFy;
}

double calculateDistanceAlCuadrado(asteroides cuerpo1, asteroides cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double distanciaAlCuadrado = (xPow + yPow);            //sqrt(base)-> (xPow+yPow)^1/2
    return distanciaAlCuadrado;
}
double calculateDistanceAlCuadrado(asteroides cuerpo1, planetas cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double distanciaAlCuadrado = (xPow + yPow);            //sqrt(base)-> (xPow+yPow)^1/2
    return distanciaAlCuadrado;
}
double calculateDistanceAlCuadrado(planetas cuerpo1, asteroides cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double distanciaAlCuadrado = (xPow + yPow);            //sqrt(base)-> (xPow+yPow)^1/2
    return distanciaAlCuadrado;
}
double calculateDistanceAlCuadrado(planetas cuerpo1, planetas cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double distanciaAlCuadrado = (xPow + yPow);            //sqrt(base)-> (xPow+yPow)^1/2
    return distanciaAlCuadrado;
}

double calculateMovNormal(asteroides cuerpo1, asteroides cuerpo2)
{

    double xAxe = cuerpo1.pos_x - cuerpo2.pos_x;
    double yAxe = cuerpo1.pos_y - cuerpo2.pos_y;
    double pendiente = yAxe / xAxe;
    if (pendiente > 1 || pendiente < -1)
    {
        pendiente = pendiente - ((int)(pendiente) / 1);
    }
    double angulo = atan(pendiente);
    return angulo;
}
double calculateMovNormal(asteroides cuerpo1, planetas cuerpo2)
{
    double xAxe = cuerpo1.pos_x - cuerpo2.pos_x;
    double yAxe = cuerpo1.pos_y - cuerpo2.pos_y;
    double pendiente = yAxe / xAxe;
    if (pendiente > 1 || pendiente < -1)
    {
        pendiente = pendiente - ((int)(pendiente) / 1);
    }
    double angulo = atan(pendiente);
    return angulo;
}
double calculateMovNormal(planetas cuerpo1, asteroides cuerpo2)
{
    double xAxe = cuerpo1.pos_x - cuerpo2.pos_x;
    double yAxe = cuerpo1.pos_y - cuerpo2.pos_y;
    double pendiente = yAxe / xAxe;
    if (pendiente > 1 || pendiente < -1)
    {
        pendiente = pendiente - ((int)(pendiente) / 1);
    }
    double angulo = atan(pendiente);
    return angulo;
}
double calculateMovNormal(planetas cuerpo1, planetas cuerpo2)
{

    double xAxe = cuerpo1.pos_x - cuerpo2.pos_x;
    double yAxe = cuerpo1.pos_y - cuerpo2.pos_y;
    double pendiente = yAxe / xAxe;
    if (pendiente > 1 || pendiente < -1)
    {
        pendiente = pendiente - ((int)(pendiente) / 1);
    }
    double angulo = atan(pendiente);
    return angulo;
}

void calculateVelocidad(int num_asteroides, int num_planetas, double **matrizFuerzasX, double **matrizFuerzasY, asteroides *arrayAsteroides)
{
    int size = num_asteroides + num_planetas;
    double accel_x = 0.0;
    double accel_y = 0.0;
    double sumatorio_Fx = 0.0;
    double sumatorio_Fy = 0.0;

    for (int i = 0; i < num_asteroides; i++) //solo se aplica la fuerza a los asteroides
    {
        sumatorio_Fx = 0.0;
        sumatorio_Fy = 0.0;
        for (int j = 0; j < size; j++) //tenemos que recorrer todas las columnas(tanto asteroides como planetas)
        {

            sumatorio_Fx += matrizFuerzasX[i][j];
            sumatorio_Fy += matrizFuerzasY[i][j];
        }

        accel_x = sumatorio_Fx / arrayAsteroides[i].masa; //calculamos la aceleración
        accel_y = sumatorio_Fy / arrayAsteroides[i].masa;

        arrayAsteroides[i].vel_x += (accel_x * Intervalotiempo);
        arrayAsteroides[i].vel_y += (accel_y * Intervalotiempo);
        arrayAsteroides[i].pos_x += (arrayAsteroides[i].vel_x * Intervalotiempo);
        arrayAsteroides[i].pos_y += (arrayAsteroides[i].vel_y * Intervalotiempo);
    }
    calculateRebotesParedes(arrayAsteroides, num_asteroides);
    calcularRebotesAsteroides(arrayAsteroides, num_asteroides);
}

void calculateRebotesParedes(asteroides *arrayAsteroides, int num_asteroides)
{

    for (int i = 0; i < num_asteroides; i++)
    {

        //Calculamos los rebotes con las paredes
        if (arrayAsteroides[i].pos_x <= 0)
        {
            cout << "REBOTE X = 0  "
                 << " : " << i << endl;                           //si el cuerpo se sale por la izquierda
            arrayAsteroides[i].pos_x = 2;                         //posicionamos en x=2
            arrayAsteroides[i].vel_x = -arrayAsteroides[i].vel_x; //cambiamos el sentido de la velocidad
        }
        if (arrayAsteroides[i].pos_x >= width)
        { //si el cuerpo se sale por la derecha
            cout << "REBOTE X=200  "
                 << " : " << i << endl;
            arrayAsteroides[i].pos_x = width - 2;                 //posicionamos en x=198
            arrayAsteroides[i].vel_x = -arrayAsteroides[i].vel_x; //cambiamos el sentido de la velocidad
        }
        if (arrayAsteroides[i].pos_y <= 0)
        { //si el cuerpo se sale por abajo
            cout << "REBOTE Y=0  "
                 << " : " << i << endl;
            arrayAsteroides[i].pos_y = 2;                         //posicionamos en y=2
            arrayAsteroides[i].vel_y = -arrayAsteroides[i].vel_y; //cambiamos el sentido de la velocidad
        }
        if (arrayAsteroides[i].pos_y >= height)
        { //si el cuerpo se sale por abajo
            cout << "REBOTE Y=200  "
                 << " : " << i << endl;
            arrayAsteroides[i].pos_y = height - 2;                //posicionamos en y=198
            arrayAsteroides[i].vel_y = -arrayAsteroides[i].vel_y; //cambiamos el sentido de la velocidad
        }
    }
}

void calcularRebotesAsteroides(asteroides *arrayAsteroides, int num_asteroides)
{
    //CALCULAMOS LOS REBOTES ENTRE ASTEROIDES
    for (int i = 0; i < num_asteroides; i++)
    {

        for (int j = 0; j < num_asteroides; j++)
        {
            double distCuadrado = calculateDistanceAlCuadrado(arrayAsteroides[i], arrayAsteroides[j]);
            double raiz = sqrt(distCuadrado);
            if (raiz <= 2 && (i != j))
            {

                double vel1x, vel1y, vel2x, vel2y;
                vel1x = arrayAsteroides[i].vel_x;
                vel2x = arrayAsteroides[j].vel_x;
                vel1y = arrayAsteroides[i].vel_y;
                vel2y = arrayAsteroides[j].vel_y;
                arrayAsteroides[i].vel_x = vel2x;
                arrayAsteroides[i].vel_y = vel2y;
                arrayAsteroides[j].vel_x = vel1x;
                arrayAsteroides[j].vel_y = vel1y;
            }
        }
    }
}

void imprimirMatrices(int num_asteroides, int num_planetas, asteroides *arrayAsteroides, double **matrizFuerzas, planetas *arrayPlanetas, int i)
{

    ofstream initFile;

    initFile.open(StepByStep, ios::app); // App significará que solo pondremos el texto al final del .txt

    initFile << "Iteración: " << i << endl;
    initFile << "---asteroids vs asteroids---" << endl;

    for (int i = 0; i < num_asteroides; i++)
    {

        for (int j = i + 1; j < num_asteroides; j++)
        {
            if (i != j)
            {
                initFile << "Asteroide: " << i << " Asteroide: " << j << " Valor de la Fuerza: " << matrizFuerzas[i][j] << " Angulo entre ambos: " << calculateMovNormal(arrayAsteroides[i], arrayAsteroides[j]) << endl;
            }
        }
    }
    initFile << "" << endl;
    initFile << "---asteroids vs planets---" << endl;

    for (int i = 0; i < num_asteroides; i++)
    {

        for (int j = i + 1; j < num_asteroides + num_planetas; j++)
        {
            if ((i != j) && (j > num_asteroides - 1))
            {
                initFile << " Asteroide: " << i << " Planeta: " << j - num_asteroides << " Valor de la Fuerza: " << matrizFuerzas[i][j] << " Angulo entre ambos: " << calculateMovNormal(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]) << endl;
            }
        }
    }
    initFile << "" << endl;

    initFile << "*********************ITERATION*********************" << endl;
    initFile.close();
}
