#include "FabricaDispositivo.hpp"
const int BOTON_FLASH = 0; // Pin que trae cableado el botón flash.
const int LED_INTEGRADO_2 =  2;     // Pin que trae cableado un LED.

void muestraSalida(int valor) {
  digitalWrite(LED_INTEGRADO_2, valor > 0 ? LOW : HIGH);
}
int recuperaEntrada() {
  const int estadoDelBoton = digitalRead(BOTON_FLASH);
  return estadoDelBoton == HIGH ? 10 : 2;
}
void muestraError(String error) {
  Serial.println(error.c_str());
}

FabricaDispositivo fabrica(muestraSalida, recuperaEntrada, muestraError);
void setup() {
  Serial.begin(115200);
  // Initializa el pin para LED_INTEGRADO_2 como salida.
  pinMode(LED_INTEGRADO_2, OUTPUT);
  // Initializa el pin para BOTÓN_FLASH como entrada.
  pinMode(BOTON_FLASH, INPUT);
  fabrica.iniciaWiFi();
  fabrica.ctrlDispositivo.setup();
}

void loop() {
  fabrica.ctrlDispositivo.loop();
}
