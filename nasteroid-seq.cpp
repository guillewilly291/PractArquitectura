
#include <fstream>
#include <iostream>
#include <random>

using namespace std; // para evitar tener que poner std::cout cada vez que se quiera imprimir



int calcParameters(int seed);
uniform_real_distribution<double> xdist{0.0, std::nextafter(200,
                                                            std ::numeric_limits<double>::max())};
uniform_real_distribution<double> ydist{0.0, std::nextafter(200,
                                                            std ::numeric_limits<double>::max())};
normal_distribution<double> mdist{1000, 50};



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

int main(int argc, char const *argv[])
{
    
    int num_asteroides, num_iteraciones, num_planetas, seed;

    /* Para ejecutar el programa como es debido se añade esto y se elimina lo de abajo, si seguimos para poder probar y tal usamos de momento lo dee abajo */
    num_asteroides = atoi(argv[1]);
    num_iteraciones  = atoi(argv[2]);
    num_planetas  = atoi(argv[3]);
    seed  = atoi(argv[4]);

    if (num_asteroides < 0 || num_planetas < 0 || num_iteraciones < 0 || seed < 0)
    {

        cout << "nasteroids-seq: Wrong arguments.\n"
             << "Correct use :\n"
             << "nasteroids - seq num_asteroides num_iteraciones num_planetas semilla " << endl;

        return -1;
    }


 /*   fstream archivo; Prueba de momento seguir investigando 

    archivo.open("init_conf.txt");

    archivo << num_asteroides ;

    archivo.close();

    */

                       /*
    cout << "Introduzca el numero de asteroides " << endl;
    cin >> num_asteroides;
    while(num_asteroides<0){
        cout<< "El numero de asteroides debe ser mayor que 0";
        cin >> num_asteroides;
    }
    cout << "Introduzca el numero de iteraciones" << endl;
    cin >> num_iteraciones;
    while (num_iteraciones < 0)
    {
        cout << "El numero de iteraciones debe ser mayor que 0";
        cin >> num_iteraciones;
    }
    
    cout << "Introduzca el numero de planetas" << endl;
    cin >> num_planetas;
    while (num_planetas < 0)
    {
        cout << "El numero de planetas debe ser mayor que 0";
        cin>> num_planetas;
    }
    cout << "Introduzca el numero de semilla" << endl;
    cin >> seed;
 */

                       asteroides *
                   arrayAsteroides;
    planetas *arrayPlanetas;

    arrayAsteroides = nasteroidSeq(num_asteroides,seed);
    cout << "Masa de prueba Asteroide = " <<  arrayAsteroides[0].masa << endl;

    arrayPlanetas = createPlanet(num_planetas, seed);
    cout << "Masa de prueba Planeta = " << arrayPlanetas[0].masa << endl;
    return 0;
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
