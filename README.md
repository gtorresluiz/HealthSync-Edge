# HealthSync

## Descrição do Projeto

Este projeto consiste em um sistema de monitoramento de estoque de vacinas utilizando um ESP32 equipado com um sensor DHT22 para medir temperatura e umidade. O sistema se conecta à rede WiFi e utiliza o protocolo MQTT para enviar dados para o servidor TagoIO. Caso as condições de temperatura e umidade estejam fora dos limites desejados, o sistema envia um email para a equipe responsável pelo cuidado das vacinas. Além disso, o projeto inclui um dashboard no TagoIO que exibe gráficos em tempo real e informações visuais sobre as condições do ambiente.

## Componentes Utilizados

- ESP32
- Sensor DHT22 (ou DHT 22, AM2302, AM2321)
- Servidor MQTT: `mqtt.tago.io`
- Plataforma de IoT: TagoIO

## Configurações

- **WiFi:**
  - SSID: *Sua conexão WiFi*
  - Senha: *Sua senha WiFi*

- **MQTT:**
  - Servidor: `mqtt.tago.io`
  - Usuário MQTT: `Default`
  - Token do Dispositivo: `b9f8992d-e935-4e16-b82f-f535eefea6ef`
  - Nome do Dispositivo: `HealthSync`
  - Porta MQTT: `1883`

## Bibliotecas Utilizadas

- [ArduinoJson](https://arduinojson.org/)
- [EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
- [DHT](https://github.com/adafruit/DHT-sensor-library) (ou a biblioteca correspondente ao seu sensor DHT)

## Instalação

1. Clone o repositório ou copie o código para o seu ambiente de desenvolvimento Arduino.
2. Instale as bibliotecas necessárias (ArduinoJson e EspMQTTClient).
3. Configure as informações de WiFi e MQTT conforme as configurações acima.
4. Carregue o código no seu ESP32.

## Uso

1. O ESP32 se conectará ao WiFi e ao servidor MQTT.
2. O sensor DHT22 medirá a temperatura e umidade.
3. Os dados serão publicados no servidor MQTT e enviados para o TagoIO.
4. O TagoIO exibirá gráficos em tempo real e informações visuais no dashboard.

## Estrutura do Código

- O código utiliza a biblioteca `EspMQTTClient` para gerenciar a conexão MQTT.
- A leitura do sensor DHT22 é realizada para obter temperatura e umidade.
- Os dados são formatados em JSON e publicados no servidor MQTT.
- Se as condições de temperatura ou umidade estiverem fora dos limites, um email é enviado.

## Dashboard TagoIO

- Um dashboard foi criado no TagoIO para visualização dos dados.
- O dashboard inclui gráficos de linhas, displays de valores atuais e imagens representando as condições do ambiente.
- Os tópicos MQTT correspondentes são utilizados para exibir as informações no dashboard.

## Contribuições

Contribuições são bem-vindas! Se encontrar problemas ou melhorias, sinta-se à vontade para criar issues ou pull requests.
