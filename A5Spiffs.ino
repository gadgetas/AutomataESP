/******************************************************************************/
/******************** MÓDULO DE SISTEMA DE ARCHIVOS SPIFFS ********************/
/******************************************************************************/
void A5ConfSpiffs(){
  log(F("(SPIFFS)Configurando"), logInfo);
  // Monta el sistema de archivos
  if (!SPIFFS.begin()) {
    log(F("(SPIFFS)Error montando el sistema de archivos"), logError);
    ESP.reset();
    return;
  }
  else
    log(F("(SPIFFS)Se ha Montado el sistema de archivos flash"), logNoticia);
}

void A5InfoSpiifs() {
  Serie.println(F("------SISTEMA ARCHIVOS------"));
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
    Serie.printf("!FILE:%s, SIZE:%s\n", fileName.c_str(), formatBytes(fileSize).c_str());
  }
}
