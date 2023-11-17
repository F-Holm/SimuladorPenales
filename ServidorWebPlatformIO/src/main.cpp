#include <Arduino.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "IPM-Wifi";
const char* password = "ipm5880!";

const char* html = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simulador penales</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }

        .soccer-goal {
            margin-top: 5vw;
            position: relative;
            width: 70vw;
            height: 35vw;
            background-color: white;
        }

        .goal-post {
            width: 1.6vw;
            background-color: black;
            position: absolute;
        }

        .top-post {
            top: 0;
            left: 0;
            height: 1.6vw;
            width: 70vw;
        }

        .left-post {
            top: 1.6vw;
            left: 0;
            height: 33.4vw;
        }

        .right-post {
            top: 1.6vw;
            right: 0;
            height: 33.4vw;
        }

        .goal-grid {
            position: absolute;
            top: 1.6vw;
            left: 1.6vw;
            width: 66.8vw;
            height: 33.4vw;
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            grid-template-rows: repeat(3, 1fr);
        }

        .goal-cell {
            border: 0.1vw solid black;
            display: flex;
            align-items: center;
            justify-content: center;
        }

        #c1{
            background-color: white;
        }
        #c2{
            background-color: white;
        }
        #c3{
            background-color: white;
        }
        #c4{
            background-color: white;
        }
        #c5{
            background-color: white;
        }
        #c6{
            background-color: white;
        }
        #c7{
            background-color: white;
        }
        #c8{
            background-color: white;
        }
        #c9{
            background-color: white;
        }
        .circulo{
            position: absolute;
            width: 10vh;
            height: 10vh;
            border-radius: 50%;
            top: 5vh;
            border: 0.1vw solid black;
        }
        #circulo1{
            background-color: green;
            margin-right: 45vw;
        }
        #circulo2{
            background-color: red;
        }
        #circulo3{
            background-color: white;
            margin-left: 45vw;
        }
        .tick::before {
            content: '\2713';
            font-size: 12vh;
            color: white;
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
        }
        .x::before{
            content: '\2717';
            font-size: 10vh;
            color: white;
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
        }
    </style>
</head>
<body>
    <div class="circulo tick" id="circulo1"></div>
    <div class="circulo x" id="circulo2"></div>
    <div class="circulo" id="circulo3"></div>
    <div class="soccer-goal">
        <div class="goal-post top-post"></div>
        <div class="goal-post left-post"></div>
        <div class="goal-post right-post"></div>
        <div class="goal-grid">
            <div class="goal-cell" id="c1"></div>
            <div class="goal-cell" id="c2"></div>
            <div class="goal-cell" id="c3"></div>
            <div class="goal-cell" id="c4"></div>
            <div class="goal-cell" id="c5"></div>
            <div class="goal-cell" id="c6"></div>
            <div class="goal-cell" id="c7"></div>
            <div class="goal-cell" id="c8"></div>
            <div class="goal-cell" id="c9"></div>
        </div>
    </div>
</body>
</html>
)rawliteral";

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
    request->send(200, "text/html", html);
  });
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Inicia el servidor
  server.begin();
}

void loop() {
  // Nada por hacer aquí
}
