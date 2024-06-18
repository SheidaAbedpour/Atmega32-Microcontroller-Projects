#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void ADC_init() {
	ADCSRA = 0x87;
	ADMUX = 0x63;
}

uint16_t ADC_read(void) {
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1 << ADIF));
	ADCSRA |= (1<<ADIF);
	return ADC;
}

void show_time(uint8_t sec) {
	uint8_t nums[] = {0x3F, 0x06, 0xA5, 0x8D, 0x19, 0x49, 0x41, 0x1F, 0x01, 0x09};
	
	uint8_t n1 = sec % 10;
	uint8_t n2 = sec / 10;
	
	PORTC = nums[n1];
	//PORTD = 0xEF;
	PORTD = 0x01;
	_delay_ms(500);
	
	PORTC = nums[n2];
	//PORTD = 0xFD;
	PORTD = 0x02;
	_delay_ms(500);
}

int main (void) {
	DDRA &= ~(1<<PA3);
	DDRB &= ~(1<<PB3);
	
	ADC_init();
	
	DDRC = 0xFF;
	DDRD = 0x03;
	
	uint16_t ADC_value;
	uint16_t min = 10;
	uint16_t max = 60;
	
	while(1) {
		//ADC_value = ADC_read();
		//uint16_t green_time = (((uint32_t)ADC_value * (max - min)) / 1023) + min;
		show_time(10);
	}
}
