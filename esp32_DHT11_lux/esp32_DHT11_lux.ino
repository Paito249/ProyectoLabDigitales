#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>

BH1750 lightMeter;
DHT dht(4, DHT11);

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Inicializa la comunicación I2C con los pines SDA y SCL definidos

  lightMeter.begin();
  dht.begin();

  Serial.println(F("BH1750 and DHT11 Test"));
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

  delay(1000);
}