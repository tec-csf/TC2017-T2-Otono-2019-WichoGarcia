#ifndef NodoB_h
#define NodoB_h
using namespace std;
template <class T>
class NodoB {
public:
int pointer = NULL;
int foo = 0;
int padre = NULL;
bool hoja = false;
T *info;
int *hijo;
NodoB(int);
NodoB(int,int,fstream &);
virtual ~NodoB();
bool check(int);
//void printInfo();
//void print(int);
};
/*template <class T>
void NodoB<T>::printInfo()
{
for(int i = 0; i < foo;i++)
{
std::cout << info[i] << " ";
}
}*/
template <class T>
bool NodoB<T>::check(int orden)
{
return foo==orden*2-1;
}
template <class T>
NodoB<T>::NodoB(int orden)
{
info = new T[2*orden-1];
hijo = new int[2*orden+1];
}
/*template <class T>
void NodoB<T>::print(int orden)
{
std::cout << "Nodo: ";
std::cout << pointer << std::endl;
std::cout << "Padre: ";
std::cout << padre << std::endl;
std::cout << "Info: ";
printInfo();
std::cout << std::endl;
if(!hoja){
std::cout << "Hijos: ";
for(int i = 0; i < foo+1;i++)
{
std::cout << hijo[i] << " ";
}
std::cout << std::endl;
}
else
{
std::cout << "Leaf" << std::endl;
}
std::cout << std::endl;
}*/
template <class T>
NodoB<T>::~NodoB(){
}
#endif /* NodoB_h */
