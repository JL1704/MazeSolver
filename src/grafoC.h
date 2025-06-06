#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "archivos.h"

// Estructura para representar un nodo en el grafo
typedef struct {
    int x;
    int y;
} Nodo;

// Definici�n de la estructura del nodo de la lista de adyacencia
typedef struct AdListaNodo {
    Nodo nodo;
    struct AdListaNodo* nodosiguiente;
} AdListaNodo;

// Definici�n de la estructura principal del grafo
typedef struct {
    int lineas;
    int columnas;
    AdListaNodo*** nodos;  // Matriz de listas de adyacencia
} Grafo;

// Funci�n para liberar la memoria de una pila de nodos
void freeStack(Nodo** stack, int size);
// Funci�n para agregar un nodo a la pila
void push(Nodo** stack, int* top, Nodo node);
// Funci�n para quitar y obtener un nodo de la pila
Nodo pop(Nodo** stack, int* top);
// Funci�n para verificar si la pila est� vac�a
bool isEmpty(int top);
// Funci�n para inicializar un grafo con el n�mero dado de l�neas y columnas
Grafo* iniGrafo(int lineas, int columnas);
// Funci�n para liberar la memoria utilizada por el grafo
void freeGrafo(Grafo* grafo);
// Funci�n para agregar una conexi�n entre dos nodos en el grafo
void addEdge(Grafo* grafo, Nodo src, Nodo dest);
// Funci�n para imprimir las conexiones del grafo en la consola
void printGrafo(Grafo* grafo, HANDLE console);
// Funci�n para convertir la informaci�n del laberinto en un grafo y encontrar un camino utilizando DFS
void convertirGrafo(struct ValoresImp* ValImp, HANDLE console);
// Funci�n de b�squeda en profundidad (DFS) para encontrar un camino en el grafo
void DFS(Grafo* grafo, Nodo start, Nodo destination, struct ValoresImp* ValImp);
// Funci�n para imprimir el laberinto con el camino resuelto
void printLab(struct ValoresImp* ValImp, HANDLE console);

