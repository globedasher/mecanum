# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an Arduino-based mecanum wheel robot project. The main code is in `mecanum.ino` which contains the standard Arduino setup() and loop() functions.

## Development Environment

This project is designed for Arduino development and may support PlatformIO based on the .gitignore patterns.

## Build and Upload Commands

For Arduino IDE:
- Verify/Compile: Use Arduino IDE's verify button or `arduino-cli compile`
- Upload: Use Arduino IDE's upload button or `arduino-cli upload`

For PlatformIO (if using):
- Build: `pio run`
- Upload: `pio run -t upload`
- Monitor serial: `pio device monitor`

## Architecture

- `mecanum.ino`: Main Arduino sketch file containing setup() and loop() functions
- Currently minimal with just serial initialization at 9600 baud

## Hardware Context

This project is designed for mecanum wheel robots, which are omnidirectional drive systems using four special wheels that can move in any direction without rotating the robot chassis.