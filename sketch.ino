#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include <DHT.h>

#define DHT_PIN 2
DHT dht(DHT_PIN, DHT22);

EspMQTTClient client{
  "Wokwi-GUEST",  // SSID do WiFi público da Wokwi
  "",             // Senha do WiFi público da Wokwi
  "mqtt.tago.io", // Endereço do servidor
  "Default",      // Usuário
  "b9f8992d-e935-4e16-b82f-f535eefea6ef",   // Token do device
  "HealthSync",          // Nome do device
  1883            // Porta de comunicação
};

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Conectando WiFi");
  while (!client.isWifiConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("WiFi Conectado");
  Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("MQTT Conectado");
}

void loop() {
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  StaticJsonDocument<300> documentoJsonTemperatura;
  documentoJsonTemperatura["variable"] = "temperatura";
  documentoJsonTemperatura["value"] = temperatura;
  documentoJsonTemperatura["unit"] = "celsius";

  char bufferJsonTemperatura[100];
  serializeJson(documentoJsonTemperatura, bufferJsonTemperatura);
  Serial.println(bufferJsonTemperatura);
  client.publish("SeuTopicoTemperatura", bufferJsonTemperatura);

  StaticJsonDocument<300> documentoJsonUmidade;
  documentoJsonUmidade["variable"] = "umidade";
  documentoJsonUmidade["value"] = umidade;
  documentoJsonUmidade["unit"] = "%";

  char bufferJsonUmidade[100];
  serializeJson(documentoJsonUmidade, bufferJsonUmidade);
  Serial.println(bufferJsonUmidade);
  client.publish("SeuTopicoUmidade", bufferJsonUmidade);

  delay(5000);
  client.loop();
}
