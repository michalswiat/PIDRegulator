#ifndef _PID_H_
#define _PID_H_

#include "Arduino.h"

class PID
{
 public:
  PID(uint32_t setpoint, uint32_t maxValue, uint32_t minValue,
      float p, float i, float d);
  uint32_t getValue(uint32_t input);
  void setPoint(uint32_t setpoint);
  
  uint32_t period = 1000;

 private:
  uint32_t setpoint;
  uint32_t max;
  uint32_t min;

  float Kp;
  float Ki;
  float Kd;
};

#endif
