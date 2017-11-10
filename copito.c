#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include "copito.h"
#include <math.h>   //Para funcion calc_tol

//Definicion de macros internas

//Crean los nuevos puntos de la base del triangulo
#define X1 (a,b) ((((a)+(b))/2)/3)  //recibe los dos puntos en x de la base
#define Y1 (a,b) ((((a)+(b))/2)/3)  //recibe los dos puntos en y de la base
#define X2 (a,b) ((((a)+(b))/2)*(2.0/3))  //recibe los dos puntos en x de la base
#define Y2 (a,b) ((((a)+(b))/2)*(2.0/3))  //recibe los dos puntos en y de la base

/*Definicion Funcion Copito
 Funcion recursiva que recive:
 *  las coordenadas de los dos puntos inferiores donde se quiere fijar un triangulo euilatero (X,Y),
 *  el odren del copo, es decir cuantos triangulos debe tener 
 * y la toleranci: cual es la minima separacion entre los puntos del triangulo.
 * 
 * No devuelve nada, imprime en un display de allegro el copo de Koch
 * Utiliza la funcion Calc para calcular los nuevos puntos donde se deben imprimir los triangulos
 */

void Copito (float x1, float y1, float x2, float y2, uint8_t ord_actual, float tol_actual )
//              {COORD. P1}         {COORD. P2}         
{
    //Caso Base dibuja un triangulo
    if ((ord_actual == orden) || (tol_actual <= tolerancia))
    {
        al_draw_filled_triangle(x1, y1, //Coordenadas de P1 (izquierda)
                                x2, y2, //Coordenadas de P2 (derecha)
                                (x1+x2)/2, y1-(x2-x1),  //Coordenadas de P3(arriba)
                                al_color_rgb_to_name( (rand () % 255), (rand () % 255), (rand () % 255)) ); //Color
    }
    else
    {
        Copito (X1(x1,x2), Y1(y1,y2),   //Coord. del nuevo P1. se encuentra a 1/3 del lateral izq del actual
                X2(x1,x2), Y2(y1,y2), //Coord. del nuevo P2. . Se encuentra a 2/3 del lateral izq del actual   
                ord_actual-1,   //Disminuyo en uno los triangulos que me faltan para alcanzar el orden propuesto
                calc_tol(X1(x1,x2), Y1(y1,y2), X2(x1,x2), Y2(y1,y2) ) );
    }
}

//Funcion que calcula la longitud de la base del triangulo actual. Pitagoras para los puntos actuales de la base



static float calc_tol (float x1, float y1, float x2, float y2)
{
    float rta = sqrt((pow((x2-x1), 2)+pow(y2-y1), 2));
    return rta;
}