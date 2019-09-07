// C++ implementation of Cocktail Sort 
#include <bits/stdc++.h> 
using namespace std; 
  
// Sorts arrar a[0..n-1] using Cocktail sort 
void cocktailSort(int a[], int n) 
{ 
    bool swapped = true; 
    int start = 0; 
    int end = n - 1; 
  
    while (swapped) { 
        // reset the swapped flag on entering 
        // the loop, because it might be true from 
        // a previous iteration. 
        swapped = false; 
  
        // loop from left to right same as 
        // the bubble sort 
        for (int i = start; i < end; ++i) { 
            if (a[i] > a[i + 1]) { 
                swap(a[i], a[i + 1]); 
                swapped = true; 
            } 
        } 
  
        // if nothing moved, then array is sorted. 
        if (!swapped) 
            break; 
  
        // otherwise, reset the swapped flag so that it 
        // can be used in the next stage 
        swapped = false; 
  
        // move the end point back by one, because 
        // item at the end is in its rightful spot 
        --end; 
  
        // from right to left, doing the 
        // same comparison as in the previous stage 
        for (int i = end - 1; i >= start; --i) { 
            if (a[i] > a[i + 1]) { 
                swap(a[i], a[i + 1]); 
                swapped = true; 
            } 
        } 
  
        // increase the starting point, because 
        // the last stage would have moved the next 
        // smallest number to its rightful spot. 
        ++start; 
    } 
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
		cocktailSort(arreglo, n);
		
		t1 = clock();
		double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
		tiempo = tiempo*1000;
		cout<<" "<<endl;
		//print(arreglo, n);
		cout<< "Tiempo: "<<tiempo<<" milisegundos"<<endl; 
//		imprimir(arreglo, n); //imprime el arreglo ya ordenado
		
}
// This code is contributed by rathbhupendra 

