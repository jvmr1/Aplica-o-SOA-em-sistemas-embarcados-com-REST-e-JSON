#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const int SensorTempPin =  A0;
const int SensorMovPin =  16;
int count = 0;
int estado = 0;
//String ip = "192.168.0.4";
String ip = "jhs.hopto.org";

void setup() {
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFiMulti.addAP("JH", "12345678");

  pinMode(SensorTempPin, INPUT);
  pinMode(SensorMovPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    //Sensor de movimento
    bool movimento;
    movimento=digitalRead(SensorMovPin);
    
    if (movimento == HIGH && estado == 0) {
      estado = 1;
      Serial.println("{\"sensornumero\":\"1\"}");
      HTTPClient http;
      http.begin("http://"+ip+":8080/ServerREST/resources/postPresenca");
      http.addHeader("Content-Type", "text/json");
      
      movimento = digitalRead(SensorMovPin);
      String postMessage = "{\"sensornumero\":\"1\"}";
      int httpCode = http.POST(postMessage);
      
      Serial.print("HTTP result Sensor: ");
      Serial.println(httpCode);
      http.writeToStream(&Serial);
      http.end();      
    }

    if (movimento == LOW) {
      estado = 0;      
    }

    //Sensor de temperatura
    if (count > 1000) {
      count = 0;
      HTTPClient http;
      http.begin("http://"+ip+":8080/ServerREST/resources/postTemperatura");      
      http.addHeader("Content-Type", "text/json");

      String postTemperatura;
      int leitura;
      float temperatura;
      leitura = analogRead(SensorTempPin);
      temperatura = ( 3.3 * leitura * 100.0) / 1023.0;
      
      postTemperatura="{\"temperatura\":\"" + String(temperatura) +"\",\"sensornumero\":\"1\"}";
      int httpCode = http.POST(postTemperatura);
      Serial.println(postTemperatura);
      
      Serial.print("HTTP result Temperatura: ");
      Serial.println(httpCode);
      http.writeToStream(&Serial);
      http.end();      
    }
  }
  count++;
  delay(1); 
}
