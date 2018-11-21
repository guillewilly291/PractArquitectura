
#include <fstream>  //escribir en un archivo
#include <iostream> //basica
#include <random>   //numeros aleatorios

using namespace std; // para evitar tener que poner std::cout cada vez que se quiera imprimir

class asteroides
{
  public:
    double pos_x;
    double pos_y;
    double masa;
};
class planetas
{
  public:
    double pos_x;
    double pos_y;
    double masa;
};

asteroides *createAsteroid(asteroides *arrayAsteroides, int, int);
planetas *createPlanet(planetas *arrayAsteroides, int, int);

double calculateDistance(asteroides, asteroides);
double calculateDistance(asteroides, planetas);
double calculateDistance(planetas, asteroides);
double calculateDistance(planetas, planetas);
double **tablaDeFuerzas(int num_asteroides, int num_planetas);

int calcParameters(int seed);
uniform_real_distribution<double> xdist{0.0, std::nextafter(200, std ::numeric_limits<double>::max())};
uniform_real_distribution<double> ydist{0.0, std::nextafter(200, std ::numeric_limits<double>::max())};
normal_distribution<double> mdist{1000, 50};

int main(int argc, char const *argv[])
{

    int num_asteroides, num_iteraciones, num_planetas, seed;

    /* Para ejecutar el programa como es debido se añade esto y se elimina lo de abajo, si seguimos para poder probar y tal usamos de momento lo dee abajo */
    /*  num_asteroides = atoi(argv[1]);//atoi es para pasar de string a numero
    num_iteraciones =atoi(argv[2]);
    num_planetas  = atoi(argv[3]);
    seed  = atoi(argv[4]);
*/
    num_asteroides = 3; //atoi es para pasar de string a numero
    num_iteraciones = 3;
    num_planetas = 3;
    seed = 3;
    argc=5;

    if (num_asteroides < 0 || num_planetas < 0 || num_iteraciones < 0 || seed < 0 || argc < 5)
    {

        cout << "nasteroids-seq: Wrong arguments.\n"
             << "Correct use :\n"
             << "nasteroids - seq num_asteroides num_iteraciones num_planetas semilla " << endl;

        return -1;
    }

    asteroides *arrayAsteroides = (asteroides *)malloc(num_asteroides * sizeof(asteroides)); //reservamos la memoria necesaria para cada array( que será igual a lo que ocuppa un
    planetas *arrayPlanetas = (planetas *)malloc(num_planetas * sizeof(planetas));           //aster/planeta * losque haya)

    arrayAsteroides = createAsteroid(arrayAsteroides, num_asteroides, seed);
    arrayPlanetas = createPlanet(arrayPlanetas, num_planetas, seed);

    ofstream myfile("init_conf.txt"); //Creamos el archivo al que deseamos enviar las configuraciones de planetas y asteroides

    double **matrizFuerzas;
        
    matrizFuerzas=tablaDeFuerzas(3,3);

    cout << "ESTO ES : " << matrizFuerzas[2][3];
        for (int i = 1; i < argc; i++)
    {
        myfile << argv[i] << " ";
    }

    myfile << endl;

    for (int i = 0; i < num_asteroides; i++)
    {
        myfile << arrayAsteroides[i].pos_x << " " << arrayAsteroides[i].pos_y << " " << arrayAsteroides[i].masa << endl;
    }

    for (int i = 0; i < num_planetas; i++)
    {
        myfile << arrayPlanetas[i].pos_x << " " << arrayPlanetas[i].pos_y << endl;
    }
    myfile.close();

    return 0;
}

asteroides *createAsteroid(asteroides *arrayAsteroides, int num_asteroides, int seed)
{
    default_random_engine re{seed}; // inicializamos el generador

    for (int i = 0; i < num_asteroides; i++)
    {
        arrayAsteroides[i].pos_x = xdist(re);
        arrayAsteroides[i].pos_y = ydist(re);
        arrayAsteroides[i].masa = mdist(re);
    }

    return arrayAsteroides;
}

planetas *createPlanet(planetas *arrayPlanetas, int num_planetas, int seed)
{

    default_random_engine re{seed}; // inicializamos el generador

    for (int i = 0; i < num_planetas; i++)
    {
        if (i % 4 == 0) //Eje Izqui
        {
            arrayPlanetas[i].pos_x = 0;
            arrayPlanetas[i].pos_y = ydist(re);
            arrayPlanetas[i].masa = mdist(re) * 10;
        }
        if (i % 4 == 1) //Eje Arriba
        {
            arrayPlanetas[i].pos_x = xdist(re);
            arrayPlanetas[i].pos_y = 200;
            arrayPlanetas[i].masa = mdist(re) * 10;
        }
        if (i % 4 == 2) //Eje Derecha
        {
            arrayPlanetas[i].pos_x = 200;
            arrayPlanetas[i].pos_y = ydist(re);
            arrayPlanetas[i].masa = mdist(re) * 10;
        }
        if (i % 4 == 3) //Eje Abajo
        {
            arrayPlanetas[i].pos_x = xdist(re);
            arrayPlanetas[i].pos_y = 0;
            arrayPlanetas[i].masa = mdist(re) * 10;
        }
    }

    return arrayPlanetas;
}

double **tablaDeFuerzas(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides)
{

    int cuerposTotales = num_asteroides + num_planetas;
    double **tablaF;
        //double tablaF[cuerposTotales][cuerposTotales];
    tablaF = new double *[cuerposTotales];
    for (int i = 0; i < cuerposTotales; i++)
    {
        tablaF[i] = new double[cuerposTotales];
    }

    cout << "Elementos de la Matriz con sus direcciones: " << endl;
    for (int i = 0; i < cuerposTotales; i++)
    {
        for (int j = i + 1; j < cuerposTotales; j++)
        {
            if (i == j)
            {
                tablaF[i][j] = 0; //la fuerza que ejerce un cuerpo sobre si mismo es 0.
            }
            else
            {

                if(i< num_asteroides && j < num_asteroides){

                    tablaF[i][j] = calculateDistance(arrayAsteroides[i], arrayAsteroides[j]); //en el nueve hay que poner el resultado de la fuerza
                    tablaF[j][i] = -calculateDistance(arrayAsteroides[i], arrayAsteroides[j]); //la fuerza que hace j sobre i es la inversa que la que ejerce i sobre j

                }else if(i< num_asteroides && j > num_asteroides){

                    tablaF[i][j] = calculateDistance(arrayAsteroides[i], arrayPlanetas[j]);  
                    tablaF[j][i] = -calculateDistance(arrayAsteroides[i], arrayPlanetas[j]); 

                }else if(i > num_asteroides && j < num_asteroides){

                    tablaF[i][j] = calculateDistance(arrayPlanetas[i], arrayAsteroides[j]);
                    tablaF[j][i] = -calculateDistance(arrayPlanetas[i] , arrayAsteroides[j]);
                }else{

                    tablaF[i][j] = calculateDistance(arrayPlanetas[i], arrayPlanetas[j]);
                    tablaF[j][i] = -calculateDistance(arrayPlanetas[i], arrayPlanetas[j]);
                }
               
            }
        }
        
    }
        for(int i = 0; i < cuerposTotales; i++)
        {
            
            for(int j = 0; j < cuerposTotales; j++)
            {
                cout<<tablaF[i][j];
            }
            cout<<""<<endl;
        }
        
    return tablaF;
}


double calculateDistance(asteroides cuerpo1, asteroides cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double sqrtResult = sqrt((xPow + yPow));               //sqrt(base)-> (xPow+yPow)^1/2
    return sqrtResult;
    }
double calculateDistance(asteroides cuerpo1, planetas cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double sqrtResult = sqrt((xPow + yPow));               //sqrt(base)-> (xPow+yPow)^1/2
    return sqrtResult;
}
double calculateDistance(planetas cuerpo1, asteroides cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double sqrtResult = sqrt((xPow + yPow));               //sqrt(base)-> (xPow+yPow)^1/2
    return sqrtResult;
}
double calculateDistance(planetas cuerpo1, planetas cuerpo2)
{ //distancia de cuerpo1 a cuerpo2

    double xPow = pow((cuerpo1.pos_x - cuerpo2.pos_x), 2); //pow(base,exponente)-> (x1-x2)^2
    double yPow = pow((cuerpo1.pos_y - cuerpo2.pos_y), 2); //pow(base,exponente)-> (y1-y2)^2
    double sqrtResult = sqrt((xPow + yPow));               //sqrt(base)-> (xPow+yPow)^1/2
    return sqrtResult;
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

                   