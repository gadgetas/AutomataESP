/******************************************************************************/
/******************* ESTRUCTURA DE PROPIEDADES DEL AUTOMATA *******************/
/******************************************************************************/
struct DatosAutomataESP {
  //******************** Variables de propiedades generales *******************/
  unsigned long tiempoError;  //  
  char IpServerTo[64];        // IP del servidor al que se conecta
  char DomainServerTo[64];    // Nombre de dominio del servidor que se conecta
  //********************************** A2Log **********************************/
  int verbosidad;             // Nivel de verbosidad  
  //********************************* M2mDNS **********************************/
  char dominio[64];           // Nombre del host, el dominio superior es local
};

/******************************************************************************/
/*************************** VARIABLES DE USO GLOBAL **************************/
/******************************************************************************/
DatosAutomataESP Datos;     //Variable almacenamiento globlal de propiedades
unsigned long tiempoAnt;    //(ms)Tiempo anterior para medición de periodos
unsigned long tErrorAnt;    //(ms)Tiempo anterior para medir periodo de error
unsigned long tSegAnt;      //(ms)Tiempo anterior para contar segundos
int segundos;               // Variable auxiliar para contar segundos

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void A1ConfGeneral() {
  // Valores por defecto de las propiedades generales  
  Datos.tiempoError = 35000;
  tiempoAnt = millis();
  tSegAnt = millis();
  tErrorAnt=millis();
  randomSeed(millis());
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void A1Informacion() {  
  //TODO: Esperar un tiempo antes de enviar mensajes
  Serial.println("");
  Serial.print(F("!Model:"));
  Serial.println(modelo);
  Serial.print(F("!Firmware:"));
  Serial.println(firmware);
  Serial.print(F("!Serie:"));
  Serial.println(numSerie);
  Serial.print(F("!ChipId:"));
  Serial.println(ESP.getChipId());
  Serial.print(F("!CoreVersion:"));
  Serial.println(ESP.getCoreVersion());
  Serial.print(F("!CpuFreqMHz:"));
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print(F("!SketchSize:"));
  Serial.println(ESP.getSketchSize());
  Serial.print(F("!HeapFree:"));
  Serial.println(ESP.getFreeHeap());
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
// Envia la información de los datos del autómata
void InfoGeneral() {
  Serie.println(F("------INFO------"));
  A1Informacion();
  Serie.print(F("!EdoActual="));
  Serie.println(Estado);
  A2LogInfo();
  M1WiFiManagerInfo();
  M2mDNSInfo();
  Serie.println(F("------INFO------"));
}
/**************************************||**************************************/
