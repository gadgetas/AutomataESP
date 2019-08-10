/******************************************************************************/
/******************* DECLARACIÓN DE LIBRERÍAS DEL AUTOMATA ********************/
/******************************************************************************/
/** Estas son las librerias que se usan, los módulos que la utilizan y las   **/
/** versiones de cada una ordenadas por prioridad y utilización              **/
/******************************************************************************/

/**************************************||**************************************/
// Librería con la funcionalidad principal de manejo del WiFi
//WiFi::https://arduino-esp8266.readthedocs.io/en/2.5.2/esp8266wifi/readme.html
#include <ESP8266WiFi.h>        //2.5.2 - M1WiFiManager

/**************************************||**************************************/
// Codificador JSON :: https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>        //6.11.3 - A1General
/**************************************||**************************************/

/***************************** Sistema de Archivos ****************************/
// Librería nativa SPIFFS para el manejo de archivos de la memoria flash
// *Importante checar sus limitaciones
// https://arduino-esp8266.readthedocs.io/en/2.5.2/filesystem.html
#include "FS.h"                 //2.5.2 - A3Config
/**************************************||**************************************/
