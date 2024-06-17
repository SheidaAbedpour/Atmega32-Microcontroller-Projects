#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void ADC_init() {
	DDRA = 0xFE;
	PORTA = 0x00;
	ADMUX = 0x60;
	ADCSRA = 0x84; 
}

uint16_t ADC_read() {
	ADCSRA |= (1<<ADSC); 
	while(ADCSRA & (1<<ADIF));
	ADCSRA |= (1<<ADIF);
	return ADC;
}


void PWM_init() {
	DDRB |= (1<<PB3); 
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01); 
}

void PWM_setDutyCycle(uint8_t duty) {
	OCR0 = duty;
}


void UART_init(unsigned int baud) {
	unsigned int ubrr = F_CPU/16/baud-1;
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
}

void UART_transmit(unsigned char data) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
}

void UART_sendString(const char* str) {
	while (*str) {
		UART_transmit(*str++);
	}
}



int main(void) {
	char buffer[100];
	uint16_t adc_value;

	ADC_init();
	PWM_init();
	UART_init(9600); 

	DDRB |= (1<<PB0) | (1<<PB1); 
	PORTB = 0x01;

	while (1) {
		adc_value = ADC_read();
		
		uint16_t min_duty = 64;
		uint16_t max_duty = 190;
		uint16_t pwm_value = ((adc_value / 1023) * (max_duty - min_duty) + min_duty); 
		PWM_setDutyCycle(pwm_value); 
		
		snprintf(buffer, sizeof(buffer), "duty:%d, pot:%d | ", pwm_value, adc_value); 
		UART_sendString(buffer);
		
		_delay_ms(500);
	}
	
	return 0;
}
