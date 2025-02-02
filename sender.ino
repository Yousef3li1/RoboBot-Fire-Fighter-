#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  
const byte address[6] = "00001";  
int xAxis, yAxis, pumpState;

void setup() {
  pinMode(A0, INPUT);  
  pinMode(A1, INPUT);  
  pinMode(2, INPUT);    
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
}

void loop() {
  xAxis = analogRead(A0) - 512;
  yAxis = analogRead(A1) - 512;
  pumpState = digitalRead(2);

  int data[3] = {xAxis, yAxis, pumpState};
  radio.write(&data, sizeof(data));
  delay(50);
}
