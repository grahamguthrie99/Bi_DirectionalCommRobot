/*

*/
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
#define xpin A3                  // x-axis of the accelerometer
#define ypin A2                 // y-axis
#define zpin A1                 //z-axis

//Communication Initialization
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
///////////////////////////////
struct controlData {
  byte onOff;
  byte movePan;
  byte forwardUp;
  byte backDown;
  byte left;
  byte right;
};
////////////////////////////
//States Array:
//Used for debouncing state switching
//button is given 3 spaces in array
// i-1 holds previous state
// i tracks button press
// i+1 holds state of machine
//OnOff switch starts at states[1]
//Movement switch starts at states[4]
boolean stateControl[] = {0, 0, 0, 0, 0, 0};

//Debouncing Variables 
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;
int xBase = 0;
int yBase = 0;
//////////////////////
controlData state;
/////////////////////

void setup() {
  //Button Setup
  pinMode(button, INPUT);
  pinMode(touchSense, INPUT);
  //RGB Light Setup
  pinMode(rLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  //Serial Setup
  Serial.begin(9600);
  //Accel Setup
  calibrateAccel();
  //ResetPrevData
  resetData();
  //Communication Setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
    
}

void loop() {
  
  boolean buttonReading = digitalRead(button);
  debounce(buttonReading, 1);
  state.onOff = stateControl[2];
  if(state.onOff){
    color(0,255, 0);
    boolean stateReading =digitalRead(touchSense);
    debounce(stateReading, 4);
    state.movePan = stateControl[5];
    if(state.movePan){
      color(0,0,255);
    }
    
    getMove();
    
  }
  else{
    color(255, 0, 0);
    calibrateAccel();
    state.movePan = 0;
    state.forwardUp = 0;
    state.backDown = 0;
    state.left = 0;
    state.right = 0;
    
  }
  Serial.print("o/f: ");
  Serial.print(state.onOff);
  Serial.print("\t"); 
  Serial.print("m/p: ");
  Serial.print(state.movePan);
  Serial.print("\t");
  Serial.print("fore: ");
  Serial.print(state.forwardUp);
  Serial.print("\t"); 
  Serial.print("back: ");
  Serial.print(state.backDown);
  Serial.print("\t"); 
  Serial.print("left: ");
  Serial.print(state.left);
  Serial.print("\t"); 
  Serial.print("right: ");
  Serial.print(state.right);
  Serial.print("\t"); 
  
  radio.write(&state, sizeof(controlData)); 
}



////////////////////////////////
void color (unsigned char red, unsigned char green, unsigned char blue)
{ 
  analogWrite(rLight, red); 
  analogWrite(bLight, blue); 
  analogWrite(gLight, green); 
}
////////////////////////////////
void calibrateAccel(){
  xBase = analogRead(xpin);
  yBase = analogRead(ypin);
  
}
////////////////////////////////
void resetData() 
{
  state.onOff = 0;
  state.movePan = 0;
  state.forwardUp = 0;
  state.backDown = 0;
  state.left = 0;
  state.right = 0;
}
////////////////////////////////
void debounce(boolean reading, int i){
  if (reading != stateControl[i-1]) {
      lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != stateControl[i]) {
         stateControl[i] = reading;
          if(stateControl[i] == 1){
            stateControl[i+1] = !(stateControl[i+1]);
            
          }
      }
  }
  stateControl[i-1] = reading; 
}
////////////////////////////////////////
void getMove(){
  int curx = analogRead(xpin);
  int cury = analogRead(ypin);
  
  //forward
  if((cury-10)> yBase){
    state.forwardUp = 1;
    state.backDown = 0;
    state.left = 0;
    state.right = 0;
    
  }
  //backward
  else if((cury+10)< yBase){
    state.forwardUp = 0;
    state.backDown = 1;
    state.left = 0;
    state.right = 0;
    
    
  }
  //right
  else if((curx-10) > xBase){
    state.forwardUp = 0;
    state.backDown = 0;
    state.left = 0;
    state.right = 1;
    
  }
  //left 
  else if((curx+10) < xBase){
    state.forwardUp = 0;
    state.backDown = 0;
    state.left = 1;
    state.right = 0;
    
  }
  else{
    state.forwardUp = 0;
    state.backDown = 0;
    state.left = 0;
    state.right = 0;
    
  }
}
