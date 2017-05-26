#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int sensorPin = A0;
int ena485=2;
int id=1;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean loopSensor=false;
float h =0;
float t = 0;
void setup() {
  pinMode(ena485, OUTPUT);
  digitalWrite(ena485,HIGH);Serial.begin(9600);
  dht.begin();// Iniciamos el sensor​
  delay(30);
  digitalWrite(ena485,LOW);
 
}

void loop() {
 
//   serialEvent();
   while(loopSensor)
   {    h=dht.readHumidity();
        t=dht.readTemperature();
        digitalWrite(ena485,HIGH);
        delay(30);
        if (isnan(t) || isnan(h)) {
            Serial.print(id);
            Serial.println(";00.00;00.00");
            
        } else {
            Serial.print(id);Serial.print(";");
            Serial.print(t);Serial.print(";");
            Serial.println(h);
         
             };
        delay(30);
  digitalWrite(ena485,LOW);
    //  serialEvent();
       if (stringComplete) 
        {
        comandos(inputString);
        inputString = "";
        stringComplete = false;
        }
        delay(5000);
   }
   
   
   if (stringComplete) 
        {
       comandos(inputString);
     
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

void comandos(String com){

  int sensorValue =0;
  float voltage=0;
  float temp=0;
  
  if(id==inputString.toInt()){
      h=dht.readHumidity();
        t=dht.readTemperature();
        digitalWrite(ena485,HIGH);
        delay(5);
        if (isnan(t) || isnan(h)) {
            Serial.print(id);
            Serial.println(";00.00;00.00");
            //Serial.print(char(10));
          //  Serial.print(char(13));
        } else {
            Serial.print(id);Serial.print(";");
            Serial.print(t);Serial.print(";");
            Serial.println(h);
            //Serial.print(char(10));Serial.print(char(13));
            };
        }
     
  delay(30);
  digitalWrite(ena485,LOW);
  }
  
  void ISR_CheckSerial(){
    serialEvent();
  }

