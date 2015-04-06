#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <SoftwareSerial.h>
#include <Wire.h>
#include <ShiftReg.h>
#include "TimerOne.h"
//-------PERSONAL LIBRARIES---------
#include "Misc.h"
#include "Const_seq.h"

#define LEDS_AZULES 0x924
#define LEDS_ROJOS 0x492
#define LEDS_VERDES 0x249

#define TIEMPO 5 // Segundos

//-------I2C-------
#define ID_BOTONERA 4
#define ID_MP3 5

class secuencia{
  
  ShiftReg shiftReg;
  SoftwareSerial mySerial = SoftwareSerial(14, 15); // RX, TX
  bool PARO = 0;
  char i2cread = 0;
  bool AZUL, ROJO, VERDE = 0;
  // Pruebas
  int ledsEncendidos = 0;
  char pistaActual = 1;
  bool rutinaEnCurso = 0;
  
  public:
    //----SECUENCIA.CPP----
    void begin();
    void esperando();
    void prepararRutina(uint8_t rutina);
    void iniciarRutina(uint8_t NumSecuencia);
    void encenderLeds(int leds);
    void rutinaParo();
    void iniciarPista(char pista);
    void pruebaLED(char led);
    //----MISC.CPP----
    void serialPrint(String mString);
    void serialPrint(int num);
    void serialPrintln(String mString);
    void serialPrintln(int num);
    void serialHello();
    void i2cInterruptRoutine();
    void BTRoutine();
    char polComando();
    bool getLeds();
    void apagarLeds();
    void pruebaMusica(char pistas);
    bool rutinaActivada();
};


#endif
