/* $Id$

*/

#ifndef SCENE_H
#define SCENE_H

#define FADEUP true
#define FADEDOWN false


#include <stdint.h>

class Scene;
typedef void (*sceneEventHandler)(Scene&);

class Scene
{
  public:

    Scene(char SceneName[8] = "", int minValue = 0, int maxValue = 100);
    void setSceneName(char SceneName[8]);
    void setFadeDirection(int fadeDirection);
    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

    inline bool getFadeDirection()
    {
       return _fadeDirection;
    }

    inline int getMinValue()
    {
       return _minValue;
    }

    inline int getMaxValue()
    {
       return _maxValue;
    }


    inline char * getSceneName()
    {
      return _sceneName;
    }

    void setScene(char SceneName[8] = "");
    
    bool operator==(Scene &rhs);

  private:

    char _sceneName[8]; 
    bool _fadeDirection;
    uint8_t _minValue;
    uint8_t _maxValue;
    
};

#endif
// SCENE_H
