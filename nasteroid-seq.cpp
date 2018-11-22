
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
    double vel_x=0.0; 
    double vel_y=0.0;    
};
class planetas
{
  public:
    double pos_x;
    double pos_y;
    double masa;
        
};

const double gravity = pow(6.674 ,-5); 
const double Intervalotiempo = 0.1;  
asteroides *createAsteroid(asteroides *arrayAsteroides, int, int);
planetas *createPlanet(planetas *arrayAsteroides, int, int);

double calculateDistance(asteroides, asteroides);
double calculateDistance(asteroides, planetas);
double calculateDistance(planetas, asteroides);
double calculateDistance(planetas, planetas);

double calculateMovNormal(planetas cuerpo1, planetas cuerpo2);
double calculateMovNormal(planetas cuerpo1, asteroides cuerpo2);
double calculateMovNormal(asteroides cuerpo1, planetas cuerpo2);
double calculateMovNormal(asteroides cuerpo1, asteroides cuerpo2);

double **tablaDeFuerzasX(int num_asteroides, int num_planetas, planetas *, asteroides *);
double **tablaDeFuerzasY(int num_asteroides, int num_planetas, planetas *, asteroides *);

void calculateVelocidad(int num_asteroides, int num_planetas, double **matrizFuerzasX, double **matrizFuerzasY, asteroides *arrayAsteroides);

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
    num_iteraciones = 500;
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

    double **matrizFuerzasX;

    double **matrizFuerzasY;

    matrizFuerzasX = tablaDeFuerzasX(num_asteroides, num_planetas, arrayPlanetas , arrayAsteroides);

    matrizFuerzasY = tablaDeFuerzasY(num_asteroides, num_planetas, arrayPlanetas, arrayAsteroides);
    
    cout << "Fuerzas Matriz X: "<< endl;
    for (int i = 0; i < num_asteroides+num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzasX[i][j] << " ";
        }
        cout << "" << endl;
    }

    cout << "Fuerzas Matriz Y: " << endl;
    for (int i = 0; i < num_asteroides + num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzasY[i][j] << " ";
        }
        cout << "" << endl;
    }

    cout << "Asteroides con sus posiciones inicial: " << endl;
    for(int i = 0 ; i < num_asteroides ; i ++){
            cout << "  Asteroide " << i << ":";
            cout << "  Posicion X: " << arrayAsteroides[i].pos_x;
            cout << "  Posicion Y: " << arrayAsteroides[i].pos_y;
            cout << "  Posicion Masa: " << arrayAsteroides[i].masa;
            cout << "  Velocidad X: " << arrayAsteroides[i].vel_x;
            cout << "  Velocidad Y " << arrayAsteroides[i].vel_y << endl;
            
    }

    for(int i = 0 ; i < 3 ; i++){ //BUucle que realiza las X iteraciones cambiando las fuerzas y las posiciones de los asteroides.
        calculateVelocidad(num_asteroides, num_planetas, matrizFuerzasX, matrizFuerzasY, arrayAsteroides);
        matrizFuerzasX = tablaDeFuerzasX(3, 3, arrayPlanetas, arrayAsteroides);
        matrizFuerzasY = tablaDeFuerzasY(3, 3, arrayPlanetas, arrayAsteroides);
     
    }

    cout << "Fuerzas Matriz X despues : " << endl;
    for (int i = 0; i < num_asteroides + num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzasX[i][j] << " ";
        }
        cout << "" << endl;
    }

    cout << "Fuerzas Matriz Y despues: " << endl;
    for (int i = 0; i < num_asteroides + num_planetas; i++)
    {

        for (int j = 0; j < num_asteroides + num_planetas; j++)
        {
            cout << matrizFuerzasY[i][j] << " ";
        }
        cout << "" << endl;
    }

    cout << "  Asteroides con sus posiciones Finales"   << endl;
    for (int i = 0; i < num_asteroides; i++)
    {

        cout << "      Asteroide " << i << ":";
        cout << "      Posicion X: " << arrayAsteroides[i].pos_x;
        cout << "      Posicion Y: " << arrayAsteroides[i].pos_y;
        cout << "      Posicion Masa: " << arrayAsteroides[i].masa;
        cout << "      Velocidad X: " << arrayAsteroides[i].vel_x;
        cout << "      Velocidad Y " << arrayAsteroides[i].vel_y << endl;
    }


    /*  for (int i = 1; i < argc; i++)
    {
        myfile << argv[i] << " ";
    }
  */

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

double **tablaDeFuerzasX(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides)
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
        tablaFx[i][i]=0;//diagonal
        for (int j = i + 1; j < cuerposTotales; j++)
        {

                if(i< num_asteroides && j < num_asteroides){
                    tablaFx[i][j] = (gravity * arrayAsteroides[i].masa * arrayAsteroides[j].masa) / calculateDistance(arrayAsteroides[i], arrayAsteroides[j]);  
                    tablaFx[i][j] *= cos(calculateMovNormal(arrayAsteroides[i],arrayAsteroides[j]));
                    
                }else if(i< num_asteroides && j >= num_asteroides){
                    tablaFx[i][j] = (gravity * arrayAsteroides[i].masa * arrayPlanetas[j - num_asteroides].masa) / calculateDistance(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]);
                    tablaFx[i][j] *= cos(calculateMovNormal(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]));                    
                    

                }else if(i >= num_asteroides && j < num_asteroides){
                    tablaFx[i][j] = (gravity * arrayPlanetas[i - num_asteroides].masa * arrayAsteroides[j].masa) / calculateDistance(arrayPlanetas[i - num_asteroides], arrayAsteroides[j]);
                    tablaFx[i][j] *= cos(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayAsteroides[j] ));
                   
                }else{
                    tablaFx[i][j] = (gravity * arrayPlanetas[i - num_asteroides].masa * arrayPlanetas[j - num_asteroides].masa) / calculateDistance(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]);
                    tablaFx[i][j] *= cos(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]));
                    
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

double **tablaDeFuerzasY(int num_asteroides, int num_planetas, planetas *arrayPlanetas, asteroides *arrayAsteroides)
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
                tablaFy[i][j] = (gravity * arrayAsteroides[i].masa * arrayAsteroides[j].masa) / calculateDistance(arrayAsteroides[i], arrayAsteroides[j]);
                tablaFy[i][j] *= sin(calculateMovNormal(arrayAsteroides[i], arrayAsteroides[j]));       
               
            }
            else if (i < num_asteroides && j >= num_asteroides)
            {
                tablaFy[i][j] = (gravity * arrayAsteroides[i].masa * arrayPlanetas[j - num_asteroides].masa) / calculateDistance(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]);
                tablaFy[i][j] *= sin(calculateMovNormal(arrayAsteroides[i], arrayPlanetas[j - num_asteroides]));
                
            }
            else if (i >= num_asteroides && j < num_asteroides)
            {
                tablaFy[i][j] = (gravity * arrayPlanetas[i - num_asteroides].masa * arrayAsteroides[j].masa) / calculateDistance(arrayPlanetas[i - num_asteroides], arrayAsteroides[j]);
                tablaFy[i][j] *= sin(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayAsteroides[j]));
               
            }
            else
            {
                tablaFy[i][j] = (gravity * arrayPlanetas[i - num_asteroides].masa * arrayPlanetas[j - num_asteroides].masa) / calculateDistance(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]);
                tablaFy[i][j] *= sin(calculateMovNormal(arrayPlanetas[i - num_asteroides], arrayPlanetas[j - num_asteroides]));
               
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

void calculateVelocidad(int num_asteroides, int num_planetas, double **matrizFuerzasX, double **matrizFuerzasY, asteroides *arrayAsteroides)
{
    int tamano = num_asteroides+num_planetas;   
    double accel_x=0.0;
    double accel_y = 0.0;
    double sumatorio_Fx = 0.0;
    double sumatorio_Fy = 0.0;
    double velocidad_x = 0.0;
    double velocidad_y = 0.0;
    double posicion_x = 0.0;
    double posicion_y = 0.0;

   

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

        arrayAsteroides[i].vel_x += (accel_x * Intervalotiempo);
        arrayAsteroides[i].vel_y += (accel_y * Intervalotiempo);
        arrayAsteroides[i].pos_x += (arrayAsteroides[i].vel_x * Intervalotiempo);
        arrayAsteroides[i].pos_y += (arrayAsteroides[i].vel_y * Intervalotiempo);
    }
    
    
}
