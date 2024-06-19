# Atmega32 Microcontroller Projects 
This repository contains two microcontroller projects implemented using AVR microcontrollers. Below is a brief overview of each project:

## DC Motor Controller

The DC Motor Controller project demonstrates how to control the speed of a DC motor using an ATmega32 microcontroller. The motor speed is adjusted via Pulse Width Modulation (PWM), which is controlled based on input from a potentiometer. Additionally, the project utilizes UART for transmitting motor speed and ADC values for monitoring purposes.

### Key Features:
- **PWM Control:** Adjusts motor speed through duty cycle modulation.
- **UART Monitoring:** Allows real-time monitoring of motor speed and potentiometer values.
- **ADC Integration:** Reads analog input from a potentiometer to set motor speed.

  
[**Code Link**](https://github.com/SheidaAbedpour/Atmega32/blob/main/DC-Motor/DC-GccBoard/DC-GccBoard/src/main.c): View the code for DC Motor Controller.

![](https://github.com/SheidaAbedpour/Atmega32/blob/main/DC-Motor/Schematic.PNG)


## Traffic Light Controller

The Traffic Light Controller project implements a traffic light control system using an AVR microcontroller. It manages two sets of traffic lights and adjusts their timings dynamically based on ADC inputs. The system utilizes timers for precise timing control and displays countdowns on 7-segment displays.

### Key Features:
- **Dynamic Timing Control:** Adjusts green and yellow light durations based on ADC inputs.
- **Timer Interrupts:** Updates traffic light states at regular intervals.
- **7-Segment Displays:** Shows remaining time for each traffic light phase.



[**Code Link**](https://github.com/SheidaAbedpour/Atmega32/blob/main/Traffic-Light-Controller/trafficLightGccBoard/trafficLightGccBoard/src/main.c): View the code for Traffic Light Controller.

![](https://github.com/SheidaAbedpour/Atmega32/blob/main/Traffic-Light-Controller/proteus/schematic.PNG)
