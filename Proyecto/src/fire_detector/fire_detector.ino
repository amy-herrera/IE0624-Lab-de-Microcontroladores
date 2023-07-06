#include <Arduino_APDS9960.h>

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>

#include "model.h"

unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 2000;
bool toneActive = false;

// pull in all the TFLM ops, you can remove this line and
// only pull in the TFLM ops you need, if would like to reduce
// the compiled size of the sketch.
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Create a static memory buffer for TFLM, the size may need to
// be adjusted based on the model you are using
constexpr int tensorArenaSize = 8 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

//Arreglo para mostrar las dos posible salidas que quiero identificar.
const char* CLASSES[] = {
  "fuego",
  "no fuego"
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(2, OUTPUT);

  if (!APDS.begin()){
      Serial.println("Error inicializando el sensor de RGB");
    }

  //get the TFL representation of the model byte array
  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("La versión del modelo no coincide!");
    while (1);
  }

  // Create an interpreter to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize);

  // Allocate memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();

  // Get pointers for the model's input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() {
  int r, g, b, c, p;
  float suma;

  // Esperar hasta que los datos de color y proximidad estén disponibles
  while (!APDS.colorAvailable() || !APDS.proximityAvailable()){};

  // Leer los valores de color y proximidad
  APDS.readColor(r,g,b,c);
  suma = r+g+b;
  p = APDS.readProximity();

  //Verificar la condición mínima para evaluar los valores capturados
  if (p >= 0 && c > 10 && suma > 0){
    float red = r/suma;
    float green = g/suma;
    float blue = b/suma;

    // Asignar los valores de entrada al tensor del modelo
    tflInputTensor->data.f[0] = red;
    tflInputTensor->data.f[1] = green;
    tflInputTensor->data.f[2] = blue;

    //Llamar al modelo para poder utilizar sus resultados
    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk){
      Serial.println("Fallo el llamado a la red");
      while(1);
      return;
    }

    //Imprimir las certidumbres
    for (int i = 0; i < 2; i++){
      Serial.print(CLASSES[i]);
      Serial.print(" ");
      Serial.print(int(tflOutputTensor->data.f[i]*100));
      Serial.print("%\n");
    }

    Serial.println();

    //Verifica el umbral establecido para poder activar el tono de alarma

    if(int(tflOutputTensor->data.f[0]*100) > 95){
      if (!toneActive){
        tone(2, 1000, 2000);
      }
    }
    else if(int(tflOutputTensor->data.f[1]*100) > 95){
      noTone(2);
    }
  
    }

}
