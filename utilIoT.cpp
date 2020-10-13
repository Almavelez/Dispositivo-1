#include "utilIoT.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>

ESP8266WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void conectaWiFi(char *ssid, char *pass) {
  Serial.println("Conectando a WiFi...");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, pass);
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println("WiFi connectado.");
  timeClient.begin();
  delay ( 500 );
}

void iniciaTimestamp() {
  timeClient.begin();
}

void getTimestamp(char* ts) {
  timeClient.update();
  unsigned long t = timeClient.getEpochTime();
  sprintf(ts, "%02d-%02d-%02dT%02d:%02d:%02d.00Z", year(t), month(t), day(t),
          hour(t), minute(t), second(t));
}

String urlDeColeccion(char* proyecto, char* coleccion) {
  String url("https://firestore.googleapis.com/v1/projects/");
  url += proyecto;
  url += "/databases/(default)/documents/";
  url += coleccion;
  return url;
}

String urlDeDocumento(char* proyecto, char* coleccion, char* id) {
  return urlDeColeccion(proyecto, coleccion) + "/" + id;
}
