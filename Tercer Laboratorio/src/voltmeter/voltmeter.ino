#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>
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
int switch_CSV = 12;
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

  Serial.begin(115200);
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(volt2, INPUT);
  pinMode(volt3, INPUT);
  pinMode(volt4, INPUT);
  //pin del switch
  pinMode(switch_AC_DC, INPUT);
  pinMode(switch_CSV, INPUT);
  //pin del PWM
  pinMode(out_PWM, OUTPUT);
  //pines de signo de tensión
  pinMode(v1_sign, INPUT);
  pinMode(v2_sign, INPUT);
  pinMode(v3_sign, INPUT);
  pinMode(v4_sign, INPUT);
  // Inicializar la pantalla
  display.begin();
  display.setContrast(50); // Ajustar el contraste de la pantalla (0-127)

  // Limpiar la pantalla
  display.clearDisplay();

}

void loop(){
  //Leer el modo en el que se están leyendo las tensiones
  int mode = digitalRead(switch_AC_DC);
  int button = digitalRead(switch_CSV);
  
  //envio de la señal cuadrada para el circuito de configuración de tensión
  
 
  analogWrite(out_PWM, 127);
  if (mode == LOW){
    v1 = ((analogRead(volt1)*2.0 + 0.5)/1024.0)*(25);
    v2 = ((analogRead(volt2)*2.0 + 0.5)/1024.0)*(25);
    v3 = ((analogRead(volt3)*2.0 + 0.5)/1024.0)*(25);
    v4 = ((analogRead(volt4)*2.0 + 0.5)/1024.0)*(25);
    display.setCursor(0, 0);
    
    display.println("Lectura en DC");
    //Tensión uno

    //display.setCursor(0, 1);
    display.print("V1:");
    //display.setCursor(83, 1);
    display.println(v1);
    //Tensión dos
    //display.setCursor(0, 2);
    display.print("V2:");
    //display.setCursor(3, 2);
    display.println(v2);
    //Tensión tres
    //display.setCursor(0, 3);
    display.print("V3:");
    //display.setCursor(83, 3);
    display.println(v3);
    //Tensión cuatro
    //display.setCursor(0, 4);
    display.print("V4:");
    //display.setCursor(83, 4);

    //display.setCursor(0, 1);
    display.print("V1:");
    //display.setCursor(83, 1);
    display.println(v1);
    //Tensión dos
    //display.setCursor(0, 2);
    display.print("V2:");
    //display.setCursor(3, 2);
    display.println(v2);
    //Tensión tres
    //display.setCursor(0, 3);
    display.print("V3:");
    //display.setCursor(83, 3);
    display.println(v3);
    //Tensión cuatro
    //display.setCursor(0, 4);
    display.print("V4:");
    //display.setCursor(83, 4);

    display.println(v4);
    
  }
  else{

  }


if (button == HIGH){
    v1 = ((analogRead(volt1)*2.0 + 0.5)/1024.0)*(25);
    v2 = ((analogRead(volt2)*2.0 + 0.5)/1024.0)*(25);
    v3 = ((analogRead(volt3)*2.0 + 0.5)/1024.0)*(25);
    v4 = ((analogRead(volt4)*2.0 + 0.5)/1024.0)*(25);
    display.setCursor(0, 0);
    
    Serial.println("Lectura en DC");
    //Tensión uno

    //display.setCursor(0, 1);
    Serial.print("V1:");
    //display.setCursor(83, 1);
    Serial.println(v1);
    //Tensión dos
    //display.setCursor(0, 2);
    Serial.print("V2:");
    //display.setCursor(3, 2);
    Serial.println(v2);
    //Tensión tres
    //display.setCursor(0, 3);
    Serial.print("V3:");
    //display.setCursor(83, 3);
    Serial.println(v3);
    //Tensión cuatro
    //display.setCursor(0, 4);
    Serial.print("V4:");
}
  
  display.display(); // Actualizar la pantalla
  delay(1000);
  display.clearDisplay();
  

}
