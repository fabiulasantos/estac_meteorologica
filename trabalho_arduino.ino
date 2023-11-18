#include <DHT.h>

//#include <ESP8266WiFi.h>
//#include <PubSubClient.h>


#define DHT_PIN 2   // Pino de dados do DHT22 conectado ao pino digital 2
#define LDR_PIN A0   // Pino analógico ao qual o LDR está conectado

//const char* ssid = "sua-rede-WiFi";
//const char* password = "sua-senha-WiFi";
//const char* mqtt_server = "endereco-do-seu-broker-MQTT";

//WiFiClient espClient;
//PubSubClient client(espClient);


DHT dht(DHT_PIN, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
  //setup_wifi();
  //client.setServer(mqtt_server, 1883);

}

void loop() {

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  int luminosidade = analogRead(LDR_PIN);

  //  if (!client.connected()) {
  //  reconnect();
  //}

  //  while (Serial.available() > 0) {
  //  String sensorData = Serial.readStringUntil('\n');
  //  client.publish("topico-mqtt", sensorData.c_str());
  //}

  //client.loop();


  //Serial.println("hello world!");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);
  Serial.println("#############################");

  // Envie os dados para o ESP8266 via comunicação serial
  //Serial.print("DHT22:");
  //Serial.print(temperatura);
  //Serial.print(",");
  //Serial.print(umidade);
  //Serial.print("|LDR:");
  //Serial.println(luminosidade);

  delay(5000);  // Aguarde 5 segundos antes de realizar a próxima leitura
}

