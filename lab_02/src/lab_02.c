#include <avr/io.h>
#include <util/delay.h>

// Definir los pines para el semáforo de tráfico
#define SEM_TRAFICO_ROJO_PIN    PB0
#define SEM_TRAFICO_AMARILLO_PIN PB1
#define SEM_TRAFICO_VERDE_PIN    PB2

// Definir los pines para el semáforo peatonal
#define SEM_PEATON_VERDE_PIN     PB3
#define SEM_PEATON_ROJO_PIN      PB4

void semaforoTrafico() {
    // Configurar los pines del semáforo de tráfico como salidas
    DDRB |= (1 << SEM_TRAFICO_ROJO_PIN) | (1 << SEM_TRAFICO_AMARILLO_PIN) | (1 << SEM_TRAFICO_VERDE_PIN);

    // Encender luz verde del semáforo de tráfico
    PORTB |= (1 << SEM_TRAFICO_VERDE_PIN);
    _delay_ms(5000); // Esperar 5 segundos

    // Cambiar a luz amarilla
    PORTB &= ~(1 << SEM_TRAFICO_VERDE_PIN);
    PORTB |= (1 << SEM_TRAFICO_AMARILLO_PIN);
    _delay_ms(2000); // Esperar 2 segundos

    // Cambiar a luz roja
    PORTB &= ~(1 << SEM_TRAFICO_AMARILLO_PIN);
    PORTB |= (1 << SEM_TRAFICO_ROJO_PIN);
    _delay_ms(5000); // Esperar 5 segundos

    // Volver al verde
    PORTB &= ~(1 << SEM_TRAFICO_ROJO_PIN);
    PORTB |= (1 << SEM_TRAFICO_VERDE_PIN);
}

void semaforoPeatonal() {
    // Configurar los pines del semáforo peatonal como salidas
    DDRB |= (1 << SEM_PEATON_VERDE_PIN) | (1 << SEM_PEATON_ROJO_PIN);

    // Encender luz roja del semáforo peatonal
    PORTB |= (1 << SEM_PEATON_ROJO_PIN);
    _delay_ms(5000); // Esperar 5 segundos

    // Cambiar a luz verde
    PORTB &= ~(1 << SEM_PEATON_ROJO_PIN);
    PORTB |= (1 << SEM_PEATON_VERDE_PIN);
    _delay_ms(5000); // Esperar 5 segundos
}

int main(void) {
    while (1) {
        semaforoTrafico();
        semaforoPeatonal();
    }

    return 0;
}
