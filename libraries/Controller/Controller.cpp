/* $Id$

#include "Controller.h"


 static CHANNEL channel[15];  
 //Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
/*
|| @constructor
|| | Set the initial state of this button
|| #
||
|| @parameter buttonPin  sets the pin that this switch is connected to
|| @parameter buttonMode indicates BUTTON_PULLUP or BUTTON_PULLDOWN resistor
*/
Controller::Controller()
{
  for(uint8_t pin=0; pin < 15; pin++) {
    channel[pin].Value = 0;
    channel[pin].Locked = 0;
  }
  //pwm.begin();
  //pwm.setPWMFreq(1600);
}



uint8_t Controller::read(uint8_t pin) // return the value as degrees
{
  return channel[pin].Value;     

}

bool Controller::write(uint8_t pin, uint8_t value)
{
    if (channel[pin].Locked = true)
    { 
        return false;
    }
//TODO limit
    channel[pin].Value = value;
    //pwm.setPWM(pin, 0, value); 
    return true;
    
}

bool Controller::lock(uint8_t pin, bool lock)
{
    channel[pin].Locked = lock;
    return channel[pin].Locked ;

}

bool Controller::locked(uint8_t pin) // return the value as degrees
{
  return channel[pin].Locked;     

}

/*
|| @description
|| | Compare a Controller object against this
|| #
||
|| @parameter  rhs the Controller to compare against this Controller
||
|| @return true if they are the same
*/
bool Controller::operator==(Controller &rhs)
{
  return (this == &rhs);
}

