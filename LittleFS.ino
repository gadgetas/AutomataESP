/******************************************************************************/
/******************** MÓDULO DE SISTEMA DE ARCHIVOS LittleFS ********************/
/******************************************************************************/
void A5ConfSpiffs(){
  log(F("(LittleFS)Configurando"), logInfo);
  // Monta el sistema de archivos
  if (!LittleFS.begin()) {
    log(F("(LittleFS)Error montando el sistema de archivos"), logError);
    ESP.reset();
    return;
  }
  else
    log(F("(LittleFS)Se ha Montado el sistema de archivos flash"), logNoticia);
}

void A5InfoSpiifs() {
  Serie.println(F("------SISTEMA ARCHIVOS------"));
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
    Serie.printf("!FILE:%s, SIZE:%s\n", fileName.c_str(), formatBytes(fileSize).c_str());
  }
}
