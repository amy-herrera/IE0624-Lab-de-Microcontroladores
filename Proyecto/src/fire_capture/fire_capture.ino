#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while(!Serial){};

  if (!APDS.begin()){
    Serial.println("Error al iniciar el sensor de color");
  }

}

void loop() {
  int r, g, b, c, p;
  float suma;

  while (!APDS.colorAvailable() || !APDS.proximityAvailable()){};

  APDS.readColor(r,g,b,c);
  suma = r+g+b;

  p = APDS.readProximity();

  if (p >= 0 && c > 10 && suma > 0){
    float red = r/suma;
    float green = g/suma;
    float blue = b/suma;

    Serial.print(red, 3);
    Serial.print(',');
    Serial.print(green, 3);
    Serial.print(',');
    Serial.print(blue, 3);
    Serial.println();
  }

}