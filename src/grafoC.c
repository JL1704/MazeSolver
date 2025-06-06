#include "grafoC.h"
#include <ctype.h>

// Función para agregar una conexión entre dos nodos en el grafo
void addEdge(Grafo* grafo, Nodo src, Nodo dest) {
    // Crear un nuevo nodo de lista de adyacencia
    AdListaNodo* nuevoNodo = (AdListaNodo*)malloc(sizeof(AdListaNodo));
    nuevoNodo->nodo = dest;  // Asignar el nodo de destino al nuevo nodo
    nuevoNodo->nodosiguiente = grafo->nodos[src.y][src.x];  // Establecer el siguiente nodo como el actual en la posición de la matriz
    grafo->nodos[src.y][src.x] = nuevoNodo;  // Actualizar la posición de la matriz con el nuevo nodo
}

// Función para inicializar un grafo con el número dado de líneas y columnas
Grafo* iniGrafo(int lineas, int columnas) {
    int i, j;
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));  // Asignar memoria para la estructura del grafo
    grafo->lineas = lineas;
    grafo->columnas = columnas;

    // Crear una matriz de listas de adyacencia
    grafo->nodos = (AdListaNodo***)malloc(lineas * sizeof(AdListaNodo**));
    for (i = 0; i < lineas; i++) {
        grafo->nodos[i] = (AdListaNodo**)malloc(columnas * sizeof(AdListaNodo*));
        for (j = 0; j < columnas; j++) {
            grafo->nodos[i][j] = NULL;  // Inicializar cada entrada de la matriz como NULL
        }
    }

    return grafo;  // Devolver el grafo inicializado
}

// Función para liberar la memoria utilizada por el grafo
void freeGrafo(Grafo* grafo) {
    int i, j;
    for (i = 0; i < grafo->lineas; i++) {
        for (j = 0; j < grafo->columnas; j++) {
            AdListaNodo* current = grafo->nodos[i][j];
            while (current != NULL) {
                AdListaNodo* nodosiguiente = current->nodosiguiente;
                free(current);  // Liberar el nodo actual
                current = nodosiguiente;
            }
        }
        free(grafo->nodos[i]);  // Liberar la fila de la matriz
    }
    free(grafo->nodos);  // Liberar la matriz de listas de adyacencia
    free(grafo);  // Liberar la estructura del grafo
}

// Agrega un nodo al tope de la pila
void push(Nodo** stack, int* top, Nodo node) {
    *top += 1;
    *stack = (Nodo*)realloc(*stack, (*top + 1) * sizeof(Nodo));  // Aumenta el tamaño de la pila
    (*stack)[*top] = node;  // Asigna el nuevo nodo al tope de la pila
}

// Elimina y devuelve el nodo del tope de la pila
Nodo pop(Nodo** stack, int* top) {
    Nodo node = (*stack)[*top];  // Obtiene el nodo del tope de la pila
    *top -= 1;  // Reduce el índice del tope de la pila
    return node;  // Devuelve el nodo eliminado
}

// Verifica si la pila está vacía
bool isEmpty(int top) {
    return top == -1;  // Devuelve true si el tope de la pila es -1 (pila vacía)
}

// Libera la memoria utilizada por la pila
void freeStack(Nodo** stack, int size) {
    free(*stack);  // Libera la memoria asignada a la pila
}

// Imprime la representación visual del grafo en la consola
void printGrafo(Grafo* grafo, HANDLE console) {
    int i, j;
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n\n\t\tConexiones entre los nodos\n\n\t");

    for (i = 0; i < grafo->lineas; i++) {
        for (j = 0; j < grafo->columnas; j++) {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("(%d, %d) conectado a:", j, i);

            // Imprime las conexiones de cada nodo
            AdListaNodo* current = grafo->nodos[i][j];
            while (current != NULL) {
                SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf(" (%d, %d) ->", current->nodo.x, current->nodo.y);
                current = current->nodosiguiente;
            }

            if (current == NULL) {
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
                printf(" NULL");
            }
            printf("\n\t");
        }
    }
}

// Realiza un recorrido en profundidad (DFS) en el grafo para encontrar el camino desde el nodo de inicio hasta el destino.
void DFS(Grafo* grafo, Nodo start, Nodo destination, struct ValoresImp* ValImp) {
    int i, j;

    // Arreglos para desplazarse en las direcciones: arriba, abajo, izquierda, derecha
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    // Inicialización de la pila para el DFS
    Nodo* stack = (Nodo*)malloc(grafo->lineas * grafo->columnas * sizeof(Nodo));
    int top = -1;

    // Estructuras para almacenar el camino y su longitud
    Nodo** camino = (Nodo**)malloc(grafo->lineas * grafo->columnas * sizeof(Nodo*));
    int* longitudCamino = (int*)malloc(grafo->lineas * grafo->columnas * sizeof(int));
    int caminoIndex = 0;

    // Inicialización de matrices para marcar nodos visitados y almacenar distancias
    bool** visitado = (bool**)malloc(grafo->lineas * sizeof(bool*));
    int** distancia = (int**)malloc(grafo->lineas * sizeof(int*));

    for (i = 0; i < grafo->lineas; i++) {
        visitado[i] = (bool*)malloc(grafo->columnas * sizeof(bool));
        distancia[i] = (int*)malloc(grafo->columnas * sizeof(int));

        for (j = 0; j < grafo->columnas; j++) {
            visitado[i][j] = false;
            distancia[i][j] = -1;
        }
    }

    // Inicialización del nodo de inicio
    visitado[start.y][start.x] = true;
    distancia[start.y][start.x] = 0;

    // Inicia el DFS desde el nodo de inicio
    push(&stack, &top, start);

    while (!isEmpty(top)) {
        Nodo current = pop(&stack, &top);

        // Almacena el nodo actual en el camino
        camino[caminoIndex] = (Nodo*)malloc(sizeof(Nodo));
        camino[caminoIndex]->x = current.x;
        camino[caminoIndex]->y = current.y;
        longitudCamino[caminoIndex++] = distancia[current.y][current.x];

        // Si se alcanza el nodo de destino, termina el DFS
        if (current.x == destination.x && current.y == destination.y) {
            break;
        }

        // Explora nodos adyacentes
        AdListaNodo* adyacente = grafo->nodos[current.y][current.x];
        while (adyacente != NULL) {
            int newX = adyacente->nodo.x;
            int newY = adyacente->nodo.y;

            // Si el nodo adyacente no ha sido visitado, lo agrega a la pila
            if (!visitado[newY][newX]) {
                push(&stack, &top, adyacente->nodo);
                visitado[newY][newX] = true;
                distancia[newY][newX] = distancia[current.y][current.x] * grafo->columnas + current.x;
            }

            adyacente = adyacente->nodosiguiente;
        }
    }

    // Libera la memoria de la pila
    freeStack(&stack, grafo->lineas * grafo->columnas);

    // Imprime el recorrido realizado
    printf("\n\n\t\tRecorrido Realizado:\n\n");
    for (i = 0; i < caminoIndex; i++) {
        printf("(%d, %d) ", camino[i]->x, camino[i]->y);
        if (i < caminoIndex - 1) {
            printf("-> ");
        }
    }
    printf("\n");
    getch();  // Pausa para visualización

    // Marca el camino en el laberinto con 'X'
    int auxiliar = camino[caminoIndex - 1]->x + camino[caminoIndex - 1]->y;
    int aux1 = camino[caminoIndex - 1]->x,aux2 = camino[caminoIndex - 1]->y;
    for (i = caminoIndex - 1; i >= 0; i--) {
        int m = camino[i]->x;
        int n = camino[i]->y;
        // tolower(ValImp->laberintoM[n][m]) == 's' || tolower(ValImp->laberintoM[n][m]) == 'd' 
        if (ValImp->laberintoM[n][m] == 'S' || ValImp->laberintoM[n][m] == 'D') {
            // No realiza ninguna acción si el nodo es la salida o el destino
        } else {
            // Marca el camino con 'X' en el laberinto
            if ((m + n - auxiliar == 1 || m + n - auxiliar == -1)&& (aux1 == m || aux2 == n)) {
                ValImp->laberintoM[n][m] = 'X';
                auxiliar = m + n;
                aux1 = m;
                aux2 = n;
            }
        }
    }

    // Libera la memoria utilizada por las estructuras de datos
    free(camino);
    free(longitudCamino);

    for (i = 0; i < grafo->lineas; i++) {
        free(visitado[i]);
        free(distancia[i]);
    }
    free(visitado);
	free(distancia);
}

// Imprime el laberinto resaltando la salida (S), destino (D) y el camino (X)
void printLab(struct ValoresImp* ValImp, HANDLE console) {
    int i, j;
    printf("\n\n\n\t\t");
    for (i = 0; i < ValImp->Filas; i++) {
        for (j = 0; j < ValImp->Col; j++) {
            if (ValImp->laberintoM[i][j] == 'S' || ValImp->laberintoM[i][j] == 'D') {
                SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("%c", ValImp->laberintoM[i][j]);  // Resalta la salida, destino en verde brillante
                SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            } else {
                if (ValImp->laberintoM[i][j] == 'X') {
                    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("%c", ValImp->laberintoM[i][j]);  // Resalta el camino en rojo brillante
                    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                } else {
                    printf("%c", ValImp->laberintoM[i][j]);  // Imprime los otros caracteres normales
                }
            }
        }
        printf("\n\t\t");
    }
    printf("\n");
    getch();  // Pausa para visualización
}

// Convierte el laberinto en un grafo y encuentra el camino utilizando DFS
void convertirGrafo(struct ValoresImp* ValImp, HANDLE console) {
    int i, j;
    Grafo* grafo = iniGrafo(ValImp->Filas, ValImp->Col);
    Nodo start = { ValImp->coxy.salida_x, ValImp->coxy.salida_y };
    Nodo destination = { ValImp->coxy.destino_x, ValImp->coxy.destino_y };

    // Identifica nodos y conexiones en el laberinto
    for (i = 0; i < ValImp->Filas; i++) {
        for (j = 0; j < ValImp->Col; j++) {
            if (ValImp->laberintoM[i][j] == '.' || ValImp->laberintoM[i][j] == 'S' || ValImp->laberintoM[i][j] == 'D') {
                Nodo currentNode = { j, i };

                // Conectar con nodos adyacentes
                if (i > 0 && (ValImp->laberintoM[i - 1][j] == '.' || ValImp->laberintoM[i - 1][j] == 'S' || ValImp->laberintoM[i - 1][j] == 'D')) {
                    addEdge(grafo, currentNode, (Nodo) { j, i - 1 });
                }
                if (i < ValImp->Filas - 1 && (ValImp->laberintoM[i + 1][j] == '.' || ValImp->laberintoM[i + 1][j] == 'S' || ValImp->laberintoM[i + 1][j] == 'D')) {
                    addEdge(grafo, currentNode, (Nodo) { j, i + 1 });
                }
                if (j > 0 && (ValImp->laberintoM[i][j - 1] == '.' || ValImp->laberintoM[i][j - 1] == 'S' || ValImp->laberintoM[i][j - 1] == 'D')) {
                    addEdge(grafo, currentNode, (Nodo) { j - 1, i });
                }
                if (j < ValImp->Col - 1 && (ValImp->laberintoM[i][j + 1] == '.' || ValImp->laberintoM[i][j + 1] == 'S' || ValImp->laberintoM[i][j + 1] == 'D')) {
                    addEdge(grafo, currentNode, (Nodo) { j + 1, i });
                }
            }
        }
    }

    // Imprime el grafo y encuentra el camino utilizando DFS
    printGrafo(grafo, console);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    DFS(grafo, start, destination, ValImp);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\t\t\tPosible camino encontrado para resolver el laberinto:");
    printf("\n\t\t\tNOTA - Si no se marca un camino por completo es porque no existe solucion");
    printLab(ValImp, console);
    freeGrafo(grafo);  // Libera la memoria del grafo
}
