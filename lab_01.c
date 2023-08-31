/*
Autor: Carlos A. Caravaca
Fecha: 2 septiembre
Título: Laboratorio 01
----------------------------------------------------------------
Descripción:
El proyecto propone un simulador de dado simple 
que utiliza LEDs para mostrar resultados. Emplea 
un microcontrolador PIC12F683 y un botón como entrada. 
Al presionar el botón, el microcontrolador genera un número 
aleatorio que representa el resultado del lanzamiento de un 
dado. Los LEDs se activan en secuencia para mostrar este número 
de manera visual, imitando las caras de un dado convencional.
*/

#include <pic14/pic12f683.h>
// CONFIG1
__code unsigned int __at (_CONFIG) configword = _INTOSCIO & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_ON & _CPD_ON;

void delay (unsigned int tiempo);
void main(void)
{
    TRISIO = 0b00000000; // Configurar pines como salidas
        GPIO = 0b00001000; //Poner pines en bajo
   
    unsigned int time = 100;
    while (1)
    {
        // prueba de encendido secuencial de LEDs
        GP0 = 1;
        delay(time);
        GP1 = 1;
        delay(time);
        GP2 = 1;
        delay(time);
        GP4 = 1;
        delay(time);
        GP5 = 1;
        delay(time);
        GP5 = 0;
        delay(time);

        // GP0 = 1;
        // GP1 = 1;
        // GP2 = 1;
        // GP4 = 1;
        // GP5 = 1;
    }

}
void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}

