#include "DaoEntradaDispositivo.hpp"
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>
#include "util.hpp"
#include <ArduinoJson.h>
#include <Arduino.h>

DaoEntradaDispositivo::DaoEntradaDispositivo(const char* huellaDigital,
    const String url): _huellaDigital(huellaDigital), _url(url) { }

String DaoEntradaDispositivo::modifica(int valor) {
  String error;
  const size_t capacity = 3 * JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);

  JsonObject fields = doc.createNestedObject("fields");
  JsonObject fields_VALOR = fields.createNestedObject("VALOR");
  fields_VALOR["integerValue"] = valor;

  String json;
  serializeJson(doc, json);

  std::unique_ptr<BearSSL::WiFiClientSecure> client(
    new BearSSL::WiFiClientSecure);
  client->setFingerprint(_huellaDigital);

  HTTPClient https;
  Serial.println("Conectando al servidor...");
  if (https.begin(*client, _url)) {
    https.addHeader(CONTENT_TYPE, APPLICATION_JSON);
    Serial.print("Inicia PATCH...\n");
    int codigoHttps = https.PATCH(json);
    if (codigoHttps > 0) {
      String texto = https.getString();
      Serial.printf("PATCH OK. codigoHttps: %d\n", codigoHttps);
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
