#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include "copito.h"
#include <math.h>   //Para funcion calc_tol

//Definicion de macros internas


//Crean los nuevos puntos de la base del triangulo (derecho)
#define X1der(x1,x2) ((((x1)+(x2))/2)/3)  //1/3Xm
#define Y1der(y1, x1, x2) ((y1)-(sin (60)*((x1)-(x2))/3))  //el eje Y crece para abajo. 1/3 de la altura (sen (60)*hip)
#define X2der(x1,x2) ((((x1)+(x2))/2)*(2.0/3))  //2/3Xm
#define Y2der(y1, x1, x2) ((y1)-(sin(60)*((x1)-(x2))*(2.0/3))) // 2/3 de la altura  

////Crean los nuevos puntos de la base del triangulo (izquierda)
#define X1izq(x1,x2) ((((x1)+(x2))/2)+(((x1)+(x2))/2)*(2.0/3)) //Xm + 2/3Xm  
#define Y1izq(y1, x1, x2) ((y1)-(sin (60)*((x1)-(x2))/3))  //Los y son iguales que los de la derecha. 1/3 de la altura
#define X2izq(x1,x2) ((((x1)+(x2))/2)+(((x1)+(x2))/2)/3)  //Xm + 1/3Xm
#define Y2izq(y1, x1, x2) ((y1)-(sin(60)*((x1)-(x2))*(2.0/3)))   

////Crean los nuevos puntos de la base del triangulo (abajo).
//No es necesario definir las Y porque son las mismas que la actual
#define X1abaj(x1,x2) (((x2)-(x1))/3) //1/3base 
#define X2abaj(x1,x2) (((x2)-(x1))*(2.0/3))  //2/3base
  

//Punto superior del triangulo

static float y3 (float y1, float x1, float x2)     //la posicion del punto de abajo menos la base (=altura hip*sen (60))
{
    float rta = y1 - (sin(60)*(x2 - x1)) ;   //ACA NOSE QUE ONDA POR LO DE QUE Y3 QUEDA RANCIO
    return rta;
}  
static float x3 (float x1, float x2)   //El punto medio de la base
{
    float rta = (x1+x2)/2;
    return rta;
}   

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
///////           {COORD. P1}         {COORD. P2}         
{
    //Caso Base dibuja un triangulo
    if ((ord_actual == orden) /*|| (tol_actual <= tolerancia)*/)    //Caso base
    {
        float x31 = x3(x1,x2);      //RESUELVO AFUERA ASI PUEDO VER BIEN EN EL GDB LAS VARIABLES
        float y31= y3(y1,x1,x2);
        
        al_draw_filled_triangle(x1, y1, //Coordenadas de P1 (izquierda)
                                x2, y2, //Coordenadas de P2 (derecha)
                                x31, y31,  //Coordenadas de P3(arriba)
                                al_color_name("pink")); //Color
        
    }
    else        //Caso Recursivo
    {
        //Dibujo los triangulos del cateto derecho
        Copito (X1der(x1,x2), Y1der(y1, x1, x2),   //Coord. del nuevo P1. se encuentra a 1/3 del lateral izq del actual
                X2der(x1,x2), Y2der(y1, x1, x2), //Coord. del nuevo P2. . Se encuentra a 2/3 del lateral izq del actual   
                ord_actual+1,   //Disminuyo en uno los triangulos que me faltan para alcanzar el orden propuesto SUMO
                calc_tol(X1der(x1,x2), Y1der(y1, x1, x2), X2der(x1,x2), Y2der(y1, x1, x2) ) );
        
        //Dibujo los triangulos del cateto izquierdo
        Copito (X1izq(x1,x2), Y1izq(y1, x1, x2),   //Coord. del nuevo P1. se encuentra a 1/3 del lateral izq del actual
                X2izq(x1,x2), Y2izq(y1, x1, x2), //Coord. del nuevo P2. . Se encuentra a 2/3 del lateral izq del actual   
                ord_actual+1,   //Disminuyo en uno los triangulos que me faltan para alcanzar el orden propuesto  PUSE SUMAR
                calc_tol(X1izq(x1,x2), Y1izq(y1, x1, x2), X2izq(x1,x2), Y2izq(y1, x1, x2) ) );
        
        if (ord_actual ==0) //Solo debo dibujar triangulos en la base la primera vez que se llama a la funcion
        {
        //Dibujo los triangulos en la base
        Copito (X1abaj (x1,x2), y1,   
                X2abaj (x1,x2), y2,   
                ord_actual+1,   //Disminuyo en uno los triangulos que me faltan para alcanzar el orden propuesto   PUSE SUMAR
                calc_tol(X1der(x1,x2), Y1der(y1, x1, x2), X2der(x1,x2), Y2der(y1, x1, x2) ) );
        al_draw_filled_triangle(x1, y1, x2, y2, x3(x1,x2), y3(y1, x1, x2), al_color_name("pink"));  //dibujo el triangulo central
        }
        
        
    }
}

//Funcion que calcula la longitud de la base del triangulo actual. Pitagoras para los puntos actuales de la base
//La nueva base se encontrara en la hipotenusa

float calc_tol (float x1, float y1, float x2, float y2) 
{
    float rta = sqrt( pow ((x2-x1),2)+ pow ( (y2-y1) ,2));
    return rta;
}


