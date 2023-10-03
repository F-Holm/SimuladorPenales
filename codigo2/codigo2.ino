class Sensor {
public:
  Sensor(int pin) {
    this->pin = pin;
    this->valorMedido = 0;
  }

  void medir() {
    valorMedido = analogRead(pin);
  }

  int obtenerValorMedido() {
    return valorMedido;
  }

private:
  int pin;
  int valorMedido;
};

class GrupoSensores {
public:
  GrupoSensores() {
    // Inicializa los sensores con los pines correspondientes
    sensores[0] = Sensor(A0);
    sensores[1] = Sensor(A1);
    sensores[2] = Sensor(A2);
    sensores[3] = Sensor(A3);
    sensores[4] = Sensor(A4);
    sensores[5] = Sensor(A5);
    sensores[6] = Sensor(A6);
    sensores[7] = Sensor(A7);
    sensores[8] = Sensor(A8);
    umbralMinimoActivacion = 100; // Establece el umbral mínimo de activación
  }

  int detectarMayorVibracion() {
    int mayorVibracion = -1;
    int valorMaximo = -1;
    bool ultimo = false;

    while(true){
      
      for (int i = 0; i < 9; i++) {
        sensores[i].medir();
        int valorMedido = sensores[i].obtenerValorMedido();
      
        if (valorMedido > umbralMinimoActivacion && valorMedido > valorMaximo) {
          mayorVibracion = i;
          valorMaximo = valorMedido;
        }
      }
    
      if (valorMedido > 0 && !ultimo){
        ultimo = true;
      }
      else if (ultimo){
        break;
      }
    }
    return mayorVibracion;
  }

private:
  Sensor sensores[9];
  int umbralMinimoActivacion;
};

GrupoSensores grupoSensores;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorDetectado = grupoSensores.detectarMayorVibracion();

  if (sensorDetectado != -1) {
    Serial.print("Se detectó una vibración en el sensor ");
    Serial.print(sensorDetectado);
    Serial.print(" con un valor de ");
    Serial.println(grupoSensores.sensores[sensorDetectado].obtenerValorMedido());
    delay(1000); // Espera 1 segundo antes de volver a verificar
  }
}
