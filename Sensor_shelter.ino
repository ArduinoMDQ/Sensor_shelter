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
int ledPin = 13;      // select the pin for the LED
int ena485=2;
int sensorValue = 0;  // variable to store the value coming from the sensor


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
    Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(ena485, OUTPUT);
  
  digitalWrite(ena485,HIGH);
  delay(50);
  Serial.println("Inicio Sensor");
  delay(50);
  digitalWrite(ena485,LOW);

}

void loop() {
  
   serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete) {
    digitalWrite(ena485,HIGH);
    delay(50);
    Serial.println(inputString);
    delay(50);
    digitalWrite(ena485,LOW);
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
   /* delay(5000);
     digitalWrite(ena485,HIGH);
     delay(50);
    Serial.println("Necesito el koinnor EDGARDO !!!");
    Serial.print("Temperatura del Shelter Balcarce 24:");
    Serial.print(sensorValue);Serial.print("ºC");
     Serial.println();
     delay(50);
     digitalWrite(ena485,LOW);*/
     
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
