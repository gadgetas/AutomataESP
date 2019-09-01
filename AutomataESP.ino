/******************************************************************************/
/**************************** NOMBRE DEL PROYECTO *****************************/
/******************************************************************************/
/** Aquí redacta la descripción del programa, esta debe ser concisa, un      **/
/** resumen general que explique el alcance y finalidad del programa         **/
/**   Placa Hardware:      ESP8266 Generico || Para que hardware se programa **/
/**   Versión IDE Arduino: 1.8.9            || Versión con que se desarrolla **/
/******************************************************************************/
/** Version 0.1.190729 || Esta es la versión actual, se usa la semántica para
/**                       los dos primero números y en el último la fecha AAMMDD
/**
/** Última revisión:   || Ultima revisión o actualización, solo la última
/** 19/03/06 Augusto - Agregan leds de monitoreo
/******************************************************************************/
const String modelo = "GLBOX";
const String firmware = "0.1.100729";
const String numSerie = "000001";

/******************************************************************************/
/******************* DECLARACIÓN DE LIBRERÍAS DEL AUTOMATA ********************/
/******************************************************************************/
/** Estas son las librerias que se usan, los módulos que la utilizan y las   **/
/** versiones de cada una ordenadas por prioridad y utilización              **/
/**************************************||**************************************/
// Librería con la funcionalidad principal de manejo del WiFi
//WiFi::https://arduino-esp8266.readthedocs.io/en/2.5.2/esp8266wifi/readme.html
#include <ESP8266WiFi.h>        //2.5.2 - M1WiFiManager
#include <WiFiManager.h>        //0.14.0- M1WiFiManager
/**************************************||**************************************/
// Codificador JSON :: https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>        //6.11.3 - A1General
/***************************** Sistema de Archivos ****************************/
// Librería nativa SPIFFS para el manejo de archivos de la memoria flash
// *Importante checar sus limitaciones
// https://arduino-esp8266.readthedocs.io/en/2.5.2/filesystem.html
#include "FS.h"                 //2.5.2 - A3Config
/**************************************||**************************************/
// Librería nativa que permite asignar un dominio local al ESP sin necesidad de 
// servidor DNS, usa el protocolo mDNS. Responde a consultas de descubrimiento
// de servicios.
#include <ESP8266mDNS.h>        //2.5.2 - A5mDNS-SD
/**************************************||**************************************/
// Librería nativa para crear un servidor web de manera sencilla
// https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <ESP8266WebServer.h>
/**************************************||**************************************/

// Definimos puerto serial para Comunicación
#define Serie Serial
#define Serial_bps 115200

// Definimos puerto serial para LOG
#define SerialLog Serial
#define SerialLog_bps 115200

/******************************************************************************/
/*************************** DECLARACIÓN DE ESTADOS ***************************/
/******************************************************************************/
const int estadoPrueba = -2;      // Estado usado para pruebas
const int estadoError = -1;       // Estado principal de manejo de errores
const int estadoSinEstado = 0;    // Usado para error en declaración de estado
const int estadoConfiguracion = 1;// Estado de configuración inicial
const int estadoConexionWiFi = 2; // Estado de conexión a un AP
const int estadoConfigMDns = 3;   // Configuracion resolucion de nombres local
const int estadoEspera = 4;       // Estado de espera
int Estado; // Variable global que contiene el estado actual

/******************************************************************************/
/*************************** INICIALIZACIÓN GENERAL ***************************/
/******************************************************************************/
void setup() {
  Serie.begin(Serial_bps);  
  /****SI ES DIFERENTE EL PUERTO DEL LOG***/
  /* Serial_bps.begin(SerialLog_bps);*/
  A1Informacion();
  CambiarEstado(estadoConfiguracion);
}

/******************************************************************************/
/*************** ESTRUCTURA PRINCIPAL DE LA MÁQUINA DE ESTADOS ****************/
/******************************************************************************/
void loop() {
  LeerIndicaciones();
  // Si ya se activo el servicio
  if (Estado>estadoConfigMDns)
    MDNS.update();
  switch (Estado) {
    case estadoPrueba:
      EstadoPrueba();
      break;
    case estadoError:
      EstadoError();
      break;
    case estadoConfiguracion:
      EstadoConfiguracion();
      break;
    case estadoConexionWiFi:
      EstadoConexionWiFi();
      break;
    case estadoConfigMDns:
      EstadoConfigMDns();
      break;
    case estadoEspera:
      EstadoEspera();
      break;
    default:
      CambiarEstado(estadoSinEstado);
      break;
  }
}
/**************************************||**************************************/
