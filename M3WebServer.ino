/******************************************************************************/
/*************************** MÓDULO DE SERVIDOR WEB ***************************/
/******************************************************************************/
/** Este módulo creamos un servidor web usando la biblioteca ESP8266WebServer**/
/** como desventaja solo atiende un cliente a la vez, así como peticiones GET**/
/** y POST. Por defecto se levanta en el puerto 80.                          **/
/**                                                                          **/
/** La raíz de los archivos públicos web, se deben almacenar en la memoria   **/
/** FLASH dentro de la carpeta public.                                       **/
/******************************************************************************/

/******************************************************************************/
/******************** TERMINALES USADAS POR EL MÓDULO WIFI ********************/
/******************************************************************************/
// No se usan terminales

/******************************************************************************/
/************** VARIABLES GLOBALES PARA LA CONEXIÓN POR DEFECTO ***************/
/******************************************************************************/
ESP8266WebServer webServer(80);

/******************************************************************************/
/*************** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **************/
/******************************************************************************/
void M3ConfWebServer() {
  // Configuramos los datos de nuestra red WiFi
  log(F("(WebServer)Configurando"), logInfo);

  // Configurar rutas y métodos
  webServer.on("/", M3handleRoot);

  webServer.on("/inline", []() {
    webServer.send(200, "text/plain", "this works as well");
  });

  webServer.onNotFound(M3handleNotFound);
}

bool M3StartWebServer(){  
  log(F("(WebServer)Iniciando..."), logInfo);
  // Debe ser ejecutada despues de que haya conectado a una red.
  if (WiFi.status() != WL_CONNECTED) {
    log(F("(WebServer)Debe estar conectado a una red WiFi"), logError);
    return false;
  }
  // Se inicia el servicio
  webServer.begin();
}

// Se dispara cuando no existe la ruta del recurso pedido
void M3handleNotFound() {
  log(F("(WebServer)Recurso no encontrado"), webServer.uri(), logError );
  String message = "File Not Found\n\nURI: ";
  message += webServer.uri();
  message += "\nMethod: ";
  message += (webServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";
  for (uint8_t i = 0; i < webServer.args(); i++) {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", message);
}

void M3handleRoot() {
  webServer.send(200, "text/plain", "hello from esp8266!");
}
