#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const int SensorTempPin =  A0;
const int SensorMovPin =  16;
const int LedTempPin =  15;  
const int LedMovPin =  13;  

void setup() {

    USE_SERIAL.begin(115200);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP("JH", "12345678");

    pinMode(SensorTempPin, INPUT);
    pinMode(SensorMovPin, INPUT);
    pinMode(LedTempPin, OUTPUT);
    pinMode(LedMovPin, OUTPUT);
    

}

void loop() {
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin("http://192.168.137.1:8080/RESTServer/resources/GetTemperatrua"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        int httpCode = http.GET();
                
        if(httpCode > 0) {           
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                
                if (payload=="L"){
                    digitalWrite(LedMovPin, HIGH);
                }
                else{
                    digitalWrite(LedMovPin, LOW);
                }
                
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        
        http.end();
    }
    
    HTTPClient http;
    http.begin("http://192.168.137.1:8080/RESTServer/resources/PutTexto");
    http.addHeader("Content-Type", "text/plain");
    String a="a";
    bool sensormov;    
    sensormov=digitalRead(SensorMovPin);
    
    if (sensormov==HIGH){
      a = "L";
      digitalWrite(LedMovPin, HIGH);
    }
    else{
      a = "D";
      digitalWrite(LedMovPin, LOW);
    }
    String postMessage=a;
    int httpCode = http.POST(postMessage);
    Serial.print("http result:");
    Serial.println(httpCode);
    http.writeToStream(&Serial);
    http.end();

    delay(1000);
}

