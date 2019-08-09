/******************************************************************************/
/******************* ESTRUCTURA DE PROPIEDADES DEL AUTOMATA *******************/
/******************************************************************************/
struct DatosAutomataESP {
  /********************************** A2Log **********************************/
  int verbosidad;               // Nivel de verbosidad
  /************************* Descripción de variable *************************/
  // Espacio para definir variables
  unsigned long tiempoError;    //
};

/*****************************************************************************/
/************** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **************/
/*****************************************************************************/
DatosAutomataESP Datos;     //Variable almacenamiento globlal de propiedades
unsigned long tiempoAnt;    //(ms)Tiempo anterior para medición de periodos
unsigned long tErrorAnt;    //(ms)Tiempo anterior para medir periodo de error
unsigned long tSegAnt;      //(ms)Tiempo anterior para contar segundos
int segundos;               // Variable auxiliar para contar segundos

/*****************************************************************************/
/*****************************************************************************/
/*************************************||**************************************/
void A1ConfGeneral() {
  // Reiniciando variables
  tiempoAnt = millis();
  tSegAnt = millis();
  randomSeed(millis());
  Datos.tiempoError = 35000;
  Datos.verbosidad = 7;
}

// Envia información del automáta
void A1Informacion() {
  Serial.print(F("!Modelo:"));
  Serial.println(modelo);
  Serial.print(F("!Firmware:"));
  Serial.println(firmware);
  Serial.print(F("!Serie:"));
  Serial.println(numSerie);
}

// Envia la información de los datos del autómata
void InfoGeneral() {
  Serie.println(F("------INFO------"));
  Serie.print(F("!EdoActual="));
  Serie.println(Estado);
  InfoWiFi();
  Serie.println(F("------INFO------"));
}
