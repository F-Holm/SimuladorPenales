#include <Arduino.h>
#define sensor 23
#define led 22

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, digitalRead(sensor));
}