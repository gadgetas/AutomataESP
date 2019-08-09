/******************************************************************************/
/******************* ESTRUCTURA DE PROPIEDADES DEL AUTOMATA *******************/
/******************************************************************************/
struct DatosAutomataESP {
  //******************** Variables de propiedades generales *******************/
  unsigned long tiempoError;    //
  //********************************** A2Log **********************************/
  int verbosidad;               // Nivel de verbosidad
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
  Serial.println("\n");
  Serial.print(F("!Modelo:"));
  Serial.println(modelo);
  Serial.print(F("!Firmware:"));
  Serial.println(firmware);
  Serial.print(F("!Serie:"));
  Serial.println(numSerie);
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
// Envia la información de los datos del autómata
void InfoGeneral() {
  Serie.println(F("------INFO------"));
  Serie.print(F("!EdoActual="));
  Serie.println(Estado);
  A2LogInfo();
  M1WiFiManagerInfo();
  Serie.println(F("------INFO------"));
}
/**************************************||**************************************/
