#include "interface.h"

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
}

void Aviso_Importante(HANDLE console){

    // Muestra el encabezado "AVISO IMPORTANTE" en color rojo brillante
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoxy(50,1);printf("AVISO IMPORTANTE");
    // Muestra el contenido en color azul brillante
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    gotoxy(20,3);printf("Objetivo:");
    gotoxy(10,4);printf("Este programa resuelve laberintos recibidos como archivos de texto");
    gotoxy(10,5);printf("utilizando el algoritmo de Búsqueda en Profundidad (DFS) aplicado a grafos.");

    gotoxy(20,7);printf("Proyecto:");
    gotoxy(10,8);printf("Este proyecto fue desarrollado como parte del Producto Integrador de Aprendizaje (PIA)");
    gotoxy(10,9);printf("para la materia de Estructura de Datos del tercer semestre de LCC");
    gotoxy(10,10);printf("en la Facultad de Ciencias Físicas y Matemáticas (FCFM) de la Universidad Autónoma de Nuevo León (UANL).");

    gotoxy(20,12);printf("Estudiante:");
    gotoxy(10,13);printf("Nombre: Jose Luis Calderon Galarza");
    gotoxy(10,14);printf("Carrera: Licenciatura en Ciencias de la Computacion (LCC)");
    gotoxy(10,15);printf("Semestre: 3");
    gotoxy(10,16);printf("Universidad: Universidad Autonoma de Nuevo Leon (UANL)\n\n");
    Presionar(console);

}

void Instrucciones(HANDLE console){

    // Muestra el encabezado "INSTRUCCIONES" en color rojo brillante
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoxy(50, 1);printf("INSTRUCCIONES");
    // Muestra el contenido en color azul brillante
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    gotoxy(10,4);printf("1.-Antes de empezar a arrancar el programa debe tener de antemano un laberinto almacenado en un archivo");
    gotoxy(13,5);printf("de texto como el que se muestra acontinuacion:");
    gotoxy(50,6);printf("########");
    gotoxy(50,7);printf("#S##..D#");
    gotoxy(50,8);printf("#.##.###");
    gotoxy(50,9);printf("#......#");
    gotoxy(50,10);printf("########");
    gotoxy(15,11);printf("1.1- Consideraciones a tomar");
    gotoxy(18,12);printf("a) Las 4 paredes exteriores deben de estar completas, estas se representan con el simbolo '#'");
    gotoxy(18,13);printf("b) Debe contar con solo un Start representado con la letra 'S' y un solo Destination representado");
	gotoxy(22,14);printf("con la letra 'D'"); 
    gotoxy(18,15);printf("c) Los '.' se toman como los caminos libres por donde se puede recorrer el laberinto");
    gotoxy(18,16);printf("d) Se recomienda no ingresar laberintos con dimensiones mas grandes que 100x100");
    gotoxy(18,17);printf("e) Las dimensiones minimas de los laberintos son de 3 x 4");
    gotoxy(18,18);printf("f) En caso de no cumplir con alguna de estas condiciones el programa no ejecutara correctamente y"); 
    gotoxy(22,19);printf("terminara su ejecucion\n\n");
    gotoxy(10,20);printf("2.- Al ingresar un laberinto valido se mostraran los valores importantes en pantalla");
    gotoxy(10,21);printf("3.- Despues de validar el laberinto podra acceder a la opcion de resolverlo");
    gotoxy(10,22);printf("4.- En la opcion de 'Resolver Laberinto' se mostraran las conexiones de los nodos, el recoorrido realizado y");
	gotoxy(14,23);printf("el laberinto resuelto");
    gotoxy(10,24);printf("5.- En la opcion de 'Guardar Laberinto' se mostrara el laberinto que actualmente se tiene almacenado y se"); 
	gotoxy(14,25);printf("tendra la opcion de guardar en nuevo archivo de texto");
    gotoxy(10,26);printf("6.- Eliga la opcion 4 cuando desee terminar la ejecucion del programa");
    gotoxy(10,27);printf("7.- En caso de cometer un error al utilizar el programa, se mostrara en pantalla el error cometido y segun el"); 
	gotoxy(14,28);printf("caso terminara el programa o seguir su ejecucion");
	gotoxy(10,29);printf("8.- Gracias por su atencion - Jose Luis Calderon Galarza\n\n");
    
	Presionar(console);
}

void Presionar(HANDLE console) {
    int i;
    for (i = 0; i < 20; i++) {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\r\t\t\t\t\tPresione una tecla para continuar");
        Sleep(500);  // Espera 500 milisegundos
        printf("\r\t\t\t\t\t                                  \r");

        // Verifica si se ha presionado una tecla
        if (_kbhit()) {
            getch(); // Limpia el búfer del teclado
            break;
        }

        Sleep(500);  // Espera 500 milisegundos
    }
}

void Menus(HANDLE console, CONSOLE_CURSOR_INFO cursorInfo){
	
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = 0; // Oculta el cursor
    SetConsoleCursorInfo(console, &cursorInfo);
    Aviso_Importante(console);
	Sleep(200);
	system("cls");
	Sleep(200);
	Instrucciones(console);
	Sleep(200);
	system("cls");
	Sleep(200);
	GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = 1; // Aparece el cursor
    SetConsoleCursorInfo(console, &cursorInfo);
    SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
}

void Opciones(HANDLE console){
		// Muestra el encabezado en color rojo brillante
    	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    	gotoxy(50, 2);printf("OPCIONES");
    	// Muestra el contenido en color azul brillante
    	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    	gotoxy(10,4);printf("1.- Leer archivo");
    	gotoxy(10,5);printf("2.- Resolver laberinto");
    	gotoxy(10,6);printf("3.- Guardar laberinto");
    	gotoxy(10,7);printf("4.- Salir");
}
