#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

uint8_t sec;
enum {GREEN, YELLOW, RED};
uint8_t light_state = GREEN;


void ADC_init() {
	ADCSRA = 0x86;
	ADMUX = 0x63;
}

uint16_t ADC_read(void) {
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1 << ADIF));
	ADCSRA |= (1<<ADIF);
	return ADC;
}


void show_time(uint8_t sec, uint8_t seg_index) {
	uint8_t nums[] = {
		0x3F, 0x06, 0xDB, 0xCF, 0xE6,
		0xED, 0xFD, 0x07, 0xFF, 0xEF
	};
	
	uint8_t n1 = sec % 10;
	uint8_t n2 = sec / 10;
	
	PORTC = nums[n1];
	PORTD = ~(1<<seg_index);
	//_delay_ms(1);
	_delay_us(600);
	
	PORTC = nums[n2];
	PORTD = ~(1<<(seg_index+1));
	//_delay_ms(1);
	_delay_us(600);	
}


void update_traffic_lights(uint8_t state) {
	switch (state) {
		case GREEN:
		case YELLOW:
		case RED:
	}	
}

void set_traffic_lights() {
	switch (light_state) {
		case GREEN:
		case YELLOW:
		case RED:
	}
}


void init_timer0() {
	DDRB = ;
	TCNT0= 0x00;
	OCR0 = ;
	TCCR0 = ;
	sei();
}

ISR(TIMER0_COMP_vect) {
	if(sec > 0){
		
	}
	update_traffic_lights();
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
		show_time(12, 0);
		show_time(34, 2);

	}
	
}
