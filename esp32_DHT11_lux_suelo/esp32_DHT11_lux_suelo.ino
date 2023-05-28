#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>

BH1750 lightMeter;
DHT dht(0, DHT11);
const int humsuelo = 4;    // Lectura del sensor de humedad del suelo
int valHumsuelo;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Inicializa la comunicación I2C con los pines SDA y SCL definidos

  lightMeter.begin();
  dht.begin();

  pinMode(humsuelo, INPUT);

  Serial.println(F("Sensor de Luz BH1750, Sensor de Humedad DHT11 y Sensor de Humedad del Suelo Test"));
}

void loop() {
  // Lectura de la luz
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  // Lectura de temperatura y humedad
  float temp = dht.readTemperature();
  float hume = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C, Humedad: ");
  Serial.print(hume);
  Serial.println(" %");

  // Lectura de humedad del suelo
  int humedadRaw = analogRead(humsuelo);
  int humedadMin = 4095; // Actualiza este valor con la lectura mínima cuando el sensor esté completamente seco
  int humedadMax = 1250;    // Actualiza este valor con la lectura máxima cuando el sensor esté completamente húmedo
  int humedadMapeada = map(humedadRaw, humedadMin, humedadMax, 0, 100);

  if (humedadMapeada > 100) {
    humedadMapeada = 100; // Establecer el valor en 100 si es mayor al límite máximo
  }

  Serial.print("Humedad del suelo: ");
  Serial.print(humedadMapeada);
  Serial.println(" %");

  delay(5000);
}