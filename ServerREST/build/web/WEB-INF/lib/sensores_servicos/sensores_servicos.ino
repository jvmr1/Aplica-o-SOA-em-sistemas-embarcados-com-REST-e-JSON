#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const int SensorTempPin =  A0;
const int SensorMovPin =  16;

String ip = "192.168.137.1";

void setup() {
  USE_SERIAL.begin(9600);
   
  WiFiMulti.addAP("JH", "12345678");

  pinMode(SensorTempPin, INPUT);
  pinMode(SensorMovPin, INPUT);
  
  Serial.begin(9600);
  int cont1=0;
  int cont2=0;
  }

void loop() {
  int cont1=0;
  int cont2=0;

  while(cont2<=10000){
  
  if (cont1==1000){    
    bool movimento;
    movimento = digitalRead(SensorMovPin);
  
    if (movimento == HIGH){
      Serial.println("Presenca"); 
      
      HTTPClient http;
      http.begin("http://"+ip+":8080/ServerREST/resources/postPresenca");
      http.addHeader("Content-Type", "text/plain");
  
      String postMessage = "Presenca";
      int httpCode = http.POST(postMessage);
      
      http.end();  
      cont1=0;
    }
  }

  else if (cont2==10000){
    int leitura;
    float temperatura;
    leitura = analogRead(SensorTempPin); 
    
    temperatura = ( 3.3 * leitura * 100.0) / 1023.0;
  
    Serial.println(temperatura); 
  
    HTTPClient http;
    http.begin("http://192.168.137.1:8080/ServerREST/resources/postTemperatura");
    http.addHeader("Content-Type", "text/plain");
    
    String postTemperatura;
    postTemperatura=String(temperatura);
    int httpCode = http.POST(postTemperatura);
    
    http.end();
    cont2=0;
  }
  
  cont1=cont1+1;
  cont2=cont2+1;
}
}
