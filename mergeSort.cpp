/* C program for Merge Sort */
#include<stdlib.h> 
#include<stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 
  
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
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
		mergeSort(arreglo,0 , n-1);
		
		t1 = clock();
		double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
		tiempo = tiempo*1000;
		cout<<" "<<endl;
		//print(arreglo, n);
		cout<< "Tiempo: "<<tiempo<<" milisegundos"<<endl; 
//		imprimir(arreglo, n); //imprime el arreglo ya ordenado
		
}
// This code is contributed by rathbhupendra 
