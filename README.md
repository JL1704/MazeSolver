# Maze Solver with Graph Algorithms

Este proyecto implementa un programa en lenguaje C capaz de resolver laberintos representados como archivos de texto, utilizando algoritmos de búsqueda en grafos (DFS). Está diseñado para convertir un laberinto textual en un grafo, aplicar un algoritmo de búsqueda y marcar la ruta desde el punto de inicio `S` hasta el destino `D`.

---

## Características

- Lectura de laberintos desde archivos `.txt`
- Representación como grafo con listas de adyacencia
- Resolución automática con búsqueda en profundidad (DFS)
- Visualización del laberinto resuelto en terminal
- Interfaz por consola amigable para el usuario
- Manejo de errores comunes (archivo inválido, caracteres erróneos, etc.)

---

## Ejemplo de Entrada y Salida

**Entrada (`archivoLab2.txt`):**

[Entrada del programa](docs/Entrada.png)


**Salida esperada (terminal):**

[Salida del programa](docs/CapturaPrograma.png)


Se marca la ruta óptima desde `S` hasta `D` utilizando el símbolo `X`.


## Compilación y Ejecución

### Requisitos

- Compilador de C (ej. `gcc`)
- Sistema compatible (Linux, Windows o macOS)

### Instrucciones

1. Clona este repositorio:

```bash
git clone https://github.com/tu-usuario/maze-solver.git
cd maze-solver
```

2. Compila el código:
```bash
gcc -o maze_solver src/*.c
```
3. Ejecuta el programa

## Manejo de Errores

El programa detecta y reporta:

- Falta de archivo o nombre inválido
- Laberintos mal formateados
- Ausencia de los puntos `S` (inicio) o `D` (destino)
- Caracteres inválidos en el mapa

---

## Posibles Mejoras Futuras

- Implementación de BFS y Dijkstra como alternativas
- Interfaz gráfica usando `ncurses` o `SDL`
- Visualización de múltiples caminos posibles

---

## Referencias

- [Teoría de Grafos - BFS/DFS](https://academia-lab.com/enciclopedia/busqueda-en-profundidad/)
- [¿Qué es un Laberinto?](https://encuentratutarea.com/que-es-un-laberinto-definicion-tipos-y-caracteristicas/)
- [World History - Laberinto](https://www.worldhistory.org/trans/es/1-531/laberinto/)

---

## Autor

**José Luis Calderón Galarza**  
Estudiante de la Facultad de Ciencias Físico Matemáticas  
Universidad Autónoma de Nuevo León

---

## Licencia

Este proyecto está licenciado bajo la licencia **MIT**. Consulta el archivo [LICENSE](./LICENSE) para más detalles.

---

## Captura

[Captura del programa](docs/CapturaPrograma.png)




