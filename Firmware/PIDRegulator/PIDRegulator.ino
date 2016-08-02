#include <avr/io.h>
#include <avr/interrupt.h>

#include "pid.h"

#define PWM_PIN 11

PID *pid;
uint32_t rpm;

void setup() {
     TIMSK1 = (1 << OCIE0A);
     TCCR1A = 0;
     TCCR1B = (1 << CS02) | (1 << CS01) | (1 << CS00);
     OCR1AH = 0;
     OCR1AL = 124;
     
     pid = new PID(1200, 255, 10, 0.1, 0.1, 0);
     
     sei();
}

void loop() {

}

ISR (TIMER1_COMPA_vect)
{
	static int32_t time;
	if(++time == pid->period)
	{
		int32_t value = pid->getValue(rpm);
		time = 0;
		analogWrite(PWM_PIN, value);
	}
}

