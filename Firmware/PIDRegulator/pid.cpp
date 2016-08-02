#include "pid.h"

PID::PID(uint32_t setpoint, uint32_t maxValue, uint32_t minValue,
	 float p, float i, float d)
{
  this->setpoint = setpoint;
  this->max = maxValue;
  this->min = minValue;

  this->Kp = p;
  this->Ki = i;
  this->Kd = d;
}

uint32_t PID::getValue(uint32_t input)
{
  static uint32_t previous;
  static int32_t IValue, DValue;
  int32_t error = this->setpoint - input;
  float output;

  IValue += (int32_t)(this->Ki * error);
  if(IValue > this->max)
    {
      IValue = max;
    }
  else if(IValue < this->min)
    {
      IValue = min;
    }

  DValue = input - previous;
  previous = input;

  output = this->Kp * error + IValue - this->Kd * DValue;
  if(output > max)
    {
      output = max;
    }
  else if(output < min)
    {
      output = min;
    }

  return (uint32_t)(output);
}
