#Import para poder enviar a thingsboard los datos
import paho.mqtt.client as mqtt
#Import para capturar los datos que llegan del puerto serial
import serial
#Import para el tiempo
import time
#import para manejar los datos
import json
import os

serial_port = serial.Serial(port="/dev/ttyACM0", baudrate="115200", timeout=1)
print("Conectado al microcontrolador")
data = []
data_header = ["x", "y", "z", "Battery"]
print(data_header)

def on_publish(client,userdata,result):             #create function for callback
    print("data published to thingsboard \n")
    pass

#Datos para la conexión con el cliente:
broker = "iot.eie.ucr.ac.cr"
topic = "v1/devices/me/telemetry"
device= "i2k08wg3y7gztp93o1yt"
port = 1883

#Establecemos los parámetros de conexión
client = mqtt.Client("B53473")
client.on_publish = on_publish
client.username_pw_set(device)
client.connect(broker, port, keepalive=60)
dictionary = dict()


while True:
   data_captured = serial_port.readline().decode('utf-8').replace('\r', "").replace("\n", "")
   data_captured = data_captured.split('\t')
   if len(data_captured) >= 3:
       dictionary['x'] = data_captured[0]
       dictionary['y'] = data_captured[1]
       dictionary['z'] = data_captured[2]
       if data_captured[3] == '1':
            alarm = "Si"
       else:
            alarm = 'No'

       dictionary['Battery Low'] = alarm
       dictionary["Battery Level"] = data_captured[4]
       output = json.dumps(dictionary)
       print(output)
       client.publish(topic, output)
