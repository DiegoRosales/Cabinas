/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by Diego J. Arevalo, August 6th, 2012.
 Released into the public domain.
 */

#include <Wtv020sd16p.h>
#include <SoftwareSerial.h>
#include <ShiftReg.h>
int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 4;  // The pin number of the data pin.
int busyPin = 5;  // The pin number of the busy pin.
int x;
/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */

ShiftReg shiftReg;
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
SoftwareSerial mySerial(14, 15); // RX, TX
void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
  //Initializes the module.
  for (int i = 6; i <= 9; i++)
    pinMode(i, OUTPUT);
    
  for(int n = 0; n<5; n++){
      for (int i = 0; i < 12; i++)
      shiftReg.digitalWriteMS(1, i, LOW);
    for (int i = 0; i<12; i++){
      shiftReg.digitalWriteMS(1, i, HIGH);
      //delay(10);
    }
    delay(50);
    for (int i = 0; i<12; i++){
      shiftReg.digitalWriteMS(1, i, LOW);
      //delay(10);
    }
    delay(50);
  }
  
  wtv020sd16p.reset();
  delay(300);
  while(digitalRead(busyPin) == HIGH){
    Serial.println("Loading...");
  }
  Serial.println("Loading completed!");
  wtv020sd16p.playVoice(1);
}

void loop() {

 /* for(int i=0; i<=8; i++){
    delay(20000);
    //Serial.println(digitalRead(busyPin));
    //wtv020sd16p.mute();
    digitalWrite(5, HIGH);
    wtv020sd16p.stopVoice();
    delay(300);
    wtv020sd16p.asyncPlayVoice(1);
    digitalWrite(5, LOW);
    /*digitalWrite(dataPin, HIGH);
    digitalWrite(clockPin, HIGH);
    delay(2500);
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    //wtv020sd16p.unmute();
    //Serial.println(i);
  }*/
 
  if(mySerial.available()){
    x = mySerial.parseInt();
    mySerial.println(x); 
    wtv020sd16p.asyncPlayVoice(x);
    //mySerial.flush();
    mySerial.println(x);  
  }
  
  if(Serial.available()){
    Serial.println("Serial is available");
    x = Serial.parseInt();
    Serial.println("Serial Parseint");
    Serial.println(x); 
    wtv020sd16p.asyncPlayVoice(x);
    //Serial.flush();
    Serial.println(x);  
  }
}
