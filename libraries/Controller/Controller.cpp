/* $Id$

*/

#include "Controller.h"


 static CHANNEL channel[15];  
 
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
    channel[pin].Lock = 0;
  }
}

uint8_t Controller::read(uint8_t pin) // return the value as degrees
{
  return channel[pin].Value;     

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

