// RF24 - Version: Latest 
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>

//Pin Definitions 
#define button 2
#define bLight 3
#define gLight 4
#define rLight 5
#define touchSense 6

//Communication Initialization
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

//States Array:
//Used for debouncing state switching
//button is given 3 spaces in array
// i-1 holds previous state
// i tracks button press
// i+1 holds state of machine
//OnOff switch starts at states[1]
//Movement switch starts at states[4]
boolean states[] = {0, 0, 0, 0, 0, 0};

//Debouncing Variables 
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;

void setup() {
  //Button Setup
  pinMode(button, INPUT);
  pinMode(touchSense, INPUT);
  //RGB Light Setup
  pinMode(rLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  Serial.begin(9600);
  //Communication Setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  /////////////////////////////////
  //OnOff Switch Read
  boolean buttonReading = digitalRead(button);
  debounce(buttonReading, 1);
  radio.write(&states[2], sizeof(states[2]));
  
  if(states[2])
  {
    //ON State
    //Robot State Switch Read 
    boolean stateReading =digitalRead(touchSense);
    debounce(stateReading, 4);
    radio.write(&states[5], sizeof(states[5]));
    
    if(states[5]){
      //MOVE State
        color(0,255, 0); 
       
    }
    else{
      //Pan Tilt State
        color(0,0,255);
    }
   
  }
  else{
    //OFF State
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
            Serial.println("switch");
          }
      }
  }
  states[i-1] = reading; 
}
////////////////////////////////
void color (unsigned char red, unsigned char green, unsigned char blue)
{ 
  analogWrite(rLight, red); 
  analogWrite(bLight, blue); 
  analogWrite(gLight, green); 
}
////////////////////////////////
