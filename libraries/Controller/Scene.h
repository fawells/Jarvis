/* $Id$

*/

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <stdint.h>


typedef struct  {
  uint8_t Value;   //0-4095
  uint8_t Lock;    //0-1
} CHANNEL;  




class Controller
{
  public:
    Controller();
    uint8_t read(uint8_t Pin);  
    
    bool operator==(Controller &rhs);

  private:
   
    
};

#endif
// CONTROLLER_H
