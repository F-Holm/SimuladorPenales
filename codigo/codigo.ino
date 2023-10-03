class GrupoSensores{
  private:
  Sensor[9] sensores;
  public:
  static bool activo = true;
  const static int valorUmbral = 10;
  static bool activo = false;
  static int[9] valoresMaximos;
  void start(){
    
  }
  void iniciarSensores(){
    for(int i = 0;i < 9;i++){
      
    }
  }
}

class Sensor{
  private:
  char[3] sensor;
  int valorActual;
  public:
  int valorMaxActual;
  void start(){
    while(GrupoSensores.activo){
      
    }
  }
  void nuevoValor(int valor){
    valorActual = valor;
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
