// C++ program to implement Tree Sort 
#include<bits/stdc++.h> 
  
using namespace std; 
  
struct Node 
{ 
    int key; 
    struct Node *left, *right; 
}; 
  
// A utility function to create a new BST Node 
struct Node *newNode(int item) 
{ 
    struct Node *temp = new Node; 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
// Stores inoder traversal of the BST 
// in arr[] 
void storeSorted(Node *root, int arr[], int &i) 
{ 
    if (root != NULL) 
    { 
        storeSorted(root->left, arr, i); 
        arr[i++] = root->key; 
        storeSorted(root->right, arr, i); 
    } 
} 
  
/* A utility function to insert a new 
   Node with given key in BST */
Node* insert(Node* node, int key) 
{ 
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
  
    /* return the (unchanged) Node pointer */
    return node; 
} 
  
// This function sorts arr[0..n-1] using Tree Sort 
void treeSort(int arr[], int n) 
{ 
    struct Node *root = NULL; 
  
    // Construct the BST 
    root = insert(root, arr[0]); 
    for (int i=1; i<n; i++) 
        insert(root, arr[i]); 
  
    // Store inoder traversal of the BST 
    // in arr[] 
    int i = 0; 
    storeSorted(root, arr, i); 
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
		treeSort(arreglo, n);
		
		t1 = clock();
		double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
		tiempo = tiempo*1000;
		cout<<" "<<endl;
		//print(arreglo, n);
		cout<< "Tiempo: "<<tiempo<<" milisegundos"<<endl; 
//		imprimir(arreglo, n); //imprime el arreglo ya ordenado
		
}
// This code is contributed by rathbhupendra 

