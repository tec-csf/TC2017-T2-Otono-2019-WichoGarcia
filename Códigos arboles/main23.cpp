#include <iostream>
#include "ArbolDosTres.h"
#include <fstream>
#include<ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{

    ArbolDosTres<int> nuevoArbol;
    int tam;
    ifstream archivo;

    archivo.open("100000.txt");
    archivo >> tam;

    for (int i=0; i<tam; i++)
    {
        int nuevoDato;
        archivo >> nuevoDato;
        nuevoArbol.insertar23(nuevoDato);
    }

    cout << "Se terminó de insertar" << endl;
    int n = 10;
    int aBuscar[n] ;
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double> tiempo;
    
    for(int i =0;i<n;i++){
        aBuscar[i]= 1 + rand() % 100000;
    }

    for(int i=0; i<10; i++)
    {
        cout << "Buscando elemento: " << aBuscar[i] << endl;
        t1 = high_resolution_clock::now();
        nuevoArbol.buscar(aBuscar[i]);
        t2 = high_resolution_clock::now();
        tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;

    }
    return 0;
}
