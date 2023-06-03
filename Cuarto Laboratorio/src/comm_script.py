#Import para poder enviar a thingsboard los datos
import paho.mqtt.client as mqtt
#Import para capturar los datos que llegan del puerto serial
import serial
#Import para el tiempo
import time
#import para manejar los datos
import json

serial_port = serial.Serial(port="/dev/ttyACM0", baudrate="Ingresar el baudrate aquí", timeout=1)
print("Conectado al microcontrolador")
data = []
data_header = ["x", "y", "z", "Battery"]
print(data_header)

def connected():
    #implementar función
    pass


import paho.mqtt.client as paho  		    #mqtt library
import os
import json
import time
from datetime import datetime

ACCESS_TOKEN='NN7QEiWaX6mxPRnVdJsQ'                 #Token of your device
broker="demo.thingsboard.io"   			    #host name
port=1883 					    #data listening port

def on_publish(client,userdata,result):             #create function for callback
    print("data published to thingsboard \n")
    pass
client1= paho.Client("control1")                    #create client object
client1.on_publish = on_publish                     #assign function to callback
client1.username_pw_set(ACCESS_TOKEN)               #access token from thingsboard device
client1.connect(broker,port,keepalive=60)           #establish connection

while True:
  
   payload="{"
   payload+="\"Humidity\":60,"
   payload+="\"Temperature\":25"
   payload+="}"
   ret= client1.publish("v1/devices/me/telemetry",payload) #topic-v1/devices/me/telemetry
   print("Please check LATEST TELEMETRY field of your device")
   print(payload)
   time.sleep(5)

