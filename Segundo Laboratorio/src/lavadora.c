#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 1000000UL

//Definición de los pines del microcontrolador:
#define BTN_START_PAUSE (1 << PINA2)
#define BTN_LOAD_LOW (1 << PINB0)
#define BTN_LOAD_MED (1 <<)
#define BTN_LOAD_HIGH (1 << PINB2)
