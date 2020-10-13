#ifndef _DAO_ENTRADA_DISPOSITIVO_H_
#define _DAO_ENTRADA_DISPOSITIVO_H_

#include <Arduino.h>

class DaoEntradaDispositivo {
  private:
    const char * const _huellaDigital;
    const String _url;
  public:
    DaoEntradaDispositivo(const char * huellaDigital, const String url);
    String modifica(int valor);
};
#endif
