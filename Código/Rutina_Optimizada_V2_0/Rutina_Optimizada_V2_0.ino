#include <SoftwareSerial.h>
#include <Wtv020sd16p.h> //Librería del MP3
#include <Wire.h>
#include <ShiftReg.h>
#include "Const_seq.h"
#include "Seq.h"

extern int const seq1[20];
extern int const seq2[20];
extern int const seq3[20];

// ---- MP3 Pins ---
int resetPin = 2;   // The pin number of the reset pin.
int clockPin = 3;   // The pin number of the clock pin.
int dataPin = 4;    // The pin number of the data pin.
int busyPin = 5;    // The pin number of the busy pin

// ---- Global variables ---
int n;               // Variable auxiliar para determinar pin de salida del Arduino
int rutina;          // Número de rutina
int secuencia[20];   // Matriz de transferencia/copia de secuencias
int leerparo;        // Variable auxiliar para disparar paro
int paro;            // Variable que identifica si se precionó la tecla/botón paro
bool ROJO = false;
bool AZUL = false;
bool VERDE = false;

// --- Modules ---
ShiftReg shiftReg;
Wtv020sd16p wtv020sd16p(resetPin, clockPin, dataPin, busyPin); //Se declara el modulo MP3
SoftwareSerial mySerial(14, 15); // RX, TX
bool I2C = false;


void setup() {
  /*--------------------------------------------*/
  /*  Bluetooth Module & Serial Initialization  */
  mySerial.begin(9600);
  mySerial.println("Iniciando...");
  Serial.begin(9600);
  
  /*----------------------*/
  /*  I2C Initialization  */
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

  /*----------------------------------*/
  /*  Shift Registers Initialization  */ 
  for (int i = 6; i <= 9; i++)
    pinMode(i, OUTPUT);
  /* Welcome sequence */
  for (int i = 0; i < 12; i++) // All off
    shiftReg.digitalWriteMS(1, i, LOW);
  for (int i = 0; i < 12; i++){ // All on
    shiftReg.digitalWriteMS(1, i, HIGH);
    delay(50);
  }
  for (int i = 0; i < 12; i++) { // All off
    shiftReg.digitalWriteMS(1, i, LOW);
    delay(50);
  }
  delay(1000);
  /*-----------------------------*/
  /*  MP3 Module Initialization  */
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  wtv020sd16p.reset(); // MP3 Reset
  while(digitalRead(busyPin) == HIGH){
    Serial.println("Cargando MP3...");
    mySerial.println("Cargando MP3...");
    delay(100);
  }
  wtv020sd16p.unmute();
  //wtv020sd16p.playVoice(1); // Test
  
  // Controller is ready
  mySerial.println("Listo!!");
  mySerial.println("Favor de ingresar la rutina...");
  mySerial.println("------------------------------");
  mySerial.println();
  
  Serial.println("Listo!!");
  Serial.println("Favor de ingresar la rutina...");
  Serial.println("------------------------------");
  Serial.println();
}

//------------------------------
//------------------------------
// Rutina de interrupción de I2C
void receiveEvent(int howMany)
{
  int x = Wire.read();
  if (x == 'x')
    paro = x;
  else
    rutina = x;
  mySerial.println("Wire!!");
  mySerial.println(x);
  I2C = true;
}

void loop() {

  if (mySerial.available() > 0 || Serial.available() || I2C) {
    leerparo = 0;
    paro = 0;
    // Decide de dónde vino la información
    if (mySerial.available()) // Modulo bluetooth
      rutina = mySerial.read();
    else if(I2C) // Botonera
      mySerial.println("I2C");
    else // Ventana de comando
      rutina = Serial.read();
    I2C = false;
    mySerial.flush();
    mySerial.print("El numero de codigo es: "); // Prueba
    mySerial.println(rutina); // Prueba
    mySerial.println();
    
    Serial.flush();
    Serial.print("El numero de codigo es: "); // Prueba
    Serial.println(rutina); // Prueba
    Serial.println();

    switch (rutina) {

        // Rutina 1, 2 o 3
      case '1':
      case '2':
      case '3':
        paro = 0;
        mySerial.print("Secuencia ");
        mySerial.print(rutina);
        mySerial.println();
        //wtv020sd16p.reset();
        delay(300);
        switch(rutina){
          case '1':
            wtv020sd16p.asyncPlayVoice(0); // Comentario temporal
            break;
          case '2':
            wtv020sd16p.asyncPlayVoice(1);
            break;
          case '3':
            wtv020sd16p.asyncPlayVoice(2);
            break;
        }
        // Buffer de la secuencia
        for (int i = 0; i < 20; i++)
          secuencia[i] = seq1[i];
        leerbit();
        apagar();
        break;

        // Rutina 4
      case '4':
        paro = 0;
        mySerial.print("Secuencia 4");
        mySerial.println();
        wtv020sd16p.asyncPlayVoice(3); // Comentario temporal
        // Buffer de la secuencia
        for (int i = 0; i < 20; i++)
          secuencia[i] = seq1[i];
        // Repite la secuencia
        for (int i = 0; i < 3; i++)
          leerbit();
        apagar();
        break;

        // Rutina 5
      case '5':
        paro = 0;
        mySerial.print("Secuencia 5");
        mySerial.println();
        wtv020sd16p.asyncPlayVoice(4); // Comentario temporal
        // Buffer de la secuencia
        for (int i = 0; i < 20; i++) {
          secuencia[i] = seq2[i];
        }
        // Repite la secuencia
        for (int i = 0; i < 3; i++)
          leerbit();
        apagar();
        break;

        // Rutina 6
      case '6':
        paro = 0;
        mySerial.print("Secuencia 6");
        mySerial.println();
        wtv020sd16p.asyncPlayVoice(5); // Comentario temporal
        // Buffer de la secuencia
        for (int i = 0; i < 20; i++) {
          secuencia[i] = seq3[i];
          // Repite la secuencia
        }
        Serial.println("Leerbit");
        for (int i = 0; i < 3; i++)
          leerbit();
        apagar();
        break;

        /*---- COLORES SÓLIDOS ---*/

        // Azul
      case '7':
        if (!paro) {
          if (!AZUL)
            mySerial.println("Color azul encendido");
          else
            mySerial.println("Color azul apagado");

          leerparo = mySerial.read();
          if (leerparo == 'x') {
            mySerial.println("PARO");
            paro = 1;
            apagar();
            AZUL = true;
          }
          // Enciende los LEDs
          for (int i = 0; i < 12; i = i + 3) {
            if (!AZUL)
              shiftReg.digitalWriteMS(1, i, HIGH);
            else
              shiftReg.digitalWriteMS(1, i, LOW);
          }
          AZUL = !AZUL;
        }
        paro = 0;
        mySerial.println("----------------------------");
        mySerial.println();
        break;

        // Rojo
      case '8':
        if (!paro) {
          if (!ROJO)
            mySerial.println("Color rojo encendido");
          else
            mySerial.println("Color rojo apagado");

          leerparo = mySerial.read();
          if (leerparo == 'x') {
            mySerial.println("PARO");
            paro = 1;
            apagar();
            ROJO = true;
          }
          // Enciende los LEDs
          for (int i = 1; i < 12; i = i + 3) {
            if (!VERDE)
              shiftReg.digitalWriteMS(1, i, HIGH);
            else
              shiftReg.digitalWriteMS(1, i, LOW);
          }
        }
        ROJO = !ROJO;
        paro = 0;
        mySerial.println("----------------------------");
        mySerial.println();
        break;

        // Verde
      case '9':
        if (!paro) {
          if (!VERDE)
            mySerial.println("Color verde encendido");
          else
            mySerial.println("Color verde apagado");

          leerparo = mySerial.read();
          if (leerparo == 'x') {
            mySerial.println("PARO");
            paro = 1;
            apagar();
            VERDE = true;
          }

          // Enciende los LEDs
          for (int i = 2; i < 12; i = i + 3) {
            if (!VERDE)
              shiftReg.digitalWriteMS(1, i, HIGH);
            else
              shiftReg.digitalWriteMS(1, i, LOW);
          }
          VERDE = !VERDE;
        }
        paro = 0;
        mySerial.println("----------------------------");
        mySerial.println();
        break;

        // Se apaga todo
      case 'x':
        apagar();
        break;

        I2C = false;
        mySerial.println("Fin de rutina");
    }
  }
}

