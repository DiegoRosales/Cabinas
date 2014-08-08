/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by Diego J. Arevalo, August 6th, 2012.
 Released into the public domain.
 */

#include <Wtv020sd16p.h>
#include <SoftwareSerial.h>
int resetPin = A2;  // The pin number of the reset pin.
int clockPin = 1;  // The pin number of the clock pin.
int dataPin = A3;  // The pin number of the data pin.
int busyPin = 6;  // The pin number of the busy pin.
int x;
/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
SoftwareSerial mySerial(14, 15); // RX, TX
void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  mySerial.begin(115200);
  //Initializes the module.
  wtv020sd16p.reset();
  wtv020sd16p.asyncPlayVoice(3);
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
    mySerial.flush();
    wtv020sd16p.asyncPlayVoice(x);
    mySerial.println(x);  
  }
}
