# Throttle Box

An ESP32-based project to control a servo motor with smooth, randomized movements. Designed for physical interaction simulation or anti-idling purposes.

## Features
- **Precise PWM Control**: Uses microsecond pulse widths for fine-tuned servo travel.
- **Smooth Easing**: Implements a Smoothstep algorithm ($3t^2 - 2t^3$) for fluid, lifelike motion.
- **Continuous Randomness**: Moves directly between random positions in a configurable range.
- **Plotter Support**: Streams numeric pulse data compatible with the Arduino Serial Plotter.

## Hardware Support
- **Target**: ESP32 (e.g., NodeMCU, DevKit).
- **Pinout**: Signal connected to **D18**.
- **Driver**: Requires Silicon Labs CP210x USB to UART Bridge drivers on Windows.

## Configuration
At the top of `main/main.ino`, you can adjust the following:
- `minPulse`: Minimum pulse width (default 1000us).
- `maxPulse`: Maximum pulse width (default 1800us).
- Timing: Wait intervals are randomized between 8-25 seconds in the `loop()`.

## Setup
1. Open the project in the Arduino IDE.
2. Install the `ESP32Servo` library.
3. Select your ESP32 board and COM port.
4. Upload and monitor via the Serial Plotter (115200 baud).
