**🔧 Embedded Systems Projects Using PIC Microcontroller**


This repository contains a collection of embedded systems projects developed using PIC microcontrollers, covering various core topics in microcontroller interfacing, peripheral programming, and real-time embedded control. Each folder represents a specific module or interface, showcasing real-time implementations with code, schematics (if any), and modular examples.

**📁 Repository Structure & Descriptions
Folder Name	Description**

**ADC**

Analog-to-Digital Converter (ADC) implementation using PIC to read analog sensor values and convert them to digital form.

**ADC-PWM**

Combines ADC input and PWM output for applications like motor speed control or brightness control based on sensor input.


**I2C**	

I2C communication protocols implemented between PIC and other I2C-compatible devices like EEPROMs or sensors.


**INTERRUPT**	

Demonstrates usage of hardware interrupts in PIC (e.g., external interrupts, timer interrupts) for asynchronous event handling.


**KEYPAD_INTERFACE**	

Interfacing 4x4 matrix keypad with PIC microcontroller for capturing user input.


**LCD**	

Interfacing 16x2 alphanumeric LCD with PIC using either 4-bit or 8-bit mode to display data or messages.


**LED_BLINK**	

Basic LED blinking project to understand GPIO pin toggling using timers or delays.


**LED_SWITCH**

Interfacing push-button switches with LEDs. Demonstrates input detection and digital output control.


**MEMORY_MAPPING**

Demonstrates how to map and access memory locations in PIC for data manipulation or storage.


**PWM**	

Pulse Width Modulation generation using PIC timers. Useful for motor control, LED dimming, etc.


**RTC/CLOCK**

Real-Time Clock interfacing or clock logic implementation to maintain time using software or hardware RTC modules.


**SEVEN_SEGMENT**

Interfacing single and multi-digit 7-segment displays for number and character output using BCD or multiplexing.


**SPI**

Serial Peripheral Interface communication implementation for interfacing sensors or memory chips.


**UART**

Universal Asynchronous Receiver/Transmitter implementation for serial communication between PIC and other devices (PC, GSM, ESP, etc.).

**🧠 Microcontroller Used**

All examples are implemented using PIC microcontrollers, such as:

PIC16F877A


**Each module contains:**

.c and .h source files (MPLAB or MikroC style)

Configuration settings

Pin mappings and setup



**🚀 Getting Started**


**Clone the repository:**


git clone https://github.com/yourusername/your-repo-name.git
Open in MPLAB X IDE for PIC

Compile and flash to your PIC microcontroller using a suitable programmer (e.g., PICkit3)


**🧰 Tools Used**

Compiler: MPLAB XC8 for PIC

IDE: MPLAB X IDE

Programmer: PICkit3 

Simulation: Proteus (optional for simulation testing)


**📌 Purpose**

This repository serves as a learning resource for embedded systems students and hobbyists to explore:

Peripheral interfacing

Embedded C programming

Real-time signal processing

Communication protocols (UART, SPI, I2C)
