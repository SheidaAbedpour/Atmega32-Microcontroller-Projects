#ifndef F_CPU
#define F_CPU 16000000UL
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
	uint8_t nums[] = {0x3F, 0x06, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x07, 0xFF, 0xEF};
	uint8_t n1 = sec % 10;
	uint8_t n2 = sec / 10;
	
	PORTC = nums[n1];
	PORTD = 0xFE;
	_delay_ms(5);
	
	PORTC = nums[n2];
	PORTD = 0xFD;
	_delay_ms(5);	
}

int main (void) {
	DDRA &= ~(1<<PA3);
	DDRB &= ~(1<<PB3);
	
	ADC_init();
	
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	uint16_t ADC_value;
	uint16_t min = 10;
	uint16_t max = 60;
		
	while(1) {
		//ADC_value = ADC_read();
		//uint16_t green_time = (((uint32_t)ADC_value * (max - min)) / 1023) + min;
		show_time(90);
	}
	
}
