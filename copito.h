
#ifndef COPITO_H
#define COPITO_H

extern uint8_t orden;   //Variable inicializada en main (argumento ingresado por el usuario)
extern uint8_t tolerancia;  //Varaible inicializada en el main (argumento introducido por el usuario)

//Prototipos de fuinciones globales
void Copito (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t ord_actual, float tol_actual );

#endif /* COPITO_H */

