
 *****
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <PubSubClient.h>

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Salao_Comunal_2G" //"...your SSID..."
#define WLAN_PASS       "############" //"...your password..."

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "fabi1993"  //"...AIO username (see https://accounts.adafruit.com)..."
#define AIO_KEY         "aio_LosH694THKvEqN61hv0xh2xViRmJ" //"...AIO key..."

/************ Global State ******************/

// Criar classe ESP8266 WiFiClient p conectar com o MQTT.
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Inicialização dos feeds no Adafruit IO
Adafruit_MQTT_Publish temperaturaFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura");
Adafruit_MQTT_Publish umidadeFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/umidade");
Adafruit_MQTT_Publish luminosidadeFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/luminosidade");


/*************************** Sketch Code ************************************/

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  //mqtt.subscribe(&onoffbutton);
}

uint32_t x=0;

void loop() {
  float temperatura, umidade, luminosidade;

  
  MQTT_connect();

  
  Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! photocell.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

 
  while (Serial.available() > 0) {
    String sensorData = Serial.readStringUntil('\n');
    //client.publish("topico-mqtt", sensorData.c_str());
  }


  // Publica dados no Adafruit IO
  publishData(temperatura, umidade, luminosidade);

  delay(5000);  // Aguarde 5 segundos antes de realizar a próxima leitura
  
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

void publishData(float temperatura, float umidade, int luminosidade) {
  // Publica dados no Adafruit IO
  if (temperaturaFeed.publish(temperatura) && umidadeFeed.publish(umidade) && luminosidadeFeed.publish(luminosidade)) {
    Serial.println("Dados publicados no Adafruit IO");
  } else {
    Serial.println("Falha ao publicar dados no Adafruit IO.");
  }
}