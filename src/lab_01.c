/*
Autor: Carlos A. Caravaca Mora.
Carne: B61512.
Fecha: 2 septiembre.
Título: Laboratorio 01.
----------------------------------------------------------------
Descripción:
El proyecto propone un simulador de dado simple 
que utiliza LEDs para mostrar resultados. Emplea 
un microcontrolador PIC12F683, amplificadores, 
resistencias y un botón como entrada.
*/

#include <pic14/pic12f683.h>
#include <stdio.h>

__code unsigned int __at (_CONFIG) configword = _INTOSCIO & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_ON & _CPD_ON;

void delay (unsigned int tiempo);

void main(void)
{
    ANSEL = 0;                  //  todos los pines configurados como digitales
    TRISIO = 0b00000000;        //  configurar pines como salidas
    GPIO = 0b00001000;          //  poner pines en bajo
    
    unsigned int time = 100;    //  para delay        

    while (1)
    {
        int contador = 0;       //  inicializar el contador en 0

        for (int i = 0; i < 7; i++) {
            contador++;

            switch (contador) 
            {
                case 1:
                    // encender cara 1
                    GP0 = 0;
                    GP2 = 0;
                    GP4 = 0;
                    GP5 = 0;
                    GP1 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 2:
                    // encender cara 2
                    
                    GP0 = 0;
                    GP1 = 0;
                    GP2 = 1;
                    GP4 = 0;
                    GP5 = 0;
                    delay(time);
                    delay(time);
                    break;
                case 3:
                    // encender cara 3
                    GP0 = 0;
                    GP2 = 1;
                    GP4 = 0;
                    GP5 = 0;
                    GP1 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 4:
                    // encender cara 4
                    GP0 = 0;
                    GP1 = 0;
                    GP2 = 0;
                    GP4 = 1;
                    GP5 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 5:
                    // encender cara 5
                    GP0 = 0;
                    GP2 = 0;
                    GP4 = 1;
                    GP5 = 1;
                    GP1 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 6:
                    // encender cara 6
                    GP0 = 0;
                    GP1 = 1;
                    GP2 = 1;
                    GP4 = 1;
                    GP5 = 1;
                    delay(time);
                    delay(time);
                    break;
                default:
                    // opción por defecto si el valor no coincide con ningún caso
                    GP0 = 0;
                    GP1 = 0;
                    GP2 = 0;
                    GP4 = 0;
                    GP5 = 0;
                    delay(time);
                    delay(time);
                    break;            
            
            }
        }
    }

}
//  implementación de la función delay
void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
