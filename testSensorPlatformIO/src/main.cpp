#include <Arduino.h>

#define sensor 23

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop() {
  digitalRead(sensor);
}