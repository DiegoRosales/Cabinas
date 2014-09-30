#include "Seq.h"
#include "TimerOne.h"
#include "Const_seq.h"

extern Wtv020sd16p wtv020sd16p;
//extern int paro;
extern SoftwareSerial mySerial;
extern int secuencia[];
extern int const seq1[];
extern int const seq2[];
extern int const seq3[];
extern int n;
extern bool I2C;
extern int leerparo;
extern ShiftReg shiftReg;
extern int ROJO;
extern bool ROJO1;
extern int VERDE;
extern bool VERDE1;
extern bool AZUL1;
extern int AZUL;
extern int rutina_temp, rutina_temp2;
extern int rutina;
int execTimes = 0;

void ejecutarRutina(int rutina/*, int execType*/) {
  execTimes++;
  /*mySerial.print("Numero de ejecuciones: ");
  mySerial.println(execTimes);*/
  //paro = 0;
  apagarLeds();
  mySerial.print("Secuencia ");
  mySerial.print(rutina - 48);
  mySerial.println();
  //wtv020sd16p.reset();
  delay(300);
  switch (rutina) {
    case '1':
      wtv020sd16p.asyncPlayVoice(0); // Comentario temporal
      break;
    case '2':
      wtv020sd16p.asyncPlayVoice(1);
      break;
    case '3':
      wtv020sd16p.asyncPlayVoice(2);
      break;
    case '4':
      wtv020sd16p.asyncPlayVoice(3);
      break;
    case '5':
      wtv020sd16p.asyncPlayVoice(4);
      break;
    case '6':
      wtv020sd16p.asyncPlayVoice(5);
      break;
  }
  // Buffer de la secuencia
  if (rutina == '1' || rutina == '4') {
    for (int i = 0; i < 20; i++)
      secuencia[i] = seq1[i];
  } else if (rutina == '2' || rutina == '5') {
    for (int i = 0; i < 20; i++)
      secuencia[i] = seq2[i];
  } else {
    for (int i = 0; i < 20; i++)
      secuencia[i] = seq3[i];
  }
  leerbit();
  execTimes--;
  if(execTimes == 0)
    apagar();
  /*mySerial.println("ejecutarRutina() ha finalizado");
  mySerial.print("execTimes: ");
  mySerial.println(execTimes);  */
}

/* Función para apagar todos los LEDs y el MP3 */
void apagar() {
  if(execTimes == 0)
    mySerial.println("Deteniendo, por favor espere...");
  for (int i = 0; i < 12; i++) {
    shiftReg.digitalWriteMS(1, i, LOW);
  }
  wtv020sd16p.stopVoice(); //Para detener reproducción de MP3 // Comentario temporal
  mySerial.flush();
  rutina = 0;
  ROJO1 = false;
  ROJO = 0;
  VERDE = 0;
  VERDE1 = false;
  AZUL1 = false;
  AZUL = 0;
  
  if(execTimes == 0)
    mySerial.println("Todo listo!");
  mySerial.println("----------------------------");
  mySerial.println();
}
void apagarLeds() {
  for (int i = 0; i < 12; i++) {
    shiftReg.digitalWriteMS(1, i, LOW);
  }
  ROJO1 = false;
  ROJO = 0;
  VERDE = 0;
  VERDE1 = false;
  AZUL1 = false;
  AZUL = 0;
}
// Ejecuta la rutina
void leerbit() {
  int paro = 0;
  for (int i = 0; i < 20; i = i + 2) {
    if (paro)
      break;
    //mySerial.print(secuencia[i]);
    //mySerial.print("/");
    //mySerial.print(secuencia[i + 1]);
    //mySerial.println();
      /*mySerial.print("Repeticion no. ");
      mySerial.println(i);
      mySerial.println();*/
    for (int j = 0; j < 75; j++) {

      n = 0;
      // Se detiene
      if (paro)
        break;
      // Enciende los LEDs correspondientes
      for (int k = 11; k >= 0; k--) {
        // Checa si no se ha detenido
        if (mySerial.available() > 0 || Serial.available() || I2C) {
          if (!I2C)
            leerparo = mySerial.read();
        }
        if (leerparo == 'x') {
          mySerial.println("-----");
          mySerial.println("PARO");
          mySerial.println("-----");
          paro = 1;
          leerparo = 0;
          wtv020sd16p.stopVoice(); // Comentario temporal
          break;
        } else if (leerparo == '*') {
          leerparo = 0;
          paro = 1;
          
          if (rutina_temp < 3){
            apagar();
            rutina_temp++;
          }else{
            rutina_temp = 1;
            break;
          }
          ejecutarRutina(rutina_temp+48);
          break;
        } else if (leerparo == '#') {
          paro = 1;
          leerparo = 0;
          if (rutina_temp2 < 6){
            apagar();
            rutina_temp2++;
          }else{
            rutina_temp2 = 4;
            break;
          }
          ejecutarRutina(rutina_temp2+48);
          break;
        }
        // Enciende los LEDs
        if (bitRead(secuencia[i], k)) {
          shiftReg.digitalWriteMS(1, n, HIGH);
          //mySerial.print("1");
        }
        else {
          shiftReg.digitalWriteMS(1, n, LOW);
          //mySerial.print("0");
        }
        n++;
      }

      if (paro)
        break;
      // Se espera 1 segundo
      //mySerial.println();
      //mySerial.println("Wait for it...");
      delay(200);
      n = 0;

      // Enciende el resto de los LEDs
      for (int m = 11; m >= 0; m--) {
        // Checa si se detuvo
        if (mySerial.available() > 0 || Serial.available() || I2C) {
          if (!I2C)
            leerparo = mySerial.read();
        }
        if (leerparo == 'x') {
          mySerial.println("-----");
          mySerial.println("PARO");
          mySerial.println("-----");
          leerparo = 0;
          paro = 1;
          wtv020sd16p.stopVoice(); // Comentario temporal
          break;
        } else if (leerparo == '*') {
          leerparo = 0;
          paro = 1;
          
          if (rutina_temp < 3){
            apagar();
            rutina_temp++;
          }else{
            rutina_temp = 1;
            break;
          }
          ejecutarRutina(rutina_temp+48);
          break;
        } else if (leerparo == '#') {
          leerparo = 0;
          paro = 1;
          
          if (rutina_temp2 < 6){
            apagar();
            rutina_temp2++;
          }else{
            rutina_temp2 = 4;
            break;
          }
          ejecutarRutina(rutina_temp2+48);
          break;
        }
        // Enciende los LEDs
        if (bitRead(secuencia[i + 1], m)) {
          shiftReg.digitalWriteMS(1, n, HIGH);
          //mySerial.print("1");
        } else {
          shiftReg.digitalWriteMS(1, n, LOW);
          //mySerial.print("0");
        }
        n++;
      }

      /*mySerial.print("paro = ");
      mySerial.println(paro);
      mySerial.println();*/
      if (paro)
        break;

      // Se espera 1 segundo
      //mySerial.println();
      delay(200);
    }
    //mySerial.println();
  }
  //apagar();

}
