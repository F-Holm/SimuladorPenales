class Sensor {
public:
Sensor() {
    this->pin = null;
    this->led1 = null;
    this->led2 = null;
    pinMode(pin, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
  }
  Sensor(int pin, int led1, int led2) {
    this->pin = pin;
    this->led1 = led1;
    this->led2 = led2;
    pinMode(pin, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
  }
  void apagarLed1(){
    digitalWrite(led1, LOW);
  }
  void apagarLed2(){
    digitalWrite(led2, LOW);
  }
  void encenderLed1(){
    digitalWrite(led1, HIGH);
  }
  void encenderLed2(){
    digitalWrite(led2, HIGH);
  }
  void apagarLeds(){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
  void encenderLeds(){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  int getPin(){
    return pin;
  }
  int getLed1(){
    return led1;
  }
  int getLed2(){
    return led2;
  }
private:
  int pin;
  int led1;
  int led2;
};

class GrupoSensores {
public:
  GrupoSensores() {
    sensores[0] = Sensor{2, 11, 20};
    sensores[1] = Sensor{3, 12, 21};
    sensores[2] = Sensor{4, 13, 22};
    sensores[3] = Sensor{5, 14, 23};
    sensores[4] = Sensor{6, 15, 24};
    sensores[5] = Sensor{7, 16, 25};
    sensores[6] = Sensor{8, 17, 26};
    sensores[7] = Sensor{9, 18, 27};
    sensores[8] = Sensor{10, 19, 28};
    setSensorObjetivo();
  }
  Sensor getSensor(int i){
    return sensores[i];
  }
  int medir(){
    int pin = -1;
    for(int i = 0;i < 9;i++){
      if (digitalRead(sensores[i].getPin() == HIGH)){
        if (pin == -1) {
          pin = i;
        }
        else {
          return -1;
        }
      }
    }
    return pin;
  }
  void setSensorObjetivo(){
    sensorObjetivo random(8);
    sensores[sensorObjetivo].encenderLeds();
  }
  int getSensorObjetivo(){
    return sensorObjetivo;
  }
private:
  Sensor sensores[9];
  int sensorObjetivo;
};

GrupoSensores grupoSensores;

int intentosRestantes = 3;

void setup() {
  grupoSensores = GrupoSensores{};
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {//Si no le pegan al arco o le pegan a 2 paneles al mismo tiempo tienen otro tiro
  int sensor = grupoSensores.medir();
  if (sensor != -1){
    if (sensor == grupoSensores.getSensorObjetivo()){
      grupoSensores.getSensor(sensor).apagarLed2();
    } else {
      grupoSensores.getSensor(sensor).apagarLed1();
    }
    //Le envío la información al ESP32 para que la muestre en la página web
    delay(5000);
    if (intentosRestantes == 1){
      intentosRestantes = 3;
      //Le digo al ESP32 que reinicie la página porque ya terminó esta perosna
      delay(5000);
    } else {
      intentosRestantes--;
    }
    grupoSensores.getSensor(sensor).apagarLeds();
    grupoSensores.setSensorObjetivo();
  }
}
