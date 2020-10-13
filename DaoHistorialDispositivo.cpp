#include "DaoHistorialDispositivo.hpp"
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>
#include "util.hpp"
#include "utilIoT.hpp"
#include <ArduinoJson.h>
#include <Arduino.h>

DaoHistorialDispositivo::DaoHistorialDispositivo(const char * idDisp,
    const char * huellaDigital, const String url):
  _idDisp(idDisp), _huellaDigital(huellaDigital), _url(url) {
  iniciaTimestamp();
}

String DaoHistorialDispositivo::agrega(int valor) {
  String error;

  char ts[30];
  getTimestamp(ts);
  Serial.println(ts);

  /* Al cálculo del tamaño le añadimos 30, que es el tamaño del buffer para
      el timestap. */
  const size_t capacity = 4 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + 30;
  DynamicJsonDocument doc(capacity);

  JsonObject fields = doc.createNestedObject("fields");
  JsonObject fields_DISP_ID = fields.createNestedObject("DISP_ID");
  fields_DISP_ID["stringValue"] = _idDisp;
  JsonObject fields_VALOR = fields.createNestedObject("VALOR");
  fields_VALOR["integerValue"] = valor;
  JsonObject fields_HIST_TS = fields.createNestedObject("HIST_TS");
  fields_HIST_TS["timestampValue"] = ts;

  String json;
  serializeJson(doc, json);

  std::unique_ptr<BearSSL::WiFiClientSecure> client(
    new BearSSL::WiFiClientSecure);
  client->setFingerprint(_huellaDigital);

  HTTPClient https;
  Serial.println("Conectando al servidor...");
  if (https.begin(*client, _url)) {
  https.addHeader(CONTENT_TYPE, APPLICATION_JSON);
    Serial.print("Inicia POST...\n");
    int codigoHttps = https.POST(json);
    if (codigoHttps > 0) {
      String texto = https.getString();
      Serial.printf("POST OK. codigoHttps: %d\n", codigoHttps);
      Serial.println(texto);
      if (codigoHttps != HTTP_CODE_OK
          && codigoHttps != HTTP_CODE_MOVED_PERMANENTLY) {
        error = texto;
      }
    } else {
      error = https.errorToString(codigoHttps);
    }
    https.end();
  } else {
    error = "La conexión falló";
  }
  return error;
}
