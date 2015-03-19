#ifndef MISC_H
#define MISC_H

#include <SoftwareSerial.h>
#include <Wire.h>
#include <ShiftReg.h>
#include "TimerOne.h"

//------SERIAL HELLO-------
#define PCB_REV "PCB Rev 1.5"
#define FW_REV "Firmware V3.0"
#define FECHA "23/02/2015"

//------PRUEBA DE LEDS-------
#define TIEMPO_MAXIMO 25

void i2cReceiveEvent(int howMany);
void proteccionLeds();

#endif
