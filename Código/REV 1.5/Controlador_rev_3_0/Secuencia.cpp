#include "Secuencia.h"

void secuencia::begin() {
  Serial.begin(115200);
  mySerial.begin(9600);
  serialHello();
  Wire.begin(ID_BOTONERA);      // join i2c bus with address #4
  Wire.onReceive(i2cReceiveEvent); // register event

  Timer1.initialize(200000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(proteccionLeds);  // attaches callback() as a timer overflow interrupt
  /*----------------------------------*/
  /*  Shift Registers Initialization  */
  for (int i = 6; i <= 9; i++)
    pinMode(i, OUTPUT);
  /* Welcome sequence */
  for (int i = 0; i < 12; i++) // All off
    shiftReg.digitalWriteMS(1, i, LOW);
  for (int i = 0; i < 12; i++) { // All on
    shiftReg.digitalWriteMS(1, i, HIGH);
    delay(50);
  }
  for (int i = 0; i < 12; i++) { // All off
    shiftReg.digitalWriteMS(1, i, LOW);
    delay(50);
  }
}

void secuencia::esperando() {
  for (;;) {
    char comando = 0;
    comando = polComando();
    if(PARO == 1){
      Serial.println("Paro espera");
      rutinaParo();  
    }
    switch (comando) {
      // Rutina
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
        prepararRutina(comando - '0');
        break;
      // Prueba de LEDs
      case '7':
      case '8':
      case '9':
        pruebaLED(comando);
        break;
      // Prueba de pistas
      case '*': // Pistas 1, 2 y 3
      case '#': // Pistas 4, 5 y 6
        pruebaMusica(comando);
        break;
      case 'x': // Paro
        rutinaParo();
        break;
      default:
        break;
    }
  }
}

void secuencia::prepararRutina(uint8_t rutina) {
  encenderLeds(0);
  serialPrint("Iniciando rutina ");
  serialPrintln(rutina);

  iniciarPista(rutina);

  if ((rutina == 1) || (rutina == 4)) {
    iniciarRutina(0, rutina);
  } else if ((rutina == 2) || (rutina == 5)) {
    iniciarRutina(1, rutina);
  } else {
    iniciarRutina(2, rutina);
  }
}

void secuencia::iniciarRutina(uint8_t NumSecuencia, uint8_t numRutina) {
  int seqBuffer[20];
  int numCiclos;
  rutinaEnCurso = 1;
  
  switch(numRutina){
    case 1:
    case 2:
    case 3:
      numCiclos = 75;
      break;
    case 4:
    case 5:
    case 6:
      numCiclos = 300;
      break;
    default:
      numCiclos = 75;
      break;
  }
  // Copia la secuencia al buffer
  for (int i = 0; i < 20; i++) seqBuffer[i] = secuencias[NumSecuencia][i];
  
  // Inicia la secuencia
  for (int i = 0; i < 16; i += 2) {
    for (int j = 0; j < numCiclos; j++) {
      encenderLeds(seqBuffer[i]);
      delay(200);
      encenderLeds(seqBuffer[i + 1]);
      delay(200);
      if (mySerial.available()) BTRoutine();
      if (PARO) break;
    }
    if (PARO) break;
  }
  rutinaParo();
}

void secuencia::encenderLeds(int leds) {
  uint8_t n = 0;
  Serial.println(leds, BIN);
  for (int i = 11; i >= 0; i--) {
    if (bitRead(leds, i)) {
      shiftReg.digitalWriteMS(1, n, HIGH);
    } else {
      shiftReg.digitalWriteMS(1, n, LOW);
    }
    n++;
  }
}

void secuencia::rutinaParo() {
  serialPrintln("Deteniendo, por favor espere...");
  PARO = 0;
  rutinaEnCurso = 0;
  apagarLeds();
  iniciarPista('s');
  serialPrintln("Todo listo");
  serialPrintln("====================");
  serialPrintln("Seleccione la rutina");
}

void secuencia::iniciarPista(char pista) {
  if (pista != 's') {
    Wire.beginTransmission(ID_MP3); // transmit to device #ID_MP3
    Wire.write('t');      // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
  Wire.beginTransmission(ID_MP3);
  Wire.write(pista);
  //Wire.endTransmission(false);
  Wire.endTransmission(true);
}

void secuencia::pruebaLED(char led) {
  switch (led) {
    case '7': // Leds azules
      serialPrint("LEDs Azules ");
      AZUL ^= 1;
      if (AZUL) serialPrintln("encendidos");
      else serialPrintln("apagados");
      ledsEncendidos ^= LEDS_AZULES;

      break;
    case '8': // Leds rojos
      serialPrint("LEDs Rojos ");
      ROJO ^= 1;
      if (ROJO) serialPrintln("encendidos");
      else serialPrintln("apagados");
      ledsEncendidos ^= LEDS_ROJOS;

      break;
    case '9': // Leds verdes
      serialPrint("LEDs Verdes ");
      VERDE ^= 1;
      if (VERDE) serialPrintln("encendidos");
      else serialPrintln("apagados");
      ledsEncendidos ^= LEDS_VERDES;

      break;
    default:
      break;
  }
  encenderLeds(ledsEncendidos);
}

