#include <stdint.h>
#include "LedControl.h"

LedControl lc = LedControl(10, 8, 9, 2);  // crea objeto

typedef struct Motores {  //Definimos de la estructura para guardar los datos de los sensores
  uint32_t fila_0;
  uint32_t fila_1;
  uint32_t fila_2;
  uint32_t fila_3;
  uint32_t fila_4;
  uint32_t fila_5;
  uint32_t fila_6;
  uint32_t fila_7;
} Motores;

union UDato {  //Definimos una union para poder mandar los datos byte a byte
  Motores datos;
  byte a[sizeof(Motores)];
} Datos;


void Enviar_Struct() {

  for (unsigned long long k = 0; k < sizeof(Motores); k++) {  //Pasamos los datos byte a byte
    Serial.write(Datos.a[k]);
  }
}
void Recibir_Struct() {
  Serial.readBytes(Datos.a, sizeof(Motores));
}



void setup() {
  lc.shutdown(0, false);  // enciende la matriz
  lc.setIntensity(0, 7);  // establece brillo
  lc.clearDisplay(0);     // blanquea matriz
  Serial.begin(9600);
  //Serial.println(sizeof(Motores));
}
uint8_t Identificador[1];  //Variable que se usa para identificar el tipo de movimiento en Y o X

void loop() {

  if (Serial.available()) {

    Serial.readBytes(Identificador, 1);
    if (Identificador[0] == 'a') {
      Recibir_Struct();
    }
  }

  lc.setRow(0, 0, Datos.datos.fila_0);
  lc.setRow(0, 1, Datos.datos.fila_1);
  lc.setRow(0, 2, Datos.datos.fila_2);
  lc.setRow(0, 3, Datos.datos.fila_3);
  lc.setRow(0, 4, Datos.datos.fila_4);
  lc.setRow(0, 5, Datos.datos.fila_5);
  lc.setRow(0, 6, Datos.datos.fila_6);
  lc.setRow(0, 7, Datos.datos.fila_7);
}
