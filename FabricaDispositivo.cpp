#include "FabricaDispositivo.hpp"
#include "CtrlDispositivo.hpp"
#include "DaoSalidaDispositivo.hpp"
#include "DaoEntradaDispositivo.hpp"
#include "DaoHistorialDispositivo.hpp"
#include "utilIoT.hpp"
#define SSID "*****"
#define PASS  "**********"
#define HUELLA_DIGITAL "***********************"
#define ID_DISP "iot2"
#define ID_PROYECTO "*********"
const String URL_ENTRADA(urlDeDocumento(ID_PROYECTO, "ENTRADA", ID_DISP));
const String URL_SALIDA(urlDeDocumento(ID_PROYECTO, "SALIDA", ID_DISP));
const String URL_HISTORIAL(urlDeColeccion(ID_PROYECTO, "HISTORIAL"));

FabricaDispositivo::FabricaDispositivo(void (*const muestraSalida)(int),
                                       int (*const recuperaEntrada)(),
                                       void (*const muestraError)(String)):
  ctrlDispositivo(ID_DISP, muestraSalida, recuperaEntrada, muestraError,
                  DaoHistorialDispositivo(ID_DISP, HUELLA_DIGITAL, URL_HISTORIAL),
                  DaoEntradaDispositivo(HUELLA_DIGITAL, URL_ENTRADA),
                  DaoSalidaDispositivo(HUELLA_DIGITAL, URL_SALIDA)) {}

void FabricaDispositivo::iniciaWiFi() {
  conectaWiFi(SSID, PASS);
}
