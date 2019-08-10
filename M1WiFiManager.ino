/******************************************************************************/
/******************* DECLARACIÓN DE LIBRERÍAS DEL AUTOMATA ********************/
/******************************************************************************/
/* Funcionalidad para la conexión del WiFi a través del módulo
/* embebido en el ESP2866
/******************************************************************************/


/******************************************************************************/
/***************** TERMINALES USADAS PARA CONECTAR EL MÓDULO ******************/
/******************************************************************************/
// No se usan terminales

/******************************************************************************/
/************** VARIABLES GLOBALES PARA LA CONEXIÓN POR DEFECTO ***************/
/******************************************************************************/
const char* ssid     = "Simple3";  // El nombre del red SSID
const char* password = "#password2000#";     // Clave de la red WiFi

/******************************************************************************/
/*************** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **************/
/******************************************************************************/
void M1ConfWiFiManager() {
  // Configuramos los datos de nuestra red WiFi
  log(F("(WiFi)Configurando"), logInfo);
  WiFi.mode(WIFI_STA);
  // Led indicador de conexión
  pinMode(LED_BUILTIN, OUTPUT);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void M1WiFiManagerInfo() {
  Serie.println(F("------WIFI INFO------"));  
  Serie.print(F("!IP="));
  Serie.println(WiFi.localIP());
  Serie.print(F("!SubNetMask="));
  Serie.println(WiFi.subnetMask());  
  Serie.printf("!StatusWiFi: %d\n", WiFi.status());
  if (Datos.verbosidad >= logDebug) {
    // Imprime información de debug
    WiFi.printDiag(SerialLog);
  }
}
