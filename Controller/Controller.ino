#include <Controller.h>

/*
  base format i=#&t=#&a=#&p=#
    i = id      ->  id of this box
    t = token   ->  for authentication [String[8]]
    a = action  ->  incoming task [read, write, lock, unlock]
    p = pin     ->  target channel 0 to 15
    
    ACTIONS:
    r = read    -> read pin [p = pin]
    w = write   -> write pin [p = pin, v = value, d = duration]
    l = lock    -> lock pin  [p = pin]
    u = unlock  -> unlock pin [p = pin] 
*/
  
#define ID           0 // i
#define TOKEN        1 // t
#define ACTION       2 // a
#define PIN          3 // p
#define VALUE        4 // v
#define DURAT        5 // d
 
char params[6] = {'i','t','a','p','v','d'};

String SerialString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

 
String token = "fg5gpo3D";
int id = 1;

Controller controller;

void setup() {
  Serial.begin(9600);
  Serial.println("Loading controller module...");
  
  SerialString.reserve(200);

}

void loop() {
  // put your main code here, to run repeatedly: 
    if (stringComplete) {
    Serial.println(SerialString); 
    processSerial();
    // clear the string:
    SerialString = "";
    stringComplete = false;
  }
}


void processSerial() {
  Serial.println("Processing Serial data..."); 
  String values[6];

  int i;
  // i=1&t=fg5gpo3D&a=r&p=2

  
  
  for (i = 0; i < 6; i = i + 1) {
    String needle = String(params[i]) + "=";
    int findParam = SerialString.indexOf(needle);
    if(findParam != -1)
          {
            int findNextParam = SerialString.indexOf("&", findParam);
            String result = SerialString.substring(findParam+2,findNextParam);
            values[i] = result;
          } 
  }

//  for (i = 0; i < 6; i = i + 1) {
//    Serial.print(params[i]);
//    Serial.print("=");
//    Serial.println(values[i]);
//  }
  
  if (values[ID].toInt() != id) {
    Serial.println("ID error");
    return;
  }
  
  if (values[TOKEN].equals(token) != true) {
    Serial.println("Token error");
    return;
  }
  
  if (values[PIN].equals("\0") == true) {
    Serial.println("Pin error");
    return;
  }
  
// As case switch doesn't work with String:

  // i=1&t=fg5gpo3D&p=2&a=r
  
  if (values[ACTION].equals("r") == true) {
    Serial.print("Reading: ");
    Serial.println(controller.read(values[PIN].toInt()));
    
  }
  
  
  // i=1&t=fg5gpo3D&p=2&a=w&v=4095
  
  if (values[ACTION].equals("w") == true) {
    Serial.println("Writing");
    
    if (values[VALUE].equals("\0") == true) {
      Serial.println("Value error");
      return;
    }
    
    if (values[DURAT].equals("\0") == true) {
      values[DURAT] = 0;
    }

  }

  // i=1&t=fg5gpo3D&p=2&a=l
  if (values[ACTION].equals("l") == true) {
    Serial.println("Locking");
  }
  
    // i=1&t=fg5gpo3D&p=2&a=u
  if (values[ACTION].equals("u") == true) {
    Serial.println("Unlocking");
  }  


   
  // Serial.println("Still here");
}



/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      SerialString += inChar;
    }
  }
}
