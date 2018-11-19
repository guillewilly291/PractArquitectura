
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

asteroides *nasteroidSeq(int, int);
planetas *createPlanet(int, int);

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

    

    asteroides * arrayAsteroides;
    planetas *arrayPlanetas;

    arrayAsteroides = nasteroidSeq(num_asteroides,seed);
    cout << "Masa de prueba Asteroide = " <<  arrayAsteroides[0].masa << endl;

    arrayPlanetas = createPlanet(num_planetas, seed);
    cout << "Masa de prueba Planeta = " << arrayPlanetas[0].masa << endl;

    imprimirArchivoPrincipal(num_asteroides, num_planetas, arrayAsteroides, arrayPlanetas);

    return 0;
}





void imprimirArchivoPrincipal(int num_asteroides, int num_planetas,  asteroides *arrayAsteroides, planetas *arrayPlanetas)
{

    ofstream myfile("init_conf.txt"); //Creamos el archivo al que deseamos enviar las configuraciones de planetas y asteroides

       

    for(int i = 0; i < num_asteroides ; i++){

        myfile << arrayAsteroides[i].pos_x << " " << arrayAsteroides[i].pos_y << " " << arrayAsteroides[i].masa << endl;
                        
    }

    for (int i = 0; i < num_planetas; i++)
    {

        myfile << arrayPlanetas[i].pos_x << " " << arrayPlanetas[i].pos_y <<  endl;
    }

    myfile.close();        
}




asteroides *nasteroidSeq(int num_asteroides, int seed){
    asteroides *devolver;
    asteroides arrayAster[num_asteroides];
    default_random_engine re{seed}; // inicializamos el generador

    for(int i = 0; i < num_asteroides; i++)
    {
        arrayAster[i].pos_x= xdist(re);
        arrayAster[i].pos_y= ydist(re);
        arrayAster[i].masa=mdist(re);
    }

    devolver = arrayAster;



     return devolver;
    
}

planetas *createPlanet( int num_planetas, int seed)
{
    planetas *devolver;
    planetas arrayPlanet[num_planetas];
    default_random_engine re{seed}; // inicializamos el generador

    for (int i = 0; i < num_planetas; i++)
    {
        if(i%4==0) //Eje Izqui
        {
            arrayPlanet[i].pos_x = 0;
            arrayPlanet[i].pos_y = ydist(re);
            arrayPlanet[i].masa = mdist(re) * 10;
        }
        if (i % 4 == 1) //Eje Arriba
        {
            arrayPlanet[i].pos_x = xdist(re);
            arrayPlanet[i].pos_y = 200;
            arrayPlanet[i].masa = mdist(re) * 10;
        }
        if (i % 4 == 2) //Eje Derecha 
        {
            arrayPlanet[i].pos_x = 200;
            arrayPlanet[i].pos_y = ydist(re);
            arrayPlanet[i].masa = mdist(re) * 10;
        }
        if (i % 4 == 3) //Eje Abajo
        {
            arrayPlanet[i].pos_x = xdist(re);
            arrayPlanet[i].pos_y = 0;
            arrayPlanet[i].masa = mdist(re) * 10;
        }
    }

    devolver = arrayPlanet;

    return devolver;
}
