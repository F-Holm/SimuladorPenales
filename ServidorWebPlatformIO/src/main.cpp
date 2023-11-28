#include <Arduino.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "IPM-Wifi";
const char* password = "ipm5880!";

String color[9] = { "white", "white", "white", "white", "white", "white", "white", "white", "white" };//white = 0 = 00 - red = 1 = 01 - blue = 2 = 10 - green = 3 = 11
int estadoIntento[3] = { 0, 0, 0 };// 0 = falló - 1 = GOL - 2 = todavía no pateó

String estado (int estado){
    switch (estado)
    {
    case 0:
    return "circulo rojo x";
        break;
    case 1:
    return "circulo verde tick";
        break;
    case 2:
    return "circulo blanco";
        break;
    }
    return "";
}

const String html () {
    String pagina = "<!DOCTYPE html>";
    pagina += "<html lang=\"es\">";
    pagina += "<head>";
    pagina += "<meta charset=\"UTF-8\">";
    pagina += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    pagina += "<title>Simulador penales</title>";
    pagina += "<style>";
    pagina += "body {";
    pagina += "    display: flex;";
    pagina += "    justify-content: center;";
    pagina += "    align-items: center;";
    pagina += "    height: 100vh;";
    pagina += "    margin: 0;";
    pagina += "}";
    pagina += ".soccer-goal {";
    pagina += "    margin-top: 5vw;";
    pagina += "    position: relative;";
    pagina += "    width: 70vw;";
    pagina += "    height: 35vw;";
    pagina += "    background-color: white;";
    pagina += "}";
    pagina += ".goal-post {";
    pagina += "    width: 1.6vw;";
    pagina += "    background-color: black;";
    pagina += "    position: absolute;";
    pagina += "}";
    pagina += ".top-post {";
    pagina += "    top: 0;";
    pagina += "    left: 0;";
    pagina += "    height: 1.6vw;";
    pagina += "    width: 70vw;";
    pagina += "}";
    pagina += ".left-post {";
    pagina += "    top: 1.6vw;";
    pagina += "    left: 0;";
    pagina += "    height: 33.4vw;";
    pagina += "}";
    pagina += ".right-post {";
    pagina += "    top: 1.6vw;";
    pagina += "    right: 0;";
    pagina += "    height: 33.4vw;";
    pagina += "}";
    pagina += ".goal-grid {";
    pagina += "    position: absolute;";
    pagina += "    top: 1.6vw;";
    pagina += "    left: 1.6vw;";
    pagina += "    width: 66.8vw;";
    pagina += "    height: 33.4vw;";
    pagina += "    display: grid;";
    pagina += "    grid-template-columns: repeat(3, 1fr);";
    pagina += "    grid-template-rows: repeat(3, 1fr);";
    pagina += "}";
    pagina += ".goal-cell {";
    pagina += "    border: 0.1vw solid black;";
    pagina += "    display: flex;";
    pagina += "    align-items: center;";
    pagina += "    justify-content: center;";
    pagina += "}";
    pagina += "#c1{";
    pagina += "    background-color: " + color[0] + ";";
    pagina += "}";
    pagina += "#c2{";
    pagina += "    background-color: " + color[1] + ";";
    pagina += "}";
    pagina += "#c3{";
    pagina += "    background-color: " + color[2] + ";";
    pagina += "}";
    pagina += "#c4{";
    pagina += "    background-color: " + color[3] + ";";
    pagina += "}";
    pagina += "#c5{";
    pagina += "    background-color: " + color[4] + ";";
    pagina += "}";
    pagina += "#c6{";
    pagina += "    background-color: " + color[5] + ";";
    pagina += "}";
    pagina += "#c7{";
    pagina += "    background-color: " + color[6] + ";";
    pagina += "}";
    pagina += "#c8{";
    pagina += "    background-color: " + color[7] + ";";
    pagina += "}";
    pagina += "#c9{";
    pagina += "    background-color: " + color[8] + ";";
    pagina += "}";
    pagina += ".circulo{";
    pagina += "    position: absolute;";
    pagina += "    width: 10vh;";
    pagina += "    height: 10vh;";
    pagina += "    border-radius: 50%;";
    pagina += "    top: 5vh;";
    pagina += "    border: 0.1vw solid black;";
    pagina += "}";
    pagina += ".verde{";
    pagina += "        background-color: green;";
    pagina += "    }";
    pagina += "    .rojo{";
    pagina += "        background-color: red;";
    pagina += "    }";
    pagina += "    .blanco{";
    pagina += "        background-color: white;";
    pagina += "    }";
    pagina += "#circulo1{";
    pagina += "    margin-right: 45vw;";
    pagina += "}";
    pagina += "#circulo2{";
    pagina += "}";
    pagina += "#circulo3{";
    pagina += "    margin-left: 45vw;";
    pagina += "}";
    pagina += ".tick::before {";
    pagina += "    content: '\\2713';";
    pagina += "    font-size: 12vh;";
    pagina += "    color: white;";
    pagina += "    position: absolute;";
    pagina += "    top: 50%;";
    pagina += "    left: 50%;";
    pagina += "    transform: translate(-50%, -50%);";
    pagina += "}";
    pagina += ".x::before{";
    pagina += "    content: '\\2717';";
    pagina += "    font-size: 10vh;";
    pagina += "    color: white;";
    pagina += "    position: absolute;";
    pagina += "    top: 50%;";
    pagina += "    left: 50%;";
    pagina += "    transform: translate(-50%, -50%);";
    pagina += "}";
    pagina += "</style>";
    pagina += "</head>";
    pagina += "<body>";
    pagina += "<div class='" + estado(estadoIntento[0]) + "' id='circulo1'></div>";
    pagina += "<div class='" + estado(estadoIntento[1]) + "' id='circulo2'></div>";
    pagina += "<div class='" + estado(estadoIntento[2]) + "' id='circulo3'></div>";
    pagina += "<div class=\"soccer-goal\">";
    pagina += "<div class=\"goal-post top-post\"></div>";
    pagina += "<div class=\"goal-post left-post\"></div>";
    pagina += "<div class=\"goal-post right-post\"></div>";
    pagina += "<div class=\"goal-grid\">";
    pagina += "<div class=\"goal-cell\" id=\"c1\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c2\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c3\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c4\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c5\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c6\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c7\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c8\"></div>";
    pagina += "<div class=\"goal-cell\" id=\"c9\"></div>";
    pagina += "</div>";
    pagina += "</div>";
    pagina += "</body>";
    pagina += "</html>";
    pagina += "<script>";
    pagina += "    function recargarPagina() {";
    pagina += "        location.reload();";
    pagina += "    }";
    pagina += "    setInterval(recargarPagina, 1000);";
    //for (int i = 0;i < 9;i++) pagina += "document.getElementById(\"c" + String(i+1) + "\").style.backgroundColor = " + color[i] + ";";
    //for (int i = 0;i < 3;i++) pagina += "document.getElementById(\"circulo" + String(i+1) + "\").className = " + estado(estadoIntento[i]) + ";";
    pagina += "</script>";

    return pagina;
}

int intAsciiToInt (int num){
  return num - 48;
}
 
void recibirYUpdate(){
  int num = 0;
  while (true){
    while(Serial.available() <= 0);
    num = intAsciiToInt(Serial.read());
    if (num == 4) break;
  }
  Serial.print(num);
  for (int i = 0;i < 9;i++){
    while (Serial.available() <= 0);
    num = intAsciiToInt(Serial.read());
    Serial.print(num);
    switch(num){
      case 0:
      	color[i] = "white";
      	break;
      case 1:
      	color[i] = "green";
      	break;
      case 2:
      	color[i] = "blue";
        //Serial.println(String(i) + "estoy en blue");
      	break;
      case 3:
      	color[i] = "red";
      	break;
    }
  }
  for (int i = 0;i < 3;i++){
    while (Serial.available() <= 0);
    num = intAsciiToInt(Serial.read());
    Serial.print(num);
    estadoIntento[i] = num;
  }

}

void changeColors(){
  switch (color[0][0])
  {
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

AsyncWebServer server(8080);

void setup() {
  Serial.begin(9600);
  // Conéctate a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }
  Serial.println("Conexión exitosa");

  // Manejo de la ruta principal "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", html());
    });
  Serial.print("Direccion IP: ");
  Serial.print(WiFi.localIP());
  Serial.println(":8080");

  // Inicia el servidor
  server.begin();

  delay(5000);
  Serial.print(4);
}
void loop() {
  delay(1000);
  /*for (int i = 0;i < 9;i++){
    if (color[i][0] != 'w') Serial.println(String(i+1) + " " + color[i]);
  }*/
  recibirYUpdate();
  //changeColors();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", html());
  });
}
