#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(14, 15); // RX, TX
const char ID_MP3 = 5;
void setup()
{
  mySerial.begin(9600);
  mySerial.println("Iniciando...");
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

int x = 0;

void loop()
{
  if(mySerial.available()){
    x = mySerial.read();
    if(x == '1'){
      Serial.println(x);
      changeTrack(1);
    }else if(x == '2'){
      Serial.println(x);
      changeTrack(2);
    }else if(x == '3'){
      Serial.println(x);
      changeTrack(3);  
    }else if(x == '4'){
      Serial.println(x);
      changeTrack(4); 
    }else if(x == '5'){
      Serial.println(x);
      changeTrack(5);
    }else if(x == '6'){
      Serial.println(x);
      changeTrack(6);
    }else if(x == 'x'){
      Wire.beginTransmission(ID_MP3);
      Wire.write('s');
      Wire.endTransmission();  
    }
  }
}

void changeTrack(char track){
      Wire.beginTransmission(ID_MP3); // transmit to device #ID_MP3
      Wire.write('t');      // sends one byte
      Wire.endTransmission();    // stop transmitting
      Wire.beginTransmission(ID_MP3);
      Wire.write(track);
      Wire.endTransmission();
}
