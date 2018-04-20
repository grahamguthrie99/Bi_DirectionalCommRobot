////////////////////////////////////////
void timeout(unsigned long del){
  unsigned long waitTime = 0;
  unsigned long take = millis();
  do{
    waitTime = millis() - take ; 
  }while(waitTime < del);
  //Serial.println("Delay");

}
////////////////////////////////////////
void microtimeout(unsigned long del){
  unsigned long waitTime = 0;
  unsigned long take = micros();
  do{
    waitTime = micros() - take ; 
  }while(waitTime < del);
  Serial.println("Delay");

}

////////////////////////////////
