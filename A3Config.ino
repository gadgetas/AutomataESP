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


}

bool CargarConfiguracion() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    log(F("EdoNoDeclarado"), logError);
    return false;
  }

  size_t size = configFile.size();

  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }
  StaticJsonDocument<1024> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, configFile);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  Datos.verbosidad = doc["verbosidad"] | 7;/*
  strlcpy(Datos.hostname,                  // <- destination
          doc["hostname"] | "example.com",  // <- source
          sizeof(Datos.hostname));         // <- destination's capacity
*/
  // Close the file (Curiously, File's destructor doesn't close the file)
  configFile.close();
  /*
  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  const char* serverName = json["serverName"];
  const char* accessToken = json["accessToken"];

  // Real world application would store these values in some variables for
  // later use.

  Serial.print("Loaded serverName: ");
  Serial.println(serverName);
  Serial.print("Loaded accessToken: ");
  Serial.println(accessToken);
  return true;*/
}
