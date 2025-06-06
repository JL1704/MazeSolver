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

// Estructura principal para almacenar informaci�n del laberinto y coordenadas
struct ValoresImp {
    int Filas;           // N�mero de filas en el laberinto
    int Col;             // N�mero de columnas en el laberinto
    char **laberintoM;   // Matriz que representa el laberinto
    struct Coordenadas coxy;  // Estructura que almacena las coordenadas de salida y destino
    bool b;              // Variable booleana para verificar si hay datos guardados
};

// Funci�n para leer un archivo y cargar la informaci�n en la estructura ValoresImp
void Leer_Archivo(struct ValoresImp* ValImp, HANDLE console);
// Funci�n para validar el laberinto y sus coordenadas
void validarLab(struct ValoresImp *ValImp);
// Funci�n para cargar el laberinto desde un archivo y almacenarlo en la estructura ValoresImp
void laberintoArr(struct ValoresImp *ValImp, char nombreAr[50]);
// Funci�n para guardar el laberinto en un archivo
void guardarLab(struct ValoresImp* ValImp);
// Funci�n para mostrar mensajes de error en la consola
void mostrarError(const char *mensaje);
// Funci�n para crear un nuevo archivo
FILE* crearArchivo(char nombreArchivo[50]);

char convertirAMayuscula(char letraMiniscula);

