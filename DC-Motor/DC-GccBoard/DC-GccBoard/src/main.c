#define F_CPU 16000000UL
#define sw (PORTB & (1<<0))

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char i;

ISR(INT0_vect) {
	i = i + 10;
}

int main(void) {
	
	// define portB.0 as input
	DDRB &= ~(1 << 0);
	PORTB |= (1 << 0);
	
	// define portC as output
	PORTC = 0xFF;
	
	// duty_cycle=25% for non-inverted correct phase
	i = 64;
	OCR0 = i; 
	
	// correct phase, non-inverted, N=1
	TCCR0 = 0x61;
	
	DDRB |= (1 << PB3);
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	
	GICR = (1 << INT0);
	
	MCUCR = 0x02;
	
	sei();
	
	while(1){
		if (sw == 0)
			PORTC = 0x01;
		else
			PORTC = 0x02;
			
		OCR0 = i;
		
	}
	
	
return 0;	
}

