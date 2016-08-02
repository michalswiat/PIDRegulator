#include <avr/io.h>
#include <avr/interrupt.h>

#include "pid.h"

#define PWM_PIN 11

static PID *pid;
static volatile uint32_t rpm, speed;
static bool work;

void setup() {
     TIMSK1 = (1 << OCIE0A);
     TCCR1A = 0;
     TCCR1B = (1 << CS02) | (1 << CS01) | (1 << CS00);
     OCR1AH = 0;
     OCR1AL = 124;
     
     pid = new PID(0, 255, 10, 0.1, 0.1, 0);
     
     sei();
}

void loop() {
     PC_handler();
     Arduino_handler();
     Switch_handler();
}

ISR (TIMER1_COMPA_vect)
{
	static int32_t time;
	if(++time == pid->period)
	{
		int32_t value = pid->getValue(speed);
		time = 0;
		analogWrite(PWM_PIN, value);
	}
}

void PC_handler(void
{
	if(!Serial.available())
	{
		return;
	}
	char sign = Serial.read();
	switch(sign)
	{
		case '+':
		     Control_acceleration();
		     break;

		case '-':
		     Control_decceleration();
		     break;

		case 'o':
		     Control_start():
		     break;

		case 'l':
		     Line_Off();
		     break;

		case 'n':
		     Line_On();
		     break;

		case 'm':
		     Control_changeMode(CONTROL_MODE_MANUAL);
		     break;

		case 'a':
		     Control_changeMode(CONTROL_MODE_AUTO);
		     break;

		case 's':
		     Control_stop();
		     break;

		case '0':
		     pid->setPoint(65);
		     break;

		case '1':
		     pid->setPoint(72);
		     break;

		case '2':
		     pid->setPoint(82);
		     break;

		case '3':
		     pid->setPoint(100);
		     break;

		case '4':
		     pid->setPoint(110);
		     break;
	}
}

void Arduino_handler(void)
{
	string data;
	while(Serial3.available())
	{
		char sign = Serial3.read();
		if(sign == '\n')
		{
			rpm = data.toFloat();
			speed = ((rpm * 60) * 3.14 * DIAMETR) / 1000;
		}
		else
		{
			data += sign;
		}
	}
}

void Switch_handler(void)
{
	if(digitalRead(startPin) == HIGH && !work)
	{
		Control_start();
	}
	if(digitalRead(stopPin) == LOW && work)
	{
		Control_stop();
	}
}

void Control_start(void)
{
	work = true;
}

void Control_stop(void)
{
	work = false;
}

void Control_acceleration(void)
{

}

void Control_decceleration(void)
{

}

void Line_on(void)
{

}

void Line_off(void)
{

}

