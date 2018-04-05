/*

*/

#include <Servo.h>

Servo left;  // create servo object to control a servo
Servo right;
Servo xrot;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
long prevTime = 0;        
long delayTime = 25;    
void setup() {
  //
  //left.attach(3);
  //right.attach(4); // attaches the servo on pin 9 to the servo object
}

void loop() {
  if((millis() - prevTime) > delayTime){
      prevTime = millis();
      
      if(pos%50 ==0){
      //left.attach(3);
      //left.write(0);
      }
      else{
       // left.detach();
      }
      pos++;
      
  }
      
  
  /*for (pos = 0; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    xrot.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 130; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    xrot.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
  /*right.attach(4);
  left.attach(3);
  right.write(0);
  left.write(0);
  delay(1000);
  right.detach();
 left.detach();
  right.attach(4);
  right.write(180);
  delay(1000);*/
  
 /*unsigned long currentMillis = millis();
 if(currentMillis - previousMillis > interval) {
     save the last time you blinked the LED 
    previousMillis = currentMillis;   
 }*/ 
 
/* if(pos%10 == 0)
 {
   right.attach(4);
   right.write(180);
   delay(1000);
   
 }
 /*else if(pos%15 == 0)
 {
  left.attach(3);
   left.write(180);
   delay(100);
   
 }
 else if(pos%3 == 0)
 {
   left.attach(3);
   right.attach(4);
   left.write(180);
   right.write(0);
   delay(1000);
 }
 else if(pos%5 == 0){
   left.attach(3);
  right.attach(4);
   left.write(0);
   right.write(180);
   delay(1000);
   
 }
  else{ 
   right.detach();
  left.detach();
  delay(1000);
 }
 right.detach();
 left.detach();
 pos++;*/
  
  
}
