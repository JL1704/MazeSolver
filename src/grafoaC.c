/*#include "grafoC.h"
#include "archivos.h"

Grafo* iniGrafo(int lineas, int columnas) {
	int i, j, k;
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        // Manejar el error de asignación de memoria
        fprintf(stderr, "Error al asignar memoria para el grafo.\n");
        exit(EXIT_FAILURE);
    }
    grafo->lineas = lineas;
    grafo->columnas = columnas;

    // Crear una matriz de nodos
    grafo->nodos = (GrafoNodo**)malloc(lineas * sizeof(GrafoNodo*));
    if (grafo->nodos == NULL) {
        // Manejar el error de asignación de memoria
        fprintf(stderr, "Error al asignar memoria para la matriz de nodos del grafo.\n");
        free(grafo);  // Liberar la memoria ya asignada para grafo
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < lineas; i++) {
        grafo->nodos[i] = (GrafoNodo*)malloc(columnas * sizeof(GrafoNodo));
        if (grafo->nodos[i] == NULL) {
            // Manejar el error de asignación de memoria
            fprintf(stderr, "Error al asignar memoria para la fila %d de nodos del grafo.\n", i);
            // Liberar la memoria ya asignada para grafo y nodos anteriores
            for (k = 0; k < i; k++) {
                free(grafo->nodos[k]);
            }
            free(grafo->nodos);
            free(grafo);
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < columnas; j++) {
            grafo->nodos[i][j].head = NULL;
        }
    }

    return grafo;
}

// Función para liberar la memoria utilizada por el grafo
void freeGraph(Grafo* grafo) {
    if (grafo == NULL) {
        // Manejar el caso en que el grafo ya sea nulo
        fprintf(stderr, "El grafo ya es nulo.\n");
        return;
    }

    int i, j;
    for (i = 0; i < grafo->lineas; i++) {
        for (j = 0; j < grafo->columnas; j++) {
            AdListaNodo* current = grafo->nodos[i][j].head;
            while (current != NULL) {
                AdListaNodo* nodosiguiente = current->nodosiguiente;
                free(current);
                current = nodosiguiente;
            }
        }
        free(grafo->nodos[i]);
    }
    free(grafo->nodos);
    free(grafo);
}

// Función para agregar una conexión entre dos nodos
void addEdge(Grafo* grafo, Nodo src, Nodo dest) {
    // Verificar que el grafo y los nodos no sean nulos
    if (grafo == NULL || grafo->nodos == NULL || src.y < 0 || src.x < 0 || dest.y < 0 || dest.x < 0 ||
        src.y >= grafo->lineas || src.x >= grafo->columnas || dest.y >= grafo->lineas || dest.x >= grafo->columnas) {
        fprintf(stderr, "Error: Grafo o nodos nulos, o coordenadas fuera de rango.\n");
        return;
    }

    // Crear un nuevo nodo adyacente a dest y enlazarlo a la lista de adyacencia de src
    AdListaNodo* nuevoNodo = (AdListaNodo*)malloc(sizeof(AdListaNodo));

    // Verificar que la asignación de memoria fue exitosa
    if (nuevoNodo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nuevo nodo.\n");
        return;
    }

    nuevoNodo->nodo = dest;
    nuevoNodo->nodosiguiente = grafo->nodos[src.y][src.x].head;
    grafo->nodos[src.y][src.x].head = nuevoNodo;
}


// Función para imprimir el grafo
// Función para imprimir el grafo
void printGraph(Grafo* grafo) {
	int i,j;
    if (grafo == NULL || grafo->nodos == NULL) {
        fprintf(stderr, "Error: Grafo nulo o nodos no inicializados.\n");
        return;
    }

    printf("Representación del Grafo:\n");

    for (i = 0; i < grafo->lineas; i++) {
        for (j = 0; j < grafo->columnas; j++) {
            printf("(%d, %d) conectado a:", j, i);

            AdListaNodo* current = grafo->nodos[i][j].head;

            if (current == NULL) {
                printf(" Ninguno");
            } else {
                while (current != NULL) {
                    printf(" (%d, %d)", current->nodo.x, current->nodo.y);
                    current = current->nodosiguiente;
                }
            }

            printf("\n");
        }
    }
    printf("\n");
}


// ... (código anterior)

void BFS(Grafo* grafo, Nodo start, Nodo destination) {
    int i, j;
    int** distancia = (int**)malloc(grafo->lineas * sizeof(int*));
    bool** visitado = (bool**)malloc(grafo->lineas * sizeof(bool*));

    for (i = 0; i < grafo->lineas; i++) {
        visitado[i] = (bool*)malloc(grafo->columnas * sizeof(bool));
        distancia[i] = (int*)malloc(grafo->columnas * sizeof(int));

        for (j = 0; j < grafo->columnas; j++) {
            visitado[i][j] = false;
            distancia[i][j] = -1;  // Inicializar todas las distancias a -1 (no alcanzables)
        }
    }

    // Cola para BFS
    Nodo* queue = (Nodo*)malloc(grafo->lineas * grafo->columnas * sizeof(Nodo));
    int front = 0, rear = 0;

    // Inicializar la cola con el nodo de inicio
    queue[rear++] = start;
    visitado[start.y][start.x] = true;
    distancia[start.y][start.x] = 0;

    // Array para almacenar todas las rutas encontradas
    Nodo** allPaths = (Nodo**)malloc(grafo->lineas * grafo->columnas * sizeof(Nodo*));
    int* pathLength = (int*)malloc(grafo->lineas * grafo->columnas * sizeof(int));
    int numPaths = 0;

    // Array para almacenar el camino encontrado
    Nodo* path = (Nodo*)malloc(grafo->lineas * grafo->columnas * sizeof(Nodo));
    int pathIndex = 0;

    // Direcciones para moverse (arriba, abajo, izquierda, derecha)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    // BFS
    while (front < rear) {
        Nodo current = queue[front++];

        // Verificar si hemos llegado al destino 'D'
        if (current.x == destination.x && current.y == destination.y) {
            // Reconstruir el camino
            int x = destination.x, y = destination.y;
            while (x != start.x || y != start.y) {
                path[pathIndex++] = (Nodo){x, y};
                int tempX = x, tempY = y;
                x = distancia[tempY][tempX] % grafo->columnas;
                y = distancia[tempY][tempX] / grafo->columnas;
            }

            // Almacenar esta ruta
            allPaths[numPaths] = (Nodo*)malloc(pathIndex * sizeof(Nodo));
            for (i = 0; i < pathIndex; i++) {
                allPaths[numPaths][i] = path[i];
            }
            pathLength[numPaths] = pathIndex;
            numPaths++;

            // Reiniciar variables para la próxima ruta
            pathIndex = 0;
            x = start.x;
            y = start.y;

            // Limpiar la matriz de visitados y distancias para el próximo camino
            for (i = 0; i < grafo->lineas; i++) {
                for (j = 0; j < grafo->columnas; j++) {
                    visitado[i][j] = false;
                    distancia[i][j] = -1;
                }
            }

            // Imprimir la ruta
            printf("Ruta encontrada:\n");
            for (i = pathLength[numPaths - 1] - 1; i >= 0; i--) {
                printf("(%d, %d) ", allPaths[numPaths - 1][i].x, allPaths[numPaths - 1][i].y);
                if (i > 0) {
                    printf("-> ");
                }
            }
            printf("\n");
        }

        // Explorar los nodos adyacentes
        for (i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (newX >= 0 && newX < grafo->columnas && newY >= 0 && newY < grafo->lineas &&
                grafo->nodos[newY][newX].head != NULL && !visitado[newY][newX]) {
                queue[rear++] = (Nodo){newX, newY};
                visitado[newY][newX] = true;
                distancia[newY][newX] = distancia[current.y][current.x] * grafo->columnas + current.x;
            }
        }
    }

    // Liberar memoria de la matriz de nodos de cada ruta
    for (i = 0; i < numPaths; i++) {
        free(allPaths[i]);
    }
    free(allPaths);

    // Encontrar el camino más corto
    if (numPaths > 0) {
        int shortestPathIndex = 0;
        int shortestPathLength = pathLength[0];

        for (i = 1; i < numPaths; i++) {
            if (pathLength[i] < shortestPathLength) {
                shortestPathIndex = i;
                shortestPathLength = pathLength[i];
            }
        }

        // Imprimir la ruta más corta
        printf("Ruta más corta encontrada:\n");
        for (i = shortestPathLength - 1; i >= 0; i--) {
            printf("(%d, %d) ", allPaths[shortestPathIndex][i].x, allPaths[shortestPathIndex][i].y);
            if (i > 0) {
                printf("-> ");
            }
        }
        printf("\n");
    } else {
        printf("No se encontraron rutas.\n");
    }

    // Liberar memoria
    free(queue);
    free(path);
    free(pathLength);
    for (i = 0; i < grafo->lineas; i++) {
        free(visitado[i]);
        free(distancia[i]);
    }
    free(visitado);
    free(distancia);
}



void convertirGrafo(struct ValoresImp* ValImp){
	int i, j;
	Grafo* grafo = iniGrafo(ValImp->Filas, ValImp->Col);
	Nodo start = {ValImp->coxy.salida_x, ValImp->coxy.salida_y};  // Coordenadas de 'S'
    Nodo destination = {ValImp->coxy.destino_x, ValImp->coxy.destino_y};  // Coordenadas de 'D'
    
    // Identificar nodos y conexiones en el laberinto
    for (i = 0; i < ValImp->Filas; i++) {
        for (j = 0; j < ValImp->Col; j++) {
            if (ValImp->laberintoM[i][j] == '.' || ValImp->laberintoM[i][j] == 'S' || ValImp->laberintoM[i][j] == 'D' || ValImp->laberintoM[i][j] == 's' || ValImp->laberintoM[i][j] == 'd') { // Punto
				Nodo currentNode = {j, i};
                // Conectar con nodos adyacentes
                if (i > 0 && ValImp->laberintoM[i - 1][j] == '.' || ValImp->laberintoM[i-1][j] == 'S' || ValImp->laberintoM[i-1][j] == 'D' || ValImp->laberintoM[i-1][j] == 's' || ValImp->laberintoM[i-1][j] == 'd') {
                    addEdge(grafo, currentNode, (Nodo){j, i - 1});
                }
                if (i < ValImp->Filas - 1 && ValImp->laberintoM[i + 1][j] == '.' || ValImp->laberintoM[i+1][j] == 'S' || ValImp->laberintoM[i+1][j] == 'D' || ValImp->laberintoM[i+1][j] == 's' || ValImp->laberintoM[i+1][j] == 'd') {
                    addEdge(grafo, currentNode, (Nodo){j, i + 1});
                }
                if (j > 0 && ValImp->laberintoM[i][j - 1] == '.' || ValImp->laberintoM[i][j-1] == 'S' || ValImp->laberintoM[i][j-1] == 'D' || ValImp->laberintoM[i][j-1] == 's' || ValImp->laberintoM[i][j-1] == 'd') {
                    addEdge(grafo, currentNode, (Nodo){j - 1, i});
                }
                if (j < ValImp->Col - 1 && ValImp->laberintoM[i][j + 1] == '.' || ValImp->laberintoM[i][j+1] == 'S' || ValImp->laberintoM[i][j+1] == 'D' || ValImp->laberintoM[i][j+1] == 's' || ValImp->laberintoM[i][j+1] == 'd') {
                    addEdge(grafo, currentNode, (Nodo){j + 1, i});
                }
            }
        }
    }

	BFS(grafo, start, destination);
	getch();
    // Imprimir el grafo
    printGraph(grafo);
    getch();
    
    // Liberar la memoria
    freeGraph(grafo);
}
*/
