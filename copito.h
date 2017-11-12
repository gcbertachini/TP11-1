#ifndef COPITO_H
#define COPITO_H

//Prototipos de funciones
void Copito (float x1, float y1, float x2, float y2, uint8_t ord_actual, float tol_actual );
float calc_tol (float x1, float y1, float x2, float y2);

//Variables necesarias
extern uint8_t orden;   //En el main
extern uint8_t tolerancia; 
#endif