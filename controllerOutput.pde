//Program creates a background sized 600x600
//As robot approches an object the background color
//changes.
//If green the foreground for the object is clear. 
//If red there is an object near the robot.
//Data is sent throught the serial port from the controller.

import processing.serial.*;
Serial contPort;

int dist; 
float col;
void setup(){
  size(600,600);
  background(255);
  String portName = Serial.list()[1];
  contPort = new Serial(this, portName, 9600);
  
 
}

void draw(){
  
  if(contPort.available() > 0){
     dist = contPort.read();
  }
  //println(dist);
  col = map(dist, 0, 100, 0, 1);
  println(col);
  background(255- (255*col), 255*col, 0); 
  
  
}
