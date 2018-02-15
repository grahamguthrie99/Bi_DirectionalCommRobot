#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>
#include <Servo.h>

#define bLight 3
#define gLight 4
#define rLight 5


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
boolean states[] = {0, 0};



void setup() {
  //Built In LED
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  Serial.begin(9600);
  
  //Radio COMM
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    states[0] = receiveState();
    Serial.println("On/Off:" + states[0]);
    if(states[0]){
      //poweredOn
      states[1] = receiveState();
      Serial.println("PAN/Move:" + states[1]);
      if(states[1]){
        //Movement Mode
        color(0,255, 0); 
        
      }
      else{
        //PanTilt Mode
        color(0,0,255);
        
      }
      
    }
    else{
    color(255, 0, 0);
      
    }
  }
  else{
    color(255, 255, 255);
     
  }

}
int receiveState(){
  bool stateChange;
  radio.read(&stateChange, sizeof(stateChange));
  return stateChange; 
}
void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function 
{ 
  analogWrite(rLight, red); 
  analogWrite(bLight, blue); 
  analogWrite(gLight, green); 
}
