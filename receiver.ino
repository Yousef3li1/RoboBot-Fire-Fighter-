#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  
const byte address[6] = "00001";  

int motorA1 = 3, motorA2 = 4;
int motorB1 = 5, motorB2 = 6;
int pumpMotor = 7;

int xAxis, yAxis, pumpState;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(pumpMotor, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int data[3];
    radio.read(&data, sizeof(data));
    xAxis = data[0];
    yAxis = data[1];
    pumpState = data[2];

    if (pumpState == 1) {
      digitalWrite(pumpMotor, HIGH);
    } else {
      digitalWrite(pumpMotor, LOW);
    }

    if (yAxis > 100) {
      moveForward();
    } else if (yAxis < -100) {
      moveBackward();
    } else if (xAxis > 100) {
      turnRight();
    } else if (xAxis < -100) {
      turnLeft();
    } else {
      stopMotors();
    }
  }
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void moveBackward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
