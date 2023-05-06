#!/usr/bin/python3
import serial
import time
import csv

fileName = "output.csv"

encabezado = "Tension1; Tension2; Tension3; Tension4\n"

ser = serial.Serial(
    port='/tmp/ttyS1',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
    timeout=20\
    )

print("connected to: " + ser.portstr)

print("Created file")

contador = 0
valores = []
file = open(fileName, mode='w', newline='')
file.write(encabezado)
num_datos = 100  # Número de datos que se esperan recibir antes de cerrar el puerto
contador_datos = 0  # Contador de datos recibidos

while True:
    linea_serie = ser.readline().decode().strip()
    valores.extend(linea_serie.split(','))
    print(valores)

    if len(valores) >= 4:
        while len(valores) >= 4:
            linea = ";".join([str(valor) for valor in valores[:4]])
            file.write(linea)
            file.write("\n")
            valores = valores[4:]
            contador += 4

    contador_datos += 1  # Incrementar el contador de datos recibidos
    if contador_datos >= num_datos:
        break
 
ser.close()
file.close()

