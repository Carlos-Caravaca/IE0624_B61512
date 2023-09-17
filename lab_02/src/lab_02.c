#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PB0 PB0     //amarillo vehículo
#define LED_PB1 PB1     //verde vehiculo
#define LED_PB2 PB2     //verde peaton
#define LED_PB3 PB3     //rojo peaton
#define LED_PD5 PD5     // Rojo vehículo
#define BUTTON_PIN PB6  //boton

volatile uint32_t mili_seg = 0;

// función de inicialización del Timer1
void Timer1_Init() {
    TCCR1A = 0;             // modo normal de operación
    TCCR1B = (1 << WGM12);  // configura el temporizador en modo CTC
    OCR1A = 249;            // valor para comparación (249 ciclos, asumiendo una frecuencia de reloj de 16 MHz y preescalador de 64)
    TIMSK |= (1 << OCIE1A); // habilita la interrupción por comparación con OCR1A
    TCCR1B |= (1 << CS11) | (1 << CS10); // Configura el preescalador a 64
}

// rutina de interrupción del Timer1 (OCIE1A)
ISR(TIMER1_COMPA_vect) {
    mili_seg++; // incrementa el contador de milisegundos en cada interrupción
}


// función para esperar un número de milisegundos usando Timer1
void timer01_ms(uint32_t ms) {
    uint32_t start_time = mili_seg;
    while (mili_seg - start_time < ms) {
        // espera hasta que se alcance el tiempo deseado
    }
}

// función para inicializar el botón como entrada con resistencia pull-up
void Button_Init() {
    DDRB &= ~(1 << BUTTON_PIN); // configura el pin del botón como entrada
    PORTB |= (1 << BUTTON_PIN); // habilita la resistencia pull-up para el botón
}

// función para verificar si el botón está presionado
uint8_t Button_IsPressed() {
    // retorna 1 si el botón está presionado
    return !(PINB & (1 << BUTTON_PIN)); 
}

int main(void) {
    // se coonfiguran los pines de los LEDs como salidas
    DDRB |= (1 << LED_PB0); 
    DDRB |= (1 << LED_PB1);
    DDRB |= (1 << LED_PB2);
    DDRB |= (1 << LED_PB3);
    DDRD |= (1 << LED_PD5);

    Timer1_Init();      // inicializa Timer1
    Button_Init();      // inicializa el botón
    sei();              // Habilita las interrupciones globales
    int WAIT = 1; 

    while (1) {
        // Se establece el estado inicial en verde para vehiculos
        // y rojo para peatones
        PORTB |= (1 << LED_PB1);    //verde vehiculo endendido
        PORTB |= (1 << LED_PB3);    //rojo peaton encendido
        PORTD &= ~(1 << LED_PD5);   //rojo vehiculo apagado
        PORTB &= ~(1 << LED_PB2);   //verde peaton apagado
        PORTB &= ~(1 << LED_PB0);   //amarillo apagado
        Button_IsPressed();
        
        if (WAIT)
        {
            timer01_ms(10000);
            WAIT = 0;
        }
        
        // se debe mantener pulsado el boton hasta que inicie 
        // la secuencia de luces, en ese momento ya se puede soltar
        if (Button_IsPressed()) {
            // LDPV parpedeando durante 3 segundos
            // junto con la luz amarilla
            PORTB &= ~(1 << LED_PB3);
            PORTB &= ~(1 << LED_PB1);
            PORTB &= ~(1 << LED_PB0); 
            timer01_ms(500);
            PORTB |= (1 << LED_PB1);
            PORTB |= (1 << LED_PB0);
            timer01_ms(500);
            PORTB &= ~(1 << LED_PB1);
            PORTB &= ~(1 << LED_PB0); 
            timer01_ms(500);
            //PORTB |= (1 << LED_PB1);
            PORTB |= (1 << LED_PB0);
            timer01_ms(500);
            //PORTB &= ~(1 << LED_PB1);
            PORTB &= ~(1 << LED_PB0); 
            timer01_ms(500);
            //PORTB |= (1 << LED_PB1);
            PORTB |= (1 << LED_PB0);
            timer01_ms(500);
            PORTB &= ~(1 << LED_PB1);
            PORTB &= ~(1 << LED_PB0); 
            // se enciende verde peaton
            // se enciende rojo vehiculo
            PORTB |= (1 << LED_PB2);
            PORTD |= (1 << LED_PD5);
            timer01_ms(15000);

            // regresa a su estado inicial
            PORTB |= (1 << LED_PB1);    //verde vehiculo endendido
            PORTB |= (1 << LED_PB3);    //rojo peaton encendido
            PORTD &= ~(1 << LED_PD5);   //rojo vehiculo apagado
            PORTB &= ~(1 << LED_PB2);   //verde peaton apagado
            PORTB &= ~(1 << LED_PB0);   //amarillo apagado

            // Espera hasta que se libere el botón para evitar múltiples pulsaciones
            while (Button_IsPressed()) {}
            WAIT = 1;
        }
    }
    return 0;   
}
