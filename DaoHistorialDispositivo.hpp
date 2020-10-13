#ifndef _DAO_HISTORIAL_DISPOSITIVO_H_
#define _DAO_HISTORIAL_DISPOSITIVO_H_

#include <Arduino.h>

class DaoHistorialDispositivo {
  private:
    const char * const _idDisp;
    const char * const _huellaDigital;
    const String _url;
  public:
    DaoHistorialDispositivo(const char * idDisp, const char * huellaDigital,
                            const String url);
    String agrega(int valor);
};
#endif
