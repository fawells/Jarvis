#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <Dimmer.h>


/*
  base format i=#&t=#&a=#&p=#
    i = id      ->  id of this box
    t = token   ->  for authentication [String[8]]
    a = action  ->  incoming task [read, write, lock, unlock]
    p = pin     ->  target channel 0 to 15
    
    ACTIONS:
    r = read    -> read pin [p = pin]
    w = write   -> write pin [p = pin, v = value, s = span, d = delay]
    l = lock    -> lock pin  [p = pin]
    u = unlock  -> unlock pin [p = pin] 
*/
  
#define ID           0 // i
#define TOKEN        1 // t
#define ACTION       2 // a
#define PIN          3 // p
#define VALUE        4 // v
#define SPAN         5 // s
#define DELAY        6 // d

char params[7] = {'i','t','a','p','v','s','d'};

String SerialString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

 
String token = "fg5gpo3D";
int id = 1;

Dimmer dimmer;

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Loading dimmer module...");
  dimmer.PWMinit();
  SerialString.reserve(200);
  

}

void loop() {
  // Update faders
  dimmer.updateFades();
  
  //Convert serial string into fade frames
  if (stringComplete)
  {
    processSerial();
    SerialString = "";
    stringComplete = false;
  }
}


void processSerial() {
  Serial.println("Processing Serial data..."); 
  String values[7];

  for (int i = 0; i < 7; i = i + 1) {
    String needle = String(params[i]) + "=";
    int findParam = SerialString.indexOf(needle);
    if(findParam != -1)
    {
      int findNextParam = SerialString.indexOf("&", findParam);
      String result = SerialString.substring(findParam+2,findNextParam);
      values[i] = result;
    } 
  }
  
 /*
  for (i = 0; i < 7; i = i + 1) {
    Serial.print(params[i]);
    Serial.print("=");
    Serial.println(values[i]);
  }
 */
 
  if (values[ID].toInt() != id)
  {
    Serial.println("ID error");
    return;
  }
  
  if (values[TOKEN].equals(token) != true)
  {
    Serial.println("Token error");
    return;
  }
  
  if (values[PIN].equals("\0") == true)
  {
    Serial.println("Pin error");
    return;
  }
  
  int pin = values[PIN].toInt();
  
// As case switch doesn't work with String:

  // i=1&t=fg5gpo3D&p=2&a=r
  
  if (values[ACTION].equals("r") == true)
  {
    Serial.print("Reading: ");
    Serial.println(dimmer.read(pin));
   }
  
  
  // i=1&t=fg5gpo3D&p=2&a=w&v=4095
  // i=1&t=fg5gpo3D&p=2&a=w&v=4095&s=1000
  // i=1&t=fg5gpo3D&p=2&a=w&v=4095&s=1000&d=1000
  
  if (values[ACTION].equals("w") == true)
  {
    Serial.println("Writing");
    
    if (values[VALUE].equals("\0") == true)
    {
      Serial.println("Value error");
      return;
    }
    
    if (values[SPAN].equals("\0") == true)
    {
      values[SPAN] = 0;
    }
    if (values[DELAY].equals("\0") == true)
    {
      values[DELAY] = 0;
    }

    if (dimmer.locked(pin))
    {
      Serial.println("Pin is locked");
      return;
    }
    bool success = dimmer.addFade(pin, values[VALUE].toInt(), values[SPAN].toInt(), values[DELAY].toInt());
    
    if (!success)
    {
      Serial.println("Buffer is full");
      return;
    }

  }

  // i=1&t=fg5gpo3D&p=2&a=l
  if (values[ACTION].equals("l") == true)
  {
    Serial.println("Locking");
    dimmer.lock(pin, true);
  }
  
    // i=1&t=fg5gpo3D&p=2&a=u
  if (values[ACTION].equals("u") == true)
  {
    Serial.println("Unlocking");
    dimmer.lock(pin, false);
  }  

  return;
}



/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n')
    {
      stringComplete = true;
    } else {
      SerialString += inChar;
    }
  }
}
