#include <iostream>
#include <stdlib.h>
#define MAX 10
using namespace std;

void menu();
// nodos n ; arcos arc ;
int matrizAdyacente[MAX][MAX];

class nodoCiudad
{
public:
    int peso;
    int ady;          // cantidad de vertices
    nodoCiudad *next; // puntero al siguiente
    nodoCiudad(int v, int p, nodoCiudad *siguiente = NULL)
    {
        ady = v;
        peso = p;
        next = siguiente;
    } // constructor para nuestro grafo
};

struct nodo
{
public:
    int vertice;
    nodoCiudad *puntero;
    nodo *next;
    nodo(int v, nodo *sig = NULL, nodoCiudad *punt = NULL)
    {
        vertice = v;
        next = sig;
        puntero = punt;
    }
    class lista;
};

typedef nodo *nodoP; // creamos un puntero nodoP

class lista
{
public:
    nodoP S; // crea puntero S de tipo nodoP

    lista() { S = NULL; }                   // crea la lista vacia
    void insertarV(int v);                  // función para insertar datos.
    bool listavVacia();                     // función para revisar si nuestra lista esta vacio
    nodoP buscarV(int v);                   // función para buscar.
    bool listaVexiste(int i, int f);        // función booleana para verificar si nuestro grafo esta vacio
    void crearArco(int i, int f, int peso); // función para crear los arcos de nuestro grafo.
    void crearMatriz();                     // función para crear nuestra matriz adyacente.
    void mostrarMatriz();                   // función para mostrar nuestra matriz.
    int cantVertices();                     // función para contar nuestros vertices o nodos.
    int existeArco(int i, int f);           // función para  verificar si nuestro grafo tiene arcos
    bool buscarAdy(nodoP aux, int ad);      // función booleana para verificar si nuestro grafo tiene arcos
};

void lista::crearArco(int i, int f, int peso)
{              // función para crear un nuevo arco
    nodoP pos; // creamos un nuevo puntero
    pos = S;
    if (listaVexiste(i, f))
    {
        while (pos != NULL)
        { // se recorre la lista  hasta encontrar el valor buscado
            if (i == pos->vertice)
            {
                if (pos->puntero == NULL)
                {                                           // si no tiene nada entonces
                    pos->puntero = new nodoCiudad(f, peso); // creamos un nuevo constructor
                }
                else
                {
                    nodoCiudad *temp = pos->puntero; // creamos un nuevo puntero y lo igualamos
                    while (temp->next != NULL)
                    {                      // ciclo mientras
                        temp = temp->next; // guardamos los datos.
                    }
                    temp->next = new nodoCiudad(f, peso); // creamos un nuevo constructor
                    temp = NULL;                          // lo igualamos a NULL
                    delete temp;                          // eliminamos el
                }
            }
            pos = pos->next; // guerdamos los datos.
        }
    }
}

bool lista::listaVexiste(int i, int f)
{ // función para verificar si nuestro grafo tiene arcos.
    if (buscarV(i) != NULL && buscarV(f) != NULL)
    {                // sentencia if.
        return true; // retornamos verdadero
    }
    else
    {                 // sino
        return false; // retornamos falso o 0.
    }
}

void lista::insertarV(int v)
{                   // función para insertar los datos a nuestro grafo
    nodoP anterior; // creamos un nuevo puntero
    if (listavVacia())
    {                       // Si la lista está vacía
        S = new nodo(v, S); // creamos un nuevo nodo
    }
    else
    {
        if (v <= S->vertice)
        {                       // si el valor a insertar es menor que el
            S = new nodo(v, S); // se inserta el nodo antes del primer dato de la lista
        }
        else
        {
            // en caso contrario se busca el nodo que tenga un dato menor a valor
            anterior = S; // Avanzamos hasta que el siguiente tenga un valor mayor que valor
            while ((anterior->next) && (anterior->next->vertice <= v))
            {
                anterior = anterior->next;
            }
            // Creamos un nuevo nodo después del nodo anterior, y cuyo siguiente
            // es el siguiente del anterior
            anterior->next = new nodo(v, anterior->next);
        }
    }
}

bool lista::listavVacia()
{                     // función booleana para verificar si nuestro grafo tiene vertices o nodos.
    return S == NULL; // verificamos si nuestro grafo esta vacio.
}

int lista::cantVertices()
{                   // función para contar nuestro vertices o nodos
    nodoP nodo = S; // creamos un nuevo nodo y lo igualamos a otro.
    int i = 0;      // creamo una nueva variable entera y la igualamos a 0
    while (nodo != NULL)
    { // contador sube 1 cuando el nodo no este vacio
        i++;
        nodo = nodo->next; // igualamos nuestro nodos, para poder sumar la cantidad de los mismos
    }
    return i;
}

int lista::existeArco(int i, int f)
{                      // función para poder realizar la matriz adyacente
    nodoP nodo;        // creamos un nuevo nodo.
    int a = 1;         // creamos una variable entera, y la inicializamos en 1
    nodo = buscarV(i); // igualamos nuestro nodo a la función buscar.
    if (nodo)
    {
        if (buscarAdy(nodo, f))
        { // sentencia if, llamamos a nuestra función booleana.
            return a;
        }
        else
        {
            return a = 0;
        }
    }
}

bool lista::buscarAdy(nodoP aux, int ad)
{                                    // función booleana para poder realizar la matriz adyacente
    nodoCiudad *temp = aux->puntero; // creamos un nuevo puntero.
    bool a;                          // creamos un varible de tipo boolena.
    while (temp)
    { // ciclo while o mientras.
        if (ad == temp->ady)
        { // sentencia if.
            return a = true;
        }                  // retornamos a verdadero.
        temp = temp->next; // igualamos nuestro puntero para que verifique todos los valores.
    }
    return a = false; // sino retornamos a falso
}

nodoP lista::buscarV(int valor)
{ // función para buscar valores dentro de nuestro grafo
    int z;
    nodoP indice, n = NULL; // creamos un nuevo nodo e igualamos a la varible n a NULL
    indice = S;             // igualamos nuestro
    while (indice != NULL)
    { // se recorre la lista  hasta encontrar el valor buscado
        if (valor == indice->vertice)
        {
            return indice; // al encontar el valor  lo retorna
        }
        indice = indice->next; // igualamos nuestros nodos para que verifiquen nuestros datos
    }
    cout << "\n\n\tEL VALOR BUSCADO NO ESTA EN EL GRAFO";
    return n; // si el valor buscado no esta en la lista retorna nulo
}

void lista::crearMatriz()
{                              // función para crear nuestra matriz adyacente.
    nodoP nodo = S, nodotemp;  // creamos un nuevo puntero y lo igualamos.
    int i, j, inicio, fin;     // creamos nuestras variables enteras.
    int cant = cantVertices(); // creamos un varibale entera y la igualamos a nuestra función cantidad de vertices.
    for (i = 0; i < cant; i++)
    {
        nodotemp = S; // igualamos nuestros punteros.
        for (j = 0; j < cant; j++)
        {
            matrizAdyacente[i][j] = existeArco(nodo->vertice, nodotemp->vertice); // guardamos en la matriz creada anteriormente los datos de nuestra función existe arco.
            nodotemp = nodotemp->next;                                            // igualamos nuestros punteros para que verifiquen todos los datos.
        }
        nodo = nodo->next; // igualamos nuestros punteros para que verifiquen todos los datos.
    }
    delete nodo;
    delete nodotemp; // Se elimina la basura.
}

void lista::mostrarMatriz()
{                          // función para mostrar nuestra matriz adyacente.
    int i, j, cant;        // creamos varibales enteras
    nodoP nodo = S;        // creamos un nuevo puntero.
    cant = cantVertices(); // igulamos  la varibale creada anteriormente a la cantidad de vertices.
    cout << "   ";         // espacios

    for (i = 0; i < cant; i++)
    {                                         // ciclo for.
        cout << "\t" << nodo->vertice << " "; // mostramos los nodos o vertices del grafo.
        nodo = nodo->next;                    // igualamos los punteros para que muestre todos los vertices
    }
    nodo = S;       // igualamos los punteros
    cout << "\n\n"; // saltos de linea.

    for (i = 0; i < cant; i++)
    { // ciclo for.

        cout << nodo->vertice; // mostramos los vertices de nuestro grafo.
        for (j = 0; j < cant; j++)
        {                                                 // ciclo for
            cout << "\t" << matrizAdyacente[i][j] << " "; // mostramos los datos guardados en la matriz.
        }
        nodo = nodo->next; // igualamos los punteros para que muestre todos los datos.
        cout << "\n";      // salto de linea.
    }
}

int main(int argc, char const *argv[])
{
    /*if (argc != 2){
        cout << "Error. Debe ejecutarse como ./problema n (cualquier n, no se usa por ahora)" << endl;
        exit(EXIT_FAILURE);}*/
    // system("color 0B");
    // menu();
    lista ciudad;
    ciudad.crearMatriz();
    ciudad.insertarV(1);
    ciudad.insertarV(2);
    ciudad.insertarV(3);
    ciudad.insertarV(4);
    ciudad.insertarV(5);       // asiganmos vaciudadores 'nombres' a ciudados nodos.
    ciudad.crearArco(1, 2, 2); // arco 1-2
    ciudad.crearArco(2, 1, 3); // 2-1
    ciudad.crearArco(1, 5, 8); // 1-5
    ciudad.crearArco(3, 1, 4); // 3-1
    ciudad.crearArco(3, 4, 6); // 3-4
    ciudad.crearArco(2, 3, 1); // 2-3
    ciudad.crearArco(2, 5, 3); // 2-5
    ciudad.crearArco(4, 3, 5); // 4-3
    ciudad.crearArco(4, 5, 9); // 4-5
    ciudad.crearArco(5, 3, 2); // 5-3
    ciudad.crearArco(5, 4, 2); // 5-4
    ciudad.mostrarMatriz();

    cout << ("Aqui comienza el lujito\n");
    return 0;
}
void creaCiudad()
{
}

/*void menu(){

    system("cls");
    int opcion=0,valor=0;
    lista ciudad;
    ciudad.insertarV(1);
    ciudad.insertarV(2);
    ciudad.insertarV(3);
    ciudad.insertarV(4);
    ciudad.insertarV(5); //asiganmos vaciudadores 'nombres' a ciudados nodos.
    ciudad.crearArco(1,2,2); //arco 1-2
    ciudad.crearArco(2,1,3); // 2-1
    ciudad.crearArco(1,5,8); // 1-5
    ciudad.crearArco(3,1,4); // 3-1
    ciudad.crearArco(3,4,6); // 3-4
    ciudad.crearArco(2,3,1); // 2-3
    ciudad.crearArco(2,5,3); // 2-5
    ciudad.crearArco(4,3,5); // 4-3
    ciudad.crearArco(4,5,9); // 4-5
    ciudad.crearArco(5,3,2); // 5-3
    ciudad.crearArco(5,4,2); // 5-4



    //De aqui es puro menu
    cout<<"\n\n\tGRAFO DIRIGIDO ALGORITMOS||UCN"; //mensaje
    cout<<"\n";
    cout<<"\n\n\t1. Mostrar Matriz Adyacente";
    cout<<"\n\n\t2. Buscar";
    cout<<"\n\n\t3. Salir";
    cout<<"\n";
    cout<<"\n";
    cout<<"\nIngrese opcion: ";
    cin>>opcion;
    switch(opcion){
    case 1:
        system("cls");
        cout<<"\n"; //salto de liena
        cout<<"\n\n\tMATRIZ DE ADYACENCIA"<<"\n\n"; //mensaje
        ciudad.crearMatriz(); //llamamos a nuestra función para que cree la matriz con los datos ingresados
        ciudad.mostrarMatriz(); //mostramos la matriz adyacente.
        cout<<"\n";
        cout<<"\n";
        system("pause");
        menu();
    break;

    case 2:
        system("cls");
        cout<<"\nIngrese numero que desea buscar: ";
        cin>>valor;
        ciudad.buscarV(valor); //función para buscar valores en nuestro grafo
        cout<<"\n";
        cout<<"\n";
        system("pause");
        menu();
    break;
    case 3:
    system("cls");
    cout<<"\n";
    cout<<"\n\n\tDISENO Y ANALISIS"; //termina nuestro programa
    cout<<"\n";
    return;
    break;
    default:
            system("cls");
            cout<<"\n\n\tOPCION NO VALIDA"; //manejo de excepciones.
            cout<<"\n";
            system("pause");
            menu();
            break;
    }
}*/