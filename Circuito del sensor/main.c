#ifdef F_CPU
#undef F_CPU
#endif
#define F_CPU 1000000

#define TRIG_PIN 3
#define ECHO_PIN 2
#define TRIG_PORT PORTD
#define TRIG_DDR  DDRD
#define ECHO_IN   PIND
#define ECHO_DDR  DDRD

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

static volatile int pulse_time = 0;

int main(void)
{
	unsigned int distance = 0;

	TRIG_DDR |= (1<<TRIG_PIN);
	ECHO_DDR &= (1<<ECHO_PIN);
	 
	DDRB |= (1<<DDB2);
   
	EIMSK |= (1<<INT0);	// habilitar INT0
	EICRA |= (1<<ISC00);	// configurar el disparador de interrupcion en cualquier cambio

	sei();
	while(1)
	{ 
		TRIG_PORT |= (1<<TRIG_PIN);
		_delay_us(15);					// activar el modulo ultrasonico durante 15us
		TRIG_PORT &= ~(1<<TRIG_PIN);

		distance = pulse_time * 0.0343 / 2;		// calcular la distancia
	
		if (distance <= 100)
		{
			PORTB |= (1<<PIND2);
		} else 
		{
			PORTB &=~ (1<<PIND2);
		}
	 }
}

// Este ISR se llama automaticamente cuando ocurre un cambio en el pin INT0 debido al cambio del pin de echo del modulo ultrasonico
ISR(INT0_vect)
{
	if ((ECHO_IN & (1<<ECHO_PIN)) == 0)
	{
		// El echo cambio de ALTO a BAJO
		TCCR1B = 0;		// contador de desactivacion
		pulse_time = TCNT1;	// la memoria de conteo se actualiza a un numero entero
		TCNT1 = 0;		// resetear la memoria del contador
	} else {
		// echo cambi� el cambio de BAJO a ALTO
		TCCR1B |= (1<<CS10);	// habilitacion de contador
	}
}
