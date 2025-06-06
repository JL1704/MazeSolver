#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "archivos.h"
#include "Validacion.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	struct ValoresImp ValImp;
	int opc;
	// Inicialización de la bandera 'b'
	ValImp.b = false;
	// Obtención del manejador de la consola
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
	// Llamada a funciones para configurar el menú y el cursor
	Menus(console, &cursorInfo);
	// Bucle principal del programa
	do {
		system("cls");
		// Mostrar opciones al usuario
		Opciones(console);
		opc = ValidacionEntero();
    	
    	// Ejecutar la opción seleccionada
    	switch (opc) {
    		case 1:
    			system("cls");
    			Leer_Archivo(&ValImp, console);
    			break;
    		case 2:
    			system("cls");
    			// Verificar si hay datos antes de llamar a convertirGrafo
    			if (ValImp.b) {
    				convertirGrafo(&ValImp, console);
    			} else {
    				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    				gotoxy(30, 2); printf("ERROR 008 - NO HAY DATOS GUARDADOS");
    				getch();
    			}
    			break;
    		case 3:
    			system("cls");
    			
    			// Verificar si hay datos antes de imprimir y guardar
    			if (ValImp.b) {
    				gotoxy(10, 2); printf("Se imprimira el laberinto\n");
	    			printLab(&ValImp, console);
	    			guardarLab(&ValImp);
    			} else {
    				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    				gotoxy(30, 2); printf("ERROR 008 - NO HAY DATOS GUARDADOS");
    				getch();
    			}
    			break;	
		}
    } while (opc != 4);
    
    // Salida del programa
    Sleep(200);
	system("cls");
	SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
    printf("\nSaliendo");
    Sleep(200);
    printf(". ");
    Sleep(200);
    printf(". ");
    Sleep(200);
    printf(". ");
	getch();
	
	return 0;
}

