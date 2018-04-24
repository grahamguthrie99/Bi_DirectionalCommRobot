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

//Received from controller 
//Determines state 
struct controlData {
  byte onOff;
  byte movePan;
  byte forwardUp;
  byte backDown;
  byte left;
  byte right;
};

//Radio intialization
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

//State object 
controlData state;

Servo leftW;  //left Wheel
Servo rightW; //right Wheel
Servo rotX;   //panorama

//Starting position for ultrasonic
//servo middle value 
unsigned long pos = 65;

//Variables for ultrasonic 
unsigned long duration = 0;
int distance = 0;

void setup() {
  //Built In LED
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  //Ultrasonic initilaization
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);

  Serial.begin(9600);
  
  resetData();
  
  //Radio COMM
  radio.begin();
  //TWO WAY
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  
  //Attach all servos 
  rotX.attach(2);
  leftW.attach(3);
  rightW.attach(4);
    
}

void loop() {
    //Reveive Data
    timeout(5);
    radio.startListening();
    //Clear Position Limits 
    if(pos == 130)
      pos--;
    if(pos == 0)
      pos++;
      
    if (radio.available()) {
      //Read data sent from controller 
      radio.read(&state, sizeof(controlData));
      
      if(state.onOff){
        if(state.movePan){
          
        //Blue: Panoramic Movement
          color(0,0, 255); 
          if(state.left){
              //if accel left then turn servo left 
              if((pos<130) && (pos>0)){
                pos = pos + 1;
              }
            rotX.write(pos);
          }
          else if(state.right){
              //if accel right then turn servo right 
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
        //Wheels are powered based on correct state
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
    
    }
 
    else{
        state.movePan = 0;
        state.forwardUp = 0;
        state.backDown = 0;
        state.left = 0;
        state.right = 0;
        
        leftW.detach();
        rightW.detach();
      
    }
    //Send Data
    //Reset trigger pin
    digitalWrite(trig, LOW);
    timeout(5);
    radio.stopListening();
    distance = calcDistance();
    //Send data to controller 
    radio.write(&distance, sizeof(distance));
    

}
////////////////////////////////////////
//Delay function
void timeout(unsigned long del){
  unsigned long waitTime = 0;
  unsigned long take = millis();
  do{
    waitTime = millis() - take ; 
    
  }while(waitTime < del);

}
////////////////////////////////////////
void microtimeout(unsigned long del){
  unsigned long waitTime = 0;
  unsigned long take = micros();
  do{
    waitTime = micros() - take ; 
  }while(waitTime < del);

}


////////////////////////////////
//Ultrasonic senor process
//trip trigger pin 
//wait
//receive in echo pin
//calculate distance based on time
int calcDistance(){
    
    unsigned long duration;
    digitalWrite(trig, HIGH);
    microtimeout(10);
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
