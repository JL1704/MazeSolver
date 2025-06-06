#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "archivos.h"

// Estructura para representar un nodo en el grafo
typedef struct {
    int x;
    int y;
} Nodo;

// Definición de la estructura del nodo de la lista de adyacencia
typedef struct AdListaNodo {
    Nodo nodo;
    struct AdListaNodo* nodosiguiente;
} AdListaNodo;

// Definición de la estructura principal del grafo
typedef struct {
    int lineas;
    int columnas;
    AdListaNodo*** nodos;  // Matriz de listas de adyacencia
} Grafo;

// Función para liberar la memoria de una pila de nodos
void freeStack(Nodo** stack, int size);
// Función para agregar un nodo a la pila
void push(Nodo** stack, int* top, Nodo node);
// Función para quitar y obtener un nodo de la pila
Nodo pop(Nodo** stack, int* top);
// Función para verificar si la pila está vacía
bool isEmpty(int top);
// Función para inicializar un grafo con el número dado de líneas y columnas
Grafo* iniGrafo(int lineas, int columnas);
// Función para liberar la memoria utilizada por el grafo
void freeGrafo(Grafo* grafo);
// Función para agregar una conexión entre dos nodos en el grafo
void addEdge(Grafo* grafo, Nodo src, Nodo dest);
// Función para imprimir las conexiones del grafo en la consola
void printGrafo(Grafo* grafo, HANDLE console);
// Función para convertir la información del laberinto en un grafo y encontrar un camino utilizando DFS
void convertirGrafo(struct ValoresImp* ValImp, HANDLE console);
// Función de búsqueda en profundidad (DFS) para encontrar un camino en el grafo
void DFS(Grafo* grafo, Nodo start, Nodo destination, struct ValoresImp* ValImp);
// Función para imprimir el laberinto con el camino resuelto
void printLab(struct ValoresImp* ValImp, HANDLE console);

