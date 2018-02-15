#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>


#define button 2
#define bLight 3
#define gLight 4
#define rLight 5
#define touchSense 6

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
/*boolean buttonState = 0;
boolean lastButtonState = 0;
boolean currentState =0;
boolean lastState = 0;
boolean onOff = 0;
boolean machState = 0;*/

//States Array:
//Used for debouncing state switching
//button is given 3 spaces in array
// i-1 holds previous state
// i tracks button press
// i+1 holds state of machine
//OnOff switch starts at states[1]
//Movement switch starts at states[4]

boolean states[] = {0, 0, 0, 0, 0, 0};

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

void setup() {
  //Button
  pinMode(button, INPUT);
  pinMode(touchSense, INPUT);
  pinMode(rLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  Serial.begin(9600);
  //COMM
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  /////////////////////////////////
  
  boolean buttonReading = digitalRead(button);
  debounce(buttonReading, 1);
  radio.write(&states[2], sizeof(states[2]));
  if(states[2])
  {
    boolean stateReading =digitalRead(touchSense);
    debounce(stateReading, 4);
    radio.write(&states[5], sizeof(states[5]));
    
    if(states[5] ==1){
        color(0,255, 0); 
        Serial.print("MOVE");
    }
    else{
        color(0,0,255);
        Serial.print("PAN");
    }
    
  }
  else{
    color(255, 0, 0);
    states[5] = 0;
  }
  
}
////////////////////////////////
void debounce(boolean reading, int i){
  if (reading != states[i-1]) {
      lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != states[i]) {
         states[i] = reading;
          if(states[i] == 1){
            states[i+1] = !(states[i+1]);
          }
      }
  }
  states[i-1] = reading; 
}
////////////////////////////////

/*void turnON(boolean reading){
  if (reading != lastButtonState) {
      lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
         buttonState = reading;
          if(buttonState == 1){
            onOff = !(onOff);
          }
      }
  }
  lastButtonState = reading; 
}
////////////////////////////////
void debounceState(boolean reading){
  if (reading != lastState) {
      lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != currentState) {
         currentState = reading;
          if(currentState == 1){
            machState = !(machState);
          }
      }
  }
  lastState = reading; 
}*/
////////////////////////////////
void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function 
{ 
  analogWrite(rLight, red); 
  analogWrite(bLight, blue); 
  analogWrite(gLight, green); 
}
