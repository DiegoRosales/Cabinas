// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Wire.h>

#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  
char x = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing MP3 module");
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
  if(!SD.begin(CARDCS)) Serial.println("Error initializing SD card");
  else Serial.println("SD card initialized correctly!");  // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  /*----------------------*/
  /*  I2C Initialization  */
  Wire.begin(5);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  
  // Play one file, don't return until complete
  Serial.println(F("Playing track 001"));
  if(!musicPlayer.playFullFile("track001.mp3")) Serial.println("Couldn't play track001.mp3");
  // Play another file in the background, REQUIRES interrupts!
  Serial.println(F("Playing track 002"));
  if(!musicPlayer.startPlayingFile("track002.mp3")) Serial.println("Couldn't play track002.mp3");
}

void loop() {
  // File is playing in the background
  if (musicPlayer.stopped()) {
    Serial.println("Done playing music");
    while (1);
  }
  if (Serial.available()) {
    char c = Serial.read();
    
    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      musicPlayer.stopPlaying();
    }
    
    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! musicPlayer.paused()) {
        Serial.println("Paused");
        musicPlayer.pausePlaying(true);
      } else { 
        Serial.println("Resumed");
        musicPlayer.pausePlaying(false);
      }
    }
  }

  delay(100);
}


//------------------------------
//------------------------------
// Rutina de interrupción de I2C
void receiveEvent(int howMany)
{
  if(x == 0){
    x = Wire.read();
    if(x == 'v'){
      Serial.println("Setting volume"); 
    }else if(x == 't'){
      Serial.println("Setting track");  
    }else if(x == 's'){
      Serial.println("Stopping...");
      musicPlayer.stopPlaying();  
      musicPlayer.softReset();
      x = 0;
    }else{
      x = 0;
    }
  }else{
    if(x == 'v'){
      x = Wire.read();
      musicPlayer.setVolume(x,x);
      Serial.println((int)x);
    }else if(x == 't'){
      x = Wire.read();
      Serial.println(x);
      musicPlayer.stopPlaying();
      switch(x){
        case 1:
          if(!musicPlayer.startPlayingFile("track001.mp3")) Serial.println("Couldn't play track001.mp3");
          else Serial.println("Playing track001.mp3");
          break;
        case 2:
          if(!musicPlayer.startPlayingFile("track002.mp3")) Serial.println("Couldn't play track002.mp3");
          else Serial.println("Playing track002.mp3");
          break;
        case 3:
          if(!musicPlayer.startPlayingFile("track003.mp3")) Serial.println("Couldn't play track003.mp3");
          else Serial.println("Playing track003.mp3");
          break;
        case 4:
          if(!musicPlayer.startPlayingFile("track004.mp3")) Serial.println("Couldn't play track004.mp3");
          else Serial.println("Playing track004.mp3");
          break;
        case 5:
          if(!musicPlayer.startPlayingFile("track005.mp3")) Serial.println("Couldn't play track005.mp3");
          else Serial.println("Playing track005.mp3");
          break;
        case 6:
          if(!musicPlayer.startPlayingFile("track006.mp3")) Serial.println("Couldn't play track006.mp3");
          else Serial.println("Playing track006.mp3");
          break;
        default:
          x = 0;
          break;
      }  
    }
    x = 0;
  }
}
