#include "DaoSalidaDispositivo.hpp"
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>
#include "ResInt.hpp"
#include "util.hpp"
#include <ArduinoJson.h>
#include <Arduino.h>

DaoSalidaDispositivo::DaoSalidaDispositivo(const char* huellaDigital,
    const String url): _huellaDigital(huellaDigital), _url(url) { }

ResInt DaoSalidaDispositivo::busca() {
  String error;
  int valor = 0;

  std::unique_ptr<BearSSL::WiFiClientSecure> client(
    new BearSSL::WiFiClientSecure);
  client->setFingerprint(_huellaDigital);

  HTTPClient https;
  Serial.println("Conectando al servidor...");
  if (https.begin(*client, _url)) {
    Serial.println("Inicia GET...");
    int codigoHttps = https.GET();
    if (codigoHttps > 0) {
      String texto = https.getString();
      Serial.printf("Get OK. codigoHttps: %d\n", codigoHttps);
      if (codigoHttps == HTTP_CODE_NOT_FOUND) {
        error = NO_ENCONTRADO;
      } else if (codigoHttps == HTTP_CODE_OK
                 || codigoHttps == HTTP_CODE_MOVED_PERMANENTLY) {
        // Este valor debe obtenerse con ArduinoJson Assistant
        const size_t capacity =
          2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 200;
        // Crea la estructura de dator para procesar JSON.
        DynamicJsonDocument doc(capacity);
        // A partir del texto devuelto por Internet, se obtiene el árbol JSON.
        deserializeJson(doc, texto);
        valor = doc["fields"]["VALOR"]["integerValue"].as<int>();
      } else {
        error = texto;
      }
    } else {
      error = https.errorToString(codigoHttps);
    }
    https.end();
  } else {
    error = "La conexión falló";
  }
  Serial.printf("valor: %d\n", valor);
  return ResInt(valor, error);
}
