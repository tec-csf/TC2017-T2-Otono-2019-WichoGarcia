#include <iostream>
#include <ctime> 

using namespace std;


int OrdShell(int arreglo[], int p){
	
	for (int gap = p/2; gap>0; gap /= 2) {
		
		for (int i=gap; i<p; i+=1) {
			
			int temporal =arreglo[i];
			int j;
			
			for (j=i;j>=gap && arreglo[j-gap] > temporal; j-=gap) 
			
				arreglo[j] = arreglo[j - gap]; 
				arreglo[j] = temporal;	
		}
	}

	return 0; 
	
}

//Parte es para imprimir el arreglo y ver si funciona el algoritmo 
	void imprimir(int arreglo[], int n) { 
	for (int a=0; a<n; a++) 
		cout << arreglo[a] << " "; 
} 

int main(int argc, char *argv[]) {


	int n = 1000000;
	int arreglo[n];
	
	//int random[n];


//esta parte genera valores aleatorios para llenar el arreglo dependiendo de n que es el tamaño del arreglo y lo llena entre valores de 1-100
	srand((unsigned)time(NULL));

		for (int i = 0; i < n; i++) {

		arreglo[i] = 1 + rand() % 100;
//		cout << arreglo[i] << " " ;//imprime el arreglo desordenado
		
	}
	
		unsigned t0,t1;
		t0 = clock();
		OrdShell(arreglo, n);
		
		t1 = clock();
		double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
		tiempo = tiempo*1000;
		cout<<" "<<endl;
		cout<< "Tiempo: "<<tiempo<<" milisegundos"<<endl; 
		cout << " " << " " ;
//		imprimir(arreglo, n); //imprime el arreglo ya ordenado
		

}
