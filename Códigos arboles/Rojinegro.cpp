
#include <iostream>
#include <fstream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

#define RED		1
#define BLACK	2

struct node {
	int key;
	struct node *left, *right, *p;
	int color;
	int size;
};

typedef struct node *NODERB;
struct node NIL;
NODERB NILPTR = &NIL;

void inorder(NODERB x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d ", x->key);
		inorder(x->right);
	}
}
void postorder(NODERB x){
	if (x != NILPTR){
		postorder(x-> right);
		printf("%d ", x->key);
		inorder(x->left);
	}
}

NODERB search(NODERB root, int k) {
	if (root == NILPTR || root->key == k)
		return root;
		
	if (k < root->key)
		return search(root->left, k);
		
	else
		return search(root->right, k);
		
}
NODERB minimum(NODERB root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}

void leftrotate(NODERB *treeroot, NODERB x) {
	NODERB y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void rightrotate(NODERB *treeroot, NODERB y) {
	NODERB x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

void rbinsertfixup(NODERB *treeroot, NODERB z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			NODERB y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					leftrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot,z->p->p);
			}
		}
		else {
			NODERB y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rightrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

void rbinsert(NODERB *treeroot, int z) {
	NODERB Z = (NODERB) malloc(sizeof(struct node));
	Z->key = z;
	NODERB y = NILPTR;
	NODERB x = *treeroot;
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	rbinsertfixup(treeroot,Z);
}

void rbtransplant(NODERB *treeroot, NODERB u, NODERB v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void rbdeletefixup(NODERB *treeroot, NODERB x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x == x->p->left) {
			NODERB w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
		else {
			NODERB w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}

void rbdelete(NODERB *treeroot, int z) {
	NODERB Z = search(*treeroot, z);
	if (Z == NILPTR) {
		printf("Node to be deleted not found\n");
		return;
	}
	NODERB y = Z;
	int yoc = y->color;
	NODERB x;
	if (Z->left == NILPTR) {
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else {
		y = minimum(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}
double getMilisegundos(clock_t c)
{
    double tiempo=0;
    tiempo = (double)((c/(double)CLOCKS_PER_SEC)*1000) ;
return tiempo;
}

main(){
	double t1,t2,tiempo;//para la función de tiempo 


	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODERB tree = NILPTR;
	int n;
	int i;

ifstream fin("elementos.txt");
int num;
for(i=0; i<=100000; i++){
fin>> num;
rbinsert(&tree, num);

}

	while (1) {
		printf("1.Insertar\n2.Buscar\n3.Menor a Mayor\n4.Mayor a Menor\n5.Borrar\n6.Altura de nodo\n7.Salida\n");
		scanf("%d", &n);
		if (n == 1) {
			printf("Número a insertar \n");
			int num;
			scanf("%d", &num);
			rbinsert(&tree, num);
		}
		else if (n == 2) {
			printf("Número a buscar\n");
			int num;
			scanf("%d", &num);
			t1=clock();
			if (search(tree, num) == NILPTR){
				printf("%d no encontrado\n", num);
			}
			else
				printf("%d Encontrado\n", num);
			t2=clock();
			 tiempo=getMilisegundos(t2-t1);
 				cout <<tiempo << " milisegundos" << endl;
		}
		else if (n == 3) {
			inorder(tree);
			printf("\n");
		}
		else if (n == 4){
			postorder(tree);
			printf("\n");
		}
		else if (n == 5) {
			printf("Número a eliminar\n");
			int num;
			scanf("%d", &num);
			rbdelete(&tree, num);
		}
		else 
			break;
	}
	return 0;
}
