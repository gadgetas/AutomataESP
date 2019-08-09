/******************************************************************************/
/******************* MODULO DE CONFIGURACIÓN Y PREFERENCIAS *******************/
/******************************************************************************/
/** Este módulo permite almacenar en la memoria flash un archivo en formato  **/
/** JSON con los valores para las configuraciones y preferencias del programa**/
/******************************************************************************/

/******************************************************************************/
/************ CONFIGURACIÓN REQUERIDA PARA EL HARDWARE Y VARIABLES ************/
/******************************************************************************/
void A3Config() {
  log(F("(Config)Configurando"), logInfo);
  if (!SPIFFS.begin()) {
    log(F("(Config)Fallo en montar la unidad"), logError);
    return;
  }
  if (!LeerConfig())
    log(F("(Config)No cargo configuracion"), logError);
}

/******************************************************************************/
bool LeerConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    log(F("(Config)Archivo no encontrado"), logError);
    return false;
  }
  //Obtiene el tamaño del archivo
  size_t size = configFile.size();
  if (size > 1024) {
    log(F("(Config)Archivo muy grande"), logError);
    configFile.close();
    return false;
  }

  StaticJsonDocument<1024> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, configFile);
  if (error) {
    configFile.close();
    log(F("(Config)Fallo interpretacion archivo"), logError);
    return false;
  }

  // Copiar valores del JsonDocument a la estructura de datos
  SetVerbosidad(doc["verbosidad"]);
  Datos.tiempoError = doc["tiempoError"];
  /*Como copiar un string
    strlcpy(Datos.hostname,                  // <- destination
          doc["hostname"] | "example.com",  // <- source
          sizeof(Datos.hostname));         // <- destination's capacity
  */
  // Cierra el archivo de configuración
  configFile.close();
  return true;
}
