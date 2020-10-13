#ifndef _DAO_SALIDA_DISPOSITIVO_H_
#define _DAO_SALIDA_DISPOSITIVO_H_
#include "ResInt.hpp"

#include <Arduino.h>

class DaoSalidaDispositivo {
  private:
    const char * const _huellaDigital;
    const String _url;
  public:
    DaoSalidaDispositivo(const char * huellaDigital, const String url);
    ResInt busca();
};
#endif
