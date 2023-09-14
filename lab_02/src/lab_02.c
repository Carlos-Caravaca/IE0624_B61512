
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PB0
#define BUTTON_PIN PB6

volatile uint32_t mili_seg = 0;
volatile uint8_t boton_presionado = 0;

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
    mili_seg++; // Incrementa el contador de milisegundos en cada interrupción
}

// Función para esperar un número de milisegundos usando Timer1
void time1_delay(uint32_t ms) {
    uint32_t start_time = mili_seg;
    while (mili_seg - start_time < ms) {
        // Espera hasta que se alcance el tiempo deseado
    }
}

// Función para inicializar el botón como entrada con resistencia pull-up
void Button_Init() {
    DDRB &= ~(1 << BUTTON_PIN); // Configura el pin del botón como entrada
    PORTB |= (1 << BUTTON_PIN); // Habilita la resistencia pull-up para el botón
}

// Función para verificar si el botón está presionado
uint8_t Button_IsPressed() {
    return !(PINB & (1 << BUTTON_PIN)); // Retorna 1 si el botón está presionado
}

int main(void) {
    DDRB |= (1 << LED_PIN); // Configura el pin del LED como salida
    Timer1_Init(); // Inicializa Timer1
    Button_Init(); // Inicializa el botón
    sei(); // Habilita las interrupciones globales
    PORTB |= (1 << LED_PIN);

    while (1) {
        if (Button_IsPressed()) {
            boton_presionado = 1; // Indica que el botón ha sido presionado
        }

        if (boton_presionado) {
            PORTB ^= (1 << LED_PIN); // Invierte el estado del LED
            time1_delay(1000); // Espera 1000 ms (1 segundo)
        }
    }

    return 0;
}
