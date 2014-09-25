/* $Id$

*/

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <stdint.h>
//#include <Adafruit_PWMServoDriver.h>

typedef struct  {
  uint8_t Value;   //0-4095
  bool Locked;
} CHANNEL;  




class Controller
{
  public:
    Controller();
    uint8_t read(uint8_t Pin);
    bool write(uint8_t pin, uint8_t value); //returns false if pin is locked    
    bool lock(uint8_t pin, bool lock = false);    
    bool locked(uint8_t pin); 
    bool operator==(Controller &rhs);

  private:
   //Adafruit_PWMServoDriver pwm;
    
};

#endif
// CONTROLLER_H
