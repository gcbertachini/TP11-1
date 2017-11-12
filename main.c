#include <allegro5/allegro.h>   //Manejo de display y eventos
#include <allegro5/allegro_image.h> //Manejo de imagenes
#include <stdio.h>      //Printf
#include <stdint.h> 
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <stdint.h>
#include <time.h>
#include "copito.h"


//Defines necesarios
#define true 1          //lo hago como defines en vez de bool porque no toma la libreria stdbool
#define false 0
#define D_WIDTH 800
#define D_HEIGHT 600



int main (void)
{
    //Declaracion de variables necesarias
    uint8_t orden = 3;  //Ingresado por el usuario    
    uint8_t ord_actual = 0; //Siempre empieza en 0, parametro que se le pasa a copito
    
    
    //Allegro
    ALLEGRO_DISPLAY *display = NULL; 
    
    
    //Seed para que cuando use random funcione siempre distinto. Por ahora no necesario
    //srand(time(NULL));
    
    //Inicializo allegro
     
   if(!al_init()) 
   {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
    
    //Inicializo display
    display = al_create_display(D_WIDTH, D_HEIGHT);
 
   if(!display) 
   {
	  fprintf(stderr, "failed to create display!\n");
      return -1;
   }
    
    //MAIN
    copito ();
    al_flip_display(display);
    
}
    
    
    
    

