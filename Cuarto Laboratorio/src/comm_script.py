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




