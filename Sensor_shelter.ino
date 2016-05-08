/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/AnalogInput

 */

int sensorPin = A0;    // select the input pin for the potentiometer

int ena485=2;


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);

  pinMode(ena485, OUTPUT);
  
  digitalWrite(ena485,HIGH);
  //delay(10);
  Serial.println("Sensor OK!!");
  delay(50);
  digitalWrite(ena485,LOW);

}

void loop() {
  
   serialEvent();
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
      
        digitalWrite(ena485,HIGH);
        delay(50);
        sensorValue= analogRead(0);
        Serial.print(sensorValue);Serial.println(" Dac");
        voltage= sensorValue*(5.0 / 1023.0);
        Serial.print(voltage);Serial.println(" Volts");
        temp=(sensorValue/1024.0)*500;
        Serial.print(temp);Serial.println(" ºC");
        delay(50);
        digitalWrite(ena485,LOW);
        break;
      case 'b':
        digitalWrite(ena485,HIGH);
        delay(50);
        Serial.println("Medicion de Baliza");
       delay(50);
        digitalWrite(ena485,LOW);
        
        break;
      case 'r':
       
        digitalWrite(ena485,HIGH);
        delay(50);
        Serial.println("Encender Extractor");
       delay(50);
        digitalWrite(ena485,LOW);
        break;
      default:break;
   }  
  
  
  }
