// HW-080
const int humsuelo = 4;    // Lectura del sensor de humedad del suelo
int valHumsuelo;

void setup() {
  Serial.begin(115200);
  pinMode(humsuelo, INPUT);
}

void loop() {
  // Leer el valor analógico del sensor de humedad del suelo
  int humedadRaw = analogRead(humsuelo);

  // Calibrar los valores de lectura para el sensor (completamente seco y completamente húmedo)
  int humedadMin = 4095; // Actualiza este valor con la lectura mínima cuando el sensor esté completamente seco
  int humedadMax = 1250;    // Actualiza este valor con la lectura máxima cuando el sensor esté completamente húmedo

  // Mapear el valor de lectura a un rango de 0 a 100 (utilizando los valores calibrados)
  int humedadMapeada = map(humedadRaw, humedadMin, humedadMax, 0, 100);

  if (humedadMapeada > 100) {
    humedadMapeada = 100; // Establecer el valor en 100 si es mayor al límite máximo
  }

  Serial.print("Humedad del suelo: ");
  Serial.print(humedadMapeada);
  Serial.println(" %");
  
  delay(5000);
}