# DC Motor Controller
This project demonstrates how to control the speed of a DC motor using an ATmega32 microcontroller. The speed is controlled via Pulse Width Modulation (PWM), with the duty cycle of the PWM signal being adjusted based on the input from a potentiometer.

![](https://github.com/SheidaAbedpour/Atmega32/blob/main/DC-Motor/Schematic.PNG)

## Overview
The project uses the following peripherals:

- ***`ADC`***: To read the potentiometer value.
- ***`PWM`: To control the speed of the DC motor.
- ***`UART`: To transmit the motor speed and ADC value for monitoring.

## Register Settings 
This project uses various registers to configure the ADC, PWM, and UART functionalities of the AVR microcontroller (ATmega32). Below is an explanation of the key register settings used in this project.

## ADC (Analog-to-Digital Converter) Initialization
The ADC initialization involves setting the ADCSRA and ADMUX registers.

### ADCSRA (ADC Control and Status Register A)
- ***`ADEN` (ADC Enable)***: Set to 1 to enable the ADC.
- ***`ADSC` (ADC Start Conversion)***: Set to 1 to start a conversion. This bit is cleared automatically.
- ***`ADATE` (ADC Auto Trigger Enable)***: Set to 0 to disable auto triggering.
- ***`ADIF` (ADC Interrupt Flag)***: Set to 0 to clear the interrupt flag.
- ***`ADIE` (ADC Interrupt Enable)***: Set to 0 to disable ADC interrupt.
- ***`ADPS2:0` (ADC Prescaler Select Bits)***: Set to 110 (prescaler = 64). This determines the ADC clock frequency.

| Bit  | 7 (ADEN) | 6 (ADSC) | 5 (ADATE) | 4 (ADIF) | 3 (ADIE) | 2 (ADPS2) | 1 (ADPS1) | 0 (ADPS0) |
|------|----------|----------|-----------|----------|----------|-----------|-----------|-----------|
| Value|     1    |     0    |     0     |     0    |    0     |     1     |     1     |     0     |


### ADMUX (ADC Multiplexer Selection Register)
- ***`REFS1:0` (Reference Selection Bits)***: Set to 01 to select AVCC as the reference voltage.
- ***`ADLAR` (ADC Left Adjust Result)***: Set to 0 for right-adjusted result.
- ***`MUX4:0` (Analog Channel Selection Bits)***: Set to 00000 to select ADC0 (channel 0).

| Bit  | 7 (REFS1) | 6 (REFS0) | 5 (ADLAR) | 4 (MUX4) | 3 (MUX3) | 2 (MUX2) | 1 (MUX1) | 0 (MUX0) |
|------|-----------|-----------|-----------|----------|----------|----------|----------|-----------|
| Value| 0         | 1         | 1         | 0        | 0        | 0        | 0        | 0         |

```c
ADCSRA = 0x86;
ADMUX = 0x40;
```

## PWM (Pulse Width Modulation) Initialization
The PWM initialization involves setting the TCCR and OCR registers.

### TCCR0 (Timer/Counter Control Register)
- ***`FOC0` (Force Output Compare)***: Set to 0 for PWM mode.
- ***`WGM00:01` (Waveform Generation Mode)***: Set to 11 for Fast PWM mode.
- ***`COM01:00` (Compare Match Output Mode)***: Set to 10 for non-inverted PWM.
- ***`CS02:00` (Clock Select Bits)***: Set to 110 for prescaler = 64.

| Bit  | 7 (FOC0) | 6 (WGM00) | 5 (COM01) | 4 (COM00) | 3  (WGM01) | 2 (CS02)  | 1 (CS01)  | 0 (CS00) |
|------|----------|-----------|-----------|-----------|------------|-----------|-----------|-----------|
| Value|     0    |     1     |     1     |     0     |    1       |     1     |     1     |     0     |

### OCR0 (Output Compare Register)
The duty cycle of the PWM signal determines the speed of the DC motor. The project ensures that the motor operates within its maximum and minimum speed limits by appropriately setting the OCR0 register value based on the ADC input from the potentiometer.


## Usage
1. **Upload the Hex File**: Load the compiled hex file into the ATmega32 microcontroller in Proteus.
2. **Connect the Potentiometer**: Use a potentiometer to provide an analog input to the ADC channel of the microcontroller.
3. **Monitor via UART**: Connect a virtual terminal in Proteus to the UART pins of the microcontroller to monitor the speed and potentiometer values.

