#include "Dimmer.h"

#define CHANNEL_SIZE    15
#define FADE_BUFFER_SIZE    2

 static CHANNEL channel[CHANNEL_SIZE];  
 static FADE fade[FADE_BUFFER_SIZE];  

/*
|| @constructor
|| | Loop through the CHANNEL and FADE struct arrays and sets inital values
|| #
||
*/

Dimmer::Dimmer()// : pwm()
{
  for(uint8_t pin=0; pin < CHANNEL_SIZE; pin++) 
  { 
    channel[pin].Value = 0;
    channel[pin].Locked = false;
  }

  for(uint8_t frame=0; frame < FADE_BUFFER_SIZE; frame++) 
  {
    fade[frame].channel = -1;
  }
}

/*
|| @description
|| | Initiate the Adafruit_PWMServoDriver
|| #
||
*/

void Dimmer::PWMinit(uint8_t addr, float freq)
{
  PWM = Adafruit_PWMServoDriver(addr);
  PWM.begin(); 
  PWM.setPWMFreq(freq);
}

/*
|| @description 
|| | Process that is run every loop
|| | 
|| | Loops though the fade buffer to find frames that are active (not -1)
|| #
||
*/
void Dimmer::updateFades()
{
    uint32_t currentMillis = millis();

    for(uint8_t frame=0; frame < FADE_BUFFER_SIZE; frame++)
    {
        if (fade[frame].channel != -1)
        {
            if (currentMillis > (fade[frame].startMillis + fade[frame].span))
            {
                // Fade is finished to release the frame
                write(fade[frame].channel , fade[frame].endValue);
                fade[frame].channel = -1; 
                continue;

            }

            if (currentMillis < fade[frame].startMillis )
            {
                // Fade is yet to start
                continue;
            }

            if (fade[frame].span == 0)
            {
                // Frame doesn't fade so write it straight away 
                write(fade[frame].channel , fade[frame].endValue);
                fade[frame].channel = -1; 
                continue;
            }
  
            float gradient = ((float)fade[frame].endValue - (float)fade[frame].startValue ) / fade[frame].span;
            uint32_t value = ((millis() - fade[frame].startMillis ) * gradient) + fade[frame].startValue;
            value = constrain(value, 0, 4095);
            write(fade[frame].channel, value);

        }
    }
}

/*
|| @description
|| | Read current value of pin
|| #
||  
|| @parameter pin   -> index of fade buffer (pin number) to query
||
|| @return current value of pin (0-4095)
*/

uint16_t Dimmer::read(uint8_t pin) // return the value as degrees
{
  return channel[pin].Value;     
}

/*
|| @description
|| | Find an empty fade frame in FADE buffer (not channel of -1)
|| | 
|| | Loops though the fade buffer to find frs that are active (not -1)
|| #
||  
|| @parameter pin   -> pin to fade
|| @parameter value -> end value of fade (0 - 4095)
|| @parameter span  -> duration of fade (starts after delay)
|| @parameter delay -> delay before staring the fade
||
|| @return true; false if fade buffer is full
*/

bool Dimmer::addFade(uint8_t pin, uint16_t value, uint16_t span, uint16_t delay)
{
    for(uint8_t frame=0; frame < FADE_BUFFER_SIZE; frame++)
    {
        if (fade[frame].channel == -1)
        {
            fade[frame].channel = pin;
            fade[frame].startValue = channel[pin].Value;
            fade[frame].endValue = value;
            fade[frame].startMillis = millis() + delay;  
            fade[frame].span = span;
            fade[frame].delay = delay;
            break;
        }
            
        if (frame == FADE_BUFFER_SIZE-1) //Fade buffer is full
        {
            return false;
        }
            
    }
    return true;
}

/*
|| @description
|| | Writes to Adafruit_PWMServoDriver
|| #
||  
|| @parameter pin   -> pin to write to
|| @parameter value -> end value of fade (0 - 4095)
||
|| @return true; false if pin is locked
*/

bool Dimmer::write(uint8_t pin, uint16_t value)
{
    if (channel[pin].Locked == true)
    { 
        return false;
    }

    value = constrain(value, 0, 4095);
    PWM.setPin(pin, value); 
    channel[pin].Value = value;
    return true;
    
}

/*
|| @description
|| | Lock pin so that no writes can occur
|| #
||  
|| @parameter pin   -> pin to write
|| @parameter lock  -> boolean for locking, true to lock, false to unlock
||
|| @return true or false locked status
*/

bool Dimmer::lock(uint8_t pin, bool lock)
{
    channel[pin].Locked = lock;
    return channel[pin].Locked;
}

/*
|| @description
|| | Query channel for locked status
|| #
||  
|| @parameter pin   -> pin to query
||
|| @return true or false locked status
*/

bool Dimmer::locked(uint8_t pin) // return the value as degrees
{
  return channel[pin].Locked;     
}


/*
|| @description
|| | Compare a Dimmer object against this
|| #
||
|| @parameter  rhs the Dimmer to compare against this Dimmer
||
|| @return true if they are the same
*/
bool Dimmer::operator==(Dimmer &rhs)
{
  return (this == &rhs);
}

