#ifndef _UTILIOT_H_
#define _UTILIOT_H_
#include <Arduino.h>

void conectaWiFi(char* ssid, char* pass);
void iniciaTimestamp();
void getTimestamp(char* ts);
String urlDeColeccion(char* proyecto, char* coleccion);
String urlDeDocumento(char* proyecto, char* coleccion, char* id);
#endif
