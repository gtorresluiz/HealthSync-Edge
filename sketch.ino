#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// MQTT Configurações
EspMQTTClient client{
  "Wokwi-GUEST", // SSID do WiFi
  "",             // Senha do WiFi
  "mqtt.tago.io", // Endereço do servidor MQTT
  "Default",      // Usuario MQTT
  "b9f8992d-e935-4e16-b82f-f535eefea6ef",   // Token do device
  "esp",          // Nome do device
  1883            // Porta de comunicação MQTT
};

char bufferJson[100];

void sendEmail(const char* topic) {
  client.publish(topic, "EnviarEmail"); // Envie um comando MQTT para acionar o envio de e-mail
}

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

// Callback da EspMQTTClient
void onConnectionEstablished() {}

void loop() {
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  // Create JSON document for temperatura
  StaticJsonDocument<300> documentoJsonTemperatura;
  documentoJsonTemperatura["variable"] = "temperatura";
  documentoJsonTemperatura["value"] = temperatura;
  documentoJsonTemperatura["unit"] = "°C";

  serializeJson(documentoJsonTemperatura, bufferJson);
  Serial.println(bufferJson);

  // Publish temperatura data to MQTT
  client.publish("SeuTopicoTemperatura", bufferJson);

  // Verificar se a temperatura está acima de 25 ou abaixo de 8
  if (temperatura > 25 || temperatura < 8) {
    // Se sim, enviar um email para temperatura
    Serial.println("Payload MQTT para Envio de Email (Temperatura):");
    Serial.println(bufferJson);
    client.publish("SeuTopicoEmailTemperatura", bufferJson);
  }

  // Create JSON document for umidade
  StaticJsonDocument<300> documentoJsonUmidade;
  documentoJsonUmidade["variable"] = "umidade";
  documentoJsonUmidade["value"] = umidade;
  documentoJsonUmidade["unit"] = "%";

  serializeJson(documentoJsonUmidade, bufferJson);
  Serial.println(bufferJson);

  // Publish umidade data to MQTT
  client.publish("SeuTopicoUmidade", bufferJson);

  // Verificar se a umidade está abaixo de 30 ou acima de 55
  if (umidade < 30 || umidade > 55) {
    // Se sim, enviar um email para umidade
    Serial.println("Payload MQTT para Envio de Email (Umidade):");
    Serial.println(bufferJson);
    client.publish("SeuTopicoEmailUmidade", bufferJson);
  }

  delay(5000);
  client.loop();
}
