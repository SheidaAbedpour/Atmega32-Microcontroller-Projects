# Traffic Light Controller 
This project implements a traffic light control system using an AVR microcontroller. The system controls two sets of traffic lights (main and sub) and adjusts the light durations based on ADC inputs.

## Overview
- ***`ADC (Analog-to-Digital Converter)`***: Reads analog signals to adjust the timing of the green and yellow lights dynamically.
- ***`Timer1`***: Generates interrupts every second to update the traffic light states and countdown timers.
- ***`7-Segment Displays`***: Show the remaining time for each light on the main and sub roads.
- ***`Traffic Lights`***: Controlled via output ports to switch between green, yellow, and red states.


## Register Settings
Setting registers is a fundamental aspect of programming microcontrollers, as these registers control the various functions and peripherals of the microcontroller. In this project, several registers are configured to manage the ADC (Analog-to-Digital Converter), timers, and GPIO (General-Purpose Input/Output) ports.

## ADC (Analog-to-Digital Converter) Registers
The ADC initialization involves setting the ADCSRA and ADMUX registers.

#### ADCSRA (ADC Control and Status Register A)

- ***`ADEN` (ADC Enable)***: Enables the ADC. This is essential for any ADC operations.
- ***`ADSC` (ADC Start Conversion)***: Not set here; this bit is set to start a conversion.
- ***`ADATE` (ADC Auto Trigger Enable)***: Disabled, meaning conversions are started manually.
- ***`ADIF` (ADC Interrupt Flag)***: Cleared to zero initially; it's set when an ADC conversion is complete.
- ***`ADIE` (ADC Interrupt Enable)***: Disabled; we're not using ADC interrupts in this application.
- ***`ADPS2`, `ADPS1`, `ADPS0` (ADC Prescaler Select Bits)***: Set to 111 (binary) to select a division factor of 128. This sets the ADC clock to F_CPU/128, which ensures the - ADC operates within the recommended frequency range (50-200 kHz) given a 16 MHz system clock.

| Bit  | 7 (ADEN) | 6 (ADSC) | 5 (ADATE) | 4 (ADIF) | 3 (ADIE) | 2 (ADPS2) | 1 (ADPS1) | 0 (ADPS0) |
|------|----------|----------|-----------|----------|----------|-----------|-----------|-----------|
| Value|     1    |     0    |     0     |     0    |    0     |     1     |     1     |     1     |

#### ADMUX (ADC Multiplexer Selection Register)

- ***`REFS1`, `REFS0` (Reference Selection Bits)***: Set to 01 to use AVcc with external capacitor at AREF pin as the reference voltage. This is a common and stable reference voltage.
- ***`ADLAR` (ADC Left Adjust Result)***: Set to 1 for left-adjusted result, making it easier to read the 8-bit result from the high byte of the ADC data register.
- ***`MUX4:0` (Analog Channel Selection Bits)***: Set to 00110 to select ADC6 as the input channel.

| Bit  | 7 (REFS1) | 6 (REFS0) | 5 (ADLAR) | 4 (MUX4) | 3 (MUX3) | 2 (MUX2) | 1 (MUX1) | 0 (MUX0) |
|------|-----------|-----------|-----------|----------|----------|----------|----------|-----------|
| Value| 0         | 1         | 1         | 0        | 0        | 1        | 1        | 0         |

```c
ADCSRA = 0x87;
ADMUX = 0x46;
```


## Timer1 Initialization
Timer1 is configured to generate interrupts at a regular interval, which is used for updating the traffic lights.

#### TCNT1 (Timer/Counter1)
This register holds the Timer/Counter1 value and is set to 0 to start counting from zero.

#### OCR1A (Output Compare Register 1A)
This register is compared with the Timer/Counter1 value. When a match occurs, the Timer1 Compare Match A interrupt is triggered. 15624 is calculated to achieve a 1-second interval given the selected prescaler.

f = f_clk / (1024 * (OCR1A + 1))


1 = (16 * 1e6) / (1024 * (OCR1A + 1))


OCR1A = 15624


#### TCCR1A (Timer/Counter1 Control Register A)
- ***`COM1A1`, `COM1A0`, `COM1B1`, `COM1B0` (Bits 7:4)***: Compare Output Mode for Channel A and B. Not used, so all are set to 0.
- ***`WGM11`, `WGM10` (Bits 1:0)***: Waveform Generation Mode Bits. Set to 00 for normal operation.
  

| Bit  | 7 (COM1A1) | 6 (COM1A0) | 5 (COM1B1) | 4 (COM1B0) | 3 -      | 2 -      | 1 (WGM11) | 0 (WGM10) |
|------|------------|------------|------------|------------|----------|----------|-----------|-----------|
| Value| 0          |  0         | 0          | 0          | 0        | 0        | 0         | 0         |

#### TCCR1B (Timer/Counter1 Control Register B)
- ***`ICNC1`, `ICES1` (Bits 7:6)***: Input Capture Noise Canceler and Input Capture Edge Select. Not used, so both are 0.
- ***`WGM13`, `WGM12` (Bits 4:3)***: Waveform Generation Mode Bits. Set WGM12 to 1 for CTC (Clear Timer on Compare Match) mode.
- ***`CS12`, `CS11`, `CS10` (Bits 2:0)***: Clock Select Bits. Set to 101 (binary) to select a prescaler of 1024.
  

| Bit  | 7 (ICNC1)  | 6 (ICES1)  | 5 -        | 4 (WGM13)  | 3 (WGM12) | 2 (CS12) | 1 (CS11) | 0 (CS10) |
|------|------------|------------|------------|------------|-----------|----------|----------|-----------|
| Value| 0          |  0         | 0          | 0          | 1         | 1        | 0        | 1         |


#### TIMSK (Timer/Counter Interrupt Mask Register)
- ***`OCIE1A` (Bit 4)***: Timer/Counter1, Output Compare A Match Interrupt Enable. Set to 1 to enable the Timer1 Compare Match A interrupt.


  ```c
  TCNT1 = 0;
  OCR1A = 15624;
  TCCR1A = 0x00;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK = (1 << OCIE1A);
  ```



### Usage of Project

This project controls two sets of traffic lights and adjusts their timing based on analog inputs.

1. **Upload the HEX File**:
   - Compile the provided code to generate a HEX file.
   - Upload the HEX file to the AVR microcontroller using a suitable programmer.

2. **Set Up in Proteus**:
   - Load the HEX file into the microcontroller in Proteus.

3. **Run the Simulation**:
   - Use the potentiometers to adjust the timings:
     - **Green Time**: Adjust using the potentiometer connected to ADC6.
     - **Yellow Time**: Adjust using the potentiometer connected to ADC7.
   - The red light time will be automatically set to 75% of the green time.

4. **Monitor Operation**:
   - Observe the traffic lights switching between green, yellow, and red states.
   - Check the 7-segment displays for the countdown of each light.

By following these steps, you can simulate and adjust the traffic light control system in Proteus using potentiometers for real-time adjustments.










