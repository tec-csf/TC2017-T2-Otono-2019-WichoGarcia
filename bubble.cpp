// C++ program for implementation of Bubble sort 
#include <bits/stdc++.h> 
using namespace std; 

void swap(int *xp, int *yp) 
{ 
	int temp = *xp; 
	*xp = *yp; 
	*yp = temp; 
} 

// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
	int i, j; 
	for (i = 0; i < n-1; i++)	 
	
	// Last i elements are already in place 
	for (j = 0; j < n-i-1; j++) 
		if (arr[j] > arr[j+1]) 
			swap(&arr[j], &arr[j+1]); 
} 

/* Function to print an array 
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) 
		cout << arr[i] << " "; 
	cout << endl; 
} 
*/
// Driver code 


void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
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
		bubbleSort(arreglo, n);
		
		t1 = clock();
		double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
		tiempo = tiempo*1000;
		cout<<" "<<endl;
		//print(arreglo, n);
		cout<< "Tiempo: "<<tiempo<<" milisegundos"<<endl; 
//		imprimir(arreglo, n); //imprime el arreglo ya ordenado
		
}
// This code is contributed by rathbhupendra 

