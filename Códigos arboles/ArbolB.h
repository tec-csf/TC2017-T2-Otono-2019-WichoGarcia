#ifndef ArbolB_h
#define ArbolB_h
#include <fstream>
#include <vector>
void insertarData(NodoB<T> & nodo,T data);
void dividirNodo(NodoB<T> & nodoPadre,int i,NodoB<T> & nodo);
void guardar(NodoB<T> & nodo);
NodoB<T> cargar(int cargarKey);
void buscar(T data);
void cargarNodo(NodoB<T> *,int);
int numNodos();
void buscarNodo(NodoB<T> & nodo,T data, bool & busqueda);
bool buscarNodo(T data);
int getNivel(NodoB<T> & nodo);
int getNivel();
};
template <class T>
bool ArbolB<T>::buscarNodo(T data)
{
NodoB<T> root = cargar(getRaiz());
bool found = false;
buscarNodo(root, data, found);
return found;
}
template <class T>
void ArbolB<T>:: buscarNodo(NodoB<T> & node,T data, bool & found)
{
int i = 0;
while(i < node.foo && data > node.info[i])
i++;
if (i < node.foo && data == node.info[i])
{
found = true;
return;
}
else if (node.hoja)
{
return;
}
else
{
for(int j = i; j<=node.foo;j++)
{
node = cargar(node.hijo[j]);
buscarNodo(node, data, found);
}
}
}
template <class T>
ArbolB<T>::ArbolB(int orden)
{
this->orden = orden;
ID = 0;
setData();
NodoB<T> node(orden);
node.pointer = ID;
node.hoja = true;
guardar(node);
ID++;
}
template <class T>
int ArbolB<T>::buscarInfo(NodoB<T> & node,T data)
{
int i=0;
while (i<node.foo && node.info[i] < data)
i++;
return i;
}
template <class T>
void ArbolB<T>::borrar(T data)
{
NodoB<T> root = cargar(getRaiz());
borrarData(root, data);
if(root.foo==0)
{
if(!root.hoja)
setRaiz(root.hijo[0]);
}
}
template <class T>
void ArbolB<T>::borrarData(NodoB<T> & node,T data)
{
int i = buscarInfo(node, data);
if(i < node.foo && node.info[i] == data)
{
if(node.hoja){
borrarHoja(node,i);
guardar(node);
}
else
{
borrarNoHoja(node,i);
guardar(node);
}
}
else{
if(node.hoja){
std::cout << "El dato " << data << " no existe en el arbol" << std::endl;
}
else
{
bool flag = ( (i==node.foo)? true : false );
NodoB<T> child = cargar(node.hijo[i]);
T chancla = child.info[1];
if(child.foo < orden)
fill(node,i);
if(flag && i > node.foo)
{
child = cargar(node.hijo[i-1]);
borrarData(child, data);
}
else
{
child = cargar(node.hijo[i]);
chancla = child.info[2];
borrarData(child,data);
}
}
}
}
template <class T>
void ArbolB<T>::borrarHoja(NodoB<T> & node,int i)
{
for (int j = i+1; j < node.foo; j++)
node.info[j-1] = node.info[j];
node.foo--;
}
template <class T>
void ArbolB<T>::borrarNoHoja(NodoB<T> & parent,int i)
{
T data = parent.info[i];
NodoB<T> child = cargar(parent.hijo[i]);
NodoB<T> childHermano = cargar(parent.hijo[i+1]);
if(child.foo >= orden)
{
T antes = getPredecesor(parent,i);
parent.info[i] = antes;
borrarData(child, antes);
}
else if(childHermano.foo >= orden)
{
T siguiente = getNext(parent,i);
parent.info[i] = siguiente;
borrarData(childHermano, siguiente);
}
else
{
merge(parent,i);
child = cargar(child.pointer);
borrarData(child,data);
}
}
template <class T>
int ArbolB<T>::getPredecesor(NodoB<T> & parent,int i)
{
NodoB<T> child = cargar(parent.hijo[i]);
while(!child.hoja)
child = cargar(child.hijo[child.foo]);
return child.info[child.foo-1];
}
template <class T>
int ArbolB<T>::getNext(NodoB<T> & parent, int i)
{
NodoB<T> child = cargar(parent.hijo[i+1]);
while(!child.hoja)
child = cargar(child.hijo[0]);
return child.info[0];
}
template <class T>
void ArbolB<T>::fill(NodoB<T> & node,int i)
{
NodoB<T> child = cargar(node.hijo[i-1]);
NodoB<T> childHermano = cargar(node.hijo[i+1]);
if(i != 0 && child.foo >= orden)
borrowPredecesor(node,i);
else if(i != node.foo && childHermano.foo >= orden)
borrowNext(node,i);
else
{
if(i != node.foo)
merge(node,i);
else
merge(node,i-1);
}
}
template <class T>
void ArbolB<T>::borrowPredecesor(NodoB<T> & parent,int i)
{
NodoB<T> child = cargar(parent.hijo[i]);
NodoB<T> childHermano = cargar(parent.hijo[i-1]);
for(int j = child.foo; j>= 0;j--)
child.info[j+1] = child.info[j];
if(!child.hoja){
for(int j = child.foo; j>=0; j--)
child.hijo[j+1] = child.hijo[j];
}
child.info[0] = parent.info[i-1];
if(!parent.hoja)
child.hijo[0] = childHermano.hijo[childHermano.foo];
parent.info[i-1] = childHermano.info[childHermano.foo-1];
child.foo++;
childHermano.foo--;
guardar(parent);
guardar(child);
guardar(childHermano);
}
template <class T>
void ArbolB<T>::borrowNext(NodoB<T> & parent,int i)
{
NodoB<T> child = cargar(parent.hijo[i]);
NodoB<T> childHermano = cargar(parent.hijo[i+1]);
child.info[child.foo] = parent.info[i];
if(!child.hoja)
child.hijo[child.foo+1] = childHermano.hijo[0];
parent.info[i] = childHermano.info[0];
for(int j = 1 ; j < childHermano.foo;j++)
childHermano.info[j-1] = childHermano.info[j];
if(!childHermano.hoja)
{
for(int j = 1; j <= childHermano.foo; j++)
childHermano.hijo[j-1] = childHermano.hijo[j];
}
child.foo++;
childHermano.foo--;
guardar(parent);
guardar(child);
guardar(childHermano);
}
template <class T>
void ArbolB<T>::merge(NodoB<T> & parent, int i)
{
NodoB<T> child = cargar(parent.hijo[i]);
NodoB<T> childHermano = cargar(parent.hijo[i+1]);
child.info[orden-1] = parent.info[i];
for (int j=0; j<childHermano.foo; j++)
child.info[j+orden] = childHermano.info[j];
if (!child.hoja)
{
for(int j=0; j<=childHermano.foo; j++)
child.hijo[j+orden] = childHermano.hijo[j];
}
for (int j=i+1; j<parent.foo; j++)
parent.info[j-1] = parent.info[j];
for (int j=i+2; j<=parent.foo; j++)
parent.hijo[j-1] = parent.hijo[j];
child.foo += childHermano.foo+1;
parent.foo--;
guardar(parent);
guardar(child);
guardar(childHermano);
}
template <class T>
void ArbolB<T>::buscar(T data)
{
NodoB<T> root = cargar(getRaiz());
buscarDato(root, data);
}
template <class T>
void ArbolB<T>::insertar(T data)
{
NodoB<T> root = cargar(getRaiz());
if(root.check(orden))
{
NodoB<T> parentNode(orden);
parentNode.pointer = ID;
setRaiz(ID);
parentNode.hoja = false;
parentNode.foo = 0;
parentNode.hijo[0] = root.pointer;
parentNode.padre = parentNode.pointer;
ID++;
dividirNodo(parentNode, 0, root);
insertarData(parentNode, data);
}
else
{
insertarData(root, data);
}
}
template <class T>
void ArbolB<T>::insertarData(NodoB<T> & node,T data)
{
int i = node.foo-1;
if(node.hoja)
{
while (i >= 0 && data < node.info[i])
{
node.info[i+1] = node.info[i];
i--;
}
node.info[i+1] = data;
node.foo++;
guardar(node);
}
else
{
while (i >= 0 && data < node.info[i])
{
i--;
}
i ++;
NodoB<T> nodeHijo = cargar(node.hijo[i]);
if(nodeHijo.check(orden))
{
dividirNodo(node, i, nodeHijo);
if(data > node.info[i])
{
i++;
nodeHijo = cargar(node.hijo[i]);
}
}
insertarData(nodeHijo, data);
}
}
template <class T>
void ArbolB<T>::dividirNodo(NodoB<T> & parentNode,int i,NodoB<T> & node)
{
node.padre = parentNode.pointer;
NodoB<T> siblingNode(orden);
siblingNode.pointer = ID;
siblingNode.padre = parentNode.pointer;
ID++;
siblingNode.hoja = node.hoja;
int div = orden-1;
siblingNode.foo = div;
for(int j = 0; j < div; j++)
{
siblingNode.info[j] = node.info[j+orden];
}
if (!node.hoja){
for(int j = 0; j < div+1; j++)
{
siblingNode.hijo[j] = node.hijo[j+orden];
}
}
node.foo = div;
for (int j = parentNode.foo+1; j >= i+1;j--)
{
parentNode.hijo[j+1] = parentNode.hijo[j];
}
parentNode.hijo[i+1] = siblingNode.pointer;
for (int j = parentNode.foo; j >= i; j--)
{
parentNode.info[j] = parentNode.info[j-1];
}
parentNode.info[i] = node.info[orden-1];
parentNode.foo++;
guardar(node);
guardar(parentNode);
guardar(siblingNode);
}
template <class T>
void ArbolB<T>::imprimirNodos()
{
NodoB<T> root = cargar(getRaiz());
imprimir(root);
std::cout << std::endl;
}
template <class T>
void ArbolB<T>::inOrder()
{
NodoB<T> root = cargar(getRaiz());
asc(root);
std::cout << std::endl;
}
template <class T>
void ArbolB<T>::reverseInOrder()
{
NodoB<T> root = cargar(getRaiz());
desc(root);
std::cout << std::endl;
}
template <class T>
void ArbolB<T>::imprimir(NodoB<T> & node)
{
NodoB<T> child(orden);
if(node.hoja)
node.print(orden);
else{
node.print(orden);
for(int i = 0; i<= node.foo; i++)
{
child = cargar(node.hijo[i]);
imprimir(child);
}
}
}
template <class T>
void ArbolB<T>::asc(NodoB<T> & node)
{
NodoB<T> child(orden);
int i;
for(i = 0; i < node.foo; i++)
{
if(!node.hoja)
{
child = cargar(node.hijo[i]);
asc(child);
}
std::cout << " " << node.info[i];
}
if(node.hoja == false)
{
child = cargar(node.hijo[i]);
asc(child);
}
}
template <class T>
void ArbolB<T>::desc(NodoB<T> & node)
{
NodoB<T> child(orden);
int i;
for(i = node.foo; i > 0; i--)
{
if(!node.hoja)
{
child = cargar(node.hijo[i]);
desc(child);
}
std::cout << " " << node.info[i-1];
}
if(node.hoja == false)
{
child = cargar(node.hijo[i]);
desc(child);
}
}
template <class T>
void ArbolB<T>::setData()
{
int root = 0;
try
{
if (std::ifstream("./data.dat"))
{
std::cout << "Archivo data.dat encontrado" << std::endl;
data.open("./data.dat", std::ios::out|std::ios::in| std::ios::binary);
std::cout << " " << std::endl;
} else
{
std::cout << "Archivo data.dat no encontrado" << std::endl;
std::cout << " " << std::endl;
data.open("./data.dat", std::ios::out | std::ios::binary);
data.close();
data.open("./data.dat", std::ios::out|std::ios::in| std::ios::binary);
}
if(data.fail())
throw 1;
}
catch (int e)
{
std::cerr << "Hubo un error al abrir los datas... Exception " << e << " caught" <<
std::endl;
}
data.seekp(0);
data.write(reinterpret_cast<char*>(&root), sizeof(int));
}
template <class T>
int ArbolB<T>::getRaiz()
{
int root;
data.seekg(0);
data.read(reinterpret_cast<char*>(&root), sizeof(int));
return root;
}
template <class T>
void ArbolB<T>::setRaiz(int rootID)
{
data.seekp(0);
data.write(reinterpret_cast<char*>(&rootID), sizeof(int));
}
template <class T>
int ArbolB<T>::numNodos()
{
int totalNodos;
data.seekg(0);
data.read(reinterpret_cast<char*>(&totalNodos), sizeof(int));
return totalNodos;
}
template <class T>
void ArbolB<T>::update(int number)
{
int total;
data.seekg(0);
data.read(reinterpret_cast<char*>(&total), sizeof(int));
total += number;
data.seekp(0);
data.write(reinterpret_cast<char*>(&total), sizeof(int));
}
template <class T>
void ArbolB<T>::guardar(NodoB<T> & node)
{
data.seekp(sizeof(int)+node.pointer*sizeof(NodoB<T>));
data.write(reinterpret_cast<char*>(&node), sizeof(NodoB<T>));
}
template <class T>
NodoB<T> ArbolB<T>::cargar(int loadKey)
{
NodoB<T> node(orden);
data.seekg(sizeof(int)+loadKey*sizeof(NodoB<T>));
data.read(reinterpret_cast<char*>(&node), sizeof(NodoB<T>));
return node;
}
template <class T>
int ArbolB<T>::getNivel()
{
NodoB<T> node = cargar(getRaiz());
return getNivel(node);
}
template <class T>
int ArbolB<T>::getNivel(NodoB<T> & node)
{
int level = 0;
while (node.padre != node.pointer) {
level++;
node = cargar(node.padre);
}
return level;
}
/*template <class T>
bool ArbolB<T>::isBTree()
{
NodoB<T> root = cargar(getRaiz());
isBTree(root);
hojaNivel.clear();
T cmp = hojaNivel[0];
bool leafs = true;
for(int i=1; i<hojaNivel.size(); i++)
{
if(hojaNivel[i] != cmp)
leafs = false;
}
return leafs;
}
template <class T>
void ArbolB<T>::isBTree(NodoB<T> & node)
{
if (node.hoja)
{
hojaNivel.push_back(getNivel(node));
}
else
{
for(int j = 0; j<=node.foo;j++)
{
node = cargar(node.hijo[j]);
isBTree(node);
}
}
}*/
template <class T>
ArbolB<T>::~ArbolB()
{
data.close();
}
#endif /* ArbolB_h */
