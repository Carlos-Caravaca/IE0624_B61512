#include <avr/io.h>
#include <avr/interrupt.h>

#define YELLOW PB0     // LED Amarillo vehículo
#define LDPV PB1     // LED Verde vehículo
#define LDPP PB2     // LED Verde peaton
#define LDPD PB3     // LED Rojo peaton
#define LDVD PD5     // LED Rojo vehículo
#define BUTTON_PIN PB6  // PIN Botón

volatile uint32_t mili_seg = 0;

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


// Función de espera, un número de milisegundos usando Timer1
void timer01_ms(uint32_t ms) {
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
    // Retorna 1 si el botón está presionado
    return !(PINB & (1 << BUTTON_PIN)); 
}

int main(void) {
    // Se configuran los pines de los LEDs como salidas
    DDRB |= (1 << YELLOW); 
    DDRB |= (1 << LDPV);
    DDRB |= (1 << LDPP);
    DDRB |= (1 << LDPD);
    DDRD |= (1 << LDVD);

    Timer1_Init();      // Inicializa Timer1
    Button_Init();      // Inicializa el botón
    sei();              // Habilita las interrupciones globales
    int WAIT = 1;       // Inicialización del estado de espera en 1
    int buttonState = 0; // Inicialmente, el botón no está presionado

    while (1) {
        // Estado inicial en verde para vehiculos y rojo para peatones
        // 10s
        buttonState = Button_IsPressed(); // Guarda el estado del botón
        PORTB |= (1 << LDPV);    // Verde vehÍculo endendido
        PORTB |= (1 << LDPD);    // Rojo peatón encendido
        PORTD &= ~(1 << LDVD);   // Rojo vehículo apagado
        PORTB &= ~(1 << LDPP);   // Verde peaton apagado
        PORTB &= ~(1 << YELLOW);   // Amarillo apagado
        
        // Estado de espera inicial 10s
        if (WAIT)
        {
            timer01_ms(10000);
            WAIT = 0;
        }
        
        if (buttonState) {
            // LDPV parpadeando durante 3 segundos de la luz verde
            // 3 SEGUNDOS
            PORTB &= ~(1 << LDPV);
            PORTB &= ~(1 << LDPD);
            PORTB &= ~(1 << YELLOW); 
            timer01_ms(500);
            PORTB |= (1 << LDPV);
            //PORTB |= (1 << LED_PB0);
            timer01_ms(500);        // 1 segundo
            PORTB &= ~(1 << LDPV);
            PORTB &= ~(1 << YELLOW); 
            timer01_ms(500);
            // Parpadea la luz amarilla, escenario más realístico
            //PORTB |= (1 << LED_PB1);
            PORTB |= (1 << YELLOW);
            timer01_ms(500);        // 2 segundos
            //PORTB &= ~(1 << LED_PB1);
            PORTB &= ~(1 << YELLOW); 
            timer01_ms(500);
            //PORTB |= (1 << LED_PB1);
            PORTB |= (1 << YELLOW);
            timer01_ms(500);        // 3 segundo
            PORTB &= ~(1 << LDPV);
            PORTB &= ~(1 << YELLOW); 
            // Encendido LED rojo vehiculo
            PORTD |= (1 << LDVD);   // espera 1 segundo
            timer01_ms(1000);      
            // Encendido LED verde peaton
            PORTB |= (1 << LDPP);
            timer01_ms(10000);      // espera 11 segundos
            PORTB &= ~(1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(500);
            PORTB |= (1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(500);        // lleva 12 segundos hasta este punto
            PORTB &= ~(1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(500);
            PORTB |= (1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(500);        // lleva 13 segundos hasta este punto
            PORTB &= ~(1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(500);        
            PORTB |= (1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(500);        // lleva 14 segundos hasta este punto
            PORTB &= ~(1 << LDPP);
            PORTD |= (1 << LDVD);
            timer01_ms(1000);       // lleva 15 segundos hasta este punto

            // Regresa al estado inicial
            PORTB |= (1 << LDPV);    // LED Verde vehículo endendido
            PORTB |= (1 << LDPD);    // LED Rojo peatón encendido
            PORTD &= ~(1 << LDVD);   // LED Rojo vehículo apagado
            PORTB &= ~(1 << LDPP);   // LED Verde peatón apagado
            PORTB &= ~(1 << YELLOW);   // LED Amarillo apagado

            // Espera hasta que se libere el botón para evitar múltiples pulsaciones
            //while (Button_IsPressed()) {}
            WAIT = 1; // Se pone el estado de espera en 1
        }
    }
    return 0;   
}
