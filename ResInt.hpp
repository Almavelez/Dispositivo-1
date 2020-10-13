#ifndef _INFO_VALOR_H_
#define _INFO_VALOR_H_

#include <Arduino.h>

class ResInt {
  public:
    const int valor;
    const String error;
    ResInt(int _valor, String _error );
    ResInt(const ResInt& ref );
    const char* valida();
};
#endif
