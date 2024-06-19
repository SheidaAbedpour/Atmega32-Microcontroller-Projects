#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t sec_main;
uint8_t sec_sub;
uint8_t green_time = 6;
uint8_t yellow_time = 2;
uint8_t red_time = 3;
enum State {GREEN, YELLOW, RED};
uint8_t light_state_main = GREEN;
uint8_t light_state_sub = RED;

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
	_delay_ms(1000);
	
	PORTC = nums[n2];
	PORTD = ~(1<<(seg_index+1));
	_delay_ms(1000);
}

void set_traffic_lights() {
	switch (light_state_main) {
		case GREEN:
		PORTA = (PORTA | (1 << PA0)) & ~((1 << PA1) | (1 << PA2));
		break;
		case YELLOW:
		PORTA = (PORTA | (1 << PA1)) & ~((1 << PA0) | (1 << PA2));
		break;
		case RED:
		PORTA = (PORTA | (1 << PA2)) & ~((1 << PA1) | (1 << PA0));
		break;
	}
	
	switch (light_state_sub) {
		case GREEN:
		PORTA = (PORTA | (1 << PA3)) & ~((1 << PA4) | (1 << PA5));
		break;
		case YELLOW:
		PORTA = (PORTA | (1 << PA4)) & ~((1 << PA3) | (1 << PA5));
		break;
		case RED:
		PORTA = (PORTA | (1 << PA5)) & ~((1 << PA4) | (1 << PA3));
		break;
	}
}

void update_traffic_lights_main() {
	switch (light_state_main) {
		case GREEN:
		if (sec_main == 0) {
			light_state_main = YELLOW;
			sec_main = yellow_time;
		}
		break;
		case YELLOW:
		if (sec_main == 0) {
			light_state_main = RED;
			sec_main = red_time;
		}
		break;
		case RED:
		if (sec_main == 0) {
			light_state_main = GREEN;
			sec_main = green_time;
		}
		break;
	}
}

void update_traffic_lights_sub() {
	switch (light_state_sub) {
		case GREEN:
		if (sec_sub == 0) {
			light_state_sub = YELLOW;
			sec_sub = yellow_time;
		}
		break;
		case YELLOW:
		if (sec_sub == 0) {
			light_state_sub = RED;
			sec_sub = red_time;
		}
		break;
		case RED:
		if (sec_sub == 0) {
			light_state_sub = GREEN;
			sec_sub = green_time;
		}
		break;
	}
}

void init_timer1() {
	TCNT1 = 0;
	OCR1A = 15624;
	TCCR1A = 0x00;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, prescaler 1024
	TIMSK = (1 << OCIE1A);
	sei();
}

ISR(TIMER1_COMPA_vect) {
	if (sec_main > 0) {
		sec_main--;
	}
	update_traffic_lights_main();

	if (sec_sub > 0) {
		sec_sub--;
	}
	update_traffic_lights_sub();

	set_traffic_lights();
}

int main (void) {
	
	DDRA = 0x3F;
	DDRB &= ~(1<<PB3);
	DDRC = 0xFF;
	DDRD = 0xFF;

	ADC_init();
	init_timer1();
	
	sec_main = green_time;
	sec_sub = red_time;
	set_traffic_lights();
	
	while(1) {
		
	}
	
	return 0;
}
