#include "interface.h" 
#include <string.h>     
#include <stdbool.h> 
#include <ctype.h>   

// Estructura para almacenar las coordenadas de salida y destino del laberinto
struct Coordenadas {
    int salida_x;
    int salida_y;
    int destino_x;
    int destino_y;
};

// Estructura principal para almacenar información del laberinto y coordenadas
struct ValoresImp {
    int Filas;           // Número de filas en el laberinto
    int Col;             // Número de columnas en el laberinto
    char **laberintoM;   // Matriz que representa el laberinto
    struct Coordenadas coxy;  // Estructura que almacena las coordenadas de salida y destino
    bool b;              // Variable booleana para verificar si hay datos guardados
};

// Función para leer un archivo y cargar la información en la estructura ValoresImp
void Leer_Archivo(struct ValoresImp* ValImp, HANDLE console);
// Función para validar el laberinto y sus coordenadas
void validarLab(struct ValoresImp *ValImp);
// Función para cargar el laberinto desde un archivo y almacenarlo en la estructura ValoresImp
void laberintoArr(struct ValoresImp *ValImp, char nombreAr[50]);
// Función para guardar el laberinto en un archivo
void guardarLab(struct ValoresImp* ValImp);
// Función para mostrar mensajes de error en la consola
void mostrarError(const char *mensaje);
// Función para crear un nuevo archivo
FILE* crearArchivo(char nombreArchivo[50]);

char convertirAMayuscula(char letraMiniscula);

