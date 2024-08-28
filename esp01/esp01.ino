#include <ESP8266WiFi.h>
#include <DHT.h>
#include "config.h"     // Archivo de configuración de conexión Wi-Fi. Ejemplo en config.example.h

#define DHTPIN 2        // Pin GPIO2 para el DHT22
#define DHTTYPE DHT22   // Tipo de sensor DHT22
#define LED_PIN 0       // Pin GPIO0 para el LED azul

DHT dht(DHTPIN, DHT22);

void setup() {
  Serial.begin(115200);       // Velocidad en baudios ajustada para la depuración
  
  dht.begin();
  Serial.println("Sensor DHT iniciado");

  pinMode(LED_PIN, OUTPUT);   // Configura el pin GPIO0 (LED_PIN) como salida para controlar el LED
  digitalWrite(LED_PIN, LOW); // Apaga el LED al iniciar (HIGH para asegurar arranque correcto)

  Serial.println();
  Serial.println("Conectando a red Wi-Fi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conexión Wi-Fi establecida");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer el sensor DHT!");
    return;
  }

  digitalWrite(LED_PIN, LOW);   // Enciende el LED antes de enviar los datos (LOW enciende el LED)

   // Imprime la humedad
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %; ");

  // Imprime la temperatura
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" ºC");

  delay(2000);                  // Simula el tiempo de envío de datos
  digitalWrite(LED_PIN, HIGH);  // Apaga el LED después de enviar los datos
  
  delay(2000);                  // Espera 2 segundos antes de la siguiente lectura
}
