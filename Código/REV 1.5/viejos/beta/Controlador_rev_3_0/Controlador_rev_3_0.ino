#include <SoftwareSerial.h>
#include <Wire.h>
#include <ShiftReg.h>
#include "TimerOne.h"
//-------PERSONAL LIBRARIES---------
#include "Misc.h"
#include "Secuencia.h"
#include "Const_seq.h"


// --- Modules ---
secuencia mSecuencia;


void setup(){
  mSecuencia.begin();  
 // mSecuencia.iniciarRutina(0);
}

void loop(){
  mSecuencia.esperando();
}

void initShiftRegister(){
  
}


