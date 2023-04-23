#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Definir pines de botones
#define START_PAUSE_PIN PINA2
#define HIGH_LOAD_PIN PINB2
#define MEDIUM_LOAD_PIN PINB1
#define LOW_LOAD_PIN PINB0

// Definir el pin para el display
#define DISPLAY PIND6

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


    DDRA |= ((1 << BCD_A_PIN) | (1 << BCD_B_PIN)); //BCD en A
    //DDRA &= ~(1 << START_PAUSE_PIN); //Entrada del botón de inicio pausa
    DDRB &= ~((1 << LOW_LOAD_PIN) | (1 << MEDIUM_LOAD_PIN) | (1 << HIGH_LOAD_PIN)); //Entradas de los botones de carga
    DDRB |= (1 << LOW_LOAD_LED_PIN) | (1 << MEDIUM_LOAD_LED_PIN) | (1 << HIGH_LOAD_LED_PIN); //LEDS en B para los Niveles de carga
    DDRB |= (1 << ENJUAGADO_LED_PIN) | (1 << CENTRIFUGADO_LED_PIN); //LEDS en B para los ciclos de lavado
    DDRD |= ((1 << LAVAR_LED_PIN) | (1 << SUMINISTRO_AGUA_LED_PIN) | (1 << BCD_C_PIN) | (1 << BCD_D_PIN) | (1 << DISPLAY)); //LEDs en D para los ciclos de lavado
    //DDRD |= ((1 << BCD_C_PIN) | (1 << BCD_D_PIN) | (1 << DISPLAY)); //BCD en D
    //DDRD |= (1 << DISPLAY); //Pin para el display
    
    // Activar pull-up para los botones
    PORTA |= (1 << START_PAUSE_PIN);
    PORTB |= (1 << LOW_LOAD_PIN) | (1 << MEDIUM_LOAD_PIN) | (1 << HIGH_LOAD_PIN);
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
volatile uint8_t decenas = 0; 
volatile uint8_t unidades = 0;
volatile int state = SUMINISTRO_AGUA;
volatile int seleccion_de_intensidad = BAJA;

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
    TIMSK |= (1 << TOIE0);
}

void setup_interrupts(){
    //Configurar las interrupciones
    
    PCMSK1 |= (1 << PCINT10); //Interrupcion del boton de inicio/pausa (prioritario)


    //Interrupcion del botón de inicio/pausa (prioritario)
    //PCMSK1 |= (1 << PCINT10);

    //Interrupciones de los niveles de carga (No prioritarios)
    PCMSK |= (1 << PCINT2) | (1 << PCINT1) | (1 << PCINT0);

    //Habilitación de las interrupciones anteriormente creadas
    GIMSK |= (1 << PCIE1) | (1 << PCIE0);
}

// Funcion para asignar los pines para los displays
void set_pines(uint8_t decimal) {

	switch (decimal) { 
    			case 0:
    				PORTD &= ~((1 << BCD_C_PIN)|(1<<BCD_D_PIN));
    				PORTA &= ~((1 << BCD_A_PIN)|(1<<BCD_B_PIN));
				    break;	
							
    			case 1:
    			    PORTD |= (1 << BCD_D_PIN);
    				PORTD &= ~((1 << BCD_C_PIN));
    				PORTA &= ~((1 << BCD_A_PIN)|(1<<BCD_B_PIN));
				    break;	
					
    			case 2:
    			    PORTD |= (1 << BCD_C_PIN);
    				PORTD &= ~((1 << BCD_D_PIN));
    			    PORTA &= ~((1 << BCD_A_PIN)|(1<<BCD_B_PIN));
				    break;	
    		
    			case 3:
    				PORTD |= ((1 << BCD_C_PIN)|(1<<BCD_D_PIN));
    				PORTA &= ~((1 << BCD_A_PIN)|(1<<BCD_B_PIN));
				    break;
						
			    case 4:		
			        PORTD &= ~((1 << BCD_C_PIN)|(1<<BCD_D_PIN));
			        PORTA |= (1 << BCD_B_PIN);
			        PORTA &= ~((1 << BCD_A_PIN));
				    break;
						
			    case 5: 
			        PORTD |= (1 << BCD_D_PIN);
    				PORTD &= ~((1 << BCD_C_PIN));	
    				PORTA |= (1 << BCD_B_PIN);
			        PORTA &= ~((1 << BCD_A_PIN));	
				    break;	
					
			    case 6:
				    PORTD |= (1 << BCD_C_PIN);
    				PORTD &= ~((1 << BCD_D_PIN));	
    				PORTA |= (1 << BCD_B_PIN);
			        PORTA &= ~((1 << BCD_A_PIN));	
				    break;	
				
			    case 7:
			        PORTD |= ((1 << BCD_C_PIN)|(1<<BCD_D_PIN));
				    PORTA |= (1 << BCD_B_PIN);
			        PORTA &= ~((1 << BCD_A_PIN));	
				    break;	
					
			    case 8:	
			        PORTD &= ~((1 << BCD_C_PIN)|(1<<BCD_D_PIN));
				    PORTA |= (1 << BCD_A_PIN);
			        PORTA &= ~((1 << BCD_B_PIN));	
				    break;	
					
			    case 9:
			        PORTD |= (1 << BCD_D_PIN);
    				PORTD &= ~((1 << BCD_C_PIN));
    				PORTA |= (1 << BCD_A_PIN);
			        PORTA &= ~((1 << BCD_B_PIN));
				    break;	
    			}						
}

/**************************************************************
*
*               Definición de los ISR
*
**************************************************************/

//ISR Para el timer
ISR(TIMER0_OVF_vect){
    static uint8_t counter = 0;
    counter++;

    //por la definición del timer a 1024, se tiene que cada 31 ciclos hay un segundo de tiempo real.
    if (counter == 97){
        segundos++;
        tiempo_restante--;
        unidades = tiempo_restante%10; 
        decenas=(tiempo_restante/10)%10;
        //Aquí se actualizan los displays
        
        counter = 0;
    }
    //Cuando se alcanza el tiempo necesario, se actualiza el estado por medio de la función
    if (segundos == tiempo_necesario){
        segundos = 0;
        TCNT0 = 0;
        //TIMSK &= ~(1 << TOIE0);
    }
    
    _delay_ms(5);
    PORTD &= ~((1 << DISPLAY));
    set_pines(decenas);
    _delay_ms(5);
    PORTD |= ((1 << DISPLAY));
    set_pines(unidades);
}

//ISR para el botón de inicio/pausa
ISR(PCINT1_vect){
    if(PINA & (1 << START_PAUSE_PIN)){
        //Si el timer está activo se debe detener:
        if (TIMSK & (1 << TOIE0)){
            TIMSK &= ~(1 << TOIE0);
        }
        else{
        // Si está detenido lo iniciamos
        TIMSK |= (1 << TOIE0);
        }
    }
}

//ISR para los botones de selección de carga
ISR(PCINT0_vect){
    if (PINB & (1 << LOW_LOAD_PIN)){
        seleccion_de_intensidad = BAJA;
        PORTB |= (1 << LOW_LOAD_LED_PIN);
        PORTB &= ~((1 << MEDIUM_LOAD_LED_PIN) | (1 << HIGH_LOAD_LED_PIN));
        tiempo_total = 9;
        tiempo_restante = tiempo_total;

    } else if(PINB & (1 << MEDIUM_LOAD_PIN)){
        seleccion_de_intensidad = MEDIA;
        PORTB |= (1 << MEDIUM_LOAD_LED_PIN);
        PORTB &= ~((1 << HIGH_LOAD_LED_PIN) | (1 << LOW_LOAD_LED_PIN));
        tiempo_total = 19;
        tiempo_restante = tiempo_total;

    } else if(PINB & (1 << HIGH_LOAD_PIN)){
        seleccion_de_intensidad = ALTA;
        PORTB |= (1 << HIGH_LOAD_LED_PIN);
        PORTB &= ~((1 << MEDIUM_LOAD_LED_PIN) | (1 << LOW_LOAD_LED_PIN));
        tiempo_total = 27;
        tiempo_restante = tiempo_total;
    }
}

//Funciones para los ciclos de lavado
void suministro_agua(){
    //encender el led de suministro de agua y apagar el resto:
    PORTD |= (1 << SUMINISTRO_AGUA_LED_PIN);
    PORTD &= ~(1 << LAVAR_LED_PIN);
    PORTB &= ~((1 << ENJUAGADO_LED_PIN)|(1<<CENTRIFUGADO_LED_PIN));
    //Establece el tiempo dependiendo del nivel de carga
    switch (seleccion_de_intensidad){
        case BAJA:
            tiempo_necesario = 1;
            break;
        
        case MEDIA:
            tiempo_necesario = 2;
            break;
        
        case ALTA:
            tiempo_necesario = 3;
            break;
    }
    if (segundos == tiempo_necesario){
        state = LAVAR;
        segundos = 0;
        TCNT0 = 0;
    }
}
void lavar(){
    //ENCENDER LEDS Y APAGAR EL RESTO
    PORTD |= (1 << LAVAR_LED_PIN);
    PORTD &= ~(1 << SUMINISTRO_AGUA_LED_PIN);
    PORTB &= ~((1 << ENJUAGADO_LED_PIN)|(1 << CENTRIFUGADO_LED_PIN));
    
    //Establecer duración de la etapa dependiendo del nivel de carga seleccionado
    switch (seleccion_de_intensidad){
        case BAJA:
            tiempo_necesario = 3;
            break;
        
        case MEDIA:
            tiempo_necesario = 7;
            break;
        
        case ALTA:
            tiempo_necesario = 10;
            break;
    }
    if (segundos == tiempo_necesario){
        state = ENJUAGAR;
        segundos = 0;
        TCNT0 = 0;
    }
}
void enjuagar(){
    PORTB |= (1 << ENJUAGADO_LED_PIN);
    PORTD &= ~((1 << SUMINISTRO_AGUA) | (1 << LAVAR_LED_PIN));
    PORTB &= ~(1 << CENTRIFUGADO_LED_PIN);
    //Establecer duración de la etapa dependiendo del nivel de carga seleccionado
    switch (seleccion_de_intensidad){
        case BAJA:
            tiempo_necesario = 2;
            break;
        
        case MEDIA:
            tiempo_necesario = 4;
            break;
        
        case ALTA:
            tiempo_necesario = 5;
            break;
    }
    if (segundos == tiempo_necesario){
        state = CENTRIFUGAR;
        segundos = 0;
        TCNT0 = 0;
    }

}

void centrifugar(){
    PORTB |= (1 << CENTRIFUGADO_LED_PIN);
    PORTD &= ~((1 << SUMINISTRO_AGUA)|(1<<LAVAR_LED_PIN));
    PORTB &= ~(1<<ENJUAGADO_LED_PIN);
    switch (seleccion_de_intensidad){
        case BAJA:
            tiempo_necesario = 3;
            break;
        
        case MEDIA:
            tiempo_necesario = 6;
            break;
        
        case ALTA:
            tiempo_necesario = 9;
            break;
    }
    if (segundos == tiempo_necesario){
        state = SUMINISTRO_AGUA;
        segundos = 0;
        TCNT0 = 0;
        //Reiniciar todos los componentes para simular el estado inicial en 0
        PORTB &= ~((1 << LOW_LOAD_LED_PIN)|(1 << MEDIUM_LOAD_LED_PIN)|(1 << HIGH_LOAD_LED_PIN));
        PORTB &= ~((1 << ENJUAGADO_LED_PIN)|(1 << CENTRIFUGADO_LED_PIN));
        PORTD &= ~((1<<LAVAR_LED_PIN)|(1 << SUMINISTRO_AGUA_LED_PIN));
    }
}

int main(void){

    //Iniciar con los LEDs apagados
    //PORTB &= ~((1 << LOW_LOAD_LED_PIN));
    PORTD &= ~(1 << SUMINISTRO_AGUA_LED_PIN);

    setup_pins();
    setup_interrupts();
    setup_timer();
    
    while (1){
    
        switch (state){
            case SUMINISTRO_AGUA:
                suministro_agua();
                break;
            case LAVAR:
                lavar();
                break;
            case ENJUAGAR:
                enjuagar();
                break;
            case CENTRIFUGAR:
                centrifugar();
                break;
        }
    }
    
    
}
