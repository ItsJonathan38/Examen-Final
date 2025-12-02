#include <ESP8266WiFi.h> 
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ====== WIFI ======
#define WIFI_SSID       "Jonathan"
#define WIFI_PASS       "jcml120206"

// ====== ADAFRUIT IO ======
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

#define AIO_USERNAME    "ItsJonathan"
#define AIO_KEY         "AIO_KEY_AQUI"

// ====== CLIENTE ======
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// ====== SUBSCRIBE ======
Adafruit_MQTT_Subscribe feedComandos =
  Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/eezybotarm");

void MQTT_connect() {
  while (!mqtt.connected()) {
    mqtt.connect();
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);  // Serial hacia ARDUINO MEGA
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  mqtt.subscribe(&feedComandos);
}

void loop() {
  MQTT_connect();

  Adafruit_MQTT_Subscribe *s;
  
  while ((s = mqtt.readSubscription(100))) {
    if (s == &feedComandos) {
      String cmd = (char *) feedComandos.lastread;
      cmd.trim();
      Serial.println(cmd);  // ENVÍA AL MEGA
    }
  }
}
