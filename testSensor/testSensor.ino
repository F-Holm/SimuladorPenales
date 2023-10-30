int pinSensor = 23;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinSensor, INPUT);
}

void loop() {
  digitalRead(pinSensor);
}
