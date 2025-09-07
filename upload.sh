#!/bin/bash
# Arduino upload script for mecanum wheel project

echo "Compiling Arduino sketch..."
arduino-cli compile --fqbn arduino:avr:uno . --build-path ./build

if [ $? -eq 0 ]; then
    # Find Arduino USB port
    USB_PORT=$(ls /dev/ttyUSB* 2>/dev/null | head -1)
    
    if [ -z "$USB_PORT" ]; then
        echo "No Arduino found on /dev/ttyUSB*"
        exit 1
    fi
    
    echo "Found Arduino on $USB_PORT"
    echo "Uploading with avrdude..."
    avrdude -v -p atmega328p -c arduino -P "$USB_PORT" -b 115200 -D -U flash:w:build/mecanum.ino.hex:i
    
    if [ $? -eq 0 ]; then
        echo "Upload successful!"
        echo "Monitor with:"
        echo "screen $USB_PORT 9600"
    else
        echo "Upload failed!"
    fi
else
    echo "Compilation failed!"
fi
