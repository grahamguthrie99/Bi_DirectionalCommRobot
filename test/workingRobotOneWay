/*

*/
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>
#include <Servo.h>

#define bLight 33
#define gLight 34
#define rLight 35
#define trig 40
#define echo 42




struct controlData {
  byte onOff;
  byte movePan;
  byte forwardUp;
  byte backDown;
  byte left;
  byte right;
};

RF24 radio(7, 8); // CE, CSN

//const byte addresses[][6] = {"00001", "00002"};
const byte address[6] = "00001";
controlData state;

Servo leftW;  
Servo rightW;
Servo rotX;
//Servo rotY;

long delayTime = 25;
long prevTime = 0;
long prevTrigTime =0;
long pos = 65;
int distance =0;

void setup() {
  //Built In LED
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);

  Serial.begin(9600);
  
  resetData();
  
  //Radio COMM
  radio.begin();
  //radio.openWritingPipe(addresses[0]); // 00002
  //radio.openReadingPipe(1, addresses[1]); // 00001
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  rotX.attach(2);
  leftW.attach(3);
  rightW.attach(4);
    
}

void loop() {
  //digitalWrite(trig, LOW);
    if(pos == 130)
      pos--;
    if(pos == 0)
      pos++;
    //Reveive Data
    if (radio.available()) {
      radio.read(&state, sizeof(controlData));
      
      if(state.onOff){
        if(state.movePan){
          //Blue: Panoramic Movement
        color(0,0, 255); 
        if(state.left){
            if((pos<130) && (pos>0)){
              pos = pos + 1;
            }
            rotX.write(pos);
         }
         else if(state.right){
            if((pos<130) && (pos>0)){
              pos = pos - 1;
            }
            rotX.write(pos);
         }
         else{
           rotX.write(pos);
           
         }
         
        }
        else{
          //Green: Wheel Movement 
          color(0,255,0);
          
          if(state.forwardUp){
            leftW.attach(3);
            rightW.attach(4);
            leftW.write(180);
            rightW.write(0);
          }
          else if(state.backDown){
            leftW.attach(3);
            rightW.attach(4);
            leftW.write(0);
            rightW.write(180);
          }
          else if(state.left){
            leftW.attach(3);
            leftW.write(180);
          }
          else if(state.right){
            rightW.attach(4);
            rightW.write(0);
          }
          else{
            leftW.detach();
            rightW.detach();
          }
        }
      }
      else{
        color(255, 0, 0);
        state.movePan = 0;
        state.forwardUp = 0;
        state.backDown = 0;
        state.left = 0;
        state.right = 0;
        leftW.detach();
        rightW.detach();
      }
      
        
      //Serial.println("pos: ");
      //Serial.print(pos);
      /*Serial.print("\t"); 
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
      Serial.print("\t"); */
    }
    else{
     Serial.println("pos: ");
      Serial.print(pos);
      //color(0, 0, 0);
        state.movePan = 0;
        state.forwardUp = 0;
        state.backDown = 0;
        state.left = 0;
        state.right = 0;
        
        leftW.detach();
        rightW.detach();
      
    }
    
    //Send Data
    
  

  /*if((micros() - prevTrigTime) > 10){
    prevTrigTime =micros();
    distance = calcDistance();
    Serial.print(distance);
    //radio.write(&distance, sizeof(distance));
  }*/
  //delay(100);
}
////////////////////////////////
int calcDistance(){
  
    long duration;
    digitalWrite(trig, HIGH);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    return duration*0.034/2;
 
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
void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function 
{ 
  analogWrite(rLight, red); 
  analogWrite(bLight, blue); 
  analogWrite(gLight, green); 
}
