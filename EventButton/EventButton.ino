/**
 * EventButton
 * by BREVIG http://alexanderbrevig.com
 * 
 * Use a button connected to digital pin 12.
 * Digital pin 12 is used as input and connected to a button
 * 
 * Whis example demonstates the event API for buttons
 */
 
#include <Button.h>
#include <Scene.h>
int WLED = 13;
boolean activeFader = false;
int WLEDval = 0;
  int direction = 1; 
  Scene test = Scene("hello", 0, 100);
Button button45 = Button(45,BUTTON_PULLDOWN,50);


/*
  Define the event handler first, this part of the sketch has a "life of it's own"
*/
void handleButtonPressEvents(Button &btn)
{
  Serial.print("/");
  
  //digitalWrite(WLED,HIGH);
}

void handleButtonReleaseEvents(Button &btn)
{
  Serial.print("\\");
    //test.setSceneName("gooddbye");
  Serial.println(button45.getMaxValue());
  //Serial.print((btn.target()));
  //(btn.getScene()).setScene("goodbye");
  //Serial.print(test.getScene());
  //btn.setScene(test);
  //Serial.print((btn.getScene()).getScene());
  btn.setActiveFader(FADER_OFF);
}

void handleButtonClickEvents(Button &btn) 
{
  Serial.println("click");
}

void handleButtonHoldEvents(Button &btn) 
{
  Serial.println("hold");
  btn.setActiveFader(FADER_UP);

}

void handleButtonTripleEvents(Button &btn) 
{
  Serial.println("triple");
  btn.setMaxValue(100);   
}

/*
  Do your regular setup stuff here
*/
void setup()
{
  Serial.begin(9800);
  pinMode(WLED,OUTPUT);
  
  button45.pressHandler(handleButtonPressEvents);
  button45.releaseHandler(handleButtonReleaseEvents);
  button45.clickHandler(handleButtonClickEvents);
  button45.holdHandler(handleButtonHoldEvents,1500);
  button45.tripleClickHandler(handleButtonTripleEvents,500);
  button45.setScene(&test);
  Serial.println(button45.getSceneName());
  test.setSceneName("gooddbye");
  Serial.println(button45.getSceneName());
  Serial.print("MaxValue: ");
  Serial.println(button45.getMaxValue());

  
}

int fader()
{
 
    if (WLEDval <= 0 ){
      direction = 1; 
    }
    if (WLEDval >=255){
      direction = -1; 
    }
  WLEDval = WLEDval + direction;
Serial.println(WLEDval);
    analogWrite(13, WLEDval);
   button45.setMaxValue(WLEDval);    
    delay(5);                      

}

void loop()
{
  button45.isPressed(); //update internal state
  if (button45.getActiveFader() != FADER_OFF){
    fader();
  }
  /*
    Feel free to do your own processing here. 
    The buttons will be handeled 'automagically' by the handler functions
  */
}
