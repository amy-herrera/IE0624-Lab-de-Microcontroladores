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






















# Abrir el archivo CSV en modo escritura
'''with open(fileName, mode='w', newline='') as file:
    # Se define el separador de campos como punto y coma
    writer = csv.writer(file, delimiter=';')
    writer.writerow(encabezado)


    while True:
        # Leer una línea desde el puerto serial
        linea = ser.readline().decode('utf-8').strip()
        
        # Si la línea es vacía, salimos del ciclo
        if not linea:
            break
        
        # Separar los valores de la línea
        valores = linea.split(',')
        print(valores)
        
        linea = ";".join([str(valor) for valor in valores])
        file.write(linea)
        time.sleep(0.1)

        
        #writer.writerow([float(v.strip()) for v in valores])

        
        # Escribir los valores en el archivo CSV
        #writer.writerow([str(v.strip()) for v in valores])
        #linea = ";".join(valores) + "\n"
        #file.write(linea)'''

file.close()
''' while True:
    for c in ser.read():
        c=chr(c)
        print(c, end='')
        line += c
        
        if c == "\n":
            with open(fileName, 'w', newline='') as file:
                writer = csv.writer(file, delimiter=';')
                writer.writerows(line + "\n")
                time.sleep(2)
                file.close()
           #file = open(fileName, "a")
           	    time.sleep(2)
           #file.write("La data obtenida se presenta acontinuacion: " + "\n")
           #file.write(line + "\n")
           #file.write("\n")
           	    file.close() '''
