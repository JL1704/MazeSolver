#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <conio.h>  

// Funci�n para posicionar el cursor en la pantalla
void gotoxy(int x, int y);
// Funci�n para mostrar un aviso importante en la consola
void Aviso_Importante(HANDLE console);
// Funci�n para mostrar las instrucciones en la consola
void Intrucciones(HANDLE console);
// Funci�n para esperar a que el usuario presione una tecla
void Presionar(HANDLE console);
// Funci�n para mostrar las opciones del programa en la consola
void Opciones(HANDLE console);

void Menus(HANDLE console, CONSOLE_CURSOR_INFO cursorInfo);
