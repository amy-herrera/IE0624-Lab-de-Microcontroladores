#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// Definir pines de botones
#define START_PAUSE_PIN PINA2
#define HIGH_LOAD_PIN PINB2
#define MEDIUM_LOAD_PIN PINB1
#define LOW_LOAD_PIN PINB0

// Definir pines de LEDs
#define CENTRIFUGADO_LED_PIN PINB4
#define ENJUAGADO_LED_PIN PINB3
#define LAVAR_LED_PIN PIND5
#define SUMINISTRO_AGUA_LED_PIN PIND4

#define LOW_LOAD_LED_PIN PINB7
#define MEDIUM_LOAD_LED_PIN PINB6
#define HIGH_LOAD_LED_PIN PINB5

// Definir pines de BCD a 7 segmentos
#define BCD_A_PIN PINA0
#define BCD_B_PIN PINA1
#define BCD_C_PIN PIND1
#define BCD_D_PIN PIND0


//Configuración de los pines del microcontrolador.
DDRA &= ~(1 << START_PAUSE_PIN);
DDRB &= ~((1 << LOW_LOAD_PIN) | (1 << MEDIUM_LOAD_PIN) | (1 << HIGH_LOAD_PIN));
DDRB |= (1 << LOW_LOAD_LED_PIN) | (1 << MEDIUM_LOAD_LED_PIN) | (1 << HIGH_LOAD_LED_PIN);
DDRB |= (1 << ENJUAGADO_LED_PIN) | (1 << CENTRIFUGADO_LED_PIN);
DDRD |= (1 << LAVAR_LED_PIN) | (1 << SUMINISTRO_AGUA_LED_PIN);
DDRA |= (1 << BCD_A_PIN) | (1 << BCD_B_PIN);
DRRD |= (1 << BCD_C_PIN) | (1 << BCD_D_PIN);
