#!/bin/bash
# Arduino upload script for mecanum wheel project

echo "Compiling Arduino sketch..."
arduino-cli compile --fqbn arduino:avr:uno . --build-path ./build

if [ $? -eq 0 ]; then
    echo "Uploading with avrdude..."
    avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:build/mecanum.ino.hex:i
    
    if [ $? -eq 0 ]; then
        echo "Upload successful!"
        echo "Monitor with: arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=9600"
    else
        echo "Upload failed!"
    fi
else
    echo "Compilation failed!"
fi