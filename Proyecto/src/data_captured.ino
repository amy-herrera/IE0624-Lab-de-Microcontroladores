#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while(!Serial){};

  if (!APDS.begin()) {
    
    Serial.println("No se inicio correctamente");
    
    }

  Serial.println("Rojo, Verde, Azul");
}

void loop() {
  int r, v, a, c, p;
  float sum;

  while (!APDS.colorAvailable() || !APDS.proximityAvailable()) {}


   APDS.readColor(r,v,a,c);
   sum = r + v + a;

   p = APDS.readProximity();

   if(p >= 0 && c > 10 && sum >0){
    
    float redRatio = r/sum;
    float greenRatio = v/sum;
    float blueRatio = a/sum;

    Serial.print(redRatio, 3);
    Serial.print(',');
    Serial.print(greenRatio, 3);
    Serial.print(',');
    Serial.print(blueRatio, 3);
    Serial.println();
    
    
    }

}
