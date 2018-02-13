#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>


#define button 2


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
boolean buttonState = 0;
boolean lastButtonState = 0;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

void setup() {
  //Button
  pinMode(button, INPUT);
  pinMode(4, OUTPUT);
  
  Serial.begin(9600);
  //COMM
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  buttonState = digitalRead(button);
  if (buttonState != lastButtonState) {
      lastDebounceTime = millis();
  }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonState != lastButtonState) {
        buttonState = lastButtonState;
      }
    }
  digitalWrite(4, buttonState);
  Serial.print(buttonState);
  
  radio.write(&buttonState, sizeof(buttonState));
  lastButtonState = buttonState;

}
