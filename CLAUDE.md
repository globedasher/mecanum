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
- CH2 (A1): Unknown function
- CH3 (A2): Strafe left/right candidate - TESTING
- CH4 (A3): Forward/reverse - NOT RESPONDING TO INPUT
- CH5 (A4): Unknown function  
- CH6 (A5): Right shoulder switch
- CH7 (D4): Left shoulder potentiometer (moved from D2)
- CH8 (D3): Left shoulder switch

**Motor Control (ESCs):**
- Front Left: D9 (escFL)
- Front Right: D10 (escFR) 
- Back Left: D6 (escBL)
- Back Right: D7 (escBR)
- All use Servo library for ESC control (1000-2000µs, 1500=stop)

**Current Issues:**
- CH4 (forward/reverse) not responding to stick input - reading constant values
- CH2 also not responding - may need to identify correct strafe channel
- Need to test CH3 or CH5 for strafe functionality
- Motor calculations working correctly when inputs are valid

## Architecture

- `mecanum.ino`: Main Arduino sketch with mecanum drive control
- `upload.sh`: Automated build/upload script using avrdude
- Uses Servo library for ESC control and mecanum wheel kinematics