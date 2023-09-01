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
#include <stdio.h>
// #include <time.h>
// CONFIG1
__code unsigned int __at (_CONFIG) configword = _INTOSCIO & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_ON & _CPD_ON;

void delay (unsigned int tiempo);

void main(void)
{
    ANSEL = 0;
    TRISIO = 0b00000000; // Configurar pines como salidas
    GPIO = 0b00001000; //Poner pines en bajo
    
    unsigned int time = 100;
    int contador = 0; // Inicializar el contador a 0

    while (1)
    {
        int contador = 0;
        for (int i = 0; i < 7; i++) {
            contador++;
        // for(int i = 0; i < sizeof(lista) / sizeof(lista[0]); i++){
        //     resultado = lista[i];
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
                    // encender cara dos
                    
                    GP0 = 0;
                    GP1 = 0;
                    GP2 = 1;
                    GP4 = 0;
                    GP5 = 0;
                    delay(time);
                    delay(time);
                    break;
                case 3:
                    // encender cara tres
                    GP0 = 0;
                    GP2 = 1;
                    GP4 = 0;
                    GP5 = 0;
                    GP1 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 4:
                    // encender cara cuatro
                    GP0 = 0;
                    GP1 = 0;
                    GP2 = 0;
                    GP4 = 1;
                    GP5 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 5:
                    // encender cara cinco
                    GP0 = 0;
                    GP2 = 0;
                    GP4 = 1;
                    GP5 = 1;
                    GP1 = 1;
                    delay(time);
                    delay(time);
                    break;
                case 6:
                    // encender cara seis
                    GP0 = 0;
                    GP1 = 1;
                    GP2 = 1;
                    GP4 = 1;
                    GP5 = 1;
                    delay(time);
                    delay(time);
                    break;
                default:
                    // Opción por defecto si el valor no coincide con ningún caso
                    GP0 = 0;
                    GP1 = 0;
                    GP2 = 0;
                    GP4 = 0;
                    GP5 = 0;
                    delay(time);
                    delay(time);
                    // ...
                    break;            
            
            }
        }
    }

}
void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}


// int main() {
//     unsigned int valor_0 = (unsigned int)time(NULL);
//     int n_aleatorio = valor_0;

//     for (int i = 0; i < 1; i++) {
//         n_aleatorio = fun_aleat(n_aleatorio);
//     }

//     return 0;
// }
// preubas exitosas
// while (1)
//     {
//         // prueba de encendido secuencial de LEDs
//         // GP0 = 1;
//         // delay(time);
//         // GP1 = 1;
//         // delay(time);
//         // GP2 = 1;
//         // delay(time);
//         // GP4 = 1;
//         // delay(time);
//         // GP4 = 0;
//         // delay(time);
//         // GP5 = 1;
//         // delay(time);
//         // GP5 = 0;
//         // delay(time);
//         // while (1)
//         {
//             /*
//             GP0 = 2;
//             GP1 = null;
//             GP2 = 1;
//             GP4 = 2;
//             GP5 = 2;

//             */
//             GP1 = 1;
//             GP0 = 1;
//             GP2 = 1;
//             GP4 = 1;
//             GP5 = 1;
//         }
        
//     }