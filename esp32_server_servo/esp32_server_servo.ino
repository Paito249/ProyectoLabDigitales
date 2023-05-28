#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "SAMSUNG";
const char* password = "99009988";

int servo_pin_D3 = 2; // Pin para el servo

Servo myservo;
int angle = 0;
bool servoOn = false;

WebServer server(80); // Crea una instancia del servidor web en el puerto 80

void handleRoot() {
  String html = "<h1>Servo Control</h1>";
  html += "<p>Servo state: ";
  html += servoOn ? "ON" : "OFF";
  html += "</p>";
  html += "<button onclick=\"toggleServo()\">Toggle Servo</button>";
  html += "<script>function toggleServo() {var xhr = new XMLHttpRequest(); xhr.open('GET', '/toggle', true); xhr.send();}</script>";
  html += "<p>Connect to: " + WiFi.localIP().toString() + "</p>"; // Agrega la dirección IP al HTML
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

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");

  myservo.attach(servo_pin_D3);

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  server.begin();
  Serial.println("Server started");
  Serial.print("Connect to: ");
  Serial.println(WiFi.localIP()); // Muestra la dirección IP por Serial
}

void loop() {
  server.handleClient();
}