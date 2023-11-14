#include <Arduino.h>

void setup() {
  // Inicializar el puerto serie
  //Serial.begin(9600);

  // Esperar un momento
  delay(1000);
}

void loop() {
  // Enviar un mensaje a través del puerto serie
  Serial.println("¡Hola, mundo!");

  // Esperar un segundo
  delay(1000);
}
