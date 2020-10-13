#include "CtrlDispositivo.hpp"
#include "DaoEntradaDispositivo.hpp"
#include "DaoHistorialDispositivo.hpp"
#include "DaoSalidaDispositivo.hpp"
#include <Arduino.h>
#include "ResInt.hpp"
#include "utilIoT.hpp"

CtrlDispositivo::CtrlDispositivo(const char* const idDisp,
                                 void (*const muestraSalida)(int), int (*const recuperaEntrada)(),
                                 void (*const muestraError)(String),
                                 DaoHistorialDispositivo daoHistorial, DaoEntradaDispositivo daoEntrada,
                                 DaoSalidaDispositivo daoSalida)
  : _idDisp(idDisp),
    _muestraSalida(muestraSalida),
    _recuperaEntrada(recuperaEntrada),
    _muestraError(muestraError),
    _daoHistorial(daoHistorial),
    _daoEntrada(daoEntrada),
    _daoSalida(daoSalida)  { }
void CtrlDispositivo::setup() {
  _entrada = 0;
  _muestraLaSalidaDelServidor();
  _enviaLaEntrada(true);
}
void CtrlDispositivo::loop() {
  _muestraLaSalidaDelServidor();
  _enviaLaEntrada(false);
}
void CtrlDispositivo::_muestraLaSalidaDelServidor() {
  const ResInt infoValor = _daoSalida.busca();
  if (infoValor.error.length() > 0) {
    (*_muestraError)(infoValor.error);
  } else {
    (*_muestraSalida)(infoValor.valor);
  }
}
void CtrlDispositivo::_enviaLaEntrada(bool forzosa) {
  const int nuevaEntrada = (*_recuperaEntrada)();
  if (forzosa || _entrada != nuevaEntrada) {
    String error = _daoEntrada.modifica(nuevaEntrada);
    if (error.length() > 0) {
      (*_muestraError)(error);
      return;
    }
    error = _daoHistorial.agrega(nuevaEntrada);
    if (error.length() > 0) {
      (*_muestraError)(error);
      return;
    }
    _entrada = nuevaEntrada;
  }
}
