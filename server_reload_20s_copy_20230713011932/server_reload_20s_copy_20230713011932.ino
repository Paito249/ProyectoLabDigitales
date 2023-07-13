#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "SAMSUNG";      // Reemplaza con el nombre de tu red Wi-Fi
const char* password = "99009988";  // Reemplaza con la contraseña de tu red Wi-Fi

BH1750 lightMeter;
DHT dht(15, DHT11);
const int humsuelo = 34;    // Lectura del sensor de humedad del suelo
int valHumsuelo;

WebServer server(80);
Servo myservo;

bool servoOn = false;
int angle = 0;

void handleRoot() {
  // Lectura de la luz
  float lux = lightMeter.readLightLevel();

  // Lectura de temperatura y humedad
  float temp = dht.readTemperature();
  float hume = dht.readHumidity();

  // Lectura de humedad del suelo
  int humedadRaw = analogRead(humsuelo);
  int humedadMin = 4095; // Actualiza este valor con la lectura mínima cuando el sensor esté completamente seco
  int humedadMax = 1250;    // Actualiza este valor con la lectura máxima cuando el sensor esté completamente húmedo
  int humedadMapeada = map(humedadRaw, humedadMin, humedadMax, 0, 100);

  if (humedadMapeada > 100) {
    humedadMapeada = 100; // Establecer el valor en 100 si es mayor al límite máximo
  }

  String html = "<html><body>";
  html += "<h1>Valores de los sensores:</h1>";
  html += "<p>Luz: " + String(lux) + " lx</p>";
  html += "<p>Temperatura: " + String(temp) + " °C</p>";
  html += "<p>Humedad: " + String(hume) + " %</p>";
  html += "<p>Humedad del suelo: " + String(humedadMapeada) + " %</p>";
  html += "<p>Servo state: ";
  html += servoOn ? "ON" : "OFF";
  html += "</p>";
  html += "<button onclick=\"toggleServo()\">Toggle Servo</button>";
  html += "<script>function toggleServo() {var xhr = new XMLHttpRequest(); xhr.open('GET', '/toggle', true); xhr.send();}</script>";
  html += "<script>setTimeout(function() { location.reload(); }, 20000);</script>"; // Recarga la página después de 10 segundos
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleToggle() {
  servoOn = !servoOn;
  if (servoOn) {
    angle = 180;
    myservo.write(angle);
    server.send(200, "text/plain", "Servo turned on");
  } else {
    angle = 0;
    myservo.write(angle);
    server.send(200, "text/plain", "Servo turned off");
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Inicializa la comunicación I2C con los pines SDA y SCL definidos

  lightMeter.begin();
  dht.begin();

  pinMode(humsuelo, INPUT);

  // Conectar a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a la red WiFi");

  // Inicializar el servo
  myservo.attach(13); // Reemplaza el número de pin con el pin que conectaste al servo

  // Configurar ruta para el servidor web
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  // Iniciar servidor web
  server.begin();
}

void loop() {
  server.handleClient();
}