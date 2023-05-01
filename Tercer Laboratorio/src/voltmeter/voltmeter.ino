#include <Adafruit_PCD8544.h>

//Definición de los pines


// Conexiones del PCD8544
#define SCLK 13
#define DIN 11
#define DC 10
#define CS 9
#define RST 8

//Configuración de la pantalla
PCD8544 lcd = PCD8544(SCLK, DIN, DC, CS, RST);

//Pines analógicos de entradas de tensión
int volt1 = A0;
int volt2 = A1;
int volt3 = A2;
int volt4 = A3;


//Pines de utilidad
int switch_AC_DC = 7;
int out_PWM = 6;

//Pines de signo para las tensiones
int v2_sign = 3;
int v1_sign = 2;
int v3_sign = 4;
int v4_sign = 5;


//Variables de almacenar tensiones:
float v1 = 0;
float v2 = 0;
float v3 = 0;
float v4 = 0;

// Establece el ciclo de trabajo al 50% para el pwm
int dutyCycle = 127;

void setup(){
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(volt2, INPUT);
  pinMode(volt3, INPUT);
  pinMode(volt4, INPUT);
  //pin del switch
  pinMode(switch_AC_DC, INPUT);
  //pin del PWM
  pinMode(out_PWM, OUTPUT);
  //pines de signo de tensión
  pinMode(v1_sign, INPUT);
  pinMode(v2_sign, INPUT);
  pinMode(v3_sign, INPUT);
  pinMode(v4_sign, INPUT);

}

void loop(){

  // Aplica el ciclo de trabajo al pinPWM
  analogWrite(pinPWM, dutyCycle);

  // se lee el valor digital del pin 7
  int pin7Value = digitalRead(pin7);

  //Se define el modo de operación:

  //Si se tiene en alto, el modo de operación es DC
  if (pin7Valule == HIGH){
    //Formula para calcular las tensiones:
    v1 = ((analogRead(volt1)*2.0 + 0.5)/1024.0)*(25);

  }

  //Si se tiene en bajo es AC
  else{

  }

}
