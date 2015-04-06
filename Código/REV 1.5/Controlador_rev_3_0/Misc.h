#ifndef MISC_H
#define MISC_H

#include <SoftwareSerial.h>
#include <Wire.h>
#include <ShiftReg.h>
#include "TimerOne.h"

//------SERIAL HELLO-------
#define PCB_REV "PCB Rev 1.5"
#define FW_REV "Firmware V3.0.2"
#define FECHA "06/04/2015"

//------PRUEBA DE LEDS-------
#define TIEMPO_MAXIMO 25

void i2cReceiveEvent(int howMany);
void proteccionLeds();

#endif
