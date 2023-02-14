from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import paho.mqtt.publish as publish
import numpy as np
import serial

try:
    ser = serial.Serial('/dev/cu.usbmodem0004402251091', 115200)
    ser.flushInput()
except:
    print("unable to open COM port")

inBuffer = list(range(4))
finalValues = list(range(2))
while True:
    for i in range(len(inBuffer)):
        for byte in ser.read():
            if byte == '\n':
                print("end of data")
                break
            inBuffer[i] = byte
            print(inBuffer[i])

    for x in range(len(finalValues)):
        #if inBuffer[x] > 0:
        finalValues[x] = inBuffer[x*2] + inBuffer[x*2+1]/100
        #else:
        #    finalValues[x] = inBuffer[x] - inBuffer[x+1]/100
        print(finalValues[x])

    publish.single("nsi/nosovand/temp", finalValues[0], hostname="mqtt.eclipseprojects.io")
    publish.single("nsi/nosovand/hum", finalValues[1], hostname="mqtt.eclipseprojects.io")
