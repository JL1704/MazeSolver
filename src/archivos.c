#include "archivos.h"

// Funci�n para leer un laberinto desde un archivo de texto, obtener informaci�n relevante y realizar algunas validaciones.
void Leer_Archivo(struct ValoresImp *ValImp, HANDLE console) {
    FILE *archivo; // Puntero al archivo que contendr� el laberinto
    char nombreArch[50], linea[100], caracter; // Arreglos de caracteres para almacenar informaci�n
    ValImp->Filas = 1; // Inicializaci�n del n�mero de filas en 1
    ValImp->Col = 0; // Inicializaci�n del n�mero de columnas en 0

    // Configuraci�n de colores en la consola
    SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(10, 4); printf("Ingrese el nombre del archivo que contiene el laberinto:");
    SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
    gotoxy(10, 5); printf("Ejemplo '../examples/archivo_de_laberinto.txt'");
    gotoxy(67, 4); scanf("%s", &nombreArch); // Solicitar al usuario el nombre del archivo

    archivo = fopen(nombreArch, "rt"); // Intentar abrir el archivo en modo lectura de texto

    // Manejo de error si el archivo no se puede abrir
    if (archivo == NULL) {
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\n\t\tERROR 005 NO SE ENCONTRO UN ARCHIVO CON EL NOMBRE %s", nombreArch);
        exit(1);
    }

    // Mensajes de lectura del archivo
    SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
    gotoxy(20, 7); printf("Se leera el archivo %s\n\n\n", nombreArch);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

    // Leer cada l�nea del archivo y mostrarla en la consola
    fgets(linea, 100, archivo);
    while (!feof(archivo)) {
        printf("\t\t\t%s", linea);
        ValImp->Filas++; // Contar el n�mero total de filas
        fgets(linea, 100, archivo);
    }
    
    printf("\t\t\t%s\n\n\t\t", linea);

    // Calcular el n�mero de columnas contando caracteres hasta el primer salto de l�nea
    fseek(archivo, 0, SEEK_SET);
    while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF) {
        ValImp->Col++;
    }
    fclose(archivo); // Cerrar el archivo
	
    // Visualizar la representaci�n en arreglo del laberinto y realizar validaciones

    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    laberintoArr(ValImp, nombreArch);
    validarLab(ValImp);
    ValImp->b = true; // Establecer b en true
    // Mostrar mensajes y visualizar informaci�n importante
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n\n\t\tValores Importantes Obtenidos");
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n\n\t\t\tEl laberinto tiene %d filas y %d columnas", ValImp->Filas, ValImp->Col);
  	printf("\n\t\t\tCoordenadas de START (%d, %d)", ValImp->coxy.salida_x, ValImp->coxy.salida_y);
    printf("\n\t\t\tCoordenadas de DESTINATION (%d, %d)\n\t", ValImp->coxy.destino_x, ValImp->coxy.destino_y);
    SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);

    getch(); // Esperar a que el usuario presione una tecla antes de cerrar la consola
}

void laberintoArr(struct ValoresImp *ValImp, char nombreAr[50]){
	
	FILE *arch;
	int i, j;
	char caracter;
	
	ValImp->laberintoM = (char **)malloc(ValImp->Filas * sizeof(char *));
	if (ValImp->laberintoM == NULL) {
        printf("Error: No se pudo asignar memoria para las filas.\n");
        exit(1);
    }

    // Asigna memoria para las columnas de cada fila
    for (i = 0; i < ValImp->Filas; i++) {
        ValImp->laberintoM[i] = (char *)malloc(ValImp->Col * sizeof(char));
        if (ValImp->laberintoM[i] == NULL) {
            printf("Error: No se pudo asignar memoria para las columnas.\n");
            exit(1);
        }
    }
	
	arch = fopen(nombreAr, "rt");
	if(arch == NULL){
		printf("\n\n\t\tERROR 005 NO SE ENCONTRO UN ARCHIVO CON EL NOMBRE %s", nombreAr);
		exit(1);
	}
	
	caracter = fgetc(arch);
	for (i = 0; i < ValImp->Filas; i++) {
        for (j = 0; j < ValImp->Col; j++) {
        	while (caracter == '\n') {
            	caracter = fgetc(arch);
        	}
        	ValImp->laberintoM[i][j] = caracter;
        	caracter = fgetc(arch);
        }
    }
    fclose(arch);
	
}

void mostrarError(const char *mensaje) {
    printf("\n\tERROR - El laberinto no es valido");
    printf("\n\t%s", mensaje);
    exit(2);
}

void validarLab(struct ValoresImp *ValImp) {
    int i, j, cs = 0, cd = 0;

    if (ValImp->Filas < 3 || ValImp->Col < 3 || (ValImp->Filas == 3 && ValImp->Col == 3))
        mostrarError("ERROR 004 DIMENSIONES DEL LABERINTO NO VALIDAS");

    for (i = 0; i < ValImp->Filas; i++) {
        for (j = 0; j < ValImp->Col; j++) {
            if ((i == 0 || i == ValImp->Filas - 1 || j == 0 || j == ValImp->Col - 1) &&
                ValImp->laberintoM[i][j] != '#'){
                mostrarError("ERROR 001 LAS PAREDES EXTERIORES DEL LABERINTO NO SON VALIDAS");
			}
            if (ValImp->laberintoM[i][j] == 'S' || ValImp->laberintoM[i][j] == 's') {
            	ValImp->laberintoM[i][j] = convertirAMayuscula(ValImp->laberintoM[i][j]);
                cs++;
                ValImp->coxy.salida_x = j;
                ValImp->coxy.salida_y = i;
            }
			if (ValImp->laberintoM[i][j] == 'D' || ValImp->laberintoM[i][j] == 'd') {
				ValImp->laberintoM[i][j] = convertirAMayuscula(ValImp->laberintoM[i][j]);
                cd++;
                ValImp->coxy.destino_x = j;
                ValImp->coxy.destino_y = i;
            }
        }
    }
    if (cs != 1)
        mostrarError("ERROR 002 NO SE ENCONTRO UN 'S' START VALIDO");
    if (cd != 1)
        mostrarError("ERROR 003 NO SE ENCONTRO UN 'D' DESTINATION VALIDO");
    
    
    printf("El laberinto si es valido");

}

// Funci�n para crear un archivo de escritura y lectura
FILE* crearArchivo(char nombreArchivo[50]) {
    FILE* archivo = fopen(nombreArchivo, "w+"); // "w+" abre el archivo para escritura y lectura, cre�ndolo si no existe
    if (archivo == NULL) {
		printf("\n\tERROR 006 - NO SE CREO EL ARCHIVO '%s' CORRECTAMENTE ", nombreArchivo);
		exit(1);
	}
    return archivo;
}

void guardarLab(struct ValoresImp* ValImp){
	
	char nombreArch[50];
	HANDLE console2 = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	
	SetConsoleTextAttribute(console2, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoxy(10,0);printf("Ingrese un nombre para crear un archivo  y guardar el laberinto:");
	SetConsoleTextAttribute(console2, FOREGROUND_INTENSITY);
	gotoxy(10,1);printf("Ejemplo 'archivo_para_guardar_laberinto.txt'");
	gotoxy(75,0);scanf("%s", &nombreArch);
	
	// Validar que el nombre de archivo termine con ".txt"
    if(strlen(nombreArch) >= 4 && strcmp(nombreArch + strlen(nombreArch) - 4, ".txt") == 0) {
        FILE* archivo = crearArchivo(nombreArch);

        if(archivo != NULL) {
			for (i = 0; i < ValImp->Filas; i++) {
        		for (j = 0; j < ValImp->Col; j++) {
        			fprintf(archivo, "%c", ValImp->laberintoM[i][j]);
        		}
        		fprintf(archivo, "\n");
        	}
            fclose(archivo); // Cerrar el archivo cuando hayas terminado
            SetConsoleTextAttribute(console2,FOREGROUND_GREEN |FOREGROUND_RED);
            printf("\n\t\tArchivo '%s' guardado exitosamente.\n", nombreArch);
        }
    }else {
    	SetConsoleTextAttribute(console2,FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\tERROR 007 - El nombre del archivo debe terminar con \".txt\"\n");
        exit(1);
    }
    getch();
}

char convertirAMayuscula(char letraMiniscula) {
    // Utiliza la funci�n toupper para convertir la letra a may�scula
    return toupper(letraMiniscula);
}
