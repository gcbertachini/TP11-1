#include <allegro5/allegro.h>   //Manejo de display y eventos
#include <allegro5/allegro_image.h> //Manejo de imagenes
#include <stdio.h>      //Printf
#include <stdint.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_color.h> 
#include <time.h>
#include "copito.h"


//Defines necesarios
#define true 1          //lo hago como defines en vez de bool porque no toma la libreria stdbool
#define false 0
#define D_WIDTH 800
#define D_HEIGHT 600

uint8_t orden = 3;      //LAS HIZE GLOBALES POR QUE SINO COPITO NO LAS VEo
float tolerancia = 30;

int main (void)
{
    //Declaracion de variables necesarias
      //Ingresado por el usuario    
    uint8_t ord_actual = 0; //Siempre empieza en 0, parametro que se le pasa a copito
    uint8_t close_display = false;
    uint8_t repeat = true;  //variable para repetir;
    
    //Allegro
    ALLEGRO_DISPLAY *display = NULL; 
    ALLEGRO_EVENT_QUEUE  *event_queue = NULL;
    
    //Seed para que cuando use random funcione siempre distinto. Por ahora no necesario
    //srand(time(NULL));
    
    //Inicializo allegro
     
   if(!al_init()) 
   {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
     if(!al_init_primitives_addon()){
	  fprintf(stderr, "failed to initialize primitives!\n");
	  return -1;}
    event_queue = al_create_event_queue();
    if(!event_queue) {
		printf("failed to create event_queue!\n");
		return -1;
	}
    //Inicializo teclado
    if(!al_install_keyboard()) {
		printf("failed to initialize the keyboard!\n");
                al_destroy_event_queue(event_queue);
		return -1;
	}
    
    
    
    
    
    //Inicializo display
    display = al_create_display(D_WIDTH, D_HEIGHT);
 
   if(!display) 
   {
       al_destroy_event_queue(event_queue);
       
	  fprintf(stderr, "failed to create display!\n");
      return -1;
   }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    //MAIN
    //al_draw_filled_triangle(250,200,550,200,400,300,al_color_name("red")); 
    while (!close_display)
    {
        ALLEGRO_EVENT evento;
        if (al_get_next_event(event_queue, &evento))    
        {
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //verifico si debo cerrar el display
                close_display = true;
            
            if (evento.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch (evento.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:        //Si se oprime escape, el programa cierra
                        close_display = true;
                        break;
                    case ALLEGRO_KEY_R:
                        repeat = true;
                        al_clear_to_color(al_color_name("black"));
                        al_rest(1.0);
                        break;
                    
                              
                }
                
            }
        
        }
        if(repeat){
            Copito (250, 200, 550, 200, ord_actual, calc_tol(250, 200, 550, 200));
            al_flip_display();
            repeat = false;
        }
    }
        
        
    
    
    //Destruyo lo que cree en Allegro
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    return 0;
    
}
    
    
    
    

