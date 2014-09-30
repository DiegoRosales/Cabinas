#include <SoftwareSerial.h>
#include <Wtv020sd16p.h> //Librería del MP3
#include <Wire.h>
#include <ShiftReg.h>
#include "Const_seq.h"
#include "Seq.h"
#include "TimerOne.h"

#define TIEMPOMAXIMO 25

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
bool ROJO1 = false;
bool VERDE1 = false;
bool AZUL1 = false;
int ROJO = 0;
int AZUL = 0;
int VERDE = 0;
int rutina_temp = 0;
int rutina_temp2 = 3;
int tiempoMaximo = 0;
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
  for (int i = 0; i < 12; i++) { // All on
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
  while (digitalRead(busyPin) == HIGH) {
    Serial.println("Cargando MP3...");
    mySerial.println("Cargando MP3...");
    delay(100);
  }
  wtv020sd16p.unmute();
  //wtv020sd16p.playVoice(1); // Test
  
  Timer1.initialize(200000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(LEDTest);  // attaches callback() as a timer overflow interrupt
  //Timer1.stop();
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

void LEDTest() {
 
  if(VERDE == 2){
    //mySerial.println("Verde parpadeando");
    for (int i = 2; i < 12; i = i + 3) {
      if (VERDE1 == 0)
        shiftReg.digitalWriteMS(1, i, HIGH);
      else
        shiftReg.digitalWriteMS(1, i, LOW);
    }
    VERDE1 = !VERDE1;  
  }
  
  if(ROJO == 2){
    //mySerial.println("Rojo parpadeando");
    for (int i = 1; i < 12; i = i + 3) {
      if (ROJO1 == 0)
        shiftReg.digitalWriteMS(1, i, HIGH);
      else
        shiftReg.digitalWriteMS(1, i, LOW);
    }
    ROJO1 = !ROJO1;  
  }
  
  if(AZUL == 2){
    for (int i = 0; i < 12; i = i + 3) {
      if (AZUL1 == 0)
        shiftReg.digitalWriteMS(1, i, HIGH);
      else
        shiftReg.digitalWriteMS(1, i, LOW);
    }
    AZUL1 = !AZUL1;
  }
  
  if(AZUL != 0 && VERDE != 0  && ROJO != 0){
    tiempoMaximo++;
    if(tiempoMaximo%5 == 0){
      mySerial.print("Apagando en ");
      mySerial.print(TIEMPOMAXIMO/5 - tiempoMaximo/5);
      mySerial.println(" segundos");
    }
  }else
    tiempoMaximo = 0;
  
  if(tiempoMaximo > TIEMPOMAXIMO){
    apagar();
    tiempoMaximo = 0;
  }
}

//------------------------------
//------------------------------
// Rutina de interrupción de I2C
void receiveEvent(int howMany)
{
  int x = Wire.read();
  if (x == 'x'){
    apagar();
    leerparo = 'x';
    //mySerial.println("I2C Paro");
  }else
    rutina = x;
  mySerial.println("Botonera");
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
    else if (I2C) // Botonera
      mySerial.println("I2C");
    else // Ventana de comando
      rutina = Serial.read();
    I2C = false;
    mySerial.flush();
    //mySerial.print("El numero de codigo es: "); // Prueba
    //mySerial.println(rutina); // Prueba
    //mySerial.println();

    Serial.flush();
    Serial.print("El numero de codigo es: "); // Prueba
    Serial.println(rutina-49); // Prueba
    Serial.println();

    switch (rutina) {

        // Rutina 1, 2 o 3
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
        ejecutarRutina(rutina);
        break;

        /*---- COLORES SÓLIDOS ---*/

        // Azul
      case '7':
          if (AZUL == 0)
            mySerial.println("Color azul encendido");
          else if (AZUL == 1)
            mySerial.println("Color azul parpadeando");
          else
            mySerial.println("Color azul apagado");
            
          // Enciende los LEDs
          for (int i = 0; i < 12; i = i + 3) {
            if (AZUL == 0)
              shiftReg.digitalWriteMS(1, i, HIGH);
            else if (AZUL == 2)
              shiftReg.digitalWriteMS(1, i, LOW);
          }
          if(AZUL == 2)
            AZUL = 0;
          else
            AZUL++;
        //mySerial.println(AZUL);
        paro = 0;
        mySerial.println("----------------------------");
        mySerial.println();
        break;

        // Rojo
      case '8':
          if (ROJO == 0)
            mySerial.println("Color rojo encendido");
          else if (ROJO == 1)
            mySerial.println("Color rojo parpadeando");
          else if (ROJO == 2)
            mySerial.println("Color rojo apagado");
            
          // Enciende los LEDs
          for (int i = 1; i < 12; i = i + 3) {
            if (ROJO == 0){
              shiftReg.digitalWriteMS(1, i, HIGH);
              ROJO1 = true;
            }
            else if (ROJO == 2){
              shiftReg.digitalWriteMS(1, i, LOW);
          }
        }
        if(ROJO == 2)
          ROJO = 0;
        else
          ROJO++;
        paro = 0;
        mySerial.println("----------------------------");
        mySerial.println();
        break;

        // Verde
      case '9':
          if (VERDE == 0)
            mySerial.println("Color verde encendido");
          else if (VERDE == 1)
            mySerial.println("Color verde parpadeando");
          else if (VERDE == 2)
            mySerial.println("Color verde apagado");

          // Enciende los LEDs
          for (int i = 2; i < 12; i = i + 3) {
            if (VERDE == 0){
              shiftReg.digitalWriteMS(1, i, HIGH);
              //VERDE1 = true;
            }
            else if (VERDE == 2) {
              shiftReg.digitalWriteMS(1, i, LOW);
            }
          }
          
          if(VERDE == 2)
            VERDE = 0;
          else
            VERDE++;
        paro = 0;
        //mySerial.println(VERDE);
        mySerial.println("----------------------------");
        mySerial.println();
        break;

      // Va ciclando las secuencias
      case '*':
        //rutina_temp = 1;
        //ejecutarRutina(rutina_temp+48);
        if(rutina_temp > 2){
          apagar();
          rutina_temp = 0;
        }else{
          mySerial.print("Iniciando cancion ");
          mySerial.println(rutina_temp + 1);
          wtv020sd16p.asyncPlayVoice(rutina_temp);
          rutina_temp++;
        }
        break;
        
      case '#':
        //rutina_temp2 = 3;

        if(rutina_temp2 > 5){
          apagar();
          rutina_temp2 = 3;
        }else{
          mySerial.print("Iniciando cancion ");
          mySerial.println(rutina_temp2 + 1);
          wtv020sd16p.asyncPlayVoice(rutina_temp2);
          rutina_temp2++;
        }
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

