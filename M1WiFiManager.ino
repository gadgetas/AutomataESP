/******************************************************************************/
/***************** MÓDULO DE CONEXIÓN WIFI USANDO WIFIMANAGER *****************/
/******************************************************************************/
/** Funcionamiento:                                                          **/
/** 1)Cuando el ESP inicializa se configura en modo estación y trata de      **/
/**   conectarse a un Access Point previamente configurado.                  **/
/** 2)Si no lo logra o no se ha guardado una red anterior el ESP se convierte**/
/**   en un Access Point, activa un Servidor DNS y uno Web con IP 192.168.4.1**/
/** 3)Por lo que podemos conectarnos a la red WiFi del ESP. Esta red tiene un**/
/**   un portal captivo, ya sea que Muestre "Unirse a la Red" en un telefono **/
/**   o nos redireccione al portal de configuración cuando usamos un navegador*/
/**   web una PC.                                                            **/
/** 4)En el portal web de configuración elegimos la red WiFi a conectarnos y **/
/**   su password, salvamos la configuración y el ESP tratará de conectarse. **/
/** 5)Si tiene exito en conectarse, continua la ejecución de nuestro programa**/
/** 6)Si no tiene exito, podemos volver a configurar                         **/
/******************************************************************************/
const String passwordAP = "12345678"; //Contraseña de ESP en modo Access Point(AP)

/******************************************************************************/
/******************** TERMINALES USADAS POR EL MÓDULO WIFI ********************/
/******************************************************************************/
// No se usan terminales

/******************************************************************************/
/************** VARIABLES GLOBALES PARA LA CONEXIÓN POR DEFECTO ***************/
/******************************************************************************/
WiFiManager wm;

/******************************************************************************/
/*************** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **************/
/******************************************************************************/
void M1ConfWiFiManager() {
  // Configuramos los datos de nuestra red WiFi
  log(F("(WiFiManager)Configurando"), logInfo);
  // Led indicador de conexión
  pinMode(LED_BUILTIN, OUTPUT);

  // Establece si muestra los mensajes de debug
  M1ModoDebug();
  // Ejecuta esta funcion cuando falló la conexión y levanta el Access Point
  wm.setAPCallback(M1ModoConfiguracion);
  // Ejecuta esta función cuando se ha configurado y conectado a una red WiFi
  wm.setSaveConfigCallback(M1ConfiguracionExitosa);
  // Si no hay nadie conectado y pasan 3 min se sale del portal de configuración
  wm.setConfigPortalTimeout(180);

  // wifi scan settings
  // wm.setRemoveDuplicateAPs(false); // do not remove duplicate ap names (true)
  // wm.setMinimumSignalQuality(20);  // set min RSSI (percentage) to show in scans, null = 8%
  // wm.setShowInfoErase(false);      // do not show erase button on info page
  // wm.setScanDispPerc(true);       // show RSSI as percentage not graph icons

  // wm.setBreakAfterConfig(true);   // always exit configportal even if wifi save fails
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M1WiFiManagerInfo() {
  Serie.println(F("------WIFIMANAGER INFO------"));
  Serie.print(F("!IP="));
  Serie.println(WiFi.localIP());
  Serie.print(F("!SubNetMask="));
  Serie.println(WiFi.subnetMask());
  Serie.print(F("!MAC="));
  Serie.println(WiFi.macAddress());
  Serie.printf("!StatusWiFi: %d\n", WiFi.status());
  if (Datos.verbosidad >= logDebug) {
    // Imprime información de debug
    WiFi.printDiag(SerialLog);
  }
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M1ResetWiFiManager() {
  log(F("(WiFiManager)Restableciendo configuracion WiFi"), logAdvertencia);
  wm.resetSettings();
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M1ConfiguracionExitosa() {
  log(F("(WiFiManager)Configuracion exitosa"), logNoticia );
  Serie.println(WiFi.psk());
  Serie.println(WiFi.SSID());
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M1ModoConfiguracion(WiFiManager *myWiFiManager) {
  log(F("(WiFiManager)Modo de configuracion"), logNoticia);
  Serie.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

/******************************************************************************/
/********************* ESTABLECE EL MODO DEBUG DEL MÓDULO *********************/
/******************************************************************************/
void M1ModoDebug() {
  //Switchea entre los mensajes debug y el que tiene establecido
  if (Datos.verbosidad == logDebug)
    wm.setDebugOutput(true);
  else
    wm.setDebugOutput(false);
}
