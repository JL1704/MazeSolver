#include "Validacion.h"


int ValidacionEntero(){
	char Aux[' '];
	int i,p,y,num;
	do{
	    gotoxy(10,8);printf("?  ");	
        fflush(stdin);
        gets(Aux);//se lee los datos introducidos
        y = strlen(Aux);
     
	    for(i=0;i < y;i++)
	      {
             if(isdigit(Aux[i]))
                p = 1;	
	         else
         		p = 0;
	         if(p ==0)
         	   {
           		 gotoxy(30,10);printf("ERROR 10 - Opcion mal introducida");
		   		 break;
         	   }
	  	 }
        if(y==0)
	      p=0;
	}while(p==0);
   
   num = atoi(Aux);
   return num;
}
