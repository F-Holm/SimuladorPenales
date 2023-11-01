#define sensor 23
#define led 2

void setup() {
Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  if (digitalRead(sensor) == HIGH) digitalWrite(led, HIGH);
  else digitalWrite(led, HIGH);
}
