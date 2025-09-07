# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an Arduino-based mecanum wheel robot project. The main code is in `mecanum.ino` which contains the standard Arduino setup() and loop() functions.

## Development Environment

This project is designed for Arduino development and may support PlatformIO based on the .gitignore patterns.

## Build and Upload Commands

**Preferred method:**
- Use `./upload.sh` script which auto-detects USB port and uses avrdude
- Script compiles with `arduino-cli` and uploads via `avrdude` 
- Monitor with: `screen /dev/ttyUSB* 9600` (exit: Ctrl+A, K, Y)

**Alternative methods:**
- Arduino IDE upload button
- `arduino-cli compile --fqbn arduino:avr:uno . --build-path ./build`
- `arduino-cli upload -p /dev/ttyUSB* --fqbn arduino:avr:uno .`

## Hardware Configuration

**Radio Control:**
- Radiolink R8EF receiver in PWM mode
- CH1 (A0): Rotate left/right - WORKING
- CH2 (A1): Unknown function (interference/noise)
- CH3 (A2): Forward/reverse - WORKING  
- CH4 (A3): Strafe left/right - WORKING
- CH5 (A4): Unknown function
- CH6 (A5): Right shoulder switch
- CH7 (D4): Left shoulder potentiometer (moved from D2)
- CH8 (D3): Left shoulder switch

**Motor Control (ESCs):**
- Front Left: D9 (escFL)
- Front Right: D10 (escFR) 
- Back Left: D8 (escBL) - moved from D6 due to D5 pin failure
- Back Right: D7 (escBR)
- All use Servo library for ESC control (1000-2000µs, 1500=stop)

**Current Issues:**
- Robot rotates instead of proper mecanum movement - kinematics math needs adjustment
- CH2 interference/noise on unused channels - may need hardware filtering (pullup resistors/caps)
- All three control inputs (CH1, CH3, CH4) are working and motors respond

## Architecture

- `mecanum.ino`: Main Arduino sketch with mecanum drive control
- `upload.sh`: Automated build/upload script using avrdude
- Uses Servo library for ESC control and mecanum wheel kinematics