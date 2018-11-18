#include <iostream>
#include <random>

using namespace std; // para evitar tener que poner std::cout cada vez que se quiera imprimir


int nasteroidSeq(int num_asteroides, int num_iteraciones, int num_planetas, int seed);
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

int main()
{
    int num_asteroides, num_iteraciones, num_planetas, seed;
    cout<< "Introduzca el numero de asteroides"<<endl;
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

    nasteroidSeq(num_asteroides, num_iteraciones, num_planetas, seed);
    return 0;
    
}


int nasteroidSeq(int num_asteroides, int num_iteraciones, int num_planetas, int seed){
    asteroides arrayAster[num_asteroides];
    default_random_engine re{seed};// inicializamos el generador
    for(int i = 0; i < num_asteroides; i++)
    {
        arrayAster[i].pos_x= xdist(re);
        arrayAster[i].pos_y= ydist(re);
        arrayAster[i].masa=mdist(re);
    }
    
}

