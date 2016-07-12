#include <TimerOne.h>


#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
int sensorPin = A0;
int ena485=2;
int ID=1;
String tag="Balcarce 24 y 25";
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean loopSensor=false;
float h =0;
float t = 0;
int contador=0;

void setup() {
  pinMode(ena485, OUTPUT);
  digitalWrite(ena485,HIGH);Serial.begin(9600);
  dht.begin();// Iniciamos el sensor​
  Serial.println(tag);
  delay(50);
  digitalWrite(ena485,LOW);
  Timer1.initialize(100000);  // 250 ms
  Timer1.attachInterrupt( ISR_CheckSerial) ;
}

void loop() {
 
//   serialEvent();
   while(loopSensor)
   { contador++;
     h=dht.readHumidity();
        t=dht.readTemperature();
        digitalWrite(ena485,HIGH);
        delay(50);
        if (isnan(t) || isnan(h)) {
            Serial.println("ID 1 00.00 00.00");
        } else {
            Serial.print("N:");Serial.print(contador);
            Serial.print(" Temp:");Serial.print(t);
            Serial.print(" Hum:");Serial.print(h);
            Serial.print(" - ");Serial.println(tag);
         
             };
        delay(50);
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
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
   
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\r') {
      stringComplete = true;
    }
  }
 
}

void comandos(String com){

  int sensorValue =0;
  float voltage=0;
  float temp=0;

  char com_char;

  com_char=inputString[0];

  switch (com_char) {
      case 't':
        h=dht.readHumidity();
        t=dht.readTemperature();
        digitalWrite(ena485,HIGH);
        delay(50);
        if (isnan(t) || isnan(h)) {
        Serial.println("ID 1 00.00 C 00.00 H");} 
        else {
            Serial.print("N:");Serial.print(contador);
            Serial.print(" Temp:");Serial.print(t);
            Serial.print(" Hum:");Serial.print(h);
            Serial.print(" - ");Serial.println(tag);
               };
        break;
      case 'b':
        digitalWrite(ena485,HIGH);
        delay(50);
        sensorValue= analogRead(0);
        Serial.print(sensorValue);Serial.println("ID ");  Serial.print(ID);
        voltage= sensorValue*(5.0 / 1023.0);
        Serial.println(voltage);
        break;
        
   /*   case 'r':
        digitalWrite(ena485,HIGH);
        delay(50);
        Serial.println("Encender Extractor");
        break;*/
      case 'l':
        loopSensor=!loopSensor;
        digitalWrite(ena485,HIGH);
        delay(50);
        Serial.print("loop:");
        Serial.println(loopSensor);
        break;  
      default:
        break;
   }  
   
  delay(100);
  digitalWrite(ena485,LOW);
  
  
  }
  
  void ISR_CheckSerial(){
    serialEvent();
  
  }

