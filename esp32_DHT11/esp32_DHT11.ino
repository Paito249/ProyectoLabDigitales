#include <DHT.h>
 

#define DHTTYPE DHT11
#define DHTPIN 4

DHT dht(DHTPIN, DHT11);

float temp, hume;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));
  dht.begin();
  if (isnan(hume)||isnan(temp)){
    Serial.println(F("Falla en la lectura del sensor"));
    return;
  }
}

void loop() {
  delay(5000);
  hume = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.println("Temperatura: " + String(temp) + ", Humedad: " + String(hume)); 
}