#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void ADC_init(void) {
	DDRA = 0xFE;
	PORTA = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x86;
}

uint16_t ADC_read(void) {
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1 << ADIF));
	ADCSRA |= (1<<ADIF);
	return ADC;
}


void PWM_init(void) {
	DDRB |= (1<<PB3);
	TCCR0 = 0x63;
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
	char buffer[20];
	uint16_t adc_value;

	ADC_init();
	PWM_init();
	UART_init(9600);

	DDRB |= (1<<PB0) | (1<<PB1);
	PORTB = 0x01;

	while (1) {
		adc_value = ADC_read();
		
		uint16_t min_duty = 8;
		uint16_t max_duty = 254;
		uint16_t pwm_value = ((uint32_t)adc_value * (max_duty - min_duty) / 1023) + min_duty;

		PWM_setDutyCycle(pwm_value);
		
		snprintf(buffer, sizeof(buffer), "duty:%u, pot:%u\r\n", pwm_value, adc_value);
		UART_sendString(buffer);
		
		_delay_ms(500);
	}
	
	return 0;
}
