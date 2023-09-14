#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PB0

volatile uint32_t ms = 0;

// Función de inicialización del Timer1
void Timer1_Init() {
    TCCR1A = 0;             // Modo normal de operación
    TCCR1B = (1 << WGM12);  // Configura el temporizador en modo CTC
    OCR1A = 249;            // Valor para comparación (249 ciclos, asumiendo una frecuencia de reloj de 16 MHz y preescalador de 64)
    TIMSK |= (1 << OCIE1A); // Habilita la interrupción por comparación con OCR1A
    TCCR1B |= (1 << CS11) | (1 << CS10); // Configura el preescalador a 64
}

// Rutina de interrupción del Timer1 (OCIE1A)
ISR(TIMER1_COMPA_vect) {
    ms++; // Incrementa el contador de milisegundos en cada interrupción
}

// Función para esperar un número de milisegundos usando Timer1
void time1_delay(uint32_t ms) {
    uint32_t start_time = ms;
    while (ms - start_time < ms) {
        // Espera hasta que se alcance el tiempo deseado
    }
}

int main(void) {
    DDRB |= (1 << LED_PIN); // Configura el pin del LED como salida
    Timer1_Init(); // Inicializa Timer1
    sei(); // Habilita las interrupciones globales

    while (1) {
        PORTB ^= (1 << LED_PIN); // Invierte el estado del LED
        time1_delay(2000); // Espera 1000 ms (1 segundo)
    }

    return 0;
}
