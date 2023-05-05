#include <Adafruit_PCD8544.h>
#include <math.h>
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
  Serial.begin(115200);
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(volt2, INPUT);
  pinMode(volt3, INPUT);
  pinMode(volt4, INPUT);
  // Pines para los switches
  pinMode(switch_AC_DC, INPUT);
  pinMode(switch_CSV, INPUT);
  // Pines de los leds
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
  int button = digitalRead(switch_CSV);
  
  if (mode == LOW){
    display.setCursor(0, 0);
    display.println("Lectura en DC");
    //Tension 1
    v1 = analogRead(volt1) * (5.0 / 1023.0);
    if (v1 < 0 || v1 > 4.9){
      digitalWrite(led_one, HIGH);
      display.print("V1:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_one, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v1 = ((v1 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      display.print("V1:");
      display.println(v1);
    }
    //Tension 2
    v2 = analogRead(volt2)* (5.0 / 1023.0);
    if (v2 < 0 || v2 > 4.9){
      digitalWrite(led_two, HIGH);
      display.print("V2:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_two, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v2 = ((v2 - 0)/(5 - 0))*(25-(-25)) + -25 +0.1;
      display.print("V2:");
      display.println(v2);
    }
    //Tension 3
    v3 = analogRead(volt3) * (5.0 / 1023.0);
    if (v3 < 0 || v3 > 4.9){
<<<<<<< HEAD
      digitalWrite(led_three, HIGH);
=======
      digitalWrite(led_one, HIGH);
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      display.print("V3:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_three, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v3 = ((v3 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      display.print("V3:");
      display.println(v3);
    }
    //Tensión 4
    v4 = analogRead(volt4) * (5.0 / 1023.0);
    if (v4 < 0 || v4 > 4.9){
<<<<<<< HEAD
      digitalWrite(led_four, HIGH);
=======
      digitalWrite(led_one, HIGH);
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      display.print("V1:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_four, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v4 = ((v4 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      display.print("V4:");
      display.println(v4);
    }
  }
  //Caso AC
  else{
    display.setCursor(0, 0);
    display.println("Lectura en AC");
    //Lectura tensión uno
    for (int i = 0; i < 1000; i++){
      v1 =+ analogRead(volt1) * (5.0 / 1023.0);
    }
    v1 = v1/1000;
    if (v1 < 0 || v1 > 4.9){
      digitalWrite(led_one, HIGH);
      display.print("V1:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_one, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v1 = ((v1 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v1 = v1*sqrt(2);
      display.print("V1:");
      display.println(v1);
    }
    //V2
    for (int i = 0; i < 1000; i++){
      v2 =+ analogRead(volt1) * (5.0 / 1023.0);
    }
    v2 = v2/1000;
    if (v2 < 0 || v2 > 4.9){
<<<<<<< HEAD
      digitalWrite(led_two, HIGH);
=======
      digitalWrite(led_one, HIGH);
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      display.print("V2:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_two, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v2 = ((v2 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v2 = v2*sqrt(2);
      display.print("V2:");
      display.println(v1);
    }
    //V3
    for (int i = 0; i < 1000; i++){
      v3 =+ analogRead(volt1) * (5.0 / 1023.0);
    }
    v3 = v3/1000;
    if (v3 < 0 || v3 > 4.9){
<<<<<<< HEAD
      digitalWrite(led_three, HIGH);
=======
      digitalWrite(led_one, HIGH);
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      display.print("V3:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_three, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v3 = ((v3 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v3 = v3*sqrt(2);
      display.print("V3:");
      display.println(v3);
    }
    //V4
    for (int i = 0; i < 1000; i++){
      v4 =+ analogRead(volt4) * (5.0 / 1023.0);
    }
    v4 = v1/1000;
    if (v4 < 0 || v4 > 4.9){
<<<<<<< HEAD
      digitalWrite(led_four, HIGH);
=======
      digitalWrite(led_one, HIGH);
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      display.print("V4:");
      display.println("ERROR");
    }
    else{
<<<<<<< HEAD
      digitalWrite(led_four, LOW);
=======
>>>>>>> 8edc739a6a2d14f2c8ffadd373a52606949ca50b
      v4 = ((v4 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v4 = v4*sqrt(2);
      display.print("V4:");
      display.println(v4);
    }


  } 


if (button == HIGH && mode == LOW){
    Serial.println("Lectura en DC");
    //Tension 1
    v1 = analogRead(volt1) * (5.0 / 1023.0);
    if (v1 < 0 || v1 > 4.9){
      Serial.print("V1:");
      Serial.println("ERROR");
    }
    else{
      v1 = ((v1 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      Serial.print("V1:");
      Serial.println(v1);
    }
    //Tension 2
    v2 = analogRead(volt2)* (5.0 / 1023.0);
    if (v2 < 0 || v2 > 4.9){
      Serial.print("V2:");
      Serial.println("ERROR");
    }
    else{
      v2 = ((v2 - 0)/(5 - 0))*(25-(-25)) + -25 +0.1;
      Serial.print("V2:");
      Serial.println(v2);
    }
    //Tension 3
    v3 = analogRead(volt3) * (5.0 / 1023.0);
    if (v3 < 0 || v3 > 4.9){
      Serial.print("V3:");
      Serial.println("ERROR");
    }
    else{
      v3 = ((v3 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      Serial.print("V3:");
      Serial.println(v3);
    }
    //Tensión 4
    v4 = analogRead(volt4) * (5.0 / 1023.0);
    if (v4 < 0 || v4 > 4.9){
      Serial.print("V1:");
      Serial.println("ERROR");
    }
    else{
      v4 = ((v4 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      Serial.print("V4:");
      Serial.println(v4);
    }
}

if (button == HIGH && mode == HIGH) {
  
    Serial.println("Lectura en AC");
    //Lectura tensión uno
    for (int i = 0; i < 1000; i++){
      v1 =+ analogRead(volt1) * (5.0 / 1023.0);
    }
    v1 = v1/1000;
    if (v1 < 0 || v1 > 4.9){
      Serial.print("V1:");
      Serial.println("ERROR");
    }
    else{
      v1 = ((v1 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v1 = v1*sqrt(2);
      Serial.print("V1:");
      Serial.println(v1);
    }
    //V2
    for (int i = 0; i < 1000; i++){
      v2 =+ analogRead(volt1) * (5.0 / 1023.0);
    }
    v2 = v2/1000;
    if (v2 < 0 || v2 > 4.9){
      Serial.print("V2:");
      Serial.println("ERROR");
    }
    else{
      v2 = ((v2 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v2 = v2*sqrt(2);
      Serial.print("V2:");
      Serial.println(v1);
    }
    //V3
    for (int i = 0; i < 1000; i++){
      v3 =+ analogRead(volt1) * (5.0 / 1023.0);
    }
    v3 = v3/1000;
    if (v3 < 0 || v3 > 4.9){
      Serial.print("V3:");
      Serial.println("ERROR");
    }
    else{
      v3 = ((v3 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v3 = v3*sqrt(2);
      Serial.print("V3:");
      Serial.println(v3);
    }
    //V4
    for (int i = 0; i < 1000; i++){
      v4 =+ analogRead(volt4) * (5.0 / 1023.0);
    }
    v4 = v1/1000;
    if (v4 < 0 || v4 > 4.9){
      Serial.print("V4:");
      Serial.println("ERROR");
    }
    else{
      v4 = ((v4 - 0)/(5 - 0))*(25-(-25)) + -25+0.1;
      v4 = v4*sqrt(2);
      Serial.print("V4:");
      Serial.println(v4);
    }
  
  }

  display.display(); // Actualizar la pantalla
  delay(1000);
  display.clearDisplay();
  
}
