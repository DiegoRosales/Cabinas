#include "Secuencia.h"

extern secuencia mSecuencia;
uint8_t contador = 0;

void secuencia::serialPrint(String mString){
    mySerial.print(mString);
    Serial.print(mString);
}
void secuencia::serialPrint(int num){
    mySerial.print(num);
    Serial.print(num);
}

void secuencia::serialPrintln(String mString){
    mySerial.println(mString);
    Serial.println(mString);
}
void secuencia::serialPrintln(int num){
    mySerial.println(num);
    Serial.println(num);
}

void secuencia::serialHello(){
  serialPrintln("Iniciando...");
  serialPrintln("Hackerspace Cholula");
  serialPrintln(FW_REV);
  serialPrintln(PCB_REV);
  serialPrintln(FECHA);
  serialPrintln("=========BIENVENIDO==========");
  serialPrintln("Seleccione la rutina");
}

void i2cReceiveEvent(int howMany){
  Serial.println("i2cReceiveEvent");
  mSecuencia.i2cInterruptRoutine();
}

void secuencia::i2cInterruptRoutine(){
  Serial.println("i2cInterruptRoutine()");
  i2cread = Wire.read();
  if(i2cread == 'x'){
    Serial.println("Paro Botonera");
    PARO = 1;  
    i2cread = 0;
  }
}

void secuencia::BTRoutine(){
  char x = mySerial.read();
  switch(x){
    case 'x': // Paro
    PARO = 1;
    break;
    
    default:
    break;    
  }  
}

char secuencia::polComando(){
  if(mySerial.available()){
    return mySerial.read();
  }else if(i2cread){
    char x = i2cread;
    i2cread = 0;
    return x;
  }else return 0;  
}

bool secuencia::getLeds(){
  return AZUL & VERDE & ROJO;
}

void secuencia::apagarLeds(){
  serialPrintln("Apagando LEDs...");
  AZUL = 0;
  ROJO = 0;
  VERDE = 0;
  encenderLeds(0);
  ledsEncendidos = 0;  
  serialPrintln("Todo listo");
  serialPrintln("====================");
  serialPrintln("Seleccione la rutina");
}

void proteccionLeds(){
  if(mSecuencia.getLeds()){
    contador ++;
    if(contador == TIEMPO_MAXIMO/5 - 1){
      mSecuencia.serialPrint("Apagando en ");
    }else if(contador%5 == 0 && contador != TIEMPO_MAXIMO){
      mSecuencia.serialPrint(TIEMPO_MAXIMO/5-(contador/5));
      mSecuencia.serialPrint(" ");
    }      
  } else contador = 0;  
  if(contador >= TIEMPO_MAXIMO){
    mSecuencia.serialPrintln("");
    mSecuencia.apagarLeds();  
  }
}

void secuencia::pruebaMusica(char pistas){
  
  switch(pistas){
    case '*':      
      if(pistaActual < 0 || pistaActual > 3) pistaActual = 1;
      serialPrint("Iniciando pista ");
      serialPrintln((uint8_t)pistaActual); 
      iniciarPista(pistaActual);
      pistaActual++;

      break;
    case '#':
      if(pistaActual > 6 || pistaActual < 4) pistaActual = 4;
      serialPrint("Iniciando pista ");
      serialPrintln((uint8_t)pistaActual); 
      iniciarPista(pistaActual);
      pistaActual++;   
      break;  
  }
    
}
