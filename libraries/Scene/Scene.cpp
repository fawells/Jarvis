/* $Id$

*/

#include <wiring_private.h>
#include "Scene.h"


/*
|| @constructor
|| | Set the initial state of this button
|| #
||
|| @parameter buttonPin  sets the pin that this switch is connected to
|| @parameter buttonMode indicates BUTTON_PULLUP or BUTTON_PULLDOWN resistor
*/
Scene::Scene(char sceneName[8], int minValue, int maxValue)
{

   setSceneName(sceneName);
//   strncpy(_sceneName, sceneName, 8);
//      _sceneName[8] = 0;
   setFadeDirection(FADEDOWN);
   setMinValue(minValue);
   setMaxValue(maxValue);



}

void Scene::setSceneName(char sceneName[8])
{
      strncpy(_sceneName, sceneName, 8);
      _sceneName[8] = 0;

}

void Scene::setFadeDirection(int fadeDirection)
{
      _fadeDirection = fadeDirection;
}

void Scene::setMinValue(int minValue)
{
      _minValue = minValue;
}

void Scene::setMaxValue(int maxValue)
{
     _maxValue = maxValue;
}
/*
|| @description
|| | Compare a button object against this
|| #
||
|| @parameter  rhs the Button to compare against this Button
||
|| @return true if they are the same
*/
bool Scene::operator==(Scene &rhs)
{
  return (this == &rhs);
}

