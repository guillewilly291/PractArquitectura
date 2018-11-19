
#include <fstream> //escribir en un archivo 
#include <iostream> //basica
#include <random> //numeros aleatorios

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

asteroides *createAsteroid(asteroides *arrayAsteroides,int, int);
planetas *createPlanet(planetas *arrayAsteroides,int, int);

void imprimirArchivoPrincipal(int num_asteroides, int num_planetas, asteroides *arrayAsteroides, planetas *arrayPlanetas);

int calcParameters(int seed);
uniform_real_distribution<double> xdist{0.0, std::nextafter(200,std ::numeric_limits<double>::max())};
uniform_real_distribution<double> ydist{0.0, std::nextafter(200,std ::numeric_limits<double>::max())};
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

    cout << "Asteroides" << num_asteroides << endl;
    cout << num_iteraciones << endl;
    cout << num_planetas << endl;
    cout << seed << endl;

    if (num_asteroides < 0 || num_planetas < 0 || num_iteraciones < 0 || seed < 0)

    {

        cout << "nasteroids-seq: Wrong arguments.\n"
             << "Correct use :\n"
             << "nasteroids - seq num_asteroides num_iteraciones num_planetas semilla " << endl;

        return -1;
    }

    

    asteroides *arrayAsteroides=(asteroides*)malloc(4*24);
    planetas *arrayPlanetas=(planetas*)malloc(4*24);

    arrayAsteroides = createAsteroid(arrayAsteroides,num_asteroides, seed);
    arrayPlanetas = createPlanet(arrayPlanetas,num_planetas, seed);

    ofstream myfile("init_conf.txt"); //Creamos el archivo al que deseamos enviar las configuraciones de planetas y asteroides

    for(int i = 0 ; i < argc ; i++)
    {
        myfile << argv[i] << " " ; 
    }

    cout << endl;

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

asteroides *createAsteroid(asteroides *arrayAsteroides,int num_asteroides, int seed)
{
    default_random_engine re{seed}; // inicializamos el generador

    for(int i = 0; i < num_asteroides; i++)
    {
        arrayAsteroides[i].pos_x= xdist(re);
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
        if(i%4==0) //Eje Izqui
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
