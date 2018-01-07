#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int sensorPin = A0;
int ena485=2;
int id=1; // Id de identificacion del dispositivo

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean loopSensor=false;
float h =0;
float t = 0;
int baliza = 0;

void setup() {
  
  pinMode(ena485, OUTPUT);
  digitalWrite(ena485,HIGH);Serial.begin(9600);
  dht.begin();// Iniciamos el sensor​
  delay(30);
  digitalWrite(ena485,LOW);
 
}

void loop() {
 
    if (stringComplete){
       medicion();
       inputString = "";
       stringComplete = false;
      }

}
 
void serialEvent() {
 
  while (Serial.available()) {
    
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\r') {
      
      stringComplete = true;
    }
  }

}

void medicion(){
  int id2=id+1;
  int sensorValue =0;
  float voltage=0;
  float temp=0;
  
  if(id==inputString.toInt()){
        h=dht.readHumidity();
        t=dht.readTemperature();
        baliza=analogRead(sensorPin);
        digitalWrite(ena485,HIGH);
        delay(5);
        if (isnan(t) || isnan(h)) {
            Serial.print(id);
            Serial.println(";00.00;00.00;0");
        } else {
            Serial.print(id);Serial.print(";");
            Serial.print(t);Serial.print(";");
            Serial.print(h);Serial.print(";");
            Serial.println(baliza);
            };
        }

   
  if((id2)==inputString.toInt()){
        h=dht.readHumidity();
        t=dht.readTemperature();
        baliza=analogRead(sensorPin);
        digitalWrite(ena485,HIGH);
        delay(5);
        if (isnan(t) || isnan(h)) {
            Serial.print(id2);
            Serial.println(";00.00;00.00;0");
        } else {
            Serial.print(id2);Serial.print(";");
            Serial.print(t+1);Serial.print(";");
            Serial.print(h+1);Serial.print(";");
            Serial.println(baliza+176);
            };
        }
     
  delay(30);
  digitalWrite(ena485,LOW);
  }
  
void ISR_CheckSerial(){
    serialEvent();
  }

