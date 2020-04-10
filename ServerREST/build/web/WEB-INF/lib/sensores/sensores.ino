const int SensorTempPin =  A0;
const int SensorMovPin =  16;
const int LedTempPin =  15;  
const int LedMovPin =  13; 

void setup() {
    pinMode(SensorTempPin, INPUT);
    pinMode(SensorMovPin, INPUT);
    pinMode(LedTempPin, OUTPUT);
    pinMode(LedMovPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  bool movimento;
  movimento = digitalRead(SensorMovPin);
  
  if (movimento == HIGH){
    Serial.println("Presenca"); 
    digitalWrite(LedMovPin, HIGH);
  }
  else{
    digitalWrite(LedMovPin, LOW);
  }
 
  int leitura;
  float temperatura;
  leitura = analogRead(SensorTempPin); 
  
  temperatura = ( 3.3 * leitura * 100.0) / 1023.0;

  Serial.println(temperatura); 
  
  if (temperatura > 31){
    digitalWrite(LedTempPin, HIGH);
  }
  else{
    digitalWrite(LedTempPin, LOW);
  }
delay(1000);
}
