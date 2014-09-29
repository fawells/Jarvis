
#ifndef DIMMER_H
#define DIMMER_H
#include <stdint.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

typedef struct  {
                              /* channel not listed as index of struct array is used */
  uint16_t Value;             /* value when the fade starts (0 - 4095) */
  bool Locked;                /* lock channel, stops value changes (true/false) */
} CHANNEL;  

typedef struct  {
    int8_t channel; 		/* channel this fade is on */
    int16_t startValue;       /* value when the fade starts (0 - 4095) */
    int16_t endValue;         /* value when the fade ends (0 - 4095) */
    uint32_t startMillis;     /* millis() when to start */
    int16_t span;             /* how long the fade will take in millis from startValue to endValue (not including delay) */
    int16_t delay;            /* delay before fade (span) starts in millis */
} FADE;  



class Dimmer
{
  public:
    Dimmer();
    void PWMinit(uint8_t addr = 0x40, float freq = 1600);
    void updateFades();
    uint16_t read(uint8_t Pin);
    bool addFade(uint8_t pin, uint16_t value = 0, uint16_t span = 0, uint16_t delay = 0);
    bool write(uint8_t pin, uint16_t value = 0);
    bool lock(uint8_t pin, bool lock = false);    
    bool locked(uint8_t pin); 

// ? isFading (is ther a fade on this channel
// ? clearFades (clear fades on a channel)

    bool operator==(Dimmer &rhs);

  private:
    Adafruit_PWMServoDriver PWM;

    
};


#endif
// DIMMER_H
