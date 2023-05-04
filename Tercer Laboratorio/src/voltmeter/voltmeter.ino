#include <Adafruit_PCD8544.h>
#include <math.h>

//Definición de los pines


// Conexiones del PCD8544
#define SCLK 13
#define DIN 11
#define DC 10
#define CS 9
#define RST 8

//Configuración de la pantalla
Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS, RST);

//Pines analógicos de entradas de tensión
int volt1 = A0;
int volt2 = A1;
int volt3 = A2;
int volt4 = A3;


//Pines de utilidad
int switch_AC_DC = 7;
int led_one = 3;
int led_two = 4;
int led_three = 5;
int led_four = 6;


//Variables de almacenar tensiones:
float v1 = 0;
float v2 = 0;
float v3 = 0;
float v4 = 0;


void setup(){
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(volt2, INPUT);
  pinMode(volt3, INPUT);
  pinMode(volt4, INPUT);
  //pin del switch
  pinMode(switch_AC_DC, INPUT);
  //pines de los leds
  pinMode(led_one, OUTPUT);
  pinMode(led_two, OUTPUT);
  pinMode(led_three, OUTPUT);
  pinMode(led_four, OUTPUT);
  // Inicializar la pantalla
  display.begin();
  display.setContrast(50); // Ajustar el contraste de la pantalla (0-127)

  // Limpiar la pantalla
  display.clearDisplay();

}

void loop(){
  v1 = 0;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  //Leer el modo en el que se están leyendo las tensiones
  int mode = digitalRead(switch_AC_DC);
  if (mode == LOW){
    display.setCursor(0, 0);
    display.println("Lectura en DC");
    //Tension 1
    v1 = analogRead(volt1) * (5.0 / 1023.0);
    if (v1 < 0 || v1 > 4.92){
      digitalWrite(led_one, HIGH);
      display.print("V1:");
      display.println("ERROR");
    }
    else{
      v1 = (61*v1 -150)/6 + 0.01;
      display.print("V1:");
      display.println(v1);
    }
    //Tension 2
    v2 = analogRead(volt2) * (5.0 / 1023.0);
    if (v1 < 0 || v1 > 4.92){
      digitalWrite(led_two, HIGH);
      display.print("V2:");
      display.println("ERROR");
    }
    else{
      v2 = (61*v2 -150)/6 + 0.01;
      display.print("V2:");
      display.println(v2);
    }
    //Tension 3
    v3 = analogRead(volt3) * (5.0 / 1023.0);
    if (v1 < 0 || v1 > 4.92){
      digitalWrite(led_one, HIGH);
      display.print("V3:");
      display.println("ERROR");
    }
    else{
      v3 = (61*v3 -150)/6 + 0.01;
      display.print("V3:");
      display.println(v3);
    }
    //Tensión 4
    v4 = analogRead(volt4) * (5.0 / 1023.0);
    if (v1 < 0 || v1 > 4.92){
      digitalWrite(led_one, HIGH);
      display.print("V1:");
      display.println("ERROR");
    }
    else{
      v4 = (61*v4 -150)/6 + 0.01;
      display.print("V4:");
      display.println(v4);
    }
  }
  //Caso AC
  else{
    display.setCursor(0, 0);
    display.println("Lectura en AC");
    //Lectura tensión uno
    for (int i = 0; i < 150; i++){
      v1 = v1 + analogRead(volt1) * (5.0 / 1023.0);
    }
    v1 = v1/150;
    if (v1 < 0 || v1 > 4.92){
      digitalWrite(led_one, HIGH);
      display.print("V1:");
      display.println("ERROR");
    }
    else{
      v1 = (61*v1 -150)/6 + 0.01;
      v1 = v1*sqrt(2);
      display.print("V1:");
      display.println(v1);
    }


  }
  
  display.display(); // Actualizar la pantalla
  delay(1000);
  display.clearDisplay();
  

}
