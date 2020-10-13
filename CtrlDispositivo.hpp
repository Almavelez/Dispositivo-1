#ifndef _CTRL_DISPOSITIVO_H_
#define _CTRL_DISPOSITIVO_H_
#include "DaoEntradaDispositivo.hpp"
#include "DaoHistorialDispositivo.hpp"
#include "DaoSalidaDispositivo.hpp"

class CtrlDispositivo {
  private:
    int _entrada;
    const char* _idDisp;
    void (*_muestraSalida)(int);
    int (*_recuperaEntrada)();
    void (*_muestraError)(String);
    DaoHistorialDispositivo _daoHistorial;
    DaoEntradaDispositivo _daoEntrada;
    DaoSalidaDispositivo _daoSalida;
    void _muestraLaSalidaDelServidor();
    void _enviaLaEntrada(bool forzosa);
  public:
    CtrlDispositivo(const char* const idDisp, void (*const muestraSalida)(int),
                    int (*const recuperaEntrada)(), void (*const muestraError)(String),
                    DaoHistorialDispositivo daoHistorial, DaoEntradaDispositivo daoEntrada,
                    DaoSalidaDispositivo daoSalida);
    void setup();
    void loop();
};

#endif
