import paho.mqtt.subscribe as subscribe
import serial

try:
    ser = serial.Serial('/dev/cu.usbmodem0004402251091', 115200)
    ser.flushInput()
except:
    print("unable to open COM port")

def print_msg(client, userdata, message):
    print("%s : %s" % (message.topic, message.payload))
    if message.payload.decode('ascii') == "red":
        ser.write(b'r')

subscribe.callback(print_msg, "nsi/nosovand/temp", hostname="mqtt.eclipseprojects.io")
