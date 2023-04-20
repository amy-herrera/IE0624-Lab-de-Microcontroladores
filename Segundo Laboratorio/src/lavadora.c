#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// Definir pines de botones
#define START_PAUSE_PIN PINA2
#define HIGH_LOAD_PIN PINB2
#define MEDIUM_LOAD_PIN PINB1
#define LOW_LOAD_PIN PINB0

<<<<<<< HEAD
// Definir el pin para el display
#define DISPLAY PIND6

=======
>>>>>>> ee10f8bf745f76b44a1baa6f6665149762a30c31
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
void setup_pins(){
    DDRA &= ~(1 << START_PAUSE_PIN); //Entrada del botón de inicio pausa
    DDRB &= ~((1 << LOW_LOAD_PIN) | (1 << MEDIUM_LOAD_PIN) | (1 << HIGH_LOAD_PIN)); //Entradas de los botones de carga
    DDRB |= (1 << LOW_LOAD_LED_PIN) | (1 << MEDIUM_LOAD_LED_PIN) | (1 << HIGH_LOAD_LED_PIN); //LEDS en B para los Niveles de carga
    DDRB |= (1 << ENJUAGADO_LED_PIN) | (1 << CENTRIFUGADO_LED_PIN); //LEDS en B para los ciclos de lavado
    DDRD |= (1 << LAVAR_LED_PIN) | (1 << SUMINISTRO_AGUA_LED_PIN); //LEDs en D para los ciclos de lavado
    DDRA |= (1 << BCD_A_PIN) | (1 << BCD_B_PIN); //BCD en A
    DRRD |= (1 << BCD_C_PIN) | (1 << BCD_D_PIN); //BCD en D
<<<<<<< HEAD
    DDRD |= (1 << DISPLAY); //Pin para el display
=======
>>>>>>> ee10f8bf745f76b44a1baa6f6665149762a30c31
}
//Definición de los estados para la lavadora
#define SUMINISTRO_AGUA 0
#define LAVAR 1
#define ENJUAGAR 2
#define CENTRIFUGAR 3

//Definir las cargas de la lavadora:
enum{
    BAJA,
    ALTA,
    MEDIA,
};

//Definición de variable útiles
volatile uint8_t segundos = 0;
volatile uint8_t tiempo_necesario = 0;
volatile uint8_t tiempo_total = 0;
volatile uint8_t tiempo_restante = 0;
int state = SUMINISTRO_AGUA;
int seleccion_de_intensidad = BAJA;
<<<<<<< HEAD

//Struct para realizar una máquina de estados representativa de la lavadora

typedef struct lavadora{
    void (*state_pointer)(void);

    int time;
} Lavadora;

void setup_timer(){
    // Configurar el modo de temporizador de comparación normal
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    // Configurar el preescaler a 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);

    //Habilitar las interrupciones del microcontrolador
    sei();

    //Prestablecer el valor del contador a 0
    TCNT0 = 0;

    //Habilitar interrupción del timer 0.
    TIMSK |= (1 << TOIE0)
}

//Configurar las interrupciones

//Interrupcion del botón de inicio/pausa (prioritario)
PCMSK1 |= (1 << PCINT10);

//Interrupciones de los niveles de carga (No prioritarios)
PCMSK0 |= (1 << PCINT2) | (1 << PCINT1) | (1 << PCINT0);

//Habilitación de las interrupciones anteriormente creadas
PCICR |= (1 << PICE1) | (1 << PCIE0);



