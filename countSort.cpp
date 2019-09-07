// C++ Program for counting sort  
#include<bits/stdc++.h>  
#include<string.h> 
using namespace std;  
#define RANGE 255  
  
// The main function that sort  
// the given string arr[] in  
// alphabatical order  
void countSort(char arr[])  
{  
    // The output character array  
    // that will have sorted arr  
    char output[strlen(arr)];  
  
    // Create a count array to store count of inidividul  
    // characters and initialize count array as 0  
    int count[RANGE + 1], i;  
    memset(count, 0, sizeof(count));  
  
    // Store count of each character  
    for(i = 0; arr[i]; ++i)  
        ++count[arr[i]];  
  
    // Change count[i] so that count[i] now contains actual  
    // position of this character in output array  
    for (i = 1; i <= RANGE; ++i)  
        count[i] += count[i-1];  
  
    // Build the output character array  
    for (i = 0; arr[i]; ++i)  
    {  
        output[count[arr[i]]-1] = arr[i];  
        --count[arr[i]];  
    }  
  
    /*  
    For Stable algorithm  
    for (i = sizeof(arr)-1; i>=0; --i)  
    {  
        output[count[arr[i]]-1] = arr[i];  
        --count[arr[i]];  
    }  
      
    For Logic : See implementation  
    */
  
    // Copy the output array to arr, so that arr now  
    // contains sorted characters  
    for (i = 0; arr[i]; ++i)  
        arr[i] = output[i];  
}  

int main(int argc, char *argv[]) {


	int n = 10;
	char arreglo[n];
	
	//int random[n];


//esta parte genera valores aleatorios para llenar el arreglo dependiendo de n que es el tamaño del arreglo y lo llena entre valores de 1-100
	srand((unsigned)time(NULL));

		for (int i = 0; i < n; i++) {

		arreglo[i] = 1 + rand() % 100;
//		cout << arreglo[i] << " " ;//imprime el arreglo desordenado
		
	}
	
		unsigned t0,t1;
		t0 = clock();
		countSort(arreglo);
		
		t1 = clock();
		double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
		tiempo = tiempo*1000;
		cout<<" "<<endl;
		//print(arreglo, n);
		cout<< "Tiempo: "<<tiempo<<" milisegundos"<<endl; 
//		imprimir(arreglo, n); //imprime el arreglo ya ordenado
		
}
// This code is contributed by rathbhupendra 
