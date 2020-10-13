#ifndef _FABRICA_H_
#define _FABRICA_H_
#include "CtrlDispositivo.hpp"
class FabricaDispositivo {
  public:
    CtrlDispositivo ctrlDispositivo;
    FabricaDispositivo(void (*const muestraSalida)(int),
                       int (*const recuperaEntrada)(), void (*const muestraError)(String));
    void iniciaWiFi();
};
#endif
