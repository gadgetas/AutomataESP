/******************************************************************************/
/******************* MODULO DE CONFIGURACIÓN Y PREFERENCIAS *******************/
/******************************************************************************/
/** Este módulo permite almacenar en la memoria flash un archivo en formato  **/
/** JSON con los valores para las configuraciones y preferencias del programa**/
/******************************************************************************/
const String archivoJSON = "/config.json"; //Archivo para guardar configuracion
const int capacidadDoc = 1024;

/******************************************************************************/
/************ CONFIGURACIÓN REQUERIDA PARA EL HARDWARE Y VARIABLES ************/
/******************************************************************************/
void A3Config() {
  log(F("(Config)Configurando"), logInfo);
  if (!LeerConfig())
    log(F("(Config)No cargo configuracion"), logError);
}

/******************************************************************************/
bool LeerConfig() {
  File configFile = SPIFFS.open(archivoJSON, "r");
  if (!configFile) {
    log(F("(Config)Archivo no encontrado"), logError);
    return false;
  }
  //Obtiene el tamaño del archivo
  size_t size = configFile.size();
  if (size > capacidadDoc) {
    log(F("(Config)Archivo muy grande"), logError);
    configFile.close();
    return false;
  }

  StaticJsonDocument<capacidadDoc> doc;

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
  // Obteniendo el dominio
  /*Como copiar un string*/
  strlcpy(Datos.dominio,                  // <- destination
          doc["dominio"] | Datos.dominio,  // <- source
          sizeof(Datos.dominio));         // <- destination's capacity
  // Cierra el archivo de configuración
  configFile.close();
  return true;
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void guardarConfig() {
  // Borramos el archivo, de otra forma solo se concatenan los datos
  if (SPIFFS.exists(archivoJSON))
    SPIFFS.remove(archivoJSON);

  File configFile = SPIFFS.open(archivoJSON, "w");
  if (!configFile) {
    log(F("(Config)Fallo abrir archivo escritura"), logError);
    return;
  }
  // Creamos el objeto JSON
  StaticJsonDocument<capacidadDoc> doc;

  // Establecemos los valores a guardar, deben ser los mismos que leemos
  // Actualizar la capacidad de la instancia, para más valores
  // 39 bytes al momento
  doc["verbosidad"] = Datos.verbosidad;
  doc["tiempoError"] = Datos.tiempoError;
  doc["dominio"] = Datos.dominio;

  // Serializamos JSON al Archivo
  if (serializeJson(doc, configFile) == 0) {
    log(F("(Config)Fallo escribir archivo JSON"), logError);
  }
  else
    log(F("(Config)JSON guardado"), logNoticia);

  // Cerramos el archivo
  configFile.close();
}
