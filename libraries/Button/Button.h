/* $Id$
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Hardware Abstraction Library for Buttons.
|| | It provides an easy way of handling buttons.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <Scene.h>

#define BUTTON_PULLUP HIGH
#define BUTTON_PULLUP_INTERNAL 2
#define BUTTON_PULLDOWN LOW

#define FADER_UP 2
#define FADER_DOWN 1
#define FADER_OFF 0

class Button;
typedef void (*buttonEventHandler)(Button&);

class Button
{
  public:

    Button(uint8_t buttonPin, uint8_t buttonMode = BUTTON_PULLUP_INTERNAL, unsigned int debounce = 0);

    void pullup(uint8_t buttonMode);
    void pulldown();

    bool isPressed();
    bool wasPressed();
    bool stateChanged();
    bool uniquePress();

    void setHoldThreshold(unsigned int holdTime);
    void setTripleThreshold(unsigned int tripleTime);

    void setDebounceDelay(unsigned int debounce);

    bool held(unsigned int time = 0);
    bool heldFor(unsigned int time);

    void pressHandler(buttonEventHandler handler);
    void releaseHandler(buttonEventHandler handler);
    void clickHandler(buttonEventHandler handler);
    void holdHandler(buttonEventHandler handler, unsigned int holdTime = 0);
    void tripleClickHandler(buttonEventHandler handler, unsigned int tripleTime = 1000);
    void setActiveFader(uint8_t faderState);
    unsigned int holdTime() const;
    inline unsigned int getPin() const
    {
      return pin;
    }

    inline unsigned int presses() const
    {
      return numberOfPresses;
    }

    inline unsigned int pressesInEvent() const
    {
      return numberOfPressesInEvent;
    }
    
    inline uint8_t getActiveFader()
    {
      return activeFader;
    }

// ***** Function for pass through to Scene class ******* //

    inline void setScene(Scene* scene)
    {
      _scene = scene ;
    }
    
    inline char * getSceneName()
    {
      return _scene->getSceneName();
    }

    inline void setFadeDirection(int fadeDirection)
    {
      _scene->setFadeDirection(fadeDirection);
    }

    inline void setMinValue(int minValue)
    {
      _scene->setMinValue(minValue);
    }

    inline void setMaxValue(int maxValue)
    {
      _scene->setMaxValue(maxValue);
    }

    inline bool getFadeDirection()
    {
       return _scene->getFadeDirection();
    }

    inline int getMinValue()
    {
       return _scene->getMinValue();
    }

    inline int getMaxValue()
    {
       return _scene->getMaxValue();
    }

    bool operator==(Button &rhs);

  private:
    void fader();
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    unsigned long pressedStartTime;
    unsigned long tripleStartTime;
    unsigned long releasedTime;
    unsigned int holdEventThreshold;
    unsigned int tripleEventThreshold;
    unsigned int debounceDelay;
    buttonEventHandler cb_onPress;
    buttonEventHandler cb_onRelease;
    buttonEventHandler cb_onClick;
    buttonEventHandler cb_onHold;
    buttonEventHandler cb_onTriple;
    unsigned int numberOfPresses;
    unsigned int numberOfPressesInEvent;
    bool triggeredHoldEvent;
    int activeFader;
    
    Scene::Scene* _scene;
    
};

#endif
// BUTTON_H
