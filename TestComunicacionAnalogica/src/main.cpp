#include<Arduino.h>

void setup() {
  Serial.begin(9600);
  while (true){
    while(Serial.available() <= 0);
    if (Serial.read() == 52) break;
  }
}
 
String color[9] = { "white", "white", "white", "white", "white", "white", "white", "white", "white" };//white = 0 - green = 1 - blue = 2 - red= 3
int estadoIntento[3] = { 0, 0, 0 };// 1 = gol - 0 = fallo - 2 = no pateo
 
void siguinteColor(){
  switch(color[0][0]){
    case 'w':
    color[0] = "green";
    break;

    case 'g':
    color[0] = "blue";
    break;

    case 'b':
    color[0] = "red";
    break;

    case 'r':
    color[0] = "white";
    break;
  }
}

void waitACK(){
  while(Serial.available() <= 0);
  Serial.read();
}

void enviarDatos (){

  Serial.print(4);
  waitACK();
  for (int i = 0;i < 9;i++){
    switch (color[i][0]){
      case 'w':
      	Serial.print(0);
      	break;
      case 'g':
      	Serial.print(1);
      	break;
      case 'b':
      	Serial.print(2);
      	break;
      case 'r':
      	Serial.print(3);
      	break;
    }
    waitACK();
  }
  for (int i = 0;i < 3;i++){
    Serial.print(estadoIntento[i]);
    waitACK;
  }
}
 
void loop() {
  siguinteColor();
  enviarDatos();
  delay(10000);
}