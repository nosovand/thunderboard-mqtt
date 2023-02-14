# MQTT Sensor Data Publisher and Subscriber

This project contains scripts and codes for measuring temperature and humidity data from a Thunderboard Sense 2 using a Si7021 sensor and publishing the data via MQTT.

#### The project consists of the following files:
publish.py: A Python script for reading data from the sensor and publishing it to an MQTT broker\
subscribe.py: A Python script for subscribing to an MQTT topic and printing the received messages\
main.c: A C file that is part of a PlatformIO project for Thunderboard Sense 2. This file reads the temperature and humidity data from the Si7021 sensor and sends it via serial to the publish.py script
